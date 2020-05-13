// Main program for sample WDM function driver
// Written by Walter Oney
// All rights reserved
// @doc

#define INITGUID				// define GUID_SIMPLE

#include "driver.h"

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo);
VOID DriverUnload(IN PDRIVER_OBJECT fdo);

///////////////////////////////////////////////////////////////////////////////
// @func Main entry point to WDM driver
// @parm Object that represents this driver
// @parm Name of registry key that contains any driver-specific information
// @rdesc Standard status code
// @comm DriverEntry is the main entry point to a WDM driver DLL. Its purpose is to
// fill in the system-supplied Driver Object with pointers to driver functions
// that will carry out operations on this device. In previous versions of NT,
// the DriverEntry routine also had the responsibility of locating the devices
// to be managed by this driver and creating the corresponding device objects.
// That job now happens in response to a Plug and Play I/O request.
// @comm This is the only function whose name is constrained to be anything in particular.
// The constraint arises because the build script specifies "DriverEntry@8" as the
// entry point. The loader doesn't actually care what this function is called (because
// it's not exported) -- it simply calls the main entry point.

extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath)
	{							// DriverEntry
	KdPrint(("simple - "
		"Entering DriverEntry: DriverObject %8.8lX\n", DriverObject));

	DriverObject->DriverUnload = DriverUnload;
	DriverObject->DriverExtension->AddDevice = AddDevice;

	// Fill in the vector of I/O request handlers. Whereas an intermediate driver must
	// supply handlers for all requests that it or any lower driver might service,
	// a lowest-level function driver only needs to handle PNP and POWER requests plus the
	// ones that it really implements.
	
	DriverObject->MajorFunction[IRP_MJ_CREATE] = RequestCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = RequestClose;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = RequestWrite;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = RequestControl;
	DriverObject->MajorFunction[IRP_MJ_PNP] = RequestPnp;
	DriverObject->MajorFunction[IRP_MJ_POWER] = RequestPower;

	// The mechanism for handling read and write requests for a device that uses
	// interrupts includes a Start I/O routine, an interrupt service routine, and
	// a deferred procedure call routine that finishes handling interrupts. We
	// need to supply the StartIo routine address here.

	DriverObject->DriverStartIo = StartIo;

	return STATUS_SUCCESS;
	}							// DriverEntry

///////////////////////////////////////////////////////////////////////////////
// @func Cleanup prior to unloading driver
// @parm Object representing this driver
// @comm DriverUnload is called when this driver is about to be unloaded. In
// previous versions of NT, this function would have gone through the list of
// DEVICE_OBJECTS belonging to this driver in order to delete each one. That
// function now happens (if it needs to) in response to IRP_MN_REMOVE_DEVICE
// PnP IRP's.

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
	{							// DriverUnload
	KdPrint(("simple - "
		"Entering DriverUnload: DriverObject %8.8lX\n", DriverObject));
	}							// DriverUnload

///////////////////////////////////////////////////////////////////////////////
// @func Create a new functional device object
// @parm Object that represents this driver
// @parm Physical device object
// @rdesc Standard status code
// @comm AddDevice is called when the Configuration Manager detects (or gets told about
// via the New Hardware Wizard) a new device for which this module is the driver. Its
// main purpose is to create a functional device object (FDO) and to layer the FDO into
// the stack of device objects.

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo)
	{							// AddDevice
	KdPrint(("simple - "
		"Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));

	NTSTATUS status;

	// Create a functional device object to represent the hardware we're managing.

	PDEVICE_OBJECT fdo;
	status = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION), NULL,
		FILE_DEVICE_UNKNOWN, 0, FALSE, &fdo);
	if (!NT_SUCCESS(status))
		{						// can't create device object
		KdPrint(("simple - "
			"IoCreateDevice failed - %X\n", status));
		return status;
		}						// can't create device object
	KdPrint(("simple - "
		"AddDevice created new device object %8.8lX\n", fdo));
	
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	pdx->DeviceObject = fdo;
	pdx->usage = 1;				// locked until RemoveDevice
	KeInitializeEvent(&pdx->evRemove, NotificationEvent, FALSE); // set when use count drops to zero

	// Register a device interface. This will provide a way for user-mode and kernel-mode
	// code to open handles to our device. Earlier kinds of drivers would have named
	// the device in the call to IoCreateDevice and would now create a symbolic link
	// whose name could be used by user-mode code.

	status = IoRegisterDeviceInterface(pdo, &GUID_SIMPLE, NULL, &pdx->ifname);
	if (!NT_SUCCESS(status))
		{						// unable to register interface
		KdPrint(("simple - "
			"IoRegisterDeviceInterface failed - %8.8lX\n", status));
		IoDeleteDevice(fdo);
		return status;
		}						// unable to register interface
	IoSetDeviceInterfaceState(&pdx->ifname, TRUE);
	KdPrint(("simple - "
		"created interface named %ws\n", pdx->ifname.Buffer));

	// Since we must pass PNP requests down to the next device object in the chain
	// (namely the physical device object created by the bus enumerator), we have
	// to remember what that device is. That's why we defined the LowerDeviceObject
	// member in our device extension.
	
	pdx->LowerDeviceObject = IoAttachDeviceToDeviceStack(fdo, pdo);

	// Monolithic kernel-mode drivers usually create device objects during DriverEntry,
	// and the I/O manager automatically clears the INITIALIZING flag. Since we're
	// creating the object later (namely in response to PnP START_DEVICE request),
	// we need to clear the flag manually.

	fdo->Flags &= ~DO_DEVICE_INITIALIZING;

	// Here is where we need to initialize the DPC (Deferred Procedure Call) object
	// that allows our interrupt service routine to request a DPC to finish handling
	// a device interrupt.

	IoInitializeDpcRequest(fdo, DpcForIsr);

	// Indicate that read/write requests should proceed using I/O manager buffers

	fdo->Flags |= DO_BUFFERED_IO;

	// Other global initialization...

	pdx->power = PowerDeviceD0;	// device starts in full power state

	// Register for idle detection. The power manager will maintain a timer for
	// us and automatically send us an IRP_MN_SET_POWER to put us into the
	// specified low power state. Note that the device argument to this
	// function must be the PDO, not the FDO. The timeout constants are
	// in seconds. Supposedly, you can request any device state here. In
	// Memphis beta 1, however, you only get notified if you've asked for
	// D3.

	pdx->idle = PoRegisterDeviceForIdleDetection(pdo, SIMPLE_IDLE_CONSERVATION,
		SIMPLE_IDLE_PERFORMANCE, PowerDeviceD3);

	return STATUS_SUCCESS;
	}							// AddDevice

///////////////////////////////////////////////////////////////////////////////
// @func Mark I/O request complete
// @parm I/O request in question
// @parm Standard status code
// @parm Additional information related to status code
// @rdesc Standard status code (same as "status" argument)

NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG info)
	{							// CompleteRequest
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
	}							// CompleteRequest

///////////////////////////////////////////////////////////////////////////////
// @func Forward request to lower level and await completion
// @parm Functional device object
// @parm I/O request
// @rdesc Standard status code
// @comm The processor must be at PASSIVE IRQL because this function initializes
// and waits for non-zero time on a kernel event object.
// @comm The only purpose of this routine in this particular driver is to pass down
// IRP_MN_START_DEVICE requests and wait for the PDO to handle them.

NTSTATUS ForwardAndWait(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// ForwardAndWait
	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);
	
	// Initialize a kernel event object to use in waiting for the lower-level
	// driver to finish processing the object. It's a little known fact that the
	// kernel stack *can* be paged, but only while someone is waiting in user mode
	// for an event to finish. Since neither we nor a completion routine can be in
	// the forbidden state, it's okay to put the event object on the stack.
	
	KEVENT event;
	KeInitializeEvent(&event, NotificationEvent, FALSE);

	IoCopyCurrentIrpStackLocationToNext(Irp);
	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnRequestComplete,
		(PVOID) &event, TRUE, TRUE, TRUE);

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status = IoCallDriver(pdx->LowerDeviceObject, Irp);
	if (status == STATUS_PENDING)
		{						// wait for completion
		KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
		status = Irp->IoStatus.Status;
		}						// wait for completion

	return status;
	}							// ForwardAndWait

///////////////////////////////////////////////////////////////////////////////
// @func Lock a SIMPLE device object
// @parm Address of our device extension
// @rdesc TRUE if it was possible to lock the device, FALSE otherwise.
// @comm A FALSE return value indicates that we're in the process of deleting
// the device object, so all new requests should be failed

BOOLEAN LockDevice(PDEVICE_EXTENSION pdx)
	{							// LockDevice
	
	// Increment use count on our device object

	LONG usage = InterlockedIncrement(&pdx->usage);

	// AddDevice initialized the use count to 1, so it ought to be bigger than
	// one now. HandleRemoveDevice sets the "removing" flag and decrements the
	// use count, possibly to zero. So if we find a use count of "1" now, we
	// should also find the "removing" flag set.

	ASSERT(usage > 1 || pdx->removing);

	// If device is about to be removed, restore the use count and return FALSE.
	// If we're in a race with HandleRemoveDevice (maybe running on another CPU),
	// the sequence we've followed is guaranteed to avoid a mistaken deletion of
	// the device object. If we test "removing" after HandleRemoveDevice sets it,
	// we'll restore the use count and return FALSE. In the meantime, if
	// HandleRemoveDevice decremented the count to 0 before we did our increment,
	// its thread will have set the remove event. Otherwise, we'll decrement to 0
	// and set the event. Either way, HandleRemoveDevice will wake up to finish
	// removing the device, and we'll return FALSE to our caller.
	// 
	// If, on the other hand, we test "removing" before HandleRemoveDevice sets it,
	// we'll have already incremented the use count past 1 and will return TRUE.
	// Our caller will eventually call UnlockDevice, which will decrement the use
	// count and might set the event HandleRemoveDevice is waiting on at that point.

	if (pdx->removing)
		{						// removing device
		if (InterlockedDecrement(&pdx->usage) == 0)
			KeSetEvent(&pdx->evRemove, 0, FALSE);
		return FALSE;
		}						// removing device

	return TRUE;
	}							// LockDevice

BOOLEAN LockDevice(IN PDEVICE_OBJECT fdo)
	{
	return LockDevice((PDEVICE_EXTENSION) fdo->DeviceExtension);
	}

///////////////////////////////////////////////////////////////////////////////
// @func Handle completion of a request by a lower-level driver
// @parm Functional device object
// @parm I/O request which has completed
// @parm Context argument supplied to IoSetCompletionRoutine, namely address of
// KEVENT object on which ForwardAndWait is waiting
// @comm This is the completion routine used for requests forwarded by ForwardAndWait. It
// sets the event object and thereby awakens ForwardAndWait.
// @comm Note that it's *not* necessary for this particular completion routine to test
// the PendingReturned flag in the IRP and then call IoMarkIrpPending. You do that in many
// completion routines because the dispatch routine can't know soon enough that the
// lower layer has returned STATUS_PENDING. In our case, we're never going to pass a
// STATUS_PENDING back up the driver chain, so we don't need to worry about this.

NTSTATUS OnRequestComplete(IN PDEVICE_OBJECT fdo, IN PIRP Irp, IN PKEVENT pev)
	{							// OnRequestComplete
	KeSetEvent(pev, 0, FALSE);
	return STATUS_MORE_PROCESSING_REQUIRED;
	}							// OnRequestComplete

///////////////////////////////////////////////////////////////////////////////
// @func Remove functional device from the system
// @parm Functional device object
// @comm Whereas AddDevice gets called by the I/O manager directly, this
// function is called in response to a PnP request with the minor function code
// of IRP_MN_REMOVE_DEVICE.

VOID RemoveDevice(IN PDEVICE_OBJECT fdo)
	{							// RemoveDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;

	IoSetDeviceInterfaceState(&pdx->ifname, FALSE);
	if (pdx->ifname.Buffer)
		ExFreePool((PVOID) pdx->ifname.Buffer);

	if (pdx->LowerDeviceObject)
		IoDetachDevice(pdx->LowerDeviceObject);

	IoDeleteDevice(fdo);
	}							// RemoveDevice

///////////////////////////////////////////////////////////////////////////////
// @func Unlock a SIMPLE device object
// @parm Address of our device extension
// @comm If the use count drops to zero, set the evRemove event because we're
// about to remove this device object.

void UnlockDevice(PDEVICE_EXTENSION pdx)
	{							// UnlockDevice
	LONG usage = InterlockedDecrement(&pdx->usage);
	ASSERT(usage >= 0);
	if (usage == 0)
		{						// removing device
		ASSERT(pdx->removing);	// HandleRemoveDevice should already have set this
		KeSetEvent(&pdx->evRemove, 0, FALSE);
		}						// removing device
	}							// UnlockDevice

void UnlockDevice(PDEVICE_OBJECT fdo)
	{
	UnlockDevice((PDEVICE_EXTENSION) fdo->DeviceExtension);
	}