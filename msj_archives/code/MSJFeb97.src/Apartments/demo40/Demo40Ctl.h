// Demo40Ctl.h : Declaration of the CDemo40Ctrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl : See Demo40Ctl.cpp for implementation.

class CDemo40Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CDemo40Ctrl)

// Constructor
public:
	CDemo40Ctrl();

// Overrides

	// Drawing function
	virtual void OnDraw(
				CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);

	// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);

	// Reset control state
	virtual void OnResetState();

// Implementation
protected:
	~CDemo40Ctrl();

	DECLARE_OLECREATE_EX(CDemo40Ctrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CDemo40Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDemo40Ctrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CDemo40Ctrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CDemo40Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CDemo40Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CDemo40Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CDemo40Ctrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};
