//***********************************************************************
//
//  DriveView.cpp
//
//***********************************************************************

#include <afxwin.h>
#include <afxcview.h>
#include <afxcoll.h>
#include <afxmt.h>
#include "Resource.h"
#include "DriveView.h"

// Image list indexes
#define ILI_HARD_DISK       0
#define ILI_FLOPPY          1
#define ILI_CD_ROM          2
#define ILI_NET_DRIVE       3
#define ILI_RAM_DRIVE       4
#define ILI_CLOSED_FOLDER   5
#define ILI_OPEN_FOLDER     6

IMPLEMENT_DYNCREATE (CDriveView, CTreeView)

BEGIN_MESSAGE_MAP (CDriveView, CTreeView)
    ON_WM_DESTROY ()
    ON_NOTIFY_REFLECT (TVN_ITEMEXPANDING, OnItemExpanding)
    ON_NOTIFY_REFLECT (TVN_SELCHANGED, OnSelChanged)
    ON_MESSAGE (WM_USER, OnDriveContentsChanged)
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////
// Class constructor

CDriveView::CDriveView () : m_event (FALSE, TRUE)
{
    m_nThreadCount = 0;
}

/////////////////////////////////////////////////////////////////////////
// Overridables

BOOL CDriveView::PreCreateWindow (CREATESTRUCT& cs)
{
    if (!CTreeView::PreCreateWindow (cs))
        return FALSE;

    cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
    return TRUE;
}

void CDriveView::OnInitialUpdate ()
{
    CTreeView::OnInitialUpdate ();
    m_imglDrives.Create (IDR_DRIVEIMAGES, 16, 1, RGB (255, 0, 255));
    GetTreeCtrl ().SetImageList (&m_imglDrives, TVSIL_NORMAL);
    InitTree ();
}

void CDriveView::OnSelectionChanged (CString& strPathName)
{
    //
    // NOTE: Override this function in a derived class to respond
    // to selection changes differently. The default implementation
    // calls UpdateAllViews to update other views of the document.
    //
    GetDocument ()->UpdateAllViews (this,
        (LPARAM) (LPCTSTR) strPathName);
}

/////////////////////////////////////////////////////////////////////////
// Message handlers

void CDriveView::OnDestroy ()
{
    // Kill all running file change notification threads.
    if (m_nThreadCount) {
        m_event.SetEvent ();
        ::WaitForMultipleObjects (m_nThreadCount, m_hThreads, TRUE,
            INFINITE);
        m_nThreadCount = 0;
    }

    // Call the base class's OnDestroy handler.
    CTreeView::OnDestroy ();
}

void CDriveView::OnItemExpanding (NMHDR* pnmh, LRESULT* pResult)
{
    NM_TREEVIEW* pnmtv = (NM_TREEVIEW*) pnmh;
    HTREEITEM hItem = pnmtv->itemNew.hItem;
    CString strPathName = GetPathFromItem (hItem);
    *pResult = FALSE;

    // Reset the drive node if the drive is empty or the media changed.
    if (!IsMediaValid (strPathName)) {
        HTREEITEM hRoot = GetDriveNode (hItem);
        GetTreeCtrl ().Expand (hRoot, TVE_COLLAPSE);
        DeleteChildren (hRoot);
        AddDummyNode (hRoot);
        *pResult = TRUE;
        return;
    }

    // Delete the item if strPathName no longer specifies a valid path.
    if (!IsPathValid (strPathName)) {
        GetTreeCtrl ().DeleteItem (hItem);
        *pResult = TRUE;
        return;
    }

    // If the item is expanding, delete the dummy item attached to it
    // and add folder items. If the item is collapsing instead, delete
    // its folder items and add a dummy item if appropriate.
    if (pnmtv->action == TVE_EXPAND) {
        DeleteChildren (hItem);
        if (!AddDirectoryNodes (hItem, strPathName))
            *pResult = TRUE;
    }
    else {
        DeleteChildren (hItem);
        if (IsDriveNode (hItem))
            AddDummyNode (hItem);
        else
            SetButtonState (hItem, strPathName);
    }
}

void CDriveView::OnSelChanged (NMHDR* pnmh, LRESULT* pResult)
{
    HTREEITEM hItem = ((NM_TREEVIEW*) pnmh)->itemNew.hItem;
    CString strPathName = GetPathFromItem (hItem);

    // Reset the drive node if the drive is empty or the media changed.
    if (!IsMediaValid (strPathName)) {
        HTREEITEM hRoot = GetDriveNode (hItem);
        GetTreeCtrl ().Expand (hRoot, TVE_COLLAPSE);
        DeleteChildren (hRoot);
        AddDummyNode (hRoot);
        return;
    }

    // Delete the item if strPathName no longer specifies a valid path.
    if (!IsPathValid (strPathName)) {
        GetTreeCtrl ().DeleteItem (hItem);
        return;
    }

    // Update the item's button state if the item is not expanded.
    if (!(GetTreeCtrl ().GetItemState (hItem, TVIS_EXPANDED) &
        TVIS_EXPANDED) || !GetTreeCtrl ().ItemHasChildren (hItem))
        UpdateButtonState (hItem, strPathName);

    // Call the view's virtual OnSelectionChanged function.
    OnSelectionChanged (strPathName);
}

LONG CDriveView::OnDriveContentsChanged (UINT wParam, LONG lParam)
{
    RefreshDrive ((UINT) wParam);
    return 0;
}

/////////////////////////////////////////////////////////////////////////
// Public member functions

void CDriveView::RefreshDrive (UINT nDrive)
{
    // Find the HTREEITEM that corresponds to the target drive.
    CString strDrive = "?:\\";
    strDrive.SetAt (0, 0x41 + nDrive);

    HTREEITEM hItem =
        FindItem (GetTreeCtrl ().GetNextItem (NULL, TVGN_ROOT),
        strDrive);

    if (hItem == NULL)
        return;

    // Reset the drive node if the drive is empty or the media changed.
    if (!IsMediaValid (strDrive)) {
        GetTreeCtrl ().Expand (hItem, TVE_COLLAPSE);
        DeleteChildren (hItem);
        AddDummyNode (hItem);
        return;
    }

    // Save the current drive and directory.
    char szHome[MAX_PATH];
    ::GetCurrentDirectory (sizeof (szHome), szHome);

    // Change to the root directory of the target drive.
    if (!::SetCurrentDirectory ((LPCTSTR) strDrive))
        return; // Invalid drive specification

    // Refresh the drive node and all displayed subfolders.
    if (hItem != NULL)
        RefreshDirectory (hItem);

    // Return to the original drive and directory.
    ::SetCurrentDirectory (szHome);
}

CString CDriveView::GetPathFromItem (HTREEITEM hItem)
{
    CString strPathName;
    while (hItem != NULL) {
        CString string = GetTreeCtrl ().GetItemText (hItem);
        if ((string.Right (1) != "\\") && !strPathName.IsEmpty ())
            string += "\\";
        strPathName = string + strPathName;
        hItem = GetTreeCtrl ().GetParentItem (hItem);
    }
    return strPathName;
}

BOOL CDriveView::ExpandPath (LPCTSTR pszPath, BOOL bSelectItem)
{
    if (::lstrlen (pszPath) < 3)
        return FALSE;

    // Begin by finding the corresponding drive node.
    CString strPathName = pszPath;
    CString strDrive = strPathName.Left (3);

    HTREEITEM hItem =
        FindItem (GetTreeCtrl ().GetNextItem (NULL, TVGN_ROOT),
        strDrive);

    if (hItem == NULL)
        return FALSE; // Invalid drive specification

    strPathName = strPathName.Right (strPathName.GetLength () - 3);

    // Now bore down through the directory structure searching for the
    // item that corresponds to the final directory name in pszPath.
    while (strPathName.GetLength () > 0) {
        GetTreeCtrl ().Expand (hItem, TVE_EXPAND);
        hItem = GetTreeCtrl ().GetChildItem (hItem);
        if (hItem == NULL)
            return FALSE;

        int nIndex = strPathName.Find ('\\');
        hItem = FindItem (hItem, nIndex == -1 ? strPathName :
            strPathName.Left (nIndex));
        if (hItem == NULL)
            return FALSE; // Invalid path name

        if (nIndex == -1)
            strPathName.Empty ();
        else
            strPathName = strPathName.Right (strPathName.GetLength () -
                nIndex - 1);
    }

    GetTreeCtrl ().Expand (hItem, TVE_EXPAND);
    if (bSelectItem)
        GetTreeCtrl ().Select (hItem, TVGN_CARET);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// Protected helper functions

UINT CDriveView::InitTree ()
{
    int nPos = 0;
    UINT nCount = 0;
    CString strDrive = "?:\\";

    DWORD dwDriveList = ::GetLogicalDrives ();

    while (dwDriveList) {
        if (dwDriveList & 1) {
            strDrive.SetAt (0, 0x41 + nPos);
            if (AddDriveNode (strDrive))
                nCount++;
        }
        dwDriveList >>= 1;
        nPos++;
    }
    return nCount;
}

BOOL CDriveView::AddDriveNode (CString& strDrive)
{
    HTREEITEM hItem;

    UINT nType = ::GetDriveType ((LPCTSTR) strDrive);
    UINT nDrive = (UINT) strDrive[0] - 0x41;

    switch (nType) {

    case DRIVE_REMOVABLE:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_FLOPPY,
            ILI_FLOPPY);
        AddDummyNode (hItem);
        m_dwMediaID[nDrive] = GetSerialNumber (strDrive);
        break;

    case DRIVE_FIXED:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_HARD_DISK,
            ILI_HARD_DISK);
        SetButtonState (hItem, strDrive);
        CreateMonitoringThread (strDrive);
        break;

    case DRIVE_REMOTE:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_NET_DRIVE,
            ILI_NET_DRIVE);
        SetButtonState (hItem, strDrive);
        CreateMonitoringThread (strDrive);
        break;

    case DRIVE_CDROM:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_CD_ROM,
            ILI_CD_ROM);
        AddDummyNode (hItem);
        m_dwMediaID[nDrive] = GetSerialNumber (strDrive);
        break;

    case DRIVE_RAMDISK:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_RAM_DRIVE,
            ILI_RAM_DRIVE);
        SetButtonState (hItem, strDrive);
        CreateMonitoringThread (strDrive);
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

UINT CDriveView::AddDirectoryNodes (HTREEITEM hItem, CString& strPathName)
{
    HANDLE hFind;
    WIN32_FIND_DATA fd;

    UINT nCount = 0;

    CString strFileSpec = strPathName;
    if (strFileSpec.Right (1) != "\\")
        strFileSpec += "\\";
    strFileSpec += "*.*";

    if ((hFind = ::FindFirstFile ((LPCTSTR) strFileSpec, &fd)) ==
        INVALID_HANDLE_VALUE) {
        if (IsDriveNode (hItem))
            AddDummyNode (hItem);
        return 0;
    }

    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            CString strFileName = (LPCTSTR) &fd.cFileName;
            if ((strFileName != ".") && (strFileName != "..")) {
                HTREEITEM hChild =
                    GetTreeCtrl ().InsertItem ((LPCTSTR) &fd.cFileName,
                    ILI_CLOSED_FOLDER, ILI_OPEN_FOLDER, hItem, TVI_SORT);

                CString strNewPathName = strPathName;
                if (strNewPathName.Right (1) != "\\")
                    strNewPathName += "\\";

                strNewPathName += (LPCTSTR) &fd.cFileName;
                SetButtonState (hChild, strNewPathName);
                nCount++;
            }
        }
    } while (::FindNextFile (hFind, &fd));

    ::FindClose (hFind);
    return nCount;
}

void CDriveView::SetButtonState (HTREEITEM hItem, CString& strPathName)
{
    if (HasSubdirectory (strPathName))
        AddDummyNode (hItem);
}

void CDriveView::UpdateButtonState (HTREEITEM hItem, CString& strPathName)
{
    if (HasSubdirectory (strPathName)) {
        if (!GetTreeCtrl ().ItemHasChildren (hItem)) {
            AddDummyNode (hItem);
            Invalidate ();
        }
    }
    else {
        if (GetTreeCtrl ().ItemHasChildren (hItem))
            DeleteChildren (hItem);
    }
}

BOOL CDriveView::HasSubdirectory (CString& strPathName)
{
    HANDLE hFind;
    WIN32_FIND_DATA fd;
    BOOL bResult = FALSE;

    CString strFileSpec = strPathName;
    if (strFileSpec.Right (1) != "\\")
        strFileSpec += "\\";
    strFileSpec += "*.*";

    if ((hFind = ::FindFirstFile ((LPCTSTR) strFileSpec, &fd)) !=
        INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                CString strFileName = (LPCTSTR) &fd.cFileName;
                if ((strFileName != ".") && (strFileName != ".."))
                    bResult = TRUE;
            }
        } while (::FindNextFile (hFind, &fd) && !bResult);
        ::FindClose (hFind);
    }

    return bResult;
}

BOOL CDriveView::IsDriveNode (HTREEITEM hItem)
{
    return (GetTreeCtrl ().GetParentItem (hItem) == NULL) ? TRUE : FALSE;
}

void CDriveView::AddDummyNode (HTREEITEM hItem)
{
    GetTreeCtrl ().InsertItem ("", 0, 0, hItem);
}

HTREEITEM CDriveView::FindItem (HTREEITEM hItem, CString& strTarget)
{
    while (hItem != NULL) {
        if (GetTreeCtrl ().GetItemText (hItem) == strTarget)
            break;
        hItem = GetTreeCtrl ().GetNextSiblingItem (hItem);
    }
    return hItem;
}

UINT CDriveView::DeleteChildren (HTREEITEM hItem)
{
    UINT nCount = 0;
    HTREEITEM hChild = GetTreeCtrl ().GetChildItem (hItem);

    while (hChild != NULL) {
        HTREEITEM hNextItem = GetTreeCtrl ().GetNextSiblingItem (hChild);
        GetTreeCtrl ().DeleteItem (hChild);
        hChild = hNextItem;
        nCount++;
    }
    return nCount;
}

HTREEITEM CDriveView::GetDriveNode (HTREEITEM hItem)
{
    HTREEITEM hParent;

    do {
        hParent = GetTreeCtrl ().GetParentItem (hItem);
        if (hParent != NULL)
            hItem = hParent;
    } while (hParent != NULL);
    return hItem;
}

DWORD CDriveView::GetSerialNumber (CString& strDrive)
{
    DWORD dwSerialNumber;
    if (!::GetVolumeInformation ((LPCTSTR) strDrive, NULL, 0,
        &dwSerialNumber, NULL, NULL, NULL, 0))
        dwSerialNumber = 0xFFFFFFFF;
    return dwSerialNumber;
}

BOOL CDriveView::IsMediaValid (CString& strPathName)
{
    // Return TRUE if the drive doesn't support removable media.
    UINT nDriveType = GetDriveType ((LPCTSTR) strPathName);
    if ((nDriveType != DRIVE_REMOVABLE) && (nDriveType != DRIVE_CDROM))
        return TRUE;

    // Return FALSE if the drive is empty (::GetVolumeInformation fails).
    DWORD dwSerialNumber;
    CString strDrive = strPathName.Left (3);
    UINT nDrive = (UINT) strDrive[0] - 0x41;

    if (!::GetVolumeInformation ((LPCTSTR) strDrive, NULL, 0,
        &dwSerialNumber, NULL, NULL, NULL, 0)) {
        m_dwMediaID[nDrive] = 0xFFFFFFFF;
        return FALSE;
    }

    // Also return FALSE if the disk's serial number has changed.
    if ((m_dwMediaID[nDrive] != dwSerialNumber) &&
        (m_dwMediaID[nDrive] != 0xFFFFFFFF)) {
        m_dwMediaID[nDrive] = dwSerialNumber;
        return FALSE;
    }

    // Update our record of the serial number and return TRUE.
    m_dwMediaID[nDrive] = dwSerialNumber;
    return TRUE;
}

BOOL CDriveView::IsPathValid (CString& strPathName)
{
    if (strPathName.GetLength () == 3)
        return TRUE;

    HANDLE hFind;
    WIN32_FIND_DATA fd;
    BOOL bResult = FALSE;

    if ((hFind = ::FindFirstFile ((LPCTSTR) strPathName, &fd)) !=
        INVALID_HANDLE_VALUE) {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                bResult = TRUE;
        ::CloseHandle (hFind);
    }
    return bResult;
}

void CDriveView::RefreshDirectory (HTREEITEM hItem)
{
    // If the item is not expanded, update its button state and return.
    if (!(GetTreeCtrl ().GetItemState (hItem, TVIS_EXPANDED) &
        TVIS_EXPANDED) || !GetTreeCtrl ().ItemHasChildren (hItem)) {
        if (!IsDriveNode (hItem)) {
            CString strPathName = GetPathFromItem (hItem);
            UpdateButtonState (hItem, strPathName);
            GetTreeCtrl ().Expand (hItem, TVE_COLLAPSE);
        }
        return;
    }

    // Delete items corresponding to subdirectories that no longer exist
    // and build a CStringList containing the names of all the items that
    // are children of hItem.
    CStringList list;
    WIN32_FIND_DATA fd;
    HANDLE hFind;

    HTREEITEM hChild = GetTreeCtrl ().GetChildItem (hItem);

    while (hChild != NULL) {
        HTREEITEM hNextItem = GetTreeCtrl ().GetNextSiblingItem (hChild);
        CString strDirName = GetTreeCtrl ().GetItemText (hChild);

        if ((hFind = ::FindFirstFile ((LPCTSTR) strDirName, &fd)) !=
            INVALID_HANDLE_VALUE) {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                list.AddTail (strDirName);
            else
                GetTreeCtrl ().DeleteItem (hChild);
            ::FindClose (hFind);
        }
        else
            GetTreeCtrl ().DeleteItem (hChild);

        hChild = hNextItem;
    }

    // Add items for newly created subdirectories.
    if ((hFind = ::FindFirstFile ("*.*", &fd)) != INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                CString strFileName = (LPCTSTR) &fd.cFileName;
                if ((strFileName != ".") && (strFileName != "..")) {
                    if (list.Find (strFileName) == NULL) {
                        hChild = GetTreeCtrl ().InsertItem (strFileName,
                            ILI_CLOSED_FOLDER, ILI_OPEN_FOLDER,
                            hItem, TVI_SORT);
                        CString strPathName = GetPathFromItem (hChild);
                        SetButtonState (hChild, strPathName);
                        list.AddTail (strFileName);
                    }
                }
            }
        } while (::FindNextFile (hFind, &fd));
    ::FindClose (hFind);
    }

    // Remove all items from the CStringList.
    list.RemoveAll ();

    // Now repeat this procedure for hItem's children.
    hChild = GetTreeCtrl ().GetChildItem (hItem);

    while (hChild != NULL) {
        CString string = GetTreeCtrl ().GetItemText (hChild);
        ::SetCurrentDirectory ((LPCTSTR) string);
        RefreshDirectory (hChild); // Recursion!
        ::SetCurrentDirectory ("..");
        hChild = GetTreeCtrl ().GetNextSiblingItem (hChild);
    }
}

void CDriveView::CreateMonitoringThread (CString& strDrive)
{
    PTHREADINFO pThreadInfo = new THREADINFO; // Thread will delete
    pThreadInfo->nDrive = (UINT) strDrive[0] - 0x41;
    pThreadInfo->hEvent = m_event.m_hObject;
    pThreadInfo->hWnd = m_hWnd;

    CWinThread* pThread = AfxBeginThread (ThreadFunc, pThreadInfo,
        THREAD_PRIORITY_IDLE);

    m_hThreads[m_nThreadCount++] = pThread->m_hThread;
}

/////////////////////////////////////////////////////////////////////////
// Thread function for detecting file system changes

UINT CDriveView::ThreadFunc (LPVOID pParam)
{
    PTHREADINFO pThreadInfo = (PTHREADINFO) pParam;
    UINT nDrive = pThreadInfo->nDrive;
    HANDLE hEvent = pThreadInfo->hEvent;
    HWND hWnd = pThreadInfo->hWnd;
    delete pThreadInfo;

    CString strDrive = "?:\\";
    strDrive.SetAt (0, 0x41 + nDrive);
    
    // Get a handle to a file change notification object.
    HANDLE hChange = ::FindFirstChangeNotification ((LPCTSTR) strDrive,
        TRUE, FILE_NOTIFY_CHANGE_DIR_NAME);

    // Return now if ::FindFirstChangeNotification failed.
    if (hChange == INVALID_HANDLE_VALUE)
        return 1;

    HANDLE aHandles[2];
    aHandles[0] = hChange;
    aHandles[1] = hEvent;
    BOOL bContinue = TRUE;

    // Sleep until a file change notification wakes this thread or
    // m_event becomes set indicating it's time for the thread to end.
    while (bContinue) {
        if (::WaitForMultipleObjects (2, aHandles, FALSE, INFINITE) -
            WAIT_OBJECT_0 == 0) { // Respond to a change notification.
            ::PostMessage (hWnd, WM_USER, (WPARAM) nDrive, 0);
            ::FindNextChangeNotification (hChange);
        }
        else // Kill this thread (m_event became signaled).
            bContinue = FALSE;
    }

    // Close the file change notification handle and return.
    ::FindCloseChangeNotification (hChange);
    return 0;
}


