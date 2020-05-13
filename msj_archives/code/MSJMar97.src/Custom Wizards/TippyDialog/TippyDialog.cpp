// TippyDialog.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "TippyDialog.h"
#include "TippyDialogaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE TippyDialogDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("TIPPYDIALOG.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(TippyDialogDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(TippyDialogDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&TippyDialogaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("TIPPYDIALOG.AWX Terminating!\n");
	}
	return 1;   // ok
}
