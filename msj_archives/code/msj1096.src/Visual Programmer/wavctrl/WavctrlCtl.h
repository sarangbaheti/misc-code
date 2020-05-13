// WavctrlCtl.h : Declaration of the CWavctrlCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl : See WavctrlCtl.cpp for implementation.

class CWavctrlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CWavctrlCtrl)

// Constructor
public:
	CWavctrlCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavctrlCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CWavctrlCtrl();

	DECLARE_OLECREATE_EX(CWavctrlCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CWavctrlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CWavctrlCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CWavctrlCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CWavctrlCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CWavctrlCtrl)
	afx_msg void Play(LPCTSTR lpWAV);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CWavctrlCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CWavctrlCtrl)
	dispidPlay = 1L,
	//}}AFX_DISP_ID
	};
};
