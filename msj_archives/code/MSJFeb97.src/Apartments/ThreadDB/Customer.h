// Customer.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCustomer command target

class CCustomer : public CCmdTarget
{
	DECLARE_DYNCREATE(CCustomer)


// Attributes
public:
	CCustomer();           // protected constructor used by dynamic creation
	CCustomer(LPTSTR , LPTSTR , long ) ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomer)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCustomer();

	// Generated message map functions
	//{{AFX_MSG(CCustomer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCustomer)
	CString m_lastName;
	afx_msg void OnLastNameChanged();
	CString m_firstName;
	afx_msg void OnFirstNameChanged();
	long m_socialSecurityNumber;
	afx_msg void OnSocialSecurityNumberChanged();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
