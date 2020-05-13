// Power request handler for sample WDM function driver
// Writtem by Walter Oney
// @doc

#include "driver.h"

NTSTATUS DefaultPowerHandler(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
NTSTATUS HandleSetPower(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
NTSTATUS OnFinishPowerUp(IN PDEVICE_OBJECT fdo, IN PIRP Irp, IN PVOID junk);
									  
///////////////////////////////////////////////////////////////////////////////
// @func Handle IRP_MJ_POWER request
// @parm Functional device object
// @parm I/O request to handle
// @rdesc Standard status code
// @comm This routine uses the IRP's minor function code to dispatch a handler
// function (such as HandleSetPower for IRP_MN_SET_POWER). It calls DefaultPowerHandler
// for any function we don't specifically need to handle.

NTSTATUS RequestPower(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// RequestPower
	if (!LockDevice(fdo))
		return CompleteRequest(Irp, STATUS_DELETE_PENDING, 0);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ASSERT(stack->MajorFunction == IRP_MJ_POWER);

	static NTSTATUS (*fcntab[])(IN PDEVICE_OBJECT fdo, IN PIRP Irp) = {
		DefaultPowerHandler,		// IRP_MN_WAIT_WAKE
		DefaultPowerHandler,		// IRP_MN_POWER_SEQUENCE
		HandleSetPower,				// IRP_MN_SET_POWER
		DefaultPowerHandler,		// IRP_MN_QUERY_POWER
		};
	
	ULONG fcn = stack->MinorFunction;
	NTSTATUS status;
	if (fcn >= arraysize(fcntab))
		{							// unknown function
		status = DefaultPowerHandler(fdo, Irp); // some function we don't know about
		UnlockDevice(fdo);
		return status;
		}							// unknown function

#if DBG
	static char* fcnname[] = {
		"IRP_MN_WAIT_WAKE",
		"IRP_MN_POWER_SEQUENCE",
		"IRP_MN_SET_POWER",
		"IRP_MN_QUERY_POWER",
		};

	if (fcn == IRP_MN_SET_POWER || fcn == IRP_MN_QUERY_POWER)
		{
		static char* sysstate[] = {
			"PowerSystemUnspecified",
			"PowerSystemWorking",
			"PowerSystemSleeping1",
			"PowerSystemSleeping2",
			"PowerSystemSleeping3",
			"PowerSystemHibernate",
			"PowerSystemShutdown",
			"PowerSystemMaximum",
			};

		static char* devstate[] = {
			"PowerDeviceUnspecified",
			"PowerDeviceD0",
			"PowerDeviceD1",
			"PowerDeviceD2",
			"PowerDeviceD3",
			"PowerDeviceMaximum",
			};

		ULONG context = stack->Parameters.Power.SystemContext;
		POWER_STATE_TYPE type = stack->Parameters.Power.Type;

		KdPrint(("sample - "
			"POWER Request (%s), SystemContext %X", fcnname[fcn], context));
		if (type == SystemPowerState)
			KdPrint((", SystemPowerState = %s\n", sysstate[stack->Parameters.Power.State.SystemState]));
		else
			KdPrint((", DevicePowerState = %s\n", devstate[stack->Parameters.Power.State.DeviceState]));
		}
	else
		KdPrint(("sample - "
			"POWER Request (%s)\n", fcnname[fcn]));

#endif // DBG

	status = (*fcntab[fcn])(fdo, Irp);
	UnlockDevice(fdo);
	return status;
	}							// RequestPower

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// @func Handle Power requests that require no specific action from this driver
// @parm Functional device object
// @parm I/O request
// @rdesc Standard status code
// @comm This function forwards a POWER IRP to the next driver using the
// special PoCallDriver function

NTSTATUS DefaultPowerHandler(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// DefaultPowerHandler
	PoStartNextPowerIrp(Irp);	// must be done while we own the IRP
	IoSkipCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	return PoCallDriver(pdx->LowerDeviceObject, Irp);
	}							// DefaultPowerHandler

///////////////////////////////////////////////////////////////////////////////
// @func Handle IRP_MN_SET_POWER and IRP_MN_QUERY_POWER requests
// @parm Functional device object
// @parm I/O request
// @rdesc Standard status code

NTSTATUS HandleSetPower(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// HandleSetPower
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG fcn = stack->MinorFunction;
	ULONG context = stack->Parameters.Power.SystemContext;
	POWER_STATE_TYPE type = stack->Parameters.Power.Type;
	POWER_STATE state = stack->Parameters.Power.State;
	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// If this IRP pertains to a system state, we want to put ourselves into
	// a corresponding device state. The rule here is very simple: if the
	// system is below SystemWorking, me must go to D3. If the system is
	// in SystemWorking, we're allowed to pick our own state (so we pick
	// D0). We can't just change our power state now, though: we must send
	// ourselves a separate POWER IRP with the selected device state.

	DEVICE_POWER_STATE devstate = (type == SystemPowerState)
		? (state.SystemState <= PowerSystemWorking ? PowerDeviceD0 : PowerDeviceD3)
		: state.DeviceState;

	// If we're adding power, first pass the IRP down. Queue the
	// requisite device IRP in the completion routine after the
	// lower layers have restored power.

	if (devstate < pdx->power)
		{					// adding more power
		IoCopyCurrentIrpStackLocationToNext(Irp);
		IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnFinishPowerUp,
			NULL, TRUE, TRUE, TRUE);
		return PoCallDriver(pdx->LowerDeviceObject, Irp);
		}					// adding more power

	// If we're removing power, first do the device specific part.
	// Then send the request down the stack. In the case of a system
	// power request, send ourselves a device power IRP to power down first.
	// In the case of a device power request, use PoSetPowerState to tell
	// the Power Manager what we're about to do and then actually depower
	// the hardware.

	else
		{					// removing power
		if (type == SystemPowerState)
			{				// change in system state
			status = SendDeviceSetPower(fdo, devstate, context);
			if (!NT_SUCCESS(status))
				{				// couldn't set device power state
				PoStartNextPowerIrp(Irp);
				return CompleteRequest(Irp, status, 0);
				}				// couldn't set device power state
			}				// change in system state
		else
			{				// change in device state
			PoSetPowerState(fdo, type, state); // before we power down
			SetPowerState(fdo, devstate);
			}				// change in device state

		return DefaultPowerHandler(fdo, Irp); // pass request down
		}					// removing power
	}							// HandleSetPower

///////////////////////////////////////////////////////////////////////////////
// @func Completion routine for IRP_MN_SET_POWER requests to enter higher power states
// @parm Device object
// @parm IRP_MJ_POWER request
// @parm Reference data from IoSetCompletionRoutine (not used)
// @rdesc Standard status code
// @comm This function handles the device-specific parts of repowering our device
// once the PDO is done with the IRP.

NTSTATUS OnFinishPowerUp(IN PDEVICE_OBJECT fdo, IN PIRP Irp, IN PVOID junk)
	{							// OnFinishPowerUp
	if (Irp->PendingReturned)
		IoMarkIrpPending(Irp);	// lower-level pended this IRP
	NTSTATUS status = Irp->IoStatus.Status;
	if (!NT_SUCCESS(status))
		return status;			// IRP failed

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ASSERT(stack->MajorFunction == IRP_MJ_POWER);
	ASSERT(stack->MinorFunction == IRP_MN_SET_POWER);
	POWER_STATE_TYPE type = stack->Parameters.Power.Type;
	POWER_STATE state = stack->Parameters.Power.State;

	// If we just handled a request to restore power to the system, we
	// want to send ourselves a device power IRP. But don't do it unless
	// there's actually a request pending right now (we may immediately get
	// another system IRP to go to a different sleep state than we were in
	// to start with).

	if (type == SystemPowerState)
		{						// restoring power to the system
		if (fdo->CurrentIrp)
			{					// have a pending request
			DEVICE_POWER_STATE devstate = state.SystemState <= PowerSystemWorking 
				? PowerDeviceD0 : PowerDeviceD3;
			status = SendDeviceSetPower(fdo, devstate, stack->Parameters.Power.SystemContext);
			}					// have a pending request
		}						// restoring power to the system

	// For a device re-power request, first restore power to the actual
	// device and then call PoSetPowerState to tell the Power Manager we
	// did so.

	else
		{						// restoring power to the device
		SetPowerState(fdo, state.DeviceState);
		PoSetPowerState(fdo, type, state); // after we power up
		}						// restoring power to the device
	
	PoStartNextPowerIrp(Irp);

	return status;
	}							// OnFinishPowerUp

///////////////////////////////////////////////////////////////////////////////
// @func Send ourselves an IRP_MN_SET_POWER request
// @parm Functional device object
// @parm Desired new device power state
// @parm System context
// @comm This function in order to let us tell ourselves to change the device
// power state. It's used when we process a system power IRP and also when
// a new data transfer IRP comes along at a time when the device is in a low-power
// state.

NTSTATUS SendDeviceSetPower(IN PDEVICE_OBJECT fdo, IN DEVICE_POWER_STATE state, ULONG context)
	{							// SendDeviceSetPower
	PIRP Irp = IoAllocateIrp(fdo->StackSize, FALSE);
	if (!Irp)
		return STATUS_INSUFFICIENT_RESOURCES;

	PIO_STACK_LOCATION stack = IoGetNextIrpStackLocation(Irp);
	stack->MajorFunction = IRP_MJ_POWER;
	stack->MinorFunction = IRP_MN_SET_POWER;
	stack->Parameters.Power.SystemContext = context;
	stack->Parameters.Power.Type = DevicePowerState;
	stack->Parameters.Power.State.DeviceState = state;

	KEVENT event;
	KeInitializeEvent(&event, NotificationEvent, FALSE);
	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnRequestComplete,
		(PVOID) &event, TRUE, TRUE, TRUE);

	NTSTATUS status = PoCallDriver(fdo, Irp);
	if (status == STATUS_PENDING)
		{						// wait for completion
		KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
		status = Irp->IoStatus.Status;
		}						// wait for completion

	IoFreeIrp(Irp);
	return status;
	}							// SendDeviceSetPower
