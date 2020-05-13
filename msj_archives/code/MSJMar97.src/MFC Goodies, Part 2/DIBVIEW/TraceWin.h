////////////////////////////////////////////////////////////////
// TRACEWIN Copyright 1995-1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// TRACEWIN is a development tool that displays MFC TRACE output in
// a window, even if you don't run under the debugger. To use tracewin,
// simply #include this file in your main .cpp file, the one that contains
// your CWinApp-derived app, and call 
//
//		MfxTraceInit();
//
// from your app's InitInstance function. You also need the TRACEWIN applet
// itself, which you can download from any MSJ bulletin board. NOTE: since 
// TraceWin.h contains code, you should only #include it in once place in
// your app. (Don't #include it in stdafx.h.)
//
// NOTE: I would have defined a static instance to initialize MfxTrace, so
// calling MfxTraceInit would be unecessary, but there's a problem with the
// order of intializations. CFileTrace requires that afxDump be initialized
// first, which can fail to happen if CFileTrace is initialized as a static
// object. Instead, I instantiate the object as a static inside MfxTraceInit.
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
// 9-26-96:  Implemented new DLL scheme. MfxTraceInit no longer required!

#ifdef _DEBUG

//////////////////
// This class loads the TRACEWIN DLL when instantiated.
//
class CLoadTraceWin {
public:
	CLoadTraceWin() {
		GetModuleHandle(NULL);	// Why ??? 
		LoadLibrary("TRWINDLL.DLL");
	}
} __LoadIt; // instantiate to load!


#endif // _DEBUG

