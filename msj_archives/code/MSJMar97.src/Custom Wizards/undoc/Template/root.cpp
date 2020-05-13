// $$root$$.cpp - implementation file

#include "stdafx.h"
#include "$$root$$.h"
#include "mainwnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////

C$$Safe_root$$App theApp;

///////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App

BEGIN_MESSAGE_MAP(C$$Safe_root$$App, CWinApp)
	//{{AFX_MSG_MAP(C$$Safe_root$$App)
	ON_COMMAND(ID_APP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL C$$Safe_root$$App::InitInstance()
	{							// C$$Safe_root$$App::InitInstance
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
	}							// C$$Safe_root$$App::InitInstance

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CAboutBox

CAboutBox::CAboutBox(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutBox::IDD, pParent)
	{							// CAboutBox::CAboutBox	
	//{{AFX_DATA_INIT(CAboutBox)
	//}}AFX_DATA_INIT
	}							// CAboutBox::CAboutBox

void CAboutBox::DoDataExchange(CDataExchange* pDX)
	{							// CAboutBox::DoDataExchange
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutBox)
	//}}AFX_DATA_MAP
	}							// CAboutBox::DoDataExchange

BEGIN_MESSAGE_MAP(CAboutBox, CDialog)
	//{{AFX_MSG_MAP(CAboutBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void C$$Safe_root$$App::OnHelpAbout() 
	{							// C$$Safe_root$$App::OnHelpAbout
	CAboutBox(dlg);
	dlg.DoModal();
	}							// C$$Safe_root$$App::OnHelpAbout
