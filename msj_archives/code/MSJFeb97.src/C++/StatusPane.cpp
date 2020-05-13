////////////////////////////////////////////////////////////////
// StatusPane Copyright 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// StatusPane illustrates how to create a program with
// popped-out (instead of pushed-in) status bar panes.
// All the action is in MainFrm.cpp
// 
#include "stdafx.h"
#include "StatusPane.h"
#include "mainfrm.h"

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
