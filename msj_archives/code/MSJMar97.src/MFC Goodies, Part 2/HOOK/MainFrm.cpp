////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// 
#include "StdAfx.h"
#include "Hook.h"
#include "MainFrm.h"
#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#else
#error "HOOK demo program requires debug mode."
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_HOOK_KBD,		OnHookKbd)
	ON_COMMAND(ID_HOOK_MOUSE,	OnHookMouse)
	ON_COMMAND(ID_HOOK_ALL,		OnHookAll)
	ON_UPDATE_COMMAND_UI(ID_HOOK_KBD,	OnUpdateHookKbd)
	ON_UPDATE_COMMAND_UI(ID_HOOK_MOUSE, OnUpdateHookMouse)
	ON_UPDATE_COMMAND_UI(ID_HOOK_ALL,   OnUpdateHookAll)
END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] = {
	ID_SEPARATOR
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))) {
		TRACE("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	return 0;
}

////////////////////////////////////////////////////////////////
// Command and UI handlers for hook/unhook commands
//
void CMainFrame::OnHookKbd() 
{
	m_kbdMsgHook.HookWindow(m_kbdMsgHook.IsHooked() ? NULL : this);
}

void CMainFrame::OnUpdateHookKbd(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_kbdMsgHook.IsHooked());
}

void CMainFrame::OnHookMouse() 
{
	m_mouseMsgHook.HookWindow(m_mouseMsgHook.IsHooked() ? NULL : this);	
}

void CMainFrame::OnUpdateHookMouse(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_mouseMsgHook.IsHooked());	
}

void CMainFrame::OnHookAll() 
{
	m_allMsgHook.HookWindow(m_allMsgHook.IsHooked() ? NULL : this);	
}

void CMainFrame::OnUpdateHookAll(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_allMsgHook.IsHooked());	
}

//////////////////
// Implementation of CMouseMsgHook just spies on mouse messages,
// displays them as debug output.
//
LRESULT CMouseMsgHook::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	if (WM_MOUSEFIRST <= msg && msg <= WM_MOUSELAST) {
		TRACE("CMouseMsgHook::%s\n", DbgName(msg));
	}
	return CMsgHook::WindowProc(msg, wp, lp);	// Important!!
}
IMPLEMENT_DYNAMIC(CMouseMsgHook, CMsgHook);

//////////////////
// CKbdMsgHook spies on keyboard messages,
//
LRESULT CKbdMsgHook::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	if (WM_KEYFIRST <= msg && msg <= WM_KEYLAST) {
		TRACE("CKbdMsgHook::%s\n", DbgName(msg));
	}
	return CMsgHook::WindowProc(msg, wp, lp);	// Important!!
}
IMPLEMENT_DYNAMIC(CKbdMsgHook, CMsgHook);

//////////////////
// CAllMsgHook spies on all WM_ messages
//
LRESULT CAllMsgHook::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	TRACEFN("CAllMsgHook::%s\n", DbgName(msg));
	return CMsgHook::WindowProc(msg, wp, lp);	// Important!!
}
IMPLEMENT_DYNAMIC(CAllMsgHook, CMsgHook);
