////////////////////////////////////////////////////////////////
// Copyright 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.1 on Windows 95
// See StatusPane.cpp
// 
class CMainFrame : public CFrameWnd {
public:
   CMainFrame();
   virtual ~CMainFrame();
protected:
   DECLARE_DYNAMIC(CMainFrame)
   CStatusBar  m_wndStatusBar;
   CToolBar    m_wndToolBar;
   BOOL        m_bStatusBarOut;

   //{{AFX_MSG(CMainFrame)
   afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnStatusBarIn();
   afx_msg void OnStatusBarOut();
   afx_msg void OnUpdateStatusBarIn(CCmdUI *pCmdUI);
   afx_msg void OnUpdateStatusBarOut(CCmdUI *pCmdUI);
   afx_msg void OnUpdateIndicator(CCmdUI *pCmdUI);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
