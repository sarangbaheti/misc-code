////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.2 on Windows 95
// See pform.cpp
// 
class CMainFrame : public CFrameWnd {
public:
	virtual ~CMainFrame();

protected:
	DECLARE_DYNCREATE(CMainFrame)
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CMainFrame();
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
