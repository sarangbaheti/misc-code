////////////////////////////////////////////////////////////////
// ShareEdit 199y Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See doc.cpp

#include "StdAfx.h"
#include "ShareEdit.h"
#include "MainFrm.h"
#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW,  CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CMyApp theApp;

CMyApp::CMyApp()
{
}

BOOL CMyApp::InitInstance()
{
	SetRegistryKey("MSJ");		// Save settings in registry, not INI file
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

#ifdef _MDIAPP
	AddDocTemplate(new CMultiDocTemplate(IDR_MYDOCTYPE,
		RUNTIME_CLASS(CSharedDoc),
		RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CMyView)));
#else
	AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CSharedDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CMyView)));
#endif

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

#ifdef _MDIAPP
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
#endif

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

#ifdef _MDIAPP
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
#endif

	return TRUE;
}

void CMyApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX).DoModal();
}
