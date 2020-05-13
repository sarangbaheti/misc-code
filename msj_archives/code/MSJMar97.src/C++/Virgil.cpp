////////////////////////////////////////////////////////////////
// VIRGIL Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// VIRGIL illustrates how to implement a bitmap with arbitrarily shaped
// "hot" regions that are detectable by clicking. It also shows how to
// use tooltips in your main window.
//
// Compiles with VC++ 4.1 or later.

#include "stdafx.h"
#include "Virgil.h"
#include "mainfrm.h"
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()

CMyApp::CMyApp()
{
}

CMyApp theApp;

//////////////////
// Standard initialization. No doc/view.
//
BOOL CMyApp::InitInstance()
{
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;
   pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();
   m_pMainWnd = pMainFrame;
	return TRUE;
}

//////////////////
// Generic Dib Control is like static,
// but paints DIB with true colors.
//
class CDibCtl : public CStatic {
protected:
	DECLARE_DYNAMIC(CDibCtl);
	CDib m_dib;
public:
	CDibCtl(UINT nID);
	CPalette* GetPalette() { return m_dib.GetPalette(); }
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

IMPLEMENT_DYNAMIC(CDibCtl, CStatic);

BEGIN_MESSAGE_MAP(CDibCtl, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

//////////////////
// Constructor: Load DIB from resource
//
CDibCtl::CDibCtl(UINT nID)
{
	m_dib.Load(AfxGetResourceHandle(), nID);
}

//////////////////
// Paint the DIB. Should really take into account
// all the stytes here (sunken, raised, etc.)
//
void CDibCtl::OnPaint()
{
	CPaintDC dc(this);
	m_dib.Draw(dc);
}

//////////////////
// About dialog with DIB in it.
//
class CAboutDlg : public CDialog {
	CPalMsgHandler m_palMsgHandler; // handles palette messages
	CDibCtl m_ctlDib;					  // DIB control
public:
	CAboutDlg() : CDialog(IDD_ABOUTBOX), m_ctlDib(IDB_BITMAP1) { }
	virtual BOOL OnInitDialog();
};

//////////////////
// Dialog created:
// - subclass DIB control
// - install palette handler
//
// The palette handler will realize the DIB's palette in the foreground
// whenever the dialog gains focus, and in the background whenever the
// parent window gets WM_PALETTECHANGED. Only because the CMainFrame also
// has a CPalMsgHandler in it--which it already does to draw the image.
// If your mainframe doesn't have a CPalMsgHandler to draw a bitmap, you must
// add one to propagate palette messages to any child dialogs it may create.
//
BOOL CAboutDlg::OnInitDialog()
{
	BOOL bRet = CDialog::OnInitDialog();
	m_ctlDib.SubclassDlgItem(IDB_BITMAP1, this);
	m_palMsgHandler.Install(this, m_ctlDib.GetPalette());
	return bRet;
}

//////////////////
// About command: run the About dialog
//
void CMyApp::OnAppAbout()
{
	CAboutDlg().DoModal();
}
