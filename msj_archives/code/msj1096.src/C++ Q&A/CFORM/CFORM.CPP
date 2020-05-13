////////////////////////////////////////////////////////////////
// CFORM Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// CFORM illustrates how to center the controls in a CFormView.
// Interesting stuff is in mainfrm.cpp.
// Compiles with VC++ 4.0 or later.

#include "stdafx.h"
#include "cform.h"
#include "mainfrm.h"
#include "doc.h"
#include "view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
   //{{AFX_MSG_MAP(CMyApp)
   ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
   //}}AFX_MSG_MAP
   ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
   ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CMyApp::CMyApp()
{
}

CMyApp theApp;

BOOL CMyApp::InitInstance()
{
   CSingleDocTemplate* pDocTemplate;
   pDocTemplate = new CSingleDocTemplate(
      IDR_MAINFRAME,
      RUNTIME_CLASS(CMyDoc),
      RUNTIME_CLASS(CMainFrame),       // main SDI frame window
      RUNTIME_CLASS(CMyFormView));
   AddDocTemplate(pDocTemplate);

   CCommandLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);
   if (!ProcessShellCommand(cmdInfo))
      return FALSE;

   return TRUE;
}

void CMyApp::OnAppAbout()
{
   CDialog(IDD_ABOUTBOX).DoModal();
}
