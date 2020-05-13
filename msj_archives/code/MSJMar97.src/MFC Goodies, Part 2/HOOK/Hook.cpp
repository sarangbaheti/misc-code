////////////////////////////////////////////////////////////////
// HOOK Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// HOOK illustrates how to use CMsgHook to hook a window's messages.
// 
#include "StdAfx.h"
#include "Hook.h"
#include "MainFrm.h"
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CApp NEAR theApp;

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CApp::CApp()
{
}

BOOL CApp::InitInstance()
{
   // Create main frame window (don't use doc/view stuff)
   // 
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;
   pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();
   m_pMainWnd = pMainFrame;

	return TRUE;
}

void CApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX, m_pMainWnd).DoModal();
}
