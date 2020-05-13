////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// 
#ifdef _MDIAPP
#define CBaseFrameWnd CMDIFrameWnd
#else
#define CBaseFrameWnd CFrameWnd
#endif

//////////////////
// Normal mainframe app
//
class CMainFrame : public CBaseFrameWnd {
public:
	CMainFrame();
	virtual ~CMainFrame();
protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	DECLARE_DYNCREATE(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};
