////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.1 on Windows 95
// See ShadeCap.cpp

/////////////////
// Mainframe that draws shaded caption a la Excel 95
//
class CMainFrame : public CFrameWnd {
public:
	CMainFrame();
	virtual ~CMainFrame();

protected:
	DECLARE_DYNCREATE(CMainFrame)
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	// Stuff for painting custom title bar:
	CFont		m_fontCaption;			// normal system font for active caption
	CFont		m_fontAcme;				// "ACME" company font (same active/inactive)
	BOOL		m_bActive;				// whether active or not;
	CRect		m_rcCaption;			// caption rectangle
	CBitmap	m_bmCaption[2];		// bitmap captions active/inactive

	// Override 
	void OnUpdateFrameTitle(BOOL bAddToTitle);

	// Helpers
	CString	GetDocTitle();
	void		PaintCaption(BOOL bActive);
	void		PaintCaption() { PaintCaption(m_bActive); }
	void		CreateFonts();
	CBitmap* GetCaptionBitmap(BOOL bActive);

	//{{AFX_MSG(CMainFrame)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnSysColorChange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSettingChange(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

