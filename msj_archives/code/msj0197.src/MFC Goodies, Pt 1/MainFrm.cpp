////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#include "StdAfx.h"
#include "DibView.h"
#include "MainFrm.h"
#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CBaseFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBaseFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR				// status line indicator
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBaseFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))) {
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	return 0;
}

//////////////////
// Palette changed: broadcast the message to all children.
//
void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	TRACEFN("CMainFrame::OnPaletteChanged\n");
	const MSG& msg = AfxGetThreadState()->m_lastSentMsg;
	SendMessageToDescendants(WM_PALETTECHANGED, msg.wParam, msg.lParam);
}

//////////////////
// I got activated: realize my palette
//
BOOL CMainFrame::OnQueryNewPalette() 
{
	TRACEFN("CMainFrame::OnQueryNewPalette\n");
	CView* pView = GetActiveFrame()->GetActiveView();
	if (pView)
		pView->SendMessage(WM_QUERYNEWPALETTE);
	return FALSE;
}
