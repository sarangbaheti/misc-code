////////////////////////////////////////////////////////////////
// ShadeCap Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// ShadeCap illustrates how to draw your own caption with flicker-free
// painting in Windows 95. ShadeCap draws a shaded caption like the
// Microsoft Office 95 products. Compiles with MFC 4.1 under Windows 95.
//
#include "StdAfx.h"
#include "ShadeCap.h"
#include "MainFrm.h"
#include "Doc.h"
#include "View.h"
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CApp NEAR theApp;

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	//{{AFX_MSG_MAP(CApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CApp::CApp()
{
}

BOOL CApp::InitInstance()
{
	MfxTraceInit();

	SetRegistryKey("MSJ");		// Save settings in registry, not INI file
	LoadStdProfileSettings();  // Standard INI file options (including MRU)

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMyView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	return TRUE;
}

void CApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX, m_pMainWnd).DoModal();
}
