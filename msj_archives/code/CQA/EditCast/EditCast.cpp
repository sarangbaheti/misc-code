////////////////////////////////////////////////////////////////
// EditCast 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// EditCast illustrates why it's not safe to cast the return from
// CWnd::GetDlgItem to a CEdit or other kind of window class.
//

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include "resource.h"
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////
// Dialog class that alters the TAB sequence and handles
// the RETURN key.
//
class CMyDialog : public CDialog {
public:
	CMyDialog();
	~CMyDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton();
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////
// Application class
//
class CApp : public CWinApp {
public:
	CApp() { }
	virtual BOOL InitInstance();
} theApp;

/////////////////
// Initialize: just run the dialog and quit.
//
BOOL CApp::InitInstance()
{
	CMyDialog dlg;
	dlg.DoModal();
	return FALSE;
}

////////////////////////////////////////////////////////////////
// CMyDialog
//
BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton)
END_MESSAGE_MAP()

//////////////////
// Construct dialog: set everything to zero or NULL.
//
CMyDialog::CMyDialog() : CDialog(IDD_DIALOG1)
{
}

CMyDialog::~CMyDialog()
{
}

/////////////////
// Initialize dialog: load accelerators and set initial focus.
//
BOOL CMyDialog::OnInitDialog()
{
	return CDialog::OnInitDialog();
}

/////////////////
// Button handler
//
void CMyDialog::OnButton()
{
	// Get the window
	CWnd*		pWnd  = GetDlgItem(IDC_EDIT1);
	ASSERT(pWnd);
	// Demonstrate that pWnd is not an edit control.
	CEdit*	pEdit = dynamic_cast<CEdit*>(pWnd);
	BOOL		bIsEdit = pWnd->IsKindOf(RUNTIME_CLASS(CEdit));
	TRACE("GetDlgItem(IDC_EDIT1) returns CWnd = %p\n", pWnd);
	TRACE("dynamic_cast to CEdit* = %p\n", pEdit);
	TRACE("pWnd->IsKindOf(RUNTIME_CLASS(CEdit)) returns %d\n", bIsEdit);
	
	// But you can treat it as one! (Do this at your own risk)
	pEdit = (CEdit*)pWnd;
	pEdit->SetSel(0, -1);
	pEdit->ReplaceSel("");
	pEdit->SetFocus();
}
