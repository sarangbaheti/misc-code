// Demo42Ctl.h : Declaration of the CDemo42Ctrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl : See Demo42Ctl.cpp for implementation.

class CDemo42Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CDemo42Ctrl)

// Constructor
public:
	CDemo42Ctrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo42Ctrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CDemo42Ctrl();

	DECLARE_OLECREATE_EX(CDemo42Ctrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CDemo42Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDemo42Ctrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CDemo42Ctrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CDemo42Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CDemo42Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CDemo42Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CDemo42Ctrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};
