// Demo42Ppg.h : Declaration of the CDemo42PropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CDemo42PropPage : See Demo42Ppg.cpp.cpp for implementation.

class CDemo42PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CDemo42PropPage)
	DECLARE_OLECREATE_EX(CDemo42PropPage)

// Constructor
public:
	CDemo42PropPage();

// Dialog Data
	//{{AFX_DATA(CDemo42PropPage)
	enum { IDD = IDD_PROPPAGE_DEMO42 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CDemo42PropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
