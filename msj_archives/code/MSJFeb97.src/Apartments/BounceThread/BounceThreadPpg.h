// BounceThreadPpg.h : Declaration of the CBounceThreadPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CBounceThreadPropPage : See BounceThreadPpg.cpp.cpp for implementation.

class CBounceThreadPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CBounceThreadPropPage)
	DECLARE_OLECREATE_EX(CBounceThreadPropPage)

// Constructor
public:
	CBounceThreadPropPage();

// Dialog Data
	//{{AFX_DATA(CBounceThreadPropPage)
	enum { IDD = IDD_PROPPAGE_BOUNCETHREAD };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CBounceThreadPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
