// datapane.cpp : implementation file
//

#include "stdafx.h"
#include "$$root$$.h"
#include "datapane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

$$IF(multipane)
IMPLEMENT_DYNCREATE(CDataPane, CWnd)

CDataPane::CDataPane()
	{							// CDataPane::CDataPane
	}							// CDataPane::CDataPane
$$ELSE // not multipane
CDataPane::CDataPane(CWnd* parent)
	{							// CDataPane::CDataPane
	Create(NULL, "", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), parent,
		AFX_IDW_PANE_FIRST);
	}							// CDataPane::CDataPane
$$ENDIF // not multipane

CDataPane::~CDataPane()
{
}


BEGIN_MESSAGE_MAP(CDataPane, CWnd)
	//{{AFX_MSG_MAP(CDataPane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDataPane message handlers
$$IF(multipane)

void CDataPane::PostNcDestroy() 
	{							// CDataPane::PostNcDestroy
	delete this;
	}							// CDataPane::PostNcDestroy
$$ENDIF

int CDataPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
	{							// CDataPane::OnCreate
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rc;
	GetClientRect(rc);
	m_ctlList.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER | LVS_SINGLESEL,
		rc, this, ID_DATA_CONTROL);

	// TODO: Replace the following code to define the column layout of the control
	
	TEXTMETRIC tm;
	CClientDC dc(this);
	dc.GetTextMetrics(&tm);

	int colwidth = 24 * tm.tmAveCharWidth;
	m_ctlList.InsertColumn(0, "Column 1", LVCFMT_LEFT, colwidth, 0);
	m_ctlList.InsertColumn(1, "Column 2", LVCFMT_LEFT, 10000, 1);

	return 0;
	}							// CDataPane::OnCreate

void CDataPane::OnSize(UINT nType, int cx, int cy) 
	{							// CDataPane::OnSize
	CWnd::OnSize(nType, cx, cy);
	m_ctlList.MoveWindow(0, 0, cx, cy);
	}							// CDataPane::OnSize
