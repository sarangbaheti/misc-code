////////////////////////////////////////////////////////////////
// HOOK Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See HOOK.CPP for description of program.
// 
#include "MsgHook.h"

//////////////////
// Msg hook to spy on mouse messages
//
class CMouseMsgHook : public CMsgHook {
	DECLARE_DYNAMIC(CMouseMsgHook);
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);	
};

//////////////////
// Msg hook to spy on mouse messages
//
class CKbdMsgHook : public CMsgHook {
	DECLARE_DYNAMIC(CKbdMsgHook);
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);	
};

//////////////////
// Msg hook to hook all WM_ messages
//
class CAllMsgHook : public CMsgHook {
	DECLARE_DYNAMIC(CAllMsgHook);
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);	
};

//////////////////
// Standard main frame
//
class CMainFrame : public CFrameWnd {
public:
	CMouseMsgHook	m_mouseMsgHook;	// mouse message hook
	CKbdMsgHook		m_kbdMsgHook;		// keyboard message hook
	CAllMsgHook		m_allMsgHook;		// all message hook

	CMainFrame();
	virtual ~CMainFrame();

protected:
	DECLARE_DYNAMIC(CMainFrame)
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	DECLARE_MESSAGE_MAP()
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHookKbd();
	afx_msg void OnHookMouse();
	afx_msg void OnHookAll();
	afx_msg void OnUpdateHookKbd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHookMouse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHookAll(CCmdUI* pCmdUI);
};
