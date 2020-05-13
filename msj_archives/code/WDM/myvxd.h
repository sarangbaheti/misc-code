// myvxd.h -- Declarations for MYVXD.VXD

#ifndef MYVXD_H
#define MYVXD_H

#define MYVXD_GETVERSION	1
#define MYVXD_OPENHANDLE	2
#define MYVXD_IOCTL			3
#define MYVXD_CLOSEHANDLE	4

typedef struct {
	UNICODE_STRING name;	// name of device to open
	DWORD access;			// desired access
	DWORD attributes;		// attributes for new file
	DWORD share;			// sharing attributes
	DWORD howcreate;		// create disposition
	DWORD options;			// create options
	DWORD hDevice;			// (OUTPUT) device handle
	} OPENHANDLE_PARMS;

typedef struct {
	DWORD hDevice;			// device handle
	DWORD code;				// I/O control code
	PVOID inbuf;			// input buffer
	DWORD cbInbuf;			// length of input buffer
	PVOID outbuf;			// output buffer
	DWORD cbOutbuf;			// length of output buffer
	} IOCTL_PARMS;

typedef struct {
	DWORD hDevice;
	} CLOSEHANDLE_PARMS;

#endif // MYVXD_H
