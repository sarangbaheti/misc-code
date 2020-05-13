// bounceth.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CBounceThread thread


#define	WM_GOTOSLEEP	WM_USER + 0x100 
#define WM_WAITMUTEX	WM_USER + 0x101
#define WM_RELEASEMUTEX	WM_USER + 0x102
#define	WM_WAITSEMAPHORE	WM_USER + 0x103
#define	WM_RELEASESEMAPHORE	WM_USER + 0x104

#define WM_WAITMANUAL	WM_USER + 0x105
#define WM_WAITAUTO		WM_USER + 0x106
#define	WM_WAITEITHER	WM_USER + 0x107
#define WM_WAITBOTH		WM_USER + 0x108


class CBounceThread : public CWinThread
{
	DECLARE_DYNCREATE(CBounceThread)

protected:

	CBounceThread();           // protected constructor used by dynamic creation

	CBrush		m_Brush ;


	int m_HorzDir ;
	int m_VertDir ;
	int m_xPos ;
	int m_yPos ;

// Attributes
public:

	COleControl	*m_pControl ;
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBounceThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBounceThread();

	// Generated message map functions
	//{{AFX_MSG(CBounceThread)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
