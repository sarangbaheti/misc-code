// Demo40Ppg.h : Declaration of the CDemo40PropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CDemo40PropPage : See Demo40Ppg.cpp.cpp for implementation.

class CDemo40PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CDemo40PropPage)
	DECLARE_OLECREATE_EX(CDemo40PropPage)

// Constructor
public:
	CDemo40PropPage();

// Dialog Data
	//{{AFX_DATA(CDemo40PropPage)
	enum { IDD = IDD_PROPPAGE_DEMO40 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CDemo40PropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
