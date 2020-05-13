// Device control request handers for sample WDM function driver
// Written by Walter Oney
// @doc

#include "driver.h"
#include "SimpleIoctl.h"
									  
///////////////////////////////////////////////////////////////////////////////
// @func Handle IRP_MJ_DEVICE_CONTROL request
// @parm Functional device object
// @parm I/O request to handle
// @rdesc Standard status code

NTSTATUS RequestControl(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// RequestControl
	if (!LockDevice(fdo))
		return CompleteRequest(Irp, STATUS_DELETE_PENDING, 0);
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	NTSTATUS status = STATUS_SUCCESS;
	ULONG info = 0;
	ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;
	ULONG outlength = stack->Parameters.DeviceIoControl.OutputBufferLength;

	if (outlength < sizeof(ULONG))
		{						// invalid buffer size
		UnlockDevice(fdo);
		return CompleteRequest(Irp, STATUS_INVALID_BUFFER_SIZE, 0);
		}						// invalid buffer size

	switch (code)
		{						// process control operation

	case IOCTL_SIMPLE_GETVER:
		{						// IOCTL_SIMPLE_GETVER_BUFFERED
		PULONG pversion = (PULONG) Irp->AssociatedIrp.SystemBuffer;
		info = sizeof(ULONG);
		*pversion = 0x04000A;
		break;
		}						// IOCTL_SIMPLE_GETVER_BUFFERED

	///////////////////////////////////////////////////////////////////////////

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
		}						// process control operation

	UnlockDevice(fdo);
	return CompleteRequest(Irp, status, info);
	}							// RequestControl

