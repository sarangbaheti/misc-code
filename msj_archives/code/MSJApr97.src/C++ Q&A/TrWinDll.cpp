////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// TRACEWIN support DLL. Uses CInjectDll to inject itself into every process,
// to "hook" afxDump and map all afxDump output to the TRACEWIN applet. If the
// process is not an MFC app, hooking afxDump has no effect and is harmless.
// You never need to call/use this DLL in your app. The TRACEWIN applet loads
// and initializes TrWinDll.
//
#include "StdAfx.h"
#include "InjectDLL.h"
#include "MfxTrace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef _DEBUG
// Since TrWinDll is used to trap axfDump, which is only defined when
// debugging is on, it makes no sense to compile this file w/o _DEBUG
#error "TRWINDLL Must be compiled with debugging on."
#endif

//////////////////
// App object for this TRWINDLL
//
class CTraceWinDLL : public CWinApp, public CInjectDll {
public:
	CTraceWinDLL()  { }
	~CTraceWinDLL() { }
	virtual BOOL InitInstance();
	virtual int  ExitInstance();
} theDLL;	// one-and-only, normal (per-process) static global

//////////////////
// DLL has been loaded into a new process: initialize tracing
//
BOOL CTraceWinDLL::InitInstance()
{
	MfxTraceInit();
	return TRUE;
}

//////////////////
// DLL is unloading (DLL_PROCESS_DETACH): Restore afxDump.
// Otherwise, afxDump.m_pFile will point to code that doesn't exist!
//
int CTraceWinDLL::ExitInstance()
{
	MfxTraceTerm();
	return CWinApp::ExitInstance();
}

//////////////////
// Init/Term functions turn tracing on/off. Called from TRACEWIN applet only.
//
__declspec(dllexport) int MfxTraceDllInit()
{
	// I use a CBT (Computer Based Training) hook, which Windows calls
	// whenever a window is created/destroyed/activated (among other things).
	// This means that tracing may not work for some apps that don't create
	// windows. You could fix this by using a WH_GETMESSAGE hook, instead,
	// but that will incur a slight performance hit EVERY time the app calls
	// GetMessage, and still only work for apps that have a message loop.
	// The CBT is less intrusive.
	//
	// If you have a bizarre app that neither creates window nor has a
	// message loop, youu can always #include "MfxTrace.h" and call
	// MfxTraceInit yourself, in lieu of the whole DLL scheme.
	//
	return theDLL.Inject(theDLL.m_hInstance, WH_CBT);
}

__declspec(dllexport) BOOL MfxTraceDllTerm()
{
	return theDLL.Remove();
}
