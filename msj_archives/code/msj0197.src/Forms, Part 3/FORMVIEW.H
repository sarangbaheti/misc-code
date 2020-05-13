// formview.h : interface of the CFormsView class
//
/////////////////////////////////////////////////////////////////////////////

class CFormsView : public CView
{
protected: // create from serialization only
	CFormsView();
	DECLARE_DYNCREATE(CFormsView)

// Attributes
public:
	CFormsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFormsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFormsView)
	afx_msg void OnTest();
	afx_msg void OnReport();
	afx_msg void OnModifyString();
	afx_msg void OnModifyCtrl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in formsView.cpp
inline CFormsDoc* CFormsView::GetDocument()
   { return (CFormsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
