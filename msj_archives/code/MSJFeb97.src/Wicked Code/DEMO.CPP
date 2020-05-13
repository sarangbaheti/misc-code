//***********************************************************************
//
//  Demo.cpp
//
//***********************************************************************

#include <afxwin.h>
#include <stdlib.h>
#include "WaitDlg.h"
#include "Demo.h"

CMyApp myApp;

/////////////////////////////////////////////////////////////////////////
// CMyApp member functions

BOOL CMyApp::InitInstance ()
{
    m_pMainWnd = new CMainWindow;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow ();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// CMainWindow message map and member functions

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)
    ON_WM_LBUTTONDOWN ()
END_MESSAGE_MAP ()

CMainWindow::CMainWindow ()
{
    Create (NULL, "CWaitDialog Demo");
}

void CMainWindow::OnLButtonDown (UINT nFlags, CPoint point)
{
    CRect rect;
    GetClientRect (&rect);
    CClientDC dc (this);

    //
    // Display a cancel dialog.
    //
    BOOL bContinue = TRUE;
    CWaitDialog dlg (&bContinue);

    int nCount = 0;
    int nPercentComplete = 0;

    //
    // Draw ellipses until Cancel is clicked or we've reached our
    // quota of ellipses.
    //
    while (bContinue) {
        DrawRandomEllipse (&dc, rect);
        if (++nCount >= 200) {
            nCount = 0;
            nPercentComplete += 2;
            dlg.SetPercentComplete (nPercentComplete);

            if (nPercentComplete == 80)
                dlg.SetMessageText ("Almost done!");

            if (nPercentComplete == 100)
                break;
        }
        dlg.Pump ();
    }

}

void CMainWindow::DrawRandomEllipse (CDC* pDC, CRect& rect)
{
    int x1 = rand () % rect.right;
    int x2 = rand () % rect.right;
    int y1 = rand () % rect.bottom;
    int y2 = rand () % rect.bottom;

    CRect rcEllipse (x1, y1, x2, y2);
    rcEllipse.NormalizeRect ();

    CBrush brush (RGB (rand () % 255, rand () % 255, rand () % 255));
    CBrush* pOldBrush = pDC->SelectObject (&brush);

    pDC->Ellipse (&rcEllipse);

    pDC->SelectObject (pOldBrush);
}
