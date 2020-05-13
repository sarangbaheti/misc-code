// $$root$$View.h : interface of the C$$Safe_root$$View class
//
/////////////////////////////////////////////////////////////////////////////

class C$$Safe_root$$View : public CView
{
protected: // create from serialization only
	C$$Safe_root$$View();
	DECLARE_DYNCREATE(C$$Safe_root$$View)

// Attributes
public:
	C$$Safe_root$$Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C$$Safe_root$$View)
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
	virtual ~C$$Safe_root$$View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C$$Safe_root$$View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in $$root$$View.cpp
inline C$$Safe_root$$Doc* C$$Safe_root$$View::GetDocument()
   { return (C$$Safe_root$$Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
