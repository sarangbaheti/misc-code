////////////////////////////////////////////////////////////////
// MTREE Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// MTREE illustrates how to implement a tree control that supports
// multiple selection. The control is in multree.[h,cpp]. MTREE
// displays a dialog to test the tree control.
// 
// Compiles with VC++ 4.1.

#include "stdafx.h"
#include "mtree.h"
#include "dlg.h"
#include "tracewin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CApp NEAR theApp;

BEGIN_MESSAGE_MAP(CApp, CWinApp)
   //{{AFX_MSG_MAP(CApp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CApp::CApp()
{
}

BOOL CApp::InitInstance()
{
   MfxTraceInit();
   CMyDialog dlg;
   m_pMainWnd = &dlg;
   int nResponse = dlg.DoModal();
   if (nResponse == IDOK) {
      // TODO: Place code here to handle when the dialog is
      //  dismissed with OK
   } else if (nResponse == IDCANCEL) {
      // TODO: Place code here to handle when the dialog is
      //  dismissed with Cancel
   }

   // Since the dialog has been closed, return FALSE so that we exit the
   //  application, rather than start the application's message pump.
   return FALSE;
}
