////////////////////////////////////////////////////////////////
// TRACEWIN 1995-1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// TRACEWIN is a tool that displays MFC diagnostic (afxDump, TRACE) output
// in the window of the TRACEWIN applet.
//
// * For apps linked with MFC.DLL, you don't need to do anything,
//   just run the TRACEWIN applet.
//
// * For apps static-linked with MFC.LIB, you must #include this file in
//   your main program file (typically where you implement your CWinApp).
//   You must also call MfxTraceInit from your app's InitInstance function.
//   Since this file contains code, you should #include it in only one place.
//
// Modification history
// 4-1-95:   Created
// 10-12-95: Use WM_COPYDATA instead of atoms. Also note the name of this 
//           file is changed to TRACEWIN.H.
// 11-10-95: Added "Keep Window on Top" feature and fixed a bug 
//           relating to saved window pos.
// 11-15-95: Save/Restore position with CWindowPlacement.
// 12-05-95: Implemented tracer object with "new" instead of static, so
//           it remains around for reporting memory leaks, if any.
// 8-27-96:  Made unicode compatible (I hope!)
// 9-14-96:  Added font UI
// 1-1-97:   New DLL scheme. TraceWin.h and MfxTraceInit no longer required
//           for apps that use DLL MFC.
// 

// Window class name used by the main window of the TRACEWIN applet.
#define TRACEWND_CLASSNAME "MfxTraceWindow"

// ID sent as COPYDATASRUCT::dwData to identify the WM_COPYDATA message
// as coming from an app using TRACEWIN.
#define ID_COPYDATA_TRACEMSG MAKELONG(MAKEWORD('t','w'),MAKEWORD('i','n'))

#ifdef _DEBUG

//////////////////
// CFileTrace is a CFile, but "writes" to the trace window
//
class CFileTrace : public CFile {
	DECLARE_DYNAMIC(CFileTrace)
	CFileTrace() { m_strFileName = "Mfx File Tracer"; }
	friend BOOL MfxTraceInit();
public:
	virtual void Write(const void* lpBuf, UINT nCount);
};
IMPLEMENT_DYNAMIC(CFileTrace, CFile)

//////////////////
// Override to write to TRACEWIN applet instead of file.
//
void CFileTrace::Write(const void* lpBuf, UINT nCount)
{
	if (!afxTraceEnabled)
		return;	// MFC tracing not enabled

	HWND hTraceWnd = ::FindWindow(TRACEWND_CLASSNAME, NULL);
	if (hTraceWnd) {
		// Found Trace window: send string with WM_COPYDATA
		// Must copy to make me the owner of the string; otherwise
		// barfs when called from MFC with traceMultiApp on
		//
		static char mybuf[1024];
		memcpy(mybuf, lpBuf, nCount);
		COPYDATASTRUCT cds;
		cds.dwData = ID_COPYDATA_TRACEMSG;
		cds.cbData = nCount;
		cds.lpData = mybuf;
		CWinApp* pApp = AfxGetApp();
		HWND hWnd = pApp ? pApp->m_pMainWnd->GetSafeHwnd() : NULL;
		SendMessage(hTraceWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);

	} else {
		// No trace window: do normal debug thing
		::OutputDebugString((LPCTSTR)lpBuf);
	}
}

/////////////////
// Initialize tracing. Replace global afxDump.m_pFile with me.
//
BOOL MfxTraceInit()
{
	if (::FindWindow(TRACEWND_CLASSNAME, NULL) && afxDump.m_pFile==NULL) {
		// Initialize tracing: replace afxDump.m_pFile w/my own CFile object
		//
		// It's important to allocate with "new" here, not a static object,
		// because CFileTrace is virtual--i.e., called through a pointer in
		// the object's vtbl--and the compiler will zero out the virtual
		// function table with a NOP function when the when a static object
		// goes out of scope. But I want my CFileTrace to stay around to
		// display memory leak diagnostics even after all static objects
		// have been destructed. So I allocate the object with new and
		// never delete it. I don't want this allocation to itself generate
		// a reported memory leak, so I turn off memory tracking before I
		// allocate, then on again after.
		//
		BOOL bEnable = AfxEnableMemoryTracking(FALSE);
		afxDump.m_pFile = new CFileTrace;
		AfxEnableMemoryTracking(bEnable);
		return TRUE;
	}
	return FALSE;
}

////////////////
// Terminate tracing: restore afxDum file ptr
//
void MfxTraceTerm()
{
	if (afxDump.m_pFile &&
		 afxDump.m_pFile->IsKindOf(RUNTIME_CLASS(CFileTrace)))
	afxDump.m_pFile = NULL;
}

#else

// For non-debug build, define MfxTraceInit as a no-op
#define MfxTraceInit()
#define MfxTraceTerm()

#endif // _DEBUG
