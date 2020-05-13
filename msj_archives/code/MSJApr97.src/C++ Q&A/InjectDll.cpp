////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// Implementation of CInjectDll handles mechanics of injecting DLL
// using windows hooks. See InjectDll.h for info how to use.
//
#include "StdAfx.h"
#include "InjectDll.h"

////////////////
// Make sure global HHOOK is in shared data segment, so all instances
// of the DLL (processes) refer to the same HHOOK (not one per process,
// which is normally the case). You must define this segment, and
// define it as SHARED, you your DLL's module-definition (.DEF) file.
//
#pragma data_seg (".InjectDll")		// you must define as SHARED in .def
HHOOK CInjectDll::g_hHook = NULL;	// one instance for all processes
#pragma data_seg ()

// Global ptr to one-and-only CInjectDll object. One per process
//
CInjectDll* CInjectDll::g_pThis = NULL;

CInjectDll::CInjectDll()
{
	ASSERT(g_pThis==NULL);	// should only be one
	g_pThis = this;			// set global ptr
}

CInjectDll::~CInjectDll()
{
	g_pThis = NULL;
}

//////////////////
// Inject the DLL. I do it by creating a system-wide hook.
// You must pass the DLL's HINSTANCE and what kind of hook to use.
// If you're using MFC, you can get the HINSTANCE from the DLL's
// CWinApp::m_hInstance.
//
// You should call Inject only once, via a DllInit function, from the
// applet that actually injects the DLL.
//
int CInjectDll::Inject(HINSTANCE hInstance, int nHookType)
{
	if (g_hHook)
		return E_ALREADY_INJECTED;
		
	ASSERT(hInstance);
	ASSERT(WH_MINHOOK<=nHookType && nHookType<=WH_MAXHOOK);

	g_hHook = SetWindowsHookEx(nHookType,	// type of hook
		HookProc,									// hook callback fn
		hInstance,									// HINSTANCE of DLL
		0);											// 0 = system-wide hook

	return g_hHook ? NOERROR : E_INJECT_FAILED;
}

//////////////////
// Un-inject the DLL. I.e., remove the hook. The DLL could remain mapped in
// any process that's still using it, e.g., if the module count is > 0.
//
BOOL CInjectDll::Remove()
{
	BOOL bRet = UnhookWindowsHookEx(g_hHook);
	g_hHook = NULL;
	return bRet;
}

//////////////////
// Internal HOOKPROC just passes the buck to virtual function.
//
LRESULT CALLBACK CInjectDll::HookProc(int nCode, WPARAM wp, LPARAM lp)
{
	ASSERT(g_pThis);				// check valid object and
	return g_pThis->OnHookProc(nCode, wp, lp);
}

//////////////////
// Virtual OnHookProc. You should override to do stuff whenever
// the hook is called. For example, you might trap WM_CREATE messages to
// subclass windows when they are created. Default calls OnInject the first
// time the new hook is called.
//
LRESULT CInjectDll::OnHookProc(int nCode, WPARAM wp, LPARAM lp)
{
	static bInjected = FALSE;	// one per process/DLL instance
	if (!bInjected) {				// if this is the first time called:
		g_pThis->OnInject();		// do first-time init..
		bInjected = TRUE;			// ..but not again
	}
	return nCode < 0 ? CallNextHookEx(g_hHook, nCode, wp, lp) : 0;
}

//////////////////
// Default when-injected function does nothing. You should override to
// do stuff when your DLL is first injected. For example, to subclass
// window procs.
//
void CInjectDll::OnInject()
{
}
