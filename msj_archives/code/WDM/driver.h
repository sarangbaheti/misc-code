// Declarations for sample WDM function driver
// Written by Walter Oney

#ifndef DRIVER_H
#define DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <wdm.h>				// standard WDM and kernel-mode declarations

#ifdef __cplusplus
} // extern "C"
#endif

///////////////////////////////////////////////////////////////////////////////
// Miscellaneous useful declarations

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))

///////////////////////////////////////////////////////////////////////////////
// Device extension structure

typedef struct tagDEVICE_EXTENSION {
	PDEVICE_OBJECT DeviceObject;			// device object this extension belongs to
	PDEVICE_OBJECT LowerDeviceObject;		// next lower driver in same stack
	UNICODE_STRING ifname;					// interface name
	LONG usage;								// use count on this device
	KEVENT evRemove;						// set when okay to remove this device
	PULONG idle;							// idle counter pointer
	BOOLEAN started;						// true if device has been started
	BOOLEAN enabled;						// true if device has been enabled for interrupts
	BOOLEAN iospace;						// true if port is in I/O space
	BOOLEAN mappedport;						// true if we mapped the port address
	BOOLEAN removing;						// TRUE if we're trying to remove this device
	DEVICE_POWER_STATE power;				// our current power state
	ULONG nports;							// number of ports
	PUCHAR base;							// base port or memory address
	PKINTERRUPT InterruptObject;			// interrupt to which device is connected
	PUCHAR buffer;							// I/O buffer pointer
	ULONG nbytes;							// # bytes remaining to transfer
	ULONG numxfer;							// # bytes actually transferred
	} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

// Idle detection constants (in seconds). We register for idle notification
// during AddDevice. If this many seconds elapse between WRITE requests, we
// put our fake device into a fake lower power state.

#define SIMPLE_IDLE_CONSERVATION	30		// sleep after 30 seconds on battery power
#define SIMPLE_IDLE_PERFORMANCE		600		// sleep after 10 minutes on AC power

///////////////////////////////////////////////////////////////////////////////
// Global functions

NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG info);
VOID DpcForIsr(IN PKDPC Dpc, IN PDEVICE_OBJECT fdo, IN PIRP Irp, IN PVOID Context);
NTSTATUS ForwardAndWait(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
BOOLEAN LockDevice(IN PDEVICE_EXTENSION pdx);
BOOLEAN LockDevice(IN PDEVICE_OBJECT fdo);
NTSTATUS OnRequestComplete(IN PDEVICE_OBJECT fdo, IN PIRP Irp, IN PKEVENT pev);
NTSTATUS SendDeviceSetPower(IN PDEVICE_OBJECT fdo, IN DEVICE_POWER_STATE state, ULONG context);
VOID SetPowerState(IN PDEVICE_OBJECT fdo, IN DEVICE_POWER_STATE state);
VOID RemoveDevice(IN PDEVICE_OBJECT fdo);
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST list);
VOID StopDevice(PDEVICE_OBJECT fdo);
VOID StartIo(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
void UnlockDevice(IN PDEVICE_EXTENSION pdx);
void UnlockDevice(IN PDEVICE_OBJECT fdo);

// I/O request handlers

NTSTATUS RequestCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS RequestClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS RequestControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS RequestPnp(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS RequestPower(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS RequestWrite(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

//////////////////////////////////////////////////////////////////////////////
// Globally unique identifer for the interface class of the SIMPLE device

// {3d93c5c0-0085-11d1-821e-0080c88327ab}

#ifndef FAR
#define FAR
#endif 

DEFINE_GUID(GUID_SIMPLE, 0x3d93c5c0, 0x0085, 0x11d1, 0x82, 0x1e, 0x00, 0x80, 0xc8, 0x83, 0x27, 0xab);

#endif // DRIVER_H
