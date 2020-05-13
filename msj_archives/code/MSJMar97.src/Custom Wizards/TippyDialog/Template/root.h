// $$root$$.h : main header file for the $$ROOT$$ application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////////////////
// To build a dialog with tooltips, derive it from CTippyDialog instead of
// CDialog. Change the constructor built by AppWizard to reference this as
// the base class. Don't change the message map. Provide string resources
// with the same IDs as the controls to contain the tip text.

class CTippyDialog : public CDialog
{								// class CTippyDialog
public:
	CTippyDialog(UINT id, CWnd* parent = NULL);

	CToolTipCtrl	m_tip;

	//{{AFX_VIRTUAL(CTippyDialog)
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
};								// class CTippyDialog

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App:
// See $$root$$.cpp for the implementation of this class
//

class C$$Safe_root$$App : public CWinApp
{
public:
	C$$Safe_root$$App();

	CTippyDialog*	m_dialog;		// dialog (with tool tips) currently being displayed
	CToolTipCtrl*	m_tip;			// tool tip control for current dialog

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C$$Safe_root$$App)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg); 
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(C$$Safe_root$$App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
