// treepane.cpp : implementation file
//

#include "stdafx.h"
#include "$$root$$.h"
#include "treepane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

$$IF(multipane)
IMPLEMENT_DYNCREATE(CTreePane, CWnd)

CTreePane::CTreePane()
	{							// CTreePane::CTreePane
	}							// CTreePane::CTreePane
$$ELSE // not multipane
CTreePane::CTreePane(CWnd* parent)
	{							// CTreePane::CTreePane
	Create(NULL, "", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), parent,
		AFX_IDW_PANE_FIRST);
	}							// CTreePane::CTreePane
$$ENDIF // not multipane

CTreePane::~CTreePane()
{
}


BEGIN_MESSAGE_MAP(CTreePane, CWnd)
	//{{AFX_MSG_MAP(CTreePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTreePane message handlers

int CTreePane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
	{							// CTreePane::OnCreate
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rc;
	GetClientRect(rc);
	m_ctlTree.Create(WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_LINESATROOT |TVS_HASBUTTONS,
		rc, this, ID_TREE_CONTROL);
	
	// TODO: Replace the following lines in order to define the tree hierarchy
	
	m_root = m_ctlTree.InsertItem("Root", 0, 0);
	m_ctlTree.InsertItem("Node1", m_root, 0);
	m_ctlTree.InsertItem("Node2", m_root, 0);
	m_ctlTree.InsertItem("Node3", m_root, 0);

	return 0;
	}							// CTreePane::OnCreate

void CTreePane::OnSize(UINT nType, int cx, int cy) 
	{							// CTreePane::OnSize
	CWnd::OnSize(nType, cx, cy);
	m_ctlTree.MoveWindow(0, 0, cx, cy);
	}							// CTreePane::OnSize
$$IF(multipane)

void CTreePane::PostNcDestroy() 
	{							// CTreePane::PostNcDestroy
	delete this;
	}							// CTreePane::PostNcDestroy
$$ENDIF // multipane
