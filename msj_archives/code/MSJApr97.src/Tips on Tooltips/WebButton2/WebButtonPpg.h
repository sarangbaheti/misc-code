// WebButtonPpg.h : Declaration of the CWebButtonPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CWebButtonPropPage : See WebButtonPpg.cpp.cpp for implementation.

class CWebButtonPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CWebButtonPropPage)
	DECLARE_OLECREATE_EX(CWebButtonPropPage)

// Constructor
public:
	CWebButtonPropPage();

// Dialog Data
	//{{AFX_DATA(CWebButtonPropPage)
	enum { IDD = IDD_PROPPAGE_WEBBUTTON };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CWebButtonPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
