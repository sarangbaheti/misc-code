// SearchThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSearchThread thread

class CThreadDBCtrl ;

class CSearchThread : public CWinThread
{
	DECLARE_DYNCREATE(CSearchThread)
protected:
	CSearchThread();           // protected constructor used by dynamic creation

// Attributes
public:

	CPtrArray	m_DispatchArray ;
	CPtrArray	m_StreamArray ;
	CThreadDBCtrl *m_pCtrl ;

	long m_ssn ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSearchThread();

	// Generated message map functions
	//{{AFX_MSG(CSearchThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
