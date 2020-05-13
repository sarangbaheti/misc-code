////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// DIBVIEW is a Device-independent bitmap viewer.
// You can open .DIB or .BMP files and view them
//
#include "StdAfx.h"
#include "DibView.h"
#include "MainFrm.h"
#include "Doc.h"
#include "View.h"
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CApp theApp;

CApp::CApp()
{
}

BOOL CApp::InitInstance()
{
	// Save settings in registry, not INI file
	SetRegistryKey("MSJ");
	LoadStdProfileSettings(8); // 8 files in MRU list

#ifdef _MDI
	AddDocTemplate(new CMultiDocTemplate(IDR_MYDOCTYPE,
		RUNTIME_CLASS(CDIBDoc),
		RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CDIBView)));
#else
	AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CDIBDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CDIBView)));
#endif

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

#ifdef _MDI
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line. Since this is a read-only viewer,
	// don't allow FileNew
	if (cmdInfo.m_nShellCommand!=CCommandLineInfo::FileNew && 
		!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

#else // SDI app
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
#endif

	return TRUE;
}

void CApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX).DoModal();
}
