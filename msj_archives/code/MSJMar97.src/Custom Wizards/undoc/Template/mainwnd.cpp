// mainwnd.cpp - implementation file

#include "stdafx.h"
#include "$$root$$.h"
#include "mainwnd.h"
$$IF(treepane)
#include "treepane.h"
$$ENDIF
$$IF(datapane)
#include "datapane.h"
$$ENDIF
$$IF(stdpane)
#include "stdpane.h"
$$ENDIF

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CMainWindow construction and destruction

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	//{{AFX_MSG_MAP(CMainWindow)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR,           // status line indicator
$$IF(indicators)
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
$$ENDIF
	};


CMainWindow::CMainWindow()
	{							// CMainWindow::CMainWindow

	// TODO: Modify the next line of code to insert the correct window title
	
	Create(NULL, "Your title here", WS_OVERLAPPEDWINDOW, rectDefault,
		NULL, MAKEINTRESOURCE(IDR_MAINMENU), 0, NULL);
	}							// CMainWindow::CMainWindow

CMainWindow::~CMainWindow()
	{							// CMainWindow::~CMainWindow
$$IF(multipane)
$$IF(stdpane)
	if (m_stdpane)
		delete m_stdpane;
$$ENDIF // stdpane
$$ELSE // not multipane
$$IF(treepane)
	if (m_treepane)
		delete m_treepane;
$$ELIF(datapane)
	if (m_datapane)
		delete m_datapane;
$$ELSE
	if (m_stdpane)
		delete m_stdpane;
$$ENDIF
$$ENDIF // not multipane
	}							// CMainWindow::~CMainWindow

///////////////////////////////////////////////////////////////////////////////

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{							// CMainWindow::OnCreate
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
$$IF(statusbar)
	
	if (!m_wndStatusBar.Create(this)
		|| !m_wndStatusBar.SetIndicators(indicators, arraysize(indicators)))
		{						// couldn't create status bar
		TRACE0("Failed to create status bar\n");
		return -1;
		}						// couldn't create status bar
$$ENDIF // statusbar
$$IF(toolbar)

	if (!m_wndToolBar.Create(this)
		|| !m_wndToolBar.LoadToolBar(IDR_MAINMENU))
		{						// couldn't create toolbar
		TRACE0("Failed to create toolbar\n");
		return -1;
		}						// couldn't create toolbar
$$IF(tooltips)

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
$$ENDIF // tooltips
$$IF(dockable)

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
$$ENDIF // dockable
$$ENDIF // tooltips

	return 0;
	}							// CMainWindow::OnCreate

///////////////////////////////////////////////////////////////////////////////

BOOL CMainWindow::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
	{							// CMainWindow::OnCreateClient
$$IF(multipane)
	CCreateContext cc;
	memset(&cc, 0, sizeof(cc));
	CRect rc;
	GetClientRect(rc);
	m_splitter.CreateStatic(this, 1, $$numpanes$$);
	int col = -1;

	CSize size(rc.right/$$numpanes$$, rc.bottom);
$$IF(treepane)

	if (m_splitter.CreateView(0, ++col, RUNTIME_CLASS(CTreePane), size, pContext))
		m_treepane = (CTreePane*) m_splitter.GetPane(0, col);
	else
		return FALSE;
$$ENDIF // treepane
$$IF(datapane)
$$IF(!stdpane)

	size.cx = rc.right - size.cx;
$$ENDIF // !stdpane

	if (m_splitter.CreateView(0, ++col, RUNTIME_CLASS(CDataPane), size, pContext))
		m_datapane = (CDataPane*) m_splitter.GetPane(0, col);
	else
		return FALSE;
$$ENDIF // datapane
$$IF(stdpane)

	size.cx = rc.right - size.cx;

	if (m_splitter.CreateView(0, ++col, RUNTIME_CLASS(CStdPane), size, pContext))
		m_stdpane = (CStdPane*) m_splitter.GetPane(0, col);
	else
		return FALSE;
$$ENDIF // stdpane
$$/////////////////////////////////////////////
$$ELSE // not multipane
$$IF(treepane)
	m_treepane = new CTreePane(this);
$$ELIF(datapane)
	m_datapane = new CDataPane(this);
$$ELSE
	m_stdpane = new CStdPane(this);
$$ENDIF
$$ENDIF // not multipane

	return TRUE;
	}							// CMainWindow::OnCreateClient
