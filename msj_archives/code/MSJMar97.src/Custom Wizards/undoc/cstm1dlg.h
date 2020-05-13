// cstm1dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog

class CCustom1Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom1Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom1Dlg)
	enum { IDD = IDD_CUSTOM1 };
	CButton	m_ctlTooltips;
	CButton	m_ctlIndicators;
	CButton	m_ctlDockable;
	BOOL	m_datapane;
	BOOL	m_dockable;
	BOOL	m_indicators;
	BOOL	m_statusbar;
	BOOL	m_stdpane;
	BOOL	m_toolbar;
	BOOL	m_tooltips;
	BOOL	m_treepane;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRect	rcBitmaps;
	CSize	szBitmaps;

	void	EnableControls();
	void	InvalidateBitmap();

	// Generated message map functions
	//{{AFX_MSG(CCustom1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnStatusbar();
	afx_msg void OnToolbar();
	afx_msg void OnPaint();
	afx_msg void OnDatapane();
	afx_msg void OnStdpane();
	afx_msg void OnTreepane();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
