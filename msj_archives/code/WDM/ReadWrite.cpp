// Read/Write request processors for sample WDM driver
// Written by Walter Oney
// @doc

#include "driver.h"

typedef struct POWER_STUFF {
	PDEVICE_EXTENSION pdx;
	DEVICE_POWER_STATE state;
	} POWER_STUFF, *PPOWER_STUFF;

BOOLEAN DisableDevice(IN PDEVICE_EXTENSION pdx);
BOOLEAN EmpowerDevice(IN PPOWER_STUFF pps);
BOOLEAN EnableDevice(IN PDEVICE_EXTENSION pdx);
VOID OnCancel(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
VOID OnCancelActiveIrp(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
BOOLEAN OnInterrupt(IN PKINTERRUPT Interrupt, IN PDEVICE_EXTENSION fdo);
BOOLEAN TransferNext(IN PDEVICE_EXTENSION pdx);

///////////////////////////////////////////////////////////////////////////////
// @func Disable device (i.e., prevent it from generating interrupts)
// @parm Address of device extension
// @rdesc Always TRUE
// @comm This function executes at DIRQL within the protection of the interrupt
// spin lock because it needs to synchronize access to whatever device feature that
// controls whether the device is enabled for generating interrupts

BOOLEAN DisableDevice(IN PDEVICE_EXTENSION pdx)
	{							// DisableDevice
	KdPrint(("simple - "
		"Disabling device\n"));
	
	// With a real device, we might actually do something to the device here
	// to enable it for operation.
	
	pdx->enabled = FALSE;
	return TRUE;
	}							// DisableDevice

///////////////////////////////////////////////////////////////////////////////
// @func Deferred procedure call routine for signalling I/O completion
// @parm Address of DPC object
// @parm Address of functional device object
// @parm I/O request packet that has now completed
// @parm Context argument supplied when requesting DPC (ignored)
// @comm This function illustrates the standard role of a DPC routine in
// completing a request.It calls IoStartNextPacket to release the next packet
// from the device queue. Then it calls IoCompleteRequest to complete the
// current request. Since it's not possible for two or more requests to be
// active at the same time, the DPC routine in this particular driver doesn't
// need to worry about dealing with more than one request.

VOID DpcForIsr(IN PKDPC Dpc, IN PDEVICE_OBJECT fdo, IN PIRP Irp, IN PVOID Context)
	{							// DpcForIsr
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// Make sure the IRP can't be cancelled now. It's also marginally possible for
	// the IRP pointer to now be invalid if the IRP got cancelled in between the
	// time the DPC was queued and the time we actually get to run. If that occurred,
	// the call our cancel routine made to IoStartNextRequest would have altered
	// the CurrentIrp pointer in our device object within the protection of the
	// cancel spin lock.
	
	KIRQL irql;
	IoAcquireCancelSpinLock(&irql);
	BOOLEAN invalid = Irp != fdo->CurrentIrp;
	if (!invalid)
		IoSetCancelRoutine(Irp, NULL);
	IoReleaseCancelSpinLock(irql);

	// If the IRP was cancelled, our cancel routine (OnCancelActiveIrp)
	// will have completed it. We don't want to complete it a second time.
	
	if (invalid || Irp->Cancel)
		return;					// was completed by OnCancelActiveIrp

	// Complete the request and allow the next one to start.
	
	ULONG count = pdx->numxfer;	// preserve # byte transferred
	IoStartNextPacket(fdo, TRUE);
	CompleteRequest(Irp, STATUS_SUCCESS, count); // request is complete
	UnlockDevice(pdx);
	}							// DpcForIsr

///////////////////////////////////////////////////////////////////////////////
// @func Set device power state
// @parm Structure containing these two fields:
// @flag pdx | Address of device extension for the device we're turning on
// @flag state | Desired new power state
// @rdesc Always TRUE
// @comm This function executes at DIRQL within the protection of the interrupt
// spin lock because it needs to synchronize access to whatever device feature that
// controls whether the device is powered.

BOOLEAN EmpowerDevice(IN PPOWER_STUFF pps)
	{							// EmpowerDevice
	PDEVICE_EXTENSION pdx = pps->pdx;
	DEVICE_POWER_STATE state = pps->state;

	// If told to enter the state we're already in, do nothing.
	
	if (state == pdx->power)
		return TRUE;			// already in the right state

#if DBG
	char* statename[] = {"", "D0", "D1", "D2", "D3"};
	KdPrint(("simple - "
		"Putting device into state %s\n", statename[state]));
#endif

	// A real device would interpret the new state relative to the old state and
	// save (or restore) some context information, send control information to the
	// device, etc. This fake device just records the power state in the device
	// extension.

	pdx->power = state;
	if (state == PowerDeviceD0)
		TransferNext(pdx);		// goose transfer logic to resume any stalled request

	return TRUE;
	}							// EmpowerDevice

///////////////////////////////////////////////////////////////////////////////
// @func Enable device (i.e., allow it to generate interrupts)
// @parm Address of device extension
// @rdesc Always TRUE
// @comm This function executes at DIRQL within the protection of the interrupt
// spin lock because it needs to synchronize access to whatever device feature that
// controls whether the device is enabled for generating interrupts

BOOLEAN EnableDevice(IN PDEVICE_EXTENSION pdx)
	{							// EnableDevice
	KdPrint(("simple - "
		"Enabling device\n"));
	
	// With a real device, we might actually do something to the device here
	// to enable the device for operation.
	
	pdx->enabled = TRUE;
	return TRUE;
	}							// EnableDevice

///////////////////////////////////////////////////////////////////////////////
// @func Handle cancellation of request for our device
// @parm Functional device object to which request is queued
// @parm Request being cancelled
// @comm We own the cancel spin lock on entry and must release it before returning.
// @comm This function illustrates the standard way of dealing with cancellation
// of an IRP. If the device object's CurrentIrp field points to the IRP, the
// IRP has been removed from the queue and is currently being processed by the
// StartIo routine. In fact, the StartIo routine has not yet reached the point
// of changing the cancel routine pointer. Since it will reach that point
// shortly after we release the cancel spin lock, it will see the Cancel flag
// and stop processing. If this IRP is *not* current, though, it's still in the
// device queue. We therefore remove the IRP from the device queue by calling
// KeRemoveEntryDeviceQueue. In either case, we complete the IRP with STATUS_CANCELLED.

VOID OnCancel(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// OnCancel
	if (fdo->CurrentIrp == Irp)
		{						// canceling current IRP
		IoReleaseCancelSpinLock(Irp->CancelIrql);
		IoStartNextPacket(fdo, TRUE); // since we'll be completing this one
		}						// canceling current IRP
	else
		{						// canceling queued IRP
		KeRemoveEntryDeviceQueue(&fdo->DeviceQueue, &Irp->Tail.Overlay.DeviceQueueEntry);
		IoReleaseCancelSpinLock(Irp->CancelIrql);
		}						// canceling queued IRP

	CompleteRequest(Irp, STATUS_CANCELLED, 0);
	UnlockDevice(fdo);
	}							// OnCancel

///////////////////////////////////////////////////////////////////////////////
// @func Handle cancellation of active request for our device
// @parm Functional device object to which request is queued
// @parm Request being cancelled
// @comm The purpose of this function is mostly to deal with cancellation of an IRP that
// we left in limbo because our device was powered down.

VOID OnCancelActiveIrp(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// OnCancelActiveIrp
	
	// We expect to only be called to cancel the current IRP for our device, but
	// guard against the possibility that some other IRP has become current by
	// not doing anything otherwise.
	
	if (fdo->CurrentIrp == Irp)
		{						// canceling active IRP
		IoReleaseCancelSpinLock(Irp->CancelIrql);
		IoStartNextPacket(fdo, TRUE);
		CompleteRequest(Irp, STATUS_CANCELLED, 0);
		UnlockDevice(fdo);
		}						// canceling active IRP
	else
		IoReleaseCancelSpinLock(Irp->CancelIrql);
	}							// OnCancelActiveIrp

///////////////////////////////////////////////////////////////////////////////
// @func Handle interrupt from our device
// @parm Interrupt object
// @parm Device extension
// @rdesc TRUE if our device generated an interrupt, FALSE otherwise
// @comm This function tests to see if the current request has finished and,
// if so, requests a DPC to complete the request. Otherwise, it advances to
// the next step in the request.

BOOLEAN OnInterrupt(IN PKINTERRUPT Interrupt, IN PDEVICE_EXTENSION pdx)
	{							// OnInterrupt
	return TransferNext(pdx);
	}							// OnInterrupt
									  
///////////////////////////////////////////////////////////////////////////////
// @func Handle IRP_MJ_CREATE request
// @parm Functional device object
// @parm I/O request to handle
// @rdesc Standard status code

NTSTATUS RequestCreate(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// RequestCreate
	KdPrint(("sample - "
		"IRP_MJ_CREATE\n"));
	
	// We have to handle this IRP to allow applications to open handles to our
	// device. We don't have to actually do anything about it, though.
	
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// RequestCreate
									  
///////////////////////////////////////////////////////////////////////////////
// @func Handle IRP_MJ_Close request
// @parm Functional device object
// @parm I/O request to handle
// @rdesc Standard status code

NTSTATUS RequestClose(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// RequestClose
	KdPrint(("sample - "
		"IRP_MJ_CLOSE\n"));
	
	// We have to handle this IRP to allow applications to close handles to our
	// device. We don't have to actually do anything about it, though.
	
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// RequestClose

///////////////////////////////////////////////////////////////////////////////
// @func Dispatch routine for IRP_MJ_WRITE
// @parm Functional device object
// @parm I/O request
// @rdesc Standard status code
// @comm This function marks the IRP pending and queues it for processing. If necessary,
// it restores power to the device, too.

NTSTATUS RequestWrite(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// RequestWrite
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// First lock the device so it can't be removed out from under the IRP

	if (!LockDevice(pdx))
		return CompleteRequest(Irp, STATUS_DELETE_PENDING, 0);

	// If we're in a low-power state, wake the device up.

	if (pdx->power > PowerDeviceD0)
		{						// restore power to device
		NTSTATUS status = SendDeviceSetPower(fdo, PowerDeviceD0, 0);
		if (!NT_SUCCESS(status))
			return CompleteRequest(Irp, status, 0);
		}						// restore power to device

	// If we successfully registered for idle detection during AddDevice,
	// reset the idle counter so the Power Manager won't automatically put
	// us to sleep any time soon.

	if (pdx->idle)
		PoSetDeviceBusy(pdx->idle);

	// Queue and pend the IRP. When its turn comes, the I/O manager will forward
	// it to our StartIo routine.

	IoMarkIrpPending(Irp);
	IoStartPacket(fdo, Irp, NULL, OnCancel);
	return STATUS_PENDING;
	}							// RequestWrite

///////////////////////////////////////////////////////////////////////////////
// @func Set device power state
// @parm Functional device object
// @parm New device power state
// @comm The IRP_MN_SET_POWER handler calls this routine to actually change the
// power state of our device. Since we need to synchronize with the ISR in the
// use of the device features that control power to the device, we raise to
// DIRQL and claim the interrupt spin lock before actually changing the power
// level.

VOID SetPowerState(IN PDEVICE_OBJECT fdo, IN DEVICE_POWER_STATE state)
	{							// SetPowerState
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	POWER_STUFF ps = {pdx, state};
	KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) EmpowerDevice, (PVOID) &ps);
	}							// SetPowerState

///////////////////////////////////////////////////////////////////////////////
// @func Configure and start the device
// @parm Functional device object
// @parm List of translated I/O resource descriptors
// @rdesc Standard status coce
// @comm This function is called by the dispatch routine for IRP_MN_START_DEVICE
// in order to determine the configuration for the device and to prepare the driver
// and the device for subsequent operation.

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST list)
	{							// StartDevice
	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	ASSERT(!pdx->started);

	// Identify the I/O resources we're supposed to use. In previous versions
	// of NT, this required nearly heroic efforts that were highly bus dependent.
	
	PCM_PARTIAL_RESOURCE_DESCRIPTOR resource = list->PartialDescriptors;
	ULONG nres = list->Count;
	
	BOOLEAN haveint = FALSE;	// TRUE if we find our interrupt
	ULONG vector;				// interrupt vector
	KIRQL irql;					// interrupt level
	KINTERRUPT_MODE mode;		// interrupt mode
	KAFFINITY affinity;			// processor affinity for interrupt

	BOOLEAN haveport = FALSE;	// TRUE if we find our port
	PHYSICAL_ADDRESS port;		// port address
	ULONG nports;				// number of ports
	BOOLEAN needmap = FALSE;	// TRUE if we need to map port address

	BOOLEAN error = FALSE;		// TRUE if there's an error in the resource descriptions

	for (ULONG i = 0; i < nres; ++i, ++resource)
		{						// for each resource
		switch (resource->Type)
			{					// switch on resource type

		case CmResourceTypePort:
			{					// CmResourceTypePort
			haveport = TRUE;
			port = resource->u.Port.Start;
			nports = resource->u.Port.Length;

			// On RISC platforms, the port address needs to be mapped by calling
			// MmMapIoSpace. We still end up using the HAL routines for port I/O,
			// though.

			needmap = (resource->Flags & CM_RESOURCE_PORT_IO) ==0;
			break;
			}					// CmResourceTypePort

		case CmResourceTypeInterrupt:
			{					// CmResourceTypeInterrupt
			haveint = TRUE;
			irql = (KIRQL) resource->u.Interrupt.Level;
			vector = resource->u.Interrupt.Vector;
			affinity = resource->u.Interrupt.Affinity;
			mode = (resource->Flags == CM_RESOURCE_INTERRUPT_LATCHED)
				? Latched : LevelSensitive;
			break;
			}					// CmResourceTypeInterrupt
		
		case CmResourceTypeMemory:
			{					// CmResourceTypeMemory
			haveport = FALSE;
			port = resource->u.Memory.Start;
			nports = resource->u.Memory.Length;
			needmap = TRUE;
			break;
			}					// CmResourceTypeMemory

		default:
			error = TRUE;
			break;
			}					// switch on resource type
		}						// for each resource

	if (error || !haveport || !haveint)
		{						// error in I/O resources
		KdPrint(("simple - "
			"Device configuration is invalid\n"));
		return STATUS_DEVICE_CONFIGURATION_ERROR;
		}						// error in I/O resources

	// We've found the expected resources. Connect to all but the interrupt.

	pdx->iospace = haveport;
	pdx->nports = nports;
	if (needmap)
		{						// we have a memory-mapped register
		pdx->base = (PUCHAR) MmMapIoSpace(port, nports, MmNonCached);
		if (!pdx->base)
			return STATUS_NO_MEMORY;
		}						// we have a memory-mapped register
	else
		pdx->base = (PUCHAR) port.LowPart;
	pdx->mappedport = needmap;
	pdx->iospace = haveport;

	// Now connect to the interrupt. We saved this for last because we must
	// be completely ready to handle an interrupt as soon as we call IoConnectInterrupt.

	DisableDevice(pdx);

	status = IoConnectInterrupt(&pdx->InterruptObject, (PKSERVICE_ROUTINE) OnInterrupt,
		(PVOID) pdx, NULL, vector, irql, irql, mode, FALSE, affinity, FALSE);
	if (!NT_SUCCESS(status))
		{						// unable to connect to interrupt
		KdPrint(("simple - "
			"IoConnectInterrupt failed with status %X\n", status));
		if (needmap)
			MmUnmapIoSpace(pdx->base, nports);
		return status;
		}						// unable to connect to interrupt

	// Now put the device into a known initial state that allows interrupts to occur.
	// Since doing so requires the same access to the device as occurs during an
	// interrupt, we need to perform those operations at raised IRQL. Note that
	// KeSynchronizeExecution returns the same boolean value returned by the critical
	// section routine it calls.

	if (!KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) EnableDevice, (PVOID) pdx))
		{						// can't enable device
		KdPrint(("simple - "
			"Unable to enable device\n"));
		IoDisconnectInterrupt(pdx->InterruptObject);
		MmUnmapIoSpace(pdx->base, nports);
		return STATUS_INVALID_DEVICE_STATE;
		}						// can't enable device

	// Device has been completely initialized and is ready to run.

	pdx->started = TRUE;
	return STATUS_SUCCESS;
	}							// StartDevice

///////////////////////////////////////////////////////////////////////////////
// @func Start I/O routine
// @parm Functional device object
// @parm I/O request
// @comm The I/O Manager maintains a queue of IRP's for the device and feeds
// them one at a time to this function.

VOID StartIo(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// StartIo
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	KIRQL oldirql;

	// This IRP may have been cancelled in between the time it was removed
	// from the queue and now. In fact, the pointer may have become invalid
	// too. If you're trying to prove the safety of this logic, it helps to
	// know that the I/O manager always owns the cancel spin lock when it
	// sets or clears the CurrentIrp field of the device object.
	
	IoAcquireCancelSpinLock(&oldirql);
	if (Irp != fdo->CurrentIrp || Irp->Cancel)
		{						// request has been cancelled
		IoReleaseCancelSpinLock(oldirql);
		return;
		}						// request has been cancelled
	else
		{						// switch cancel routines
		ASSERT(Irp == fdo->CurrentIrp);
		IoSetCancelRoutine(Irp, OnCancelActiveIrp);
		IoReleaseCancelSpinLock(oldirql);
		}						// switch cancel routines

	// Initialize the state information in the device extension that we use for
	// processing the request.

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	pdx->buffer = (PUCHAR) Irp->AssociatedIrp.SystemBuffer;
	pdx->nbytes = stack->Parameters.Write.Length;
	pdx->numxfer = 0;

	// Try to transfer the first byte.

	KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) TransferNext, (PVOID) pdx);
	}							// StartIo

///////////////////////////////////////////////////////////////////////////////
// @func Stop the device
// @parm Functional device object
// @comm This function is called by the dispatch routine for IRP_MN_STOP_DEVICE
// in order to undo everything that was done inside StartDevice.

VOID StopDevice(IN PDEVICE_OBJECT fdo)
	{							// StopDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	if (!pdx->started)
		return;					// device not started, so nothing to do
	pdx->started = FALSE;

	ASSERT(pdx->InterruptObject);
	KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) DisableDevice, (PVOID) pdx); 
	IoDisconnectInterrupt(pdx->InterruptObject);
	pdx->InterruptObject = NULL;

	if (pdx->mappedport)
		MmUnmapIoSpace((PVOID) pdx->base, pdx->nports);
	}							// StopDevice

///////////////////////////////////////////////////////////////////////////////
// @func Setup to transfer the next data byte
// @parm Device extension
// @rdesc TRUE if an IRP is active for this device, FALSE otherwise.
// @comm This function is called at DIRQL under the protection of the interrupt
// spin lock because it shares data with the ISR.

BOOLEAN TransferNext(IN PDEVICE_EXTENSION pdx)
	{							// TransferNext
	PIRP Irp = pdx->DeviceObject->CurrentIrp;
	if (!Irp)
		return FALSE;			// no transfer pending

	// See if the current request is complete. If so, schedule a DPC to complete it.
	
	if (!pdx->nbytes)
		{						// count exhausted
		IoRequestDpc(pdx->DeviceObject, Irp, NULL);
		return TRUE;
		}						// count exhausted

	// Check the device power state. If the device is off, don't do anything. (The
	// IRP will stall until the device is repowered or until someone cancels it.)

	if (pdx->power > PowerDeviceD0)
		return TRUE;			// let IRP stall until power is restored

	// To write a byte, we just output it to the data output port. When the device is
	// ready for the next byte, it will generate an interrupt.

	if (pdx->iospace)
		WRITE_PORT_UCHAR(pdx->base, *pdx->buffer);
	else
		WRITE_REGISTER_UCHAR(pdx->base, *pdx->buffer);

	++pdx->buffer;
	--pdx->nbytes;
	++pdx->numxfer;

	return TRUE;
	}							// TransferNext
