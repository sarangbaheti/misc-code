// ThreadDBCtl.h : Declaration of the CThreadDBCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl : See ThreadDBCtl.cpp for implementation.

class CThreadDBCtrl : public COleControl
{
	DECLARE_DYNCREATE(CThreadDBCtrl)

	friend class CSearchThread ;

// Constructor
public:
	CThreadDBCtrl();

	CSearchThread *	m_pSearchThread ;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadDBCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CThreadDBCtrl();

	DECLARE_OLECREATE_EX(CThreadDBCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CThreadDBCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CThreadDBCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CThreadDBCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CThreadDBCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CThreadDBCtrl)
	afx_msg BOOL StartSearch(long SocialSecurityNumber);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CThreadDBCtrl)
	void FireSearchFinished(LPDISPATCH ClientObj)
		{FireEvent(eventidSearchFinished,EVENT_PARAM(VTS_DISPATCH), ClientObj);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CThreadDBCtrl)
	dispidStartSearch = 1L,
	eventidSearchFinished = 1L,
	//}}AFX_DISP_ID
	};
};
