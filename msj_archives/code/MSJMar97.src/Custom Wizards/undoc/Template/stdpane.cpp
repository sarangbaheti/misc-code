// stdpane.cpp : implementation file
//

#include "stdafx.h"
#include "$$root$$.h"
#include "stdpane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

$$IF(multipane)
IMPLEMENT_DYNCREATE(CStdPane, CWnd)

CStdPane::CStdPane()
	{							// CStdPane::CStdPane
	}							// CStdPane::CStdPane
$$ELSE // not multipane
CStdPane::CStdPane(CWnd* parent)
	{							// CStdPane::CStdPane
	Create(NULL, "", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), parent,
		AFX_IDW_PANE_FIRST);
	}							// CStdPane::CStdPane
$$ENDIF // not multipane

CStdPane::~CStdPane()
	{							// CStdPane::~CStdPane
	}							// CStdPane::~CStdPane

BEGIN_MESSAGE_MAP(CStdPane, CWnd)
	//{{AFX_MSG_MAP(CStdPane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
$$IF(multipane)

// Need to override PreCreateWindow because splitter will otherwise create a window
// without a background brush.

BOOL CStdPane::PreCreateWindow(CREATESTRUCT& cs) 
	{							// CStdPane::PreCreateWindow
	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
		::LoadCursor(NULL, IDC_ARROW), (HBRUSH) (COLOR_WINDOW + 1), NULL);
	return CWnd::PreCreateWindow(cs);
	}							// CStdPane::PreCreateWindow
$$ENDIF // multipane
