////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#include "PalHook.h"

//////////////////
// DIB view class. A scroll view that draws DIBs and realizes palettes.
//
class CDIBView : public CScrollView {
public:
	DECLARE_DYNCREATE(CDIBView)
	CDIBView();
	virtual ~CDIBView();

	CDIBDoc* GetDocument()	{ return (CDIBDoc*)m_pDocument; }
	CDib* GetDIB();
	void SetZoom(int iZoom);

protected:
	static CFont g_font;	// current display font, global for all views
	CPalMsgHandler m_palMsgHandler;	// handles palette messages
	CRect	m_rcDIB;			// bitmap rectangle (zoomed)
	CRect	m_rcText;		// text rectangle to format BITMAPINFO
	int	m_iZoom;			// current zoom factor
	BOOL	m_bSized;		// first-time sized or not?
	BOOL	m_bUseDrawDib;	// whether to use DrawDib for drawing

	void DrawBITMAPHEADER(CDC& dc, CDib* pDIB, CRect& rc, UINT nFormat=0);
	void UpdateScrollSizes();

	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

	DECLARE_MESSAGE_MAP()
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnZoom(UINT nID);
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnFontChange(UINT nID);
	afx_msg void OnDither();
	afx_msg void OnUpdateDither(CCmdUI* pCmdUI);
	afx_msg void OnSizeToFit();
};
