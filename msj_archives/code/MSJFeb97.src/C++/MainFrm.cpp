////////////////////////////////////////////////////////////////
// Copyright 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.1 on Windows 95
//
// Illustrates how to create a program with popped-out (instead of pushed-in)
// status bar panes.
// 
#include "stdafx.h"
#include "StatusPane.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
   //{{AFX_MSG_MAP(CMainFrame)
   ON_WM_CREATE()
   ON_COMMAND(ID_STATUS_BAR_IN,  OnStatusBarIn)
   ON_COMMAND(ID_STATUS_BAR_OUT, OnStatusBarOut)
   ON_UPDATE_COMMAND_UI(ID_STATUS_BAR_IN,  OnUpdateStatusBarIn)
   ON_UPDATE_COMMAND_UI(ID_STATUS_BAR_OUT, OnUpdateStatusBarOut)
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_CAPS, OnUpdateIndicator)
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_NUM,  OnUpdateIndicator)
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_SCRL, OnUpdateIndicator)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] = {
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
   m_bStatusBarOut = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
      return -1;

   // Create toolbar
   if (!m_wndToolBar.Create(this) ||
      !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   // Create status bar
   if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators,
        sizeof(indicators)/sizeof(UINT))) {
      TRACE("Failed to create status bar\n");
      return -1;      // fail to create
   }

   // You could also set the status bar pane styles here

   return 0;
}

//////////////////
// Status Bar In/Status Bar Out commands just toggle a flag
//
void CMainFrame::OnStatusBarIn()
{
   m_bStatusBarOut = FALSE;
}
void CMainFrame::OnStatusBarOut()
{
   m_bStatusBarOut = TRUE;
}

////////////////
// Set radio button on whichever command is currently in effect.
//
void CMainFrame::OnUpdateStatusBarIn(CCmdUI *pCmdUI)
{
   pCmdUI->SetRadio(!m_bStatusBarOut);
}
void CMainFrame::OnUpdateStatusBarOut(CCmdUI *pCmdUI)
{
   pCmdUI->SetRadio(m_bStatusBarOut);
}

//////////////////
// Update status pane indicator: set the "checked" state.
//
// TRUE  =  MFC draws it popped out
// FALSE =  MFC draws it pushed in
//
void CMainFrame::OnUpdateIndicator(CCmdUI *pCmdUI)
{
   pCmdUI->SetCheck(m_bStatusBarOut);
}
