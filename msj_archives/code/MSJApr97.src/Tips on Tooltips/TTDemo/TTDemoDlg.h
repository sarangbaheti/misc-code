// TTDemoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTTDemoDlg dialog

#include "TitleTipListBox.h"
#include "ODListBox.h"

class CTTDemoDlg : public CDialog
{
// Construction
public:
	CTTDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTTDemoDlg)
	enum { IDD = IDD_TTDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CTitleTipListBox m_RegListBox; // Regular listbox
	CODListBox m_ODListBox; // Owner-draw listbox

	// Generated message map functions
	//{{AFX_MSG(CTTDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
