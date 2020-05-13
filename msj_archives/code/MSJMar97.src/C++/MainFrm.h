////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.1 on Windows 95
// See Virgil.cpp
// 
#include "Dib.h"
#include "PalHook.h" // to handle palette messages

class CMainFrame : public CFrameWnd {
	DECLARE_DYNCREATE(CMainFrame)

public:
	CMainFrame();
	virtual ~CMainFrame();

protected:
	CStatusBar		m_wndStatusBar;	// status bar
	CPalMsgHandler m_palMsgHandler;	// handles palette messages
	CDib				m_dibImage;			// image bitmap
	CDib				m_dibMask;			// mask bitmap
	BOOL				m_bViewMask;		// whether to view mask or dib

	CString GetWhoItIs(CPoint pt) const; // Helper

	// Override for finding tool tip
	virtual int  OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

	DECLARE_MESSAGE_MAP()
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnIndicatorWho(CCmdUI* pCmdUI);
	afx_msg void OnGetTooltipText(NMHDR* pNMHDR, LRESULT* plRes);
	afx_msg void OnViewMaskOrImage();
	afx_msg void OnUpdateViewMaskOrImage(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
};
