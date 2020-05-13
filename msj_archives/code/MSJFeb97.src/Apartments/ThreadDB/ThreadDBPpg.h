// ThreadDBPpg.h : Declaration of the CThreadDBPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CThreadDBPropPage : See ThreadDBPpg.cpp.cpp for implementation.

class CThreadDBPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CThreadDBPropPage)
	DECLARE_OLECREATE_EX(CThreadDBPropPage)

// Constructor
public:
	CThreadDBPropPage();

// Dialog Data
	//{{AFX_DATA(CThreadDBPropPage)
	enum { IDD = IDD_PROPPAGE_THREADDB };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CThreadDBPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
