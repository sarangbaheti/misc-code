////////////////
// Main fram handles sizing and overrides RecalcLayout
// to move view so that form appears centered.
//
class CMainFrame : public CFrameWnd {
public:
   virtual ~CMainFrame();

protected:
   DECLARE_DYNCREATE(CMainFrame)
   CStatusBar  m_wndStatusBar;   // sataus bar window, as normal
   CToolBar    m_wndToolBar;     // ditto for tool bar

   // Following two are new CFORM stuff
   CRect       m_rcNormalView;   // rectangle for normal (MFC) view pos
   BOOL        m_bCenterForm;    // whether to center the form
   BOOL        m_bFixPaint;      // whether to fix painting
   
   CMainFrame();

   // override to center form
   virtual void RecalcLayout(BOOL bNotify = TRUE);

   //{{AFX_MSG(CMainFrame)
   afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnPaint(); // override required to paint rectangles.
   afx_msg void OnCenterForm();
   afx_msg void OnUpdateCenterForm(CCmdUI* pCmdUI);
   afx_msg void OnFixPaint();
   afx_msg void OnUpdateFixPaint(CCmdUI* pCmdUI);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
