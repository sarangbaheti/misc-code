////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//

#ifdef _MDI
#define CBaseFrameWnd CMDIFrameWnd
#else
#define CBaseFrameWnd CFrameWnd
#endif

////////////////
// Palette-handling main frame window
//
class CMainFrame : public CBaseFrameWnd {
public:
	CMainFrame();
	virtual ~CMainFrame();
protected:
	DECLARE_DYNCREATE(CMainFrame)
	CStatusBar	m_wndStatusBar;	// status bar
	CToolBar		m_wndToolBar;		// tool (button) bar

	DECLARE_MESSAGE_MAP()
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaletteChanged(CWnd* pFoucsWnd);
	afx_msg BOOL OnQueryNewPalette();
};
