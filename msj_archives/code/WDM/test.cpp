// Test program for sample WDM driver
// Written by Walter Oney

#include <windows.h>
#include <stdio.h>
#include <winioctl.h>
#include <setupapi.h>
#include "SimpleIoctl.h"

///////////////////////////////////////////////////////////////////////////////
// {3d93c5c0-0085-11d1-821e-0080c88327ab}
#include <initguid.h>
DEFINE_GUID(GUID_SIMPLE, 0x3d93c5c0, 0x0085, 0x11d1, 0x82, 0x1e, 0x00, 0x80, 0xc8, 0x83, 0x27, 0xab);

typedef struct _UNICODE_STRING {
    WORD Length;
    WORD MaximumLength;
    LPWSTR  Buffer;
} UNICODE_STRING;

#define Not_VxD
#include "myvxd.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void main(int argc, char* argv[])
	{							// main

	// Determine the interface name of the SIMPLE device we want to talk to.
	// We'll take the first such interface. A real application would probably
	// ask the user to choose based on a FriendlyName value in the registry.

	HDEVINFO info = SetupDiGetClassDevs((LPGUID) &GUID_SIMPLE, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (info == INVALID_HANDLE_VALUE)
		{
		printf("Error %d trying to open enumeration handle for GUID_SIMPLE\n", GetLastError());
		exit(1);
		}

	SP_INTERFACE_DEVICE_DATA ifdata;
	ifdata.cbSize = sizeof(ifdata);
	if (!SetupDiEnumInterfaceDevice(info, NULL, (LPGUID) &GUID_SIMPLE, 0, &ifdata))
		{
		printf("Error %d trying to enumerate interfaces\n", GetLastError());
		SetupDiDestroyDeviceInfoList(info);
		exit(1);
		}

	DWORD needed;
	SetupDiGetInterfaceDeviceDetail(info, &ifdata, NULL, 0, &needed, NULL);
	PSP_INTERFACE_DEVICE_DETAIL_DATA detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA) malloc(needed);
	if (!detail)
		{
		printf("Error %d trying to get memory for interface detail\n", GetLastError());
		SetupDiDestroyDeviceInfoList(info);
		exit(1);
		}

	detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
	if (!SetupDiGetInterfaceDeviceDetail(info, &ifdata, detail, needed, NULL, NULL))
		{
		printf("Error %d getting interface detail\n", GetLastError());
		free((PVOID) detail);
		SetupDiDestroyDeviceInfoList(info);
		exit(1);
		}

	char name[MAX_PATH];
	strncpy(name, detail->DevicePath, sizeof(name));
	free((PVOID) detail);
	SetupDiDestroyDeviceInfoList(info);

	// Now that we have the name of a SIMPLE device, open a handle to it.

	HANDLE hfile = CreateFile(name, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hfile == INVALID_HANDLE_VALUE)
		{
		printf("Error %d trying to open %s\n", GetLastError(), name);
		exit(1);
		}

	DWORD version;
	DWORD junk;
	DWORD testval = 42;

	BOOL dowrite = argc >= 2 && strcmpi(argv[1], "-dowrite") == 0;

///////////////////////////////////////////////////////////////////////////////

	if (DeviceIoControl(hfile, IOCTL_SIMPLE_GETVER, &testval, sizeof(testval),
		&version, sizeof(version), &junk, NULL))
		printf("IOCTL reports version %d.%2.2d\n", HIWORD(version), LOWORD(version));
	else
		printf("IOCTL failed with code %d\n", GetLastError());

///////////////////////////////////////////////////////////////////////////////

	if (dowrite)
		{
		DWORD nwritten;
		if (WriteFile(hfile, "Hi!", 3, &nwritten, NULL))
			printf("WriteFile succeeded, sent %d bytes\n", nwritten);
		else
			printf("WriteFile failed with code %d\n", GetLastError());
		}

///////////////////////////////////////////////////////////////////////////////

	HANDLE hvxd = CreateFile("\\\\.\\MYVXD.VXD", 0, 0, 0, 0, FILE_FLAG_DELETE_ON_CLOSE, NULL);
	if (hvxd == INVALID_HANDLE_VALUE)
		printf("Unable to dynamically load MYVXD\n");
	else
		{						// test VxD interface
		WCHAR fname[MAX_PATH] = L"\\DosDevices\\";
		int offset = wcslen(fname);
		MultiByteToWideChar(CP_OEMCP, 0, name+4, -1, fname+offset, MAX_PATH - offset);

		OPENHANDLE_PARMS open = {
			{wcslen(fname) * 2, sizeof(fname), fname},
			GENERIC_READ | GENERIC_WRITE,
			};

		if (DeviceIoControl(hvxd, MYVXD_OPENHANDLE, &open, sizeof(open), NULL, 0, NULL, NULL))
			{					// opened handle okay
			IOCTL_PARMS ioctl = {
				open.hDevice,
				IOCTL_SIMPLE_GETVER_BUFFERED,
				NULL,
				0,
				&version,
				sizeof(version),
				};
			
			if (DeviceIoControl(hvxd, MYVXD_IOCTL, &ioctl, sizeof(ioctl), NULL, 0, NULL, NULL))
				printf("IOCTL_SIMPLE_GETVER via VxD reports version number %d.%2.2d\n", HIWORD(version), LOWORD(version));
			else
				printf("IOCTL_SIMPLE_GETVER via VxD failed with code %d\n", GetLastError());

			CLOSEHANDLE_PARMS close = {open.hDevice};
			if (DeviceIoControl(hvxd, MYVXD_CLOSEHANDLE, &close, sizeof(close), NULL, 0, NULL, NULL))
				printf("MYVXD_CLOSEHANDLE succeeded\n");
			else
				printf("MYVXD_CLOSEHANDLE failed with code %d\n", GetLastError());
			}					// opened handle okay
		else
			printf("MYVXD_OPENHANDLE failed with code %d\n", GetLastError());
		
		CloseHandle(hvxd);
		}						// test VxD interface

	CloseHandle(hfile);
	}							// main