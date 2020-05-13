// cstm1dlg.cpp : implementation file
//

#include "stdafx.h"
#include "undoc.h"
#include "cstm1dlg.h"
#include "undocaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg()
	: CAppWizStepDlg(CCustom1Dlg::IDD)
	{							// CCustom1Dlg::CCustom1Dlg
	//{{AFX_DATA_INIT(CCustom1Dlg)
	m_datapane = FALSE;
	m_dockable = TRUE;
	m_indicators = TRUE;
	m_statusbar = TRUE;
	m_stdpane = TRUE;
	m_toolbar = TRUE;
	m_tooltips = TRUE;
	m_treepane = FALSE;
	//}}AFX_DATA_INIT
	}							// CCustom1Dlg::CCustom1Dlg


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
	{							// Custom1Dlg::DoDataExchange
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Control(pDX, IDB_TOOLTIPS, m_ctlTooltips);
	DDX_Control(pDX, IDB_INDICATORS, m_ctlIndicators);
	DDX_Control(pDX, IDB_DOCKABLE, m_ctlDockable);
	DDX_Check(pDX, IDB_DATAPANE, m_datapane);
	DDX_Check(pDX, IDB_DOCKABLE, m_dockable);
	DDX_Check(pDX, IDB_INDICATORS, m_indicators);
	DDX_Check(pDX, IDB_STATUSBAR, m_statusbar);
	DDX_Check(pDX, IDB_STDPANE, m_stdpane);
	DDX_Check(pDX, IDB_TOOLBAR, m_toolbar);
	DDX_Check(pDX, IDB_TOOLTIPS, m_tooltips);
	DDX_Check(pDX, IDB_TREEPANE, m_treepane);
	//}}AFX_DATA_MAP
	}							// Custom1Dlg::DoDataExchange

CString csprintf(const char* ctl, ...)
	{							// csprintf
	char buffer[512];
	wvsprintf(buffer, ctl, (char*) (&ctl + 1));
	return buffer;
	}							// csprintf

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.

BOOL CCustom1Dlg::OnDismiss()
	{							// CCustom1Dlg::OnDismiss
	if (!UpdateData(TRUE))
		return FALSE;

	#define d Undocaw.m_Dictionary
	#define ds(n,v) d[_T(#n)] = #v
	#define dr(n) d.RemoveKey(_T(#n))

	int numclasses = 0;
	CString paneclass;

	if (m_treepane)
		{						// tree pane included
		ds(treepane, 1);
		paneclass += csprintf("Class%d=CTreePane\n", numclasses+4);
		++numclasses;
		}						// tree pane included
	else
		dr(treepane);

	if (m_datapane)
		{						// tree pane included
		ds(datapane, 1);
		paneclass += csprintf("Class%d=CDataPane\n", numclasses+4);
		++numclasses;
		}						// tree pane included
	else
		dr(datapane);

	if (m_stdpane)
		{						// tree pane included
		ds(stdpane, 1);
		paneclass += csprintf("Class%d=CStdPane\n", numclasses+4);
		++numclasses;
		}						// tree pane included
	else
		dr(stdpane);

	d[_T("numclasses")] = csprintf("%d", numclasses+3);
	d[_T("numpanes")] = csprintf("%d", numclasses);
	d[_T("paneclass")] = paneclass;

	if (numclasses > 1)
		ds(multipane, 1);
	else
		dr(multipane);

	if (m_toolbar)
		{						// toolbar requested
		ds(toolbar, 1);
		
		if (m_dockable)
			ds(dockable, 1);
		else
			dr(dockable);
		
		if (m_tooltips)
			ds(tooltips, 1);
		else
			dr(tooltips);
		}						// toolbar requested
	else
		{						// no toolbar requested
		dr(toolbar);
		dr(dockable);
		dr(tooltips);
		}						// no toolbar requested

	if (m_statusbar)
		{						// status bar requested
		ds(statusbar, 1);

		if (m_indicators)
			ds(indicators, 1);
		else
			dr(indicators);
		}						// status bar requested
	else
		{						// no status bar requested
		dr(statusbar);
		dr(indicators);
		}						// no status bar requested
	
	return TRUE;				// i.e., okay to dismiss dialog
	}							// CCustom1Dlg::OnDismiss


BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_BN_CLICKED(IDB_STATUSBAR, OnStatusbar)
	ON_BN_CLICKED(IDB_TOOLBAR, OnToolbar)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDB_DATAPANE, OnDatapane)
	ON_BN_CLICKED(IDB_STDPANE, OnStdpane)
	ON_BN_CLICKED(IDB_TREEPANE, OnTreepane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg message handlers

void CCustom1Dlg::EnableControls()
	{							// CCustom1Dlg::EnableControls
	BOOL toolbar = IsDlgButtonChecked(IDB_TOOLBAR);
	BOOL statusbar = IsDlgButtonChecked(IDB_STATUSBAR);

	m_ctlTooltips.EnableWindow(toolbar);
	m_ctlDockable.EnableWindow(toolbar);

	m_ctlIndicators.EnableWindow(statusbar);
	}							// CCustom1Dlg::EnableControls

BOOL CCustom1Dlg::OnInitDialog() 
	{							// CCustom1Dlg::OnStatusbar
	CAppWizStepDlg::OnInitDialog();
	EnableControls();
	
	// Determine location and size for appearance bitmap
	
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_TYSY_TNDNSN);
	BITMAP bm;
	bitmap.GetObject(sizeof(bm), &bm);
	CRect rc;
	GetClientRect(&rc);
	rcBitmaps.left = rc.right / 20;
	rcBitmaps.top = rc.bottom / 20;
	szBitmaps.cx = bm.bmWidth;
	szBitmaps.cy = bm.bmHeight;
	rcBitmaps.right = rcBitmaps.left + szBitmaps.cx;
	rcBitmaps.bottom = rcBitmaps.top + szBitmaps.cy;
	
	return TRUE;
	}							// CCustom1Dlg::OnStatusbar

void CCustom1Dlg::OnStatusbar() 
	{							// CCustom1Dlg::OnStatusbar
	EnableControls();
	InvalidateBitmap();
	}							// CCustom1Dlg::OnStatusbar

void CCustom1Dlg::OnToolbar() 
	{							// CCustom1Dlg::OnToolbar
	EnableControls();
	InvalidateBitmap();
	}							// CCustom1Dlg::OnToolbar

void CCustom1Dlg::OnTreepane() 
	{							// CCustom1Dlg::OnTreepane
	InvalidateBitmap();
	}							// CCustom1Dlg::OnTreepane

void CCustom1Dlg::OnDatapane() 
	{							// CCustom1Dlg::OnDatapane
	InvalidateBitmap();
	}							// CCustom1Dlg::OnDatapane

void CCustom1Dlg::OnStdpane() 
	{							// CCustom1Dlg::OnStdpane
	InvalidateBitmap();
	}							// CCustom1Dlg::OnStdpane

void CCustom1Dlg::InvalidateBitmap()
	{							// CCustom1Dlg::InvalidateBitmap
	InvalidateRect(&rcBitmaps);
	}							// CCustom1Dlg::InvalidateBitmap

void CCustom1Dlg::OnPaint() 
	{							// CCustom1Dlg::OnPaint
	CPaintDC dc(this);
	CRect rc;
	
	// Paint the left 40% of the dialog cyan
	
	GetClientRect(&rc);
	rc.right = rcBitmaps.left + 166; // match up with change in shadow color
	CBrush cyan;
	cyan.CreateSolidBrush(RGB(0, 255, 255));
	dc.FillRect(rc, &cyan);
	dc.DrawEdge(&rc, EDGE_ETCHED, BF_RIGHT);

	// Draw a bitmap illustrating what the final application
	// will look like

	BOOL toolbar = IsDlgButtonChecked(IDB_TOOLBAR);
	BOOL statusbar = IsDlgButtonChecked(IDB_STATUSBAR);
	BOOL treepane = IsDlgButtonChecked(IDB_TREEPANE);
	BOOL datapane = IsDlgButtonChecked(IDB_DATAPANE);
	BOOL stdpane = IsDlgButtonChecked(IDB_STDPANE);

	int index = (toolbar * 16) + (statusbar * 8) + (treepane * 4)
		+ (datapane * 2) + stdpane;
	static UINT bmid[32] = {
		IDB_TNSN_TNDNSN,
		IDB_TNSN_TNDNSY,
		IDB_TNSN_TNDYSN,
		IDB_TNSN_TNDYSY,
		IDB_TNSN_TYDNSN,
		IDB_TNSN_TYDNSY,
		IDB_TNSN_TYDYSN,
		IDB_TNSN_TYDYSY,

		IDB_TNSY_TNDNSN,
		IDB_TNSY_TNDNSY,
		IDB_TNSY_TNDYSN,
		IDB_TNSY_TNDYSY,
		IDB_TNSY_TYDNSN,
		IDB_TNSY_TYDNSY,
		IDB_TNSY_TYDYSN,
		IDB_TNSY_TYDYSY,

		IDB_TYSN_TNDNSN,
		IDB_TYSN_TNDNSY,
		IDB_TYSN_TNDYSN,
		IDB_TYSN_TNDYSY,
		IDB_TYSN_TYDNSN,
		IDB_TYSN_TYDNSY,
		IDB_TYSN_TYDYSN,
		IDB_TYSN_TYDYSY,

		IDB_TYSY_TNDNSN,
		IDB_TYSY_TNDNSY,
		IDB_TYSY_TNDYSN,
		IDB_TYSY_TNDYSY,
		IDB_TYSY_TYDNSN,
		IDB_TYSY_TYDNSY,
		IDB_TYSY_TYDYSN,
		IDB_TYSY_TYDYSY,
		};

	CBitmap bitmap;
	bitmap.LoadBitmap(bmid[index]);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap* oldbitmap = dcMem.SelectObject(&bitmap);

	dc.BitBlt(rcBitmaps.left, rcBitmaps.top, szBitmaps.cx, szBitmaps.cy,
		&dcMem, 0, 0, SRCCOPY);
	
	dcMem.SelectObject(oldbitmap);
	}							// CCustom1Dlg::OnPaint
