
//***********************************************************************
//
//  MainFrame.cpp
//
//***********************************************************************

#include <afxwin.h>
#include <afxcview.h>
#include <afxmt.h>
#include "Resource.h"
#include "MainFrame.h"
#include "DriveView.h"

IMPLEMENT_DYNCREATE (CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP (CMainFrame, CFrameWnd)
    ON_WM_CREATE ()
    ON_COMMAND_RANGE (IDM_MENU_BASE, IDM_MENU_BASE + 25, OnRefreshDrive)
END_MESSAGE_MAP ()

BOOL CMainFrame::PreCreateWindow (CREATESTRUCT& cs)
{
    if (!CFrameWnd::PreCreateWindow (cs))
        return FALSE;

    cs.style &= ~FWS_ADDTOTITLE;
    return TRUE;
}

int CMainFrame::OnCreate (LPCREATESTRUCT lpcs)
{
    if (CFrameWnd::OnCreate (lpcs) == -1)
        return -1;

    DWORD dwDriveList = ::GetLogicalDrives ();

    for (int i=0; i<26; i++) {
        if (!(dwDriveList & 1))
            GetMenu ()->DeleteMenu (IDM_MENU_BASE + i, MF_BYCOMMAND);
        dwDriveList >>= 1;
    }
    return 0;
}

void CMainFrame::OnRefreshDrive (UINT nID)
{
    UINT nDrive = nID - IDM_MENU_BASE;
    ((CDriveView*) GetActiveView ())->RefreshDrive (nDrive);
}


