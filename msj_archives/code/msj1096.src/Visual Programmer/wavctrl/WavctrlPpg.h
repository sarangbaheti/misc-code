// WavctrlPpg.h : Declaration of the CWavctrlPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CWavctrlPropPage : See WavctrlPpg.cpp.cpp for implementation.

class CWavctrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CWavctrlPropPage)
	DECLARE_OLECREATE_EX(CWavctrlPropPage)

// Constructor
public:
	CWavctrlPropPage();

// Dialog Data
	//{{AFX_DATA(CWavctrlPropPage)
	enum { IDD = IDD_PROPPAGE_WAVCTRL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CWavctrlPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
