////////////////////////////////////////////////////////////////
// TRACEWIN Copyright 1995-1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// Implementation of TRACEWIN applet. This is the applet sits around
// and waiting for WM_COPYDATA messages from other apps using TRACEWIN.
//
#include "StdAfx.h"
#include "MainFrm.h"
#include "WinPlace.h"
#include "resource.h"

/////////////////
// Application class
//
class CTraceWinApp : public CWinApp {
public:
	CTraceWinApp();
	~CTraceWinApp();
	virtual BOOL InitInstance();
	virtual int  ExitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

CTraceWinApp NEAR theApp;

BEGIN_MESSAGE_MAP(CTraceWinApp, CWinApp)
	//{{AFX_MSG_MAP(CTraceWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Functions in TrWinDll.cpp
BOOL MfxTraceDllInit();			
BOOL MfxTraceDllTerm();

CTraceWinApp::CTraceWinApp()
{
}

CTraceWinApp::~CTraceWinApp()
{
}

//////////////////
// TRACEWIN applet starting up.
//
BOOL CTraceWinApp::InitInstance()
{
	// Save settings in registry, not INI file
	SetRegistryKey("MSJ");

   // Create main frame window (don't use doc/view)
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;

	// Load window position from profile
	CWindowPlacement wp;
	if (!wp.Restore(CMainFrame::REGKEY, "MainWindow", pMainFrame))
		pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();
   m_pMainWnd = pMainFrame;

	// Inject TrWinDll into all processes
	int nErr = MfxTraceDllInit();
	if (nErr) {
		AfxMessageBox(nErr==1? "Can't run multiple instances of TRACEWIN."
			: "Error injecting DLL. Tracing not enabled.",
			MB_OK|MB_ICONEXCLAMATION);
	}
	return (nErr!=1);
}

/////////////////
// TRACEWIN applet closed: remove DLL from all processes
//
int CTraceWinApp::ExitInstance()
{
	MfxTraceDllTerm(); // un-inject DLL
	return CWinApp::ExitInstance();
}

void CTraceWinApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX).DoModal();
}
