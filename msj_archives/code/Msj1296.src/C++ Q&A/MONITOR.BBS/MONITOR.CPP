////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.1 on Windows 95
//
// MONITOR shows how to create a main window that is only a title bar,
// and how to prevent Windows from drawing size cursors in up/down or
// left/right directions
//
#include "StdAfx.h"
#include "TraceWin.h"

////////////////
// Remove this comment to see the original bug
//
//#define BUG

//////////////////
// Standard application class
//
class CMonitorApp : public CWinApp {
public:
   CMonitorApp() : CWinApp() { }
   virtual BOOL InitInstance();
};

//////////////////
// Monitor window is main frame
//
class CMonitorWindow : public CFrameWnd {
public:
   CMonitorWindow();
   afx_msg void OnTimer(UINT nIdEvent);
   afx_msg void OnPaint();
   afx_msg UINT OnNcHitTest(CPoint point);
   DECLARE_MESSAGE_MAP()   
};          

CMonitorApp theApp;

//////////////////
// Initialize app: create main window
//
BOOL CMonitorApp::InitInstance()
{
   MfxTraceInit();
   m_pMainWnd = new CMonitorWindow;
   m_pMainWnd->ShowWindow(m_nCmdShow);
   m_pMainWnd->UpdateWindow();
   return TRUE;
}   

BEGIN_MESSAGE_MAP(CMonitorWindow, CFrameWnd)
   ON_WM_TIMER()
   ON_WM_PAINT()
   ON_WM_NCHITTEST()
END_MESSAGE_MAP() 

//////////////////
// Create monitor window. Constructor actually creates window too.
//
CMonitorWindow::CMonitorWindow()
{
   // Compute size of window: smallest to display text
   CString s = _T("Memory: 100%% used [Phys:999999K total/999999K free]");
   CWindowDC dc(NULL);                            // screen DC
   CSize sz = dc.GetTextExtent(s, s.GetLength()); // size of text
   sz.cx += 2*GetSystemMetrics(SM_CXSMICON) +     // plus icon, close box,
      2*GetSystemMetrics(SM_CXSIZEFRAME);         // and sizable frame
   sz.cy += 2*GetSystemMetrics(SM_CYFIXEDFRAME);  // should be SIZEFRAME, but
                                                  // it doesn't matter
   CreateEx(WS_EX_TOPMOST, NULL, NULL,
#ifdef BUG
      // The buggy version uses WS_BORDER to disallow sizing,
      // resulting in a frame that's too narrow.
      WS_BORDER 
#else
      // The fix uses WS_THICKFRAME to get the fat border, but
      // disallows sizing by trapping WM_NCHITTEST
      WS_THICKFRAME
#endif
      | WS_CAPTION | WS_SYSMENU,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      sz.cx,
      sz.cy,
      NULL, 0);

   TRACE("Desired size = %d x %d\n", sz.cx, sz.cy);
   CRect rc;
   GetWindowRect(&rc);
   TRACE("Actual size  = %d x %d\n", rc.Width(), rc.Height());
   GetClientRect(&rc);
   TRACE("Client size  = %d x %d\n", rc.Width(), rc.Height());

   TRACE("Minimum window height = %d\n",  GetSystemMetrics(SM_CYMIN));
   TRACE("Caption height = %d\n",         GetSystemMetrics(SM_CYCAPTION));
   TRACE("Sizable border height   = %d\n",GetSystemMetrics(SM_CYSIZEFRAME));
   TRACE("Non-sizable border height = %d\n",
      GetSystemMetrics(SM_CYFIXEDFRAME));

   SetTimer((UINT) 1, (UINT) 7500, NULL);
   OnTimer(1); // first update immediately
}

//////////////////
// Update the window caption by getting new memory stats
//
void CMonitorWindow::OnTimer(UINT nIdEvent)
{ 
   MEMORYSTATUS ms;
   ms.dwLength = sizeof(MEMORYSTATUS);
   GlobalMemoryStatus(&ms);
   CString s;
   s.Format(_T("Memory: %2ld%% used [Phys:%ldK total/%ldK free]"),
      ms.dwMemoryLoad,
      ms.dwTotalPhys>>10,
      ms.dwAvailPhys>>10);
   SetWindowText(s);
}

//////////////////
// Handle WM_NCCHITTEST:
// Re-map top/bottom to HTBORDER, and corners to HTLEFT or HTRIGHT
//
UINT CMonitorWindow::OnNcHitTest(CPoint point)
{
   UINT nRet = CFrameWnd::OnNcHitTest(point);
#ifndef BUG
   switch (nRet) {
   case HTTOP:
   case HTBOTTOM:
      return HTBORDER;
   case HTTOPLEFT:
   case HTBOTTOMLEFT:
      return HTLEFT;
   case HTTOPRIGHT:
   case HTBOTTOMRIGHT:
      return HTRIGHT;
   }
#endif
   return nRet;
}

//////////////////
// Paint client red to make it contrast more with frame/caption
//
void CMonitorWindow::OnPaint()
{
   CPaintDC dc(this);
   CRect rc;
   GetClientRect(&rc);
   CBrush b(RGB(255,0,0)); // red
   CBrush* pOldBrush = dc.SelectObject(&b);
   dc.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
   dc.SelectObject(pOldBrush);
}
