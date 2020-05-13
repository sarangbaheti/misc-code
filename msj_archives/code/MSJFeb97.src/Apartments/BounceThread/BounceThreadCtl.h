// BounceThreadCtl.h : Declaration of the CBounceThreadCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl : See BounceThreadCtl.cpp for implementation.

class CBounceThread ;

class CBounceThreadCtrl : public COleControl
{
	DECLARE_DYNCREATE(CBounceThreadCtrl)

// Constructor
public:
	CBounceThreadCtrl();

	CBounceThread *m_pThread ;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBounceThreadCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CBounceThreadCtrl();

	DECLARE_OLECREATE_EX(CBounceThreadCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CBounceThreadCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CBounceThreadCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CBounceThreadCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CBounceThreadCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPopupBeepeverysecond();
	afx_msg void OnUpdatePopupBeepeverysecond(CCmdUI* pCmdUI);
	afx_msg void OnPopupPriorityAbove();
	afx_msg void OnUpdatePopupPriorityAbove(CCmdUI* pCmdUI);
	afx_msg void OnPopupPriorityBelow();
	afx_msg void OnUpdatePopupPriorityBelow(CCmdUI* pCmdUI);
	afx_msg void OnPopupPriorityHighest();
	afx_msg void OnUpdatePopupPriorityHighest(CCmdUI* pCmdUI);
	afx_msg void OnPopupPriorityIdle();
	afx_msg void OnUpdatePopupPriorityIdle(CCmdUI* pCmdUI);
	afx_msg void OnPopupPriorityLowest();
	afx_msg void OnUpdatePopupPriorityLowest(CCmdUI* pCmdUI);
	afx_msg void OnPopupPriorityNormal();
	afx_msg void OnUpdatePopupPriorityNormal(CCmdUI* pCmdUI);
	afx_msg void OnPopupPriorityTimecritical();
	afx_msg void OnUpdatePopupPriorityTimecritical(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CBounceThreadCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CBounceThreadCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CBounceThreadCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};
