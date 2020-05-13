//***************************************************************************
//
//  Demo.cpp
//
//***************************************************************************

#include <afxwin.h>
#include <afxcmn.h>
#include "SortView.h"
#include "Demo.h"

CMyApp myApp;

/////////////////////////////////////////////////////////////////////////////
// CMyApp member functions

BOOL CMyApp::InitInstance ()
{
    m_pMainWnd = new CMainWindow;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow ();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainWindow message map and member functions

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)
    ON_WM_CREATE ()
    ON_WM_SIZE ()
END_MESSAGE_MAP ()

CMainWindow::CMainWindow ()
{
    Create (NULL, "CSortListCtrl Demo");
}

int CMainWindow::OnCreate (LPCREATESTRUCT lpcs)
{
    if (CFrameWnd::OnCreate (lpcs) == -1)
        return -1;

    //
    // Create the list view control.
    //
    if (!m_wndListView.Create (WS_CHILD | WS_VISIBLE | LVS_REPORT,
        CRect (0, 0, 0, 0), this, ID_LISTVIEW))
        return -1;

    //
    // Fill the control with items.
    //
    InitListCtrl ();
    return 0;
}

void CMainWindow::OnSize (UINT nType, int cx, int cy)
{
    //
    // When this window is resized, resize the list view control so that
    // it fills its parent's client area.
    //
    if ((nType == SIZE_RESTORED) || (nType == SIZE_MAXIMIZED))
        m_wndListView.SetWindowPos (NULL, 0, 0, cx, cy,
            SWP_NOMOVE | SWP_NOZORDER);
}

void CMainWindow::InitListCtrl ()
{
    //
    // Create the column headers.
    //
    m_wndListView.InsertColumn (0, "File Name", LVCFMT_LEFT, 192);
    m_wndListView.InsertColumn (1, "Size", LVCFMT_RIGHT, 128);
    m_wndListView.InsertColumn (2, "Created", LVCFMT_CENTER, 128);

    //
    // Get the path to the Windows directory.
    //
    char szPath[MAX_PATH];
    ::GetWindowsDirectory (szPath, sizeof (szPath));
    if (szPath[::lstrlen (szPath) - 1] != '\\')
        ::lstrcat (szPath, "\\");
    ::lstrcat (szPath, "*.*");

    //
    // Populate the list view control.
    //
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile (szPath, &fd);

    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            if (!AddItemToListView (fd))
                break;
        }
    } while (::FindNextFile (hFind, &fd));

    ::FindClose (hFind);
}

BOOL CMainWindow::AddItemToListView (WIN32_FIND_DATA& fd)
{
    //
    // Allocate an ITEMINFO structure to hold the item's data.
    //
    PITEMINFO pItem;
    try {
        pItem = new ITEMINFO;
    }
    catch (CMemoryException* e) {
        e->Delete ();
        return FALSE;
    }

    //
    // Initialize the ITEMINFO structure's fields.
    //
    pItem->strFileName = fd.cFileName;
    pItem->dwFileSize = fd.nFileSizeLow;
    pItem->ftCreated = fd.ftCreationTime;

    //
    // Add the item to the list view control.
    //
    if (m_wndListView.InsertItem (pItem) == -1)
        return FALSE;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl member functions

int CMyListCtrl::OnCompareItems (void* pItem1, void* pItem2, int nColumn)
{
    int nResult = 0;
    PITEMINFO p1 = (PITEMINFO) pItem1;
    PITEMINFO p2 = (PITEMINFO) pItem2;

    switch (nColumn) {

    case 0: // File name
        nResult = p1->strFileName.CompareNoCase (p2->strFileName);
        break;

    case 1: // File size
        nResult = p1->dwFileSize - p2->dwFileSize;
        break;

    case 2: // Date and time created
        nResult = ::CompareFileTime (&p1->ftCreated, &p2->ftCreated);
        break;
    }
    return nResult;
}

CString CMyListCtrl::OnNeedText (void* pItem, int nColumn)
{
    CString string;
    PITEMINFO p = (PITEMINFO) pItem;

    switch (nColumn) {

    case 0: // File name
        string = p->strFileName;
        break;

    case 1: // File size
        string.Format ("%u", p->dwFileSize);
        break;

    case 2: // Date and time created
        CTime time (p->ftCreated);

        BOOL pm = FALSE;
        int nHour = time.GetHour ();
        if (nHour == 0)
            nHour = 12;
        else if (nHour == 12)
            pm = TRUE;
        else if (nHour > 12) {
            nHour -= 12;
            pm = TRUE;
        }

        string.Format ("%d/%0.2d/%0.2d (%d:%0.2d%c)",
            time.GetMonth (), time.GetDay (), time.GetYear () % 100,
            nHour, time.GetMinute (), pm ? 'p' : 'a');
        break;
    }
    return string;
}

void CMyListCtrl::OnDeleteItem (void* pItem)
{
    delete (PITEMINFO) pItem;
}
