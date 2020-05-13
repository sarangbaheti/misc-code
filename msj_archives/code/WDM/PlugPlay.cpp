// Plug and Play handlers for sample WDM function driver
// Written by Walter Oney
// All rights reserved
// @doc

#include "driver.h"

NTSTATUS DefaultPnpHandler(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
NTSTATUS HandleRemoveDevice(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
NTSTATUS HandleStartDevice(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
NTSTATUS HandleStopDevice(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
VOID ShowResources(IN PCM_PARTIAL_RESOURCE_LIST list);
									  
///////////////////////////////////////////////////////////////////////////////
// @func Handle IRP_MJ_PNP request
// @parm Functional device object
// @parm I/O request to handle
// @rdesc Standard status code
// @comm This routine uses the IRP's minor function code to dispatch a handler
// function (like HandleStartDevice for IRP_MN_START_DEVICE) that actually
// handles the request. It calls DefaultPnpHandler for requests that we don't
// specifically need to handle.

NTSTATUS RequestPnp(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// RequestPnp
	if (!LockDevice(fdo))
		return CompleteRequest(Irp, STATUS_DELETE_PENDING, 0);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ASSERT(stack->MajorFunction == IRP_MJ_PNP);

	static NTSTATUS (*fcntab[])(IN PDEVICE_OBJECT fdo, IN PIRP Irp) = {
		HandleStartDevice,		// IRP_MN_START_DEVICE
		DefaultPnpHandler,		// IRP_MN_QUERY_REMOVE_DEVICE
		HandleRemoveDevice,		// IRP_MN_REMOVE_DEVICE
		DefaultPnpHandler,		// IRP_MN_CANCEL_REMOVE_DEVICE
		HandleStopDevice,		// IRP_MN_STOP_DEVICE
		DefaultPnpHandler,		// IRP_MN_QUERY_STOP_DEVICE
		DefaultPnpHandler,		// IRP_MN_CANCEL_STOP_DEVICE
		DefaultPnpHandler,		// IRP_MN_QUERY_DEVICE_RELATIONS
		DefaultPnpHandler,		// IRP_MN_QUERY_INTERFACE
		DefaultPnpHandler,		// IRP_MN_QUERY_CAPABILITIES
		DefaultPnpHandler,		// IRP_MN_QUERY_RESOURCES
		DefaultPnpHandler,		// IRP_MN_QUERY_RESOURCE_REQUIREMENTS
		DefaultPnpHandler,		// IRP_MN_QUERY_DEVICE_TEXT
		DefaultPnpHandler,		// 
		DefaultPnpHandler,		// 
		DefaultPnpHandler,		// IRP_MN_READ_CONFIG
		DefaultPnpHandler,		// IRP_MN_WRITE_CONFIG
		DefaultPnpHandler,		// IRP_MN_EJECT
		DefaultPnpHandler,		// IRP_MN_SET_LOCK
		DefaultPnpHandler,		// IRP_MN_QUERY_ID
		DefaultPnpHandler,		// IRP_MN_PNP_DEVICE_STATE
		};

	ULONG fcn = stack->MinorFunction;
	NTSTATUS status;
	if (fcn >= arraysize(fcntab))
		{						// unknown function
		status = DefaultPnpHandler(fdo, Irp); // some function we don't know about
		UnlockDevice(fdo);
		return status;
		}						// unknown function

#if DBG
	static char* fcnname[] = {
		"IRP_MN_START_DEVICE",
		"IRP_MN_QUERY_REMOVE_DEVICE",
		"IRP_MN_REMOVE_DEVICE",
		"IRP_MN_CANCEL_REMOVE_DEVICE",
		"IRP_MN_STOP_DEVICE",
		"IRP_MN_QUERY_STOP_DEVICE",
		"IRP_MN_CANCEL_STOP_DEVICE",
		"IRP_MN_QUERY_DEVICE_RELATIONS",
		"IRP_MN_QUERY_INTERFACE",
		"IRP_MN_QUERY_CAPABILITIES",
		"IRP_MN_QUERY_RESOURCES",
		"IRP_MN_QUERY_RESOURCE_REQUIREMENTS",
		"IRP_MN_QUERY_DEVICE_TEXT",
		"",
		"",
		"IRP_MN_READ_CONFIG",
		"IRP_MN_WRITE_CONFIG",
		"IRP_MN_EJECT",
		"IRP_MN_SET_LOCK",
		"IRP_MN_QUERY_ID",
		"IRP_MN_PNP_DEVICE_STATE",
		};
#endif // DBG

	KdPrint(("sample - "
		"PNP Request (%s)\n", fcnname[fcn]));

	status = (*fcntab[fcn])(fdo, Irp);
	if (fcn != IRP_MN_REMOVE_DEVICE)
		UnlockDevice(fdo);
	return status;
	}							// RequestPnp

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// @func Handle PnP requests that require no specific action from this driver
// @parm Functional device object
// @parm I/O request
// @rdesc Standard status code
// @comm This function sends the request down to the next lower layer and
// returns whatever status that generates.

NTSTATUS DefaultPnpHandler(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// DefaultPnpHandler
	IoSkipCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	return IoCallDriver(pdx->LowerDeviceObject, Irp);
	}							// DefaultPnpHandler

///////////////////////////////////////////////////////////////////////////////
// @func Handle IRP_MN_REMOVE_DEVICE request
// @parm Functional device object
// @parm I/O request to handle
// @rdesc Standard status code
// @comm This routine calls StopDevice to shut the device down, DefaultPnpHandler
// to pass the request down the stack, and RemoveDevice to cleanup the FDO.

NTSTATUS HandleRemoveDevice(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// HandleRemoveDevice

	// Wait for any pending I/O operations to complete

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	pdx->removing = TRUE;
	UnlockDevice(pdx);			// once for LockDevice at start of dispatch
	UnlockDevice(pdx);			// once for initialization during AddDevice
	KeWaitForSingleObject(&pdx->evRemove, Executive, KernelMode, FALSE, NULL);

	// Do any processing required for *us* to remove the device. This
	// would include completing any outstanding requests, etc.

	StopDevice(fdo);

	// Let lower-level drivers handle this request. Ignore whatever
	// result eventuates.

	NTSTATUS status = DefaultPnpHandler(fdo, Irp);

	// Remove the device object

	RemoveDevice(fdo);
	return status;				// lower-level completed IoStatus already
	}							// HandleRemoveDevice

///////////////////////////////////////////////////////////////////////////////
// @func Handle IRP_MN_START_DEVICE request
// @parm Functional device object
// @parm I/O request to handle
// @rdesc Standard status code
// @comm This routine calls ForwardAndWait to pass the IRP down the stack and
// StartDevice to configure the device and this driver. Then it completes the
// IRP.

NTSTATUS HandleStartDevice(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// HandleStartDevice

	// First let all lower-level drivers handle this request. In this particular
	// sample, the only lower-level driver should be the physical device created
	// by the bus driver, but there could theoretically be any number of intervening
	// bus filter devices. Those drivers may need to do some setup at this point
	// in time before they'll be ready to handle non-PnP IRP's.

	NTSTATUS status = ForwardAndWait(fdo, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, Irp->IoStatus.Information);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	
#if DBG
	KdPrint(("  Resources:\n"));
	ShowResources(&stack->Parameters.StartDevice.AllocatedResources->List[0].PartialResourceList);
	KdPrint(("  Translated Resources:\n"));
	ShowResources(&stack->Parameters.StartDevice.AllocatedResourcesTranslated->List[0].PartialResourceList);
#endif // DBG

	status = StartDevice(fdo, &stack->Parameters.StartDevice.AllocatedResourcesTranslated->List[0].PartialResourceList);

	return CompleteRequest(Irp, status, 0);
	}							// HandleStartDevice

///////////////////////////////////////////////////////////////////////////////	
// @func Handle IRP_MN_STOP_DEVICE request
// @parm Functional device object
// @parm I/O request to handle
// @rdesc Standard status code
// @comm We will sometimes, but not always, get a STOP_DEVICE before getting a
// REMOVE_DEVICE.

NTSTATUS HandleStopDevice(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// HandleStopDevice
	NTSTATUS status = DefaultPnpHandler(fdo, Irp);
	StopDevice(fdo);
	return status;
	}							// HandleStopDevice

///////////////////////////////////////////////////////////////////////////////	

#if DBG

// @func List PnP resources assigned to our device
// @parm List of resource descriptors to display
// @comm Used only in the checked build of the driver

VOID ShowResources(IN PCM_PARTIAL_RESOURCE_LIST list)
	{							// ShowResources
	PCM_PARTIAL_RESOURCE_DESCRIPTOR resource = list->PartialDescriptors;
	ULONG nres = list->Count;
	ULONG i;

	for (i = 0; i < nres; ++i, ++resource)
		{						// for each resource
		ULONG type = resource->Type;

		static char* name[] = {
			"CmResourceTypeNull",
			"CmResourceTypePort",
			"CmResourceTypeInterrupt",
			"CmResourceTypeMemory",
			"CmResourceTypeDma",
			"CmResourceTypeDeviceSpecific",
			"CmResourceTypeBusNumber",
			"CmResourceTypeDevicePrivate",
			"CmResourceTypeAssignedResource",
			"CmResourceTypeSubAllocateFrom",
			};

		KdPrint(("    type %s", type < arraysize(name) ? name[type] : "unknown"));

		switch (type)
			{					// select on resource type
		case CmResourceTypePort:
		case CmResourceTypeMemory:
			KdPrint((" start %8X%8.8lX length %X\n",
				resource->u.Port.Start.HighPart, resource->u.Port.Start.LowPart,
				resource->u.Port.Length));
			break;
		
		case CmResourceTypeInterrupt:
			KdPrint(("  level %X, vector %X, affinity %X\n",
				resource->u.Interrupt.Level, resource->u.Interrupt.Vector,
				resource->u.Interrupt.Affinity));
			break;
	
		case CmResourceTypeDma:
			KdPrint(("  channel %d, port %X\n",
				resource->u.Dma.Channel, resource->u.Dma.Port));
			}					// select on resource type
		}						// for each resource
	}							// ShowResources

#endif // DBG