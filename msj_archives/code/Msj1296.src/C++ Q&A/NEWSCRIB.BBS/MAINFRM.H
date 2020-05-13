////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation.
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See SCRIBBLE.CPP for Description of program.
//
class CMainFrame : public CFrameWnd {
   DECLARE_DYNCREATE(CMainFrame)
public:
   CMainFrame();
   virtual ~CMainFrame();
protected:
   CStatusBar  m_wndStatusBar;
   CToolBar    m_wndToolBar;
   //{{AFX_MSG(CMainFrame)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};















