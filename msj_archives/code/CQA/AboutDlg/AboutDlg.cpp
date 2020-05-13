////////////////////////////////////////////////////////////////
// ABOUTDLG Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// ABOUTDLG illustrates how to use CStaticLink to implement an About
// dialog with a web link in it.

#include "StdAfx.h"
#include "Resource.h"
#include "StatLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////
// Standard main frame class
//
class CMainFrame : public CFrameWnd {
protected:
	DECLARE_DYNAMIC(CMainFrame)
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

/////////////////
// Standard app class
//
class CMyApp : public CWinApp {
public:
	CMyApp();
protected:
	DECLARE_DYNAMIC(CMyApp)
	virtual BOOL InitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////
// CMyApp implementation
//
CMyApp theApp;

IMPLEMENT_DYNAMIC(CMyApp, CWinApp)

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()

CMyApp::CMyApp()
{
}

//////////////////
// Standard InitInstance
//
BOOL CMyApp::InitInstance()
{
   // Create main frame window (don't use doc/view stuff)
   // 
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;
   pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();
   m_pMainWnd = pMainFrame;

	return TRUE;
}

//////////////////
// Custom about dialog uses CStaticLink for hyperlinks.
//    * for text control, URL is specified as text in dialog editor
//    * for icon control, URL is specified by setting m_iconLink.m_link
//
class CAboutDlg : public CDialog {
public:
	CAboutDlg() : CDialog(IDD_ABOUTBOX) { }

protected:
	CStaticLink m_textLink;		// static text
	CStaticLink m_iconLink;		// static icon

	//////////////////
	// Initialize dialog: subclass static controls
	//
	virtual BOOL OnInitDialog() {
		m_textLink.SubclassDlgItem(IDC_URLTEXT, this);
		m_iconLink.SubclassDlgItem(IDC_URLICON, this);
		m_iconLink.m_link = _T("http://www.microsoft.com/msj");
		return CDialog::OnInitDialog();
	}
};

//////////////////
// Handle Help | About : run the About dialog
//
void CMyApp::OnAppAbout()
{
	CAboutDlg().DoModal();
}

////////////////////////////////////////////////////////////////
// CMainFrame implementation
//
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] = {
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))) {
		TRACE("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	return 0;
}
