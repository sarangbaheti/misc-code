// undoc.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "undoc.h"
#include "undocaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE UndocDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("UNDOC.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(UndocDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(UndocDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&Undocaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("UNDOC.AWX Terminating!\n");
	}
	return 1;   // ok
}
