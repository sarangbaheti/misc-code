////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See ShadeCap.cpp.
// 

////////////////
// Generic MFC Edit View
//
class CMyView : public CEditView {
public:
	CMyView();
	virtual ~CMyView();
protected:
	CFont m_font;
	DECLARE_DYNCREATE(CMyView)
	//{{AFX_MSG(CMyView)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
