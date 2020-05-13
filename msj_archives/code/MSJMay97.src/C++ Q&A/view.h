////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.2 on Windows 95
// See view.cpp
//

class CMyFormView : public CFormView {
private:
	DECLARE_DYNCREATE(CMyFormView)
	CMyFormView();
	CBitmap	m_bmDents;		// background bitmap (dents)
	CBitmap	m_bmMarble;		// background bitmap (marble)

	CBrush	m_brDents;		// pattern brush (dents)
	CBrush	m_brCyan;		// solid cyan brush (for marble)
	CBrush	m_brHollow;		// hollow brush

	CSize		m_szMarble;		// size of marble bitmap (for tiling)
	UINT		m_nWhich;		// whether to display marble or dents
	BOOL		m_bEditToo;		// paint edit controls too?

public:
	virtual ~CMyFormView();
	CMyDoc* GetDocument()	{ return (CMyDoc*)m_pDocument; }

protected:
	DECLARE_MESSAGE_MAP()

	//{{AFX_MSG(CMyFormView)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL	OnViewWhich(UINT nId);
	afx_msg void	OnUpdateViewWhich(CCmdUI* pCmdUI);
	afx_msg void	OnViewEditToo();
	afx_msg void	OnUpdateViewEditToo(CCmdUI* pCmdUI);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg void	OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
};
