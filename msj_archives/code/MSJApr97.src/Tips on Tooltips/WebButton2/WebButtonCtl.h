// WebButtonCtl.h : Declaration of the CWebButtonCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl : See WebButtonCtl.cpp for implementation.

class CWebButtonCtrl : public COleControl
{
	DECLARE_DYNCREATE(CWebButtonCtrl)

// Constructor
public:
	CWebButtonCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebButtonCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

// Implementation
protected:
	CBitmap m_Bitmap;

	~CWebButtonCtrl();
	void RelayToolTipEvent(const MSG* pMsg);

	DECLARE_OLECREATE_EX(CWebButtonCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CWebButtonCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CWebButtonCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CWebButtonCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);
	LRESULT OnOcmDrawItem(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CWebButtonCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	BOOL OnToolNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CWebButtonCtrl)
	BOOL m_bToolTipEnabled;
	afx_msg void OnToolTipEnabledChanged();
	CString m_strToolTipText;
	afx_msg void OnToolTipTextChanged();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CWebButtonCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CWebButtonCtrl)
	dispidToolTipEnabled = 1L,
	dispidToolTipText = 2L,
	//}}AFX_DISP_ID
	};
};
