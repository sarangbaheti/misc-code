// StdVxd.h -- Standard declarations for C-language VxDs
// VxD Wizard generated for myvxd project

#ifndef STDVXD_H
#define STDVXD_H

#ifdef __cplusplus
	extern "C" {
	#define SYSCTL extern "C"
#else // not __cplusplus
	#define SYSCTL
#endif // not __cplusplus

#include <wdm.h>
#define WANTVXDWRAPS
#include <basedef.h>
#undef NULL
#define NULL ((void*) 0)
#include <vmm.h>
#include <ntkern.h>
#include <debug.h>
#include <crs.h>

#include <vwin32.h>
#include <vxdwraps.h>
#include <winerror.h>

#ifdef __cplusplus
} // extern "C"
#endif
		
///////////////////////////////////////////////////////////////////////////////
// Useful general-purpose definitions

#include <string.h>
#pragma intrinsic(memcmp, memcpy, memset, strcat, strcmp, strcpy, strlen)

#ifdef DEBUG
	#undef ASSERT
	#define ASSERT(e) if(!(e)){Debug_Printf("Assertion failure in " __FILE__ ", line %d: " #e "\r\n", __LINE__);\
		_asm int 1\
		}
#else
	#define ASSERT(e)
#endif

#ifndef MAKELONG
	#define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))
#endif

#ifndef FIELDOFFSET
	#define FIELDOFFSET(type, field) ((DWORD)(&((type *)0)->field))
#endif

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

#ifndef NAKED
	#define NAKED __declspec(NAKED)
#endif

#endif // STDVXD_H
