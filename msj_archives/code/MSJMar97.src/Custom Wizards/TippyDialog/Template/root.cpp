// $$root$$.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "$$root$$.h"

#include "MainFrm.h"
#include "$$root$$Doc.h"
#include "$$root$$View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App

BEGIN_MESSAGE_MAP(C$$Safe_root$$App, CWinApp)
	//{{AFX_MSG_MAP(C$$Safe_root$$App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App construction

C$$Safe_root$$App::C$$Safe_root$$App()
{
	m_dialog = NULL;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only C$$Safe_root$$App object

C$$Safe_root$$App theApp;

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App initialization

BOOL C$$Safe_root$$App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(C$$Safe_root$$Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(C$$Safe_root$$View));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Concerning what's going on here with tooltips in dialogs, see Q135873

BOOL C$$Safe_root$$App::ProcessMessageFilter(int code, LPMSG lpMsg)
	{
	if (m_dialog && m_tip
		&& (lpMsg->hwnd == m_dialog->m_hWnd || ::IsChild(m_dialog->m_hWnd, lpMsg->hwnd)))
		
		m_tip->RelayEvent(lpMsg);
	
	return CWinApp::ProcessMessageFilter(code, lpMsg);
	}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CTippyDialog::CTippyDialog(UINT id, CWnd* parent) : CDialog(id, parent)
	{							// CTippyDialog::CTippyDialog
	}							// CTippyDialog::CTippyDialog

BOOL CTippyDialog::OnInitDialog()
	{							// CTippyDialog::OnInitDialog
	CDialog::OnInitDialog();
	theApp.m_dialog = this;
	theApp.m_tip = &m_tip;
	m_tip.Create(this);
	EnumChildWindows(m_hWnd, EnumChildProc, (LPARAM) this);
	m_tip.Activate(TRUE);
	return TRUE;
	}							// CTippyDialog::OnInitDialog

BOOL CALLBACK CTippyDialog::EnumChildProc(HWND hwnd, LPARAM lParam)
	{							// CTippyDialog::EnumChildProc
	CTippyDialog* me = (CTippyDialog*) lParam;
	char classname[64];
	GetClassName(hwnd, classname, sizeof(classname));
	if (stricmp(classname, "STATIC") == 0)
		return TRUE;			// ignore static controls
	UINT id = GetWindowLong(hwnd, GWL_ID);

	TOOLINFO ti;
	memset(&ti, 0, sizeof(ti));
	ti.cbSize = sizeof(ti);
	ti.hwnd = me->m_hWnd;				// owner of the tool
	ti.uFlags = TTF_IDISHWND;			// indicates uID is an HWND
	ti.uId = (UINT) hwnd;				// window containing the tool
	ti.hinst = AfxGetResourceHandle();	// where to find string resource
	ti.lpszText = MAKEINTRESOURCE(id);	// tip text
	me->m_tip.SendMessage(TTM_ADDTOOL, 0, (LPARAM) &ti);

	return TRUE;
	}							// CTippyDialog::EnumChildProc

void CTippyDialog::PostNcDestroy() 
	{							// CTippyDialog::PostNcDestroy
	CDialog::PostNcDestroy();
	theApp.m_dialog = NULL;
	theApp.m_tip = NULL;
	}							// CTippyDialog::PostNcDestroy

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CTippyDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CTippyDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void C$$Safe_root$$App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App commands
