// DTDemoView.h : interface of the CDTDemoView class
//
/////////////////////////////////////////////////////////////////////////////

class CDTDemoView : public CView
{
protected: // create from serialization only
	CDTDemoView();
	DECLARE_DYNCREATE(CDTDemoView)

// Attributes
public:
	CDTDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDTDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CToolTipCtrl m_ToolTip;
	const CCircle* m_pCircleHit; // The current circle hit by mouse

	const CCircle* HitTest(const CPoint& Point);

// Generated message map functions
protected:
	//{{AFX_MSG(CDTDemoView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	BOOL OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DTDemoView.cpp
inline CDTDemoDoc* CDTDemoView::GetDocument()
   { return (CDTDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
