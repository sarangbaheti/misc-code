// $$root$$.h - interface to C$$Safe_root$$App class

#ifndef $$ROOT$$_H
#define $$ROOT$$_H

#include "resource.h"

#ifndef arraysize
#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

///////////////////////////////////////////////////////////////////////////////

class C$$Safe_root$$App : public CWinApp
{								// class C$$Safe_root$$App
public:
	//{{AFX_VIRTUAL(C$$Safe_root$$App)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(C$$Safe_root$$App)
	afx_msg void OnHelpAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};								// class C$$Safe_root$$App

/////////////////////////////////////////////////////////////////////////////

class CAboutBox : public CDialog
{
public:
	CAboutBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutBox)
	enum { IDD = IDD_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutBox)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // $$ROOT$$_H
