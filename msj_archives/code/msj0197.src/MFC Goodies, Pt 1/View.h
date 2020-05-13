////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//

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

protected:
	BOOL	m_bDither; // whether to dither the image

	// Overrides
	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();

	int DoRealizePalette(BOOL bForeground); // helper to realize the palette

	DECLARE_MESSAGE_MAP()
	afx_msg void OnDither();
	afx_msg void OnUpdateDither(CCmdUI* pCmdUI);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};
