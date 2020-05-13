// mainwnd.cpp - implementation file

#include "stdafx.h"
#include "$$root$$.h"
#include "mainwnd.h"
$$IF(multipane)
$$IF(treepane)
#include "treepane.h"
$$ENDIF
$$IF(datapane)
#include "datapane.h"
$$ENDIF
$$IF(stdpane)
#include "stdpane.h"
$$ENDIF
$$ENDIF // multipane

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
    {                           // CMainWindow::CMainWindow

    // TODO: Modify the next line of code to insert the correct window title
    
    Create(NULL, "Your title here", WS_OVERLAPPEDWINDOW, rectDefault,
        NULL, MAKEINTRESOURCE(IDR_MAINMENU), 0, NULL);
    }                           // CMainWindow::CMainWindow

CMainWindow::~CMainWindow()
    {                           // CMainWindow::~CMainWindow
$$IF(multipane)
$$IF(stdpane)
    if (m_stdpane)
        delete m_stdpane;
$$ENDIF // stdpane
$$ENDIF // multipane
    }                           // CMainWindow::~CMainWindow

///////////////////////////////////////////////////////////////////////////////

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
    {                           // CMainWindow::OnCreate
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
$$IF(statusbar)
    
    if (!m_wndStatusBar.Create(this)
        || !m_wndStatusBar.SetIndicators(indicators, arraysize(indicators)))
        {                       // couldn't create status bar
        TRACE0("Failed to create status bar\n");
        return -1;
        }                       // couldn't create status bar
$$ENDIF // statusbar
$$IF(toolbar)

    if (!m_wndToolBar.Create(this)
        || !m_wndToolBar.LoadToolBar(IDR_MAINMENU))
        {                       // couldn't create toolbar
        TRACE0("Failed to create toolbar\n");
        return -1;
        }                       // couldn't create toolbar
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
$$//////////////////////////////////////////////////////////
$$IF(!multipane)
$$IF(treepane)
    CRect rc;
    GetClientRect(rc);
    m_ctlTree.Create(WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_LINESATROOT |TVS_HASBUTTONS,
        rc, this, ID_TREE_CONTROL);
    
    // TODO: Replace the following lines in order to define the tree hierarchy
    
    m_root = m_ctlTree.InsertItem("Root", 0, 0);
    m_ctlTree.InsertItem("Node1", m_root, 0);
    m_ctlTree.InsertItem("Node2", m_root, 0);
    m_ctlTree.InsertItem("Node3", m_root, 0);
$$ENDIF // treepane
$$IF(datapane)
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
$$ENDIF // datapane
$$ENDIF // not multipane

    return 0;
    }                           // CMainWindow::OnCreate
$$IF(multipane) // panes within splitter

///////////////////////////////////////////////////////////////////////////////

BOOL CMainWindow::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
    {                           // CMainWindow::OnCreateClient
    CCreateContext cc;
    memset(&cc, 0, sizeof(cc));
    CRect rc;
    GetClientRect(rc);
    m_splitter.CreateStatic(this, 1, $$numpanes$$);
    int col = -1;

    CSize size(rc.right/$$numclasses$$, rc.bottom);
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

    return TRUE;
    }                           // CMainWindow::OnCreateClient
$$ENDIF // multipane
// mainwnd.h - interface to CMainWindow class

#ifndef MAINWND_H
#define MAINWND_H

///////////////////////////////////////////////////////////////////////////////

$$IF(treepane)
class CTreePane;
$$ENDIF
$$IF(datapane)
class CDataPane;
$$ENDIF
$$IF(stdpane)
class CStdPane;
$$ENDIF

class CMainWindow : public CFrameWnd
{                               // class CMainWindow
public:
    CMainWindow();
    virtual ~CMainWindow();

$$IF(multipane)
    CSplitterWnd    m_splitter; // frame for view panes
$$IF(treepane)
    CTreePane*      m_treepane;
$$ENDIF
$$IF(datapane)
    CDataPane*      m_datapane;
$$ENDIF
$$IF(stdpane)
    CStdPane*       m_stdpane;
$$ENDIF
$$ELSE // not multipane
$$/////////////////////////////////////////////////////////
$$IF(treepane)
    CTreeCtrl       m_ctlTree;
    HTREEITEM       m_root;
$$ENDIF
$$IF(datapane)
    CListCtrl       m_ctlList;
$$ENDIF
$$ENDIF // not multipane

    //{{AFX_VIRTUAL(CMainWindow)
$$IF(multipane)
    protected:
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
$$ENDIF
    //}}AFX_VIRTUAL

protected:
$$IF(statusbar)
    CStatusBar  m_wndStatusBar;
$$ENDIF
$$IF(toolbar)
    CToolBar    m_wndToolBar;
$$ENDIF
    //{{AFX_MSG(CMainWindow)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};                              // class CMainWindow

#endif
