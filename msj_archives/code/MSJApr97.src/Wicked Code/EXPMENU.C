//***************************************************************************
//
//  ExpMenu.c
//
//***************************************************************************

#include <windows.h>
#include <commctrl.h>
#include <shlobj.h>
#include "ExpMenu.h"

/////////////////////////////////////////////////////////////////////////////
// Function prototypes

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

void PopulateListView (HWND);
void AddItemToListView (HWND, WIN32_FIND_DATA*);

BOOL DoExplorerMenu (HWND, LPCTSTR, POINT);
UINT GetItemCount (LPITEMIDLIST);
LPITEMIDLIST GetNextItem (LPITEMIDLIST);
LPITEMIDLIST DuplicateItem (LPMALLOC, LPITEMIDLIST);

/////////////////////////////////////////////////////////////////////////////
// WinMain

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpszCmdLine, int nCmdShow)
{
    static char szWndClassName[] = "ExpMenuWndClass";
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    wc.style = 0;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szWndClassName;

    RegisterClass (&wc);

    hwnd = CreateWindow (szWndClassName, "Explorer Context Menu Demo",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, HWND_DESKTOP, NULL, hInstance, NULL);

    ShowWindow (hwnd, nCmdShow);
    UpdateWindow (hwnd);

    while (GetMessage (&msg, NULL, 0, 0)) {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
    return msg.wParam;
}

/////////////////////////////////////////////////////////////////////////////
// Window procedure

LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HBITMAP hBitmap;
    HINSTANCE hInstance;
    LV_HITTESTINFO hti; 
    LPNMHDR pnmhdr;
    char szLabel[MAX_PATH];
    char szPath[MAX_PATH];
    DWORD dwPos;

    static HWND hwndListView;
    static HIMAGELIST hImageList;

    switch (msg) {

    case WM_CREATE:
        //
        // Create a list view control in the main window.
        //
        InitCommonControls ();
        hInstance = ((LPCREATESTRUCT) lParam)->hInstance;

        hwndListView = CreateWindowEx (WS_EX_CLIENTEDGE, WC_LISTVIEW, "",
            WS_CHILD | WS_VISIBLE | LVS_ICON | LVS_SINGLESEL | LVS_AUTOARRANGE,
            0, 0, 0, 0, hwnd, (HMENU) ID_LISTVIEW, hInstance, NULL);

        hBitmap = LoadBitmap (hInstance, MAKEINTRESOURCE (ID_BITMAP));
        hImageList = ImageList_Create (32, 32, ILC_MASK, 2, 1);
        ImageList_AddMasked (hImageList, hBitmap, RGB (255, 0, 255));
        DeleteObject (hBitmap);

        ListView_SetImageList (hwndListView, hImageList, LVSIL_NORMAL);
        PopulateListView (hwndListView);
        return 0;

    case WM_SIZE:
        //
        // Resize the list view to fit the client area of its parent.
        //
        if ((wParam == SIZE_RESTORED) || (wParam == SIZE_MAXIMIZED))
            SetWindowPos (hwndListView, NULL, 0, 0, (int) LOWORD (lParam),
                (int) HIWORD (lParam), SWP_NOMOVE | SWP_NOZORDER); 
        return 0;

    case WM_NOTIFY:
        //
        // Display a context menu when something is right-clicked.
        //
        pnmhdr = (LPNMHDR) lParam;

        if (pnmhdr->code == NM_RCLICK) {
            dwPos = GetMessagePos ();
            hti.pt.x = (int) LOWORD (dwPos);
            hti.pt.y = (int) HIWORD (dwPos);
            ScreenToClient (hwnd, &hti.pt);

            ListView_HitTest (hwndListView, &hti);

            if (hti.flags & LVHT_ONITEM) {
                ListView_GetItemText (hwndListView, hti.iItem, 0, szLabel,
                    sizeof (szLabel));

                GetWindowsDirectory (szPath, sizeof (szPath));
                if (szPath[lstrlen (szPath) - 1] != '\\')
                    lstrcat (szPath, "\\");
                lstrcat (szPath, szLabel);

                DoExplorerMenu (hwnd, szPath, hti.pt);

                //
                // NOTE: Here's a great place to refresh the list view control
                // in case a file or folder was created, renamed, or deleted
                // as a result of a context menu command. We don't do it here
                // because that's not the point of this example.
                //
            }
            return 0;
        }
        break;

    case WM_DESTROY:
        //
        // Clean up and terminate.
        //
        DestroyWindow (hwndListView);
        DeleteObject (hImageList);
        PostQuitMessage (0);
        return 0;
    }
    return DefWindowProc (hwnd, msg, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// Window procedure helper functions

void PopulateListView (HWND hwnd)
{
    WIN32_FIND_DATA fd;
    char szPath[MAX_PATH];
    HANDLE hFind;

    //
    // Get the path to the Windows directory and append "*.*".
    //
    GetWindowsDirectory (szPath, sizeof (szPath));
    if (szPath[lstrlen (szPath) - 1] != '\\')
        lstrcat (szPath, "\\");
    lstrcat (szPath, "*.*");

    //
    // Create one list view item for each file or folder.
    //
    if ((hFind = FindFirstFile (szPath, &fd)) != INVALID_HANDLE_VALUE) {
        AddItemToListView (hwnd, &fd);
        while (FindNextFile (hFind, &fd))
            AddItemToListView (hwnd, &fd);
        FindClose (hFind);
    }
}

void AddItemToListView (HWND hwnd, WIN32_FIND_DATA* pfd)
{
    LV_ITEM lvi;

    //
    // Initialize the LV_ITEM structure's iImage field to display a file or
    // folder icon, and skip "." and ".." folders.
    //
    if (pfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        if (pfd->cFileName[0] == '.')
            return;
        lvi.iImage = 1; // Folder
    }
    else
        lvi.iImage = 0; // File

    //
    // Initialize the remaining members of the LV_ITEM structure.
    //
    lvi.mask = LVIF_TEXT | LVIF_IMAGE;
    lvi.iItem = ListView_GetItemCount (hwnd);
    lvi.iSubItem = 0;
    lvi.pszText = pfd->cFileName;

    //
    // Add the item to the list view.
    //
    ListView_InsertItem (hwnd, &lvi);
}

/////////////////////////////////////////////////////////////////////////////
// Context menu functions

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  FUNCTION:       DoExplorerMenu
//
//  DESCRIPTION:    Given a path name to a file or folder object, displays
//                  the shell's context menu for that object and executes
//                  the menu command (if any) selected by the user.
//
//  INPUT:          hwnd    = Handle of the window in which the menu will be
//                            displayed.
//
//                  pszPath = Pointer to an ANSI or Unicode string
//                            specifying the path to the object.
//
//                  point   = x and y coordinates of the point where the
//                            menu's upper left corner should be located, in
//                            client coordinates relative to hwnd.
//  
//  RETURNS:        TRUE if successful, FALSE if not.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BOOL DoExplorerMenu (HWND hwnd, LPCTSTR pszPath, POINT point)
{
    LPMALLOC pMalloc;
    LPSHELLFOLDER psfFolder, psfNextFolder;
    LPITEMIDLIST pidlMain, pidlItem, pidlNextItem, *ppidl;
    LPCONTEXTMENU pContextMenu;
    CMINVOKECOMMANDINFO ici;
    ULONG ulCount, ulAttr;
    TCHAR tchPath[MAX_PATH];
    WCHAR wchPath[MAX_PATH];    
    UINT nCount, nCmd;
    BOOL bResult;
    HMENU hMenu;

    //
    // Make sure the file name is fully qualified and in Unicode format.
    //
    GetFullPathName (pszPath, sizeof (tchPath) / sizeof (TCHAR), tchPath,
        NULL);

    if (IsTextUnicode (tchPath, lstrlen (tchPath), NULL))
        lstrcpy ((char *) wchPath, tchPath);
    else
        MultiByteToWideChar (CP_ACP, 0, pszPath, -1, wchPath,
            sizeof (wchPath) / sizeof (WCHAR));

    //
    // Get pointers to the shell's IMalloc interface and the desktop's
    // IShellFolder interface.
    //
    bResult = FALSE;

    if (!SUCCEEDED (SHGetMalloc (&pMalloc)))
        return bResult;

    if (!SUCCEEDED (SHGetDesktopFolder (&psfFolder))) {
        pMalloc->lpVtbl->Release (pMalloc);
        return bResult;
    }

    //
    // Convert the path name into a pointer to an item ID list (pidl).
    //
    if (SUCCEEDED (psfFolder->lpVtbl->ParseDisplayName (psfFolder, hwnd,
        NULL, wchPath, &ulCount, &pidlMain, &ulAttr)) && (pidlMain != NULL)) {

        if (nCount = GetItemCount (pidlMain)) { // nCount must be > 0
            //
            // Initialize psfFolder with a pointer to the IShellFolder
            // interface of the folder that contains the item whose context
            // menu we're after, and initialize pidlItem with a pointer to
            // the item's item ID. If nCount > 1, this requires us to walk
            // the list of item IDs stored in pidlMain and bind to each
            // subfolder referenced in the list.
            //
            pidlItem = pidlMain;

            while (--nCount) {
                //
                // Create a 1-item item ID list for the next item in pidlMain.
                //
                pidlNextItem = DuplicateItem (pMalloc, pidlItem);
                if (pidlNextItem == NULL) {
                    pMalloc->lpVtbl->Free (pMalloc, pidlMain);
                    psfFolder->lpVtbl->Release (psfFolder);
                    pMalloc->lpVtbl->Release (pMalloc);
                    return bResult;
                }

                //
                // Bind to the folder specified in the new item ID list.
                //
                if (!SUCCEEDED (psfFolder->lpVtbl->BindToObject (psfFolder,
                    pidlNextItem, NULL, &IID_IShellFolder, &psfNextFolder))) {
                    pMalloc->lpVtbl->Free (pMalloc, pidlNextItem);
                    pMalloc->lpVtbl->Free (pMalloc, pidlMain);
                    psfFolder->lpVtbl->Release (psfFolder);
                    pMalloc->lpVtbl->Release (pMalloc);
                    return bResult;
                }

                //
                // Release the IShellFolder pointer to the parent folder
                // and set psfFolder equal to the IShellFolder pointer for
                // the current folder.
                //
                psfFolder->lpVtbl->Release (psfFolder);
                psfFolder = psfNextFolder;

                //
                // Release the storage for the 1-item item ID list we created
                // just a moment ago and initialize pidlItem so that it points
                // to the next item in pidlMain.
                //
                pMalloc->lpVtbl->Free (pMalloc, pidlNextItem);
                pidlItem = GetNextItem (pidlItem);
            }

            //
            // Get a pointer to the item's IContextMenu interface and call
            // IContextMenu::QueryContextMenu to initialize a context menu.
            //
            ppidl = &pidlItem;
            if (SUCCEEDED (psfFolder->lpVtbl->GetUIObjectOf (psfFolder,
                hwnd, 1, ppidl, &IID_IContextMenu, NULL, &pContextMenu))) {

                hMenu = CreatePopupMenu ();
                if (SUCCEEDED (pContextMenu->lpVtbl->QueryContextMenu (
                    pContextMenu, hMenu, 0, 1, 0x7FFF, CMF_EXPLORE))) {

                    ClientToScreen (hwnd, &point);

                    //
                    // Display the context menu.
                    //
                    nCmd = TrackPopupMenu (hMenu, TPM_LEFTALIGN |
                        TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD,
                        point.x, point.y, 0, hwnd, NULL);

                    //
                    // If a command was selected from the menu, execute it.
                    //
                    if (nCmd) {
                        ici.cbSize          = sizeof (CMINVOKECOMMANDINFO);
                        ici.fMask           = 0;
                        ici.hwnd            = hwnd;
                        ici.lpVerb          = MAKEINTRESOURCE (nCmd - 1);
                        ici.lpParameters    = NULL;
                        ici.lpDirectory     = NULL;
                        ici.nShow           = SW_SHOWNORMAL;
                        ici.dwHotKey        = 0;
                        ici.hIcon           = NULL;

                        if (SUCCEEDED (
                            pContextMenu->lpVtbl->InvokeCommand (
                            pContextMenu, &ici)))
                            bResult = TRUE;
                    }
                }
                DestroyMenu (hMenu);
                pContextMenu->lpVtbl->Release (pContextMenu);
            }
        }
        pMalloc->lpVtbl->Free (pMalloc, pidlMain);
    }

    //
    // Clean up and return.
    //
    psfFolder->lpVtbl->Release (psfFolder);
    pMalloc->lpVtbl->Release (pMalloc);

    return bResult;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  FUNCTION:       GetItemCount
//
//  DESCRIPTION:    Computes the number of item IDs in an item ID list.
//
//  INPUT:          pidl = Pointer to an item ID list.
//
//  RETURNS:        Number of item IDs in the list.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

UINT GetItemCount (LPITEMIDLIST pidl)
{
    USHORT nLen;
    UINT nCount;

    nCount = 0;
    while ((nLen = pidl->mkid.cb) != 0) {
        pidl = GetNextItem (pidl);
        nCount++;
    }
    return nCount;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  FUNCTION:       GetNextItem
//
//  DESCRIPTION:    Finds the next item in an item ID list.
//
//  INPUT:          pidl = Pointer to an item ID list.
//
//  RETURNS:        Pointer to the next item.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LPITEMIDLIST GetNextItem (LPITEMIDLIST pidl)
{
    USHORT nLen;

    if ((nLen = pidl->mkid.cb) == 0)
        return NULL;
    
    return (LPITEMIDLIST) (((LPBYTE) pidl) + nLen);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  FUNCTION:       DuplicateItem
//
//  DESCRIPTION:    Makes a copy of the next item in an item ID list.
//
//  INPUT:          pMalloc = Pointer to an IMalloc interface.
//                  pidl    = Pointer to an item ID list.
//
//  RETURNS:        Pointer to an ITEMIDLIST containing the copied item ID.
//
//  NOTES:          It is the caller's responsibility to free the memory
//                  allocated by this function when the item ID is no longer
//                  needed. Example:
//
//                    pidlItem = DuplicateItem (pMalloc, pidl);
//                      .
//                      .
//                      .
//                    pMalloc->lpVtbl->Free (pMalloc, pidlItem);
//
//                  Failure to free the ITEMIDLIST will result in memory
//                  leaks.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LPITEMIDLIST DuplicateItem (LPMALLOC pMalloc, LPITEMIDLIST pidl)
{
    USHORT nLen;
    LPITEMIDLIST pidlNew;

    nLen = pidl->mkid.cb;
    if (nLen == 0)
        return NULL;

    pidlNew = (LPITEMIDLIST) pMalloc->lpVtbl->Alloc (pMalloc,
        nLen + sizeof (USHORT));
    if (pidlNew == NULL)
        return NULL;

    CopyMemory (pidlNew, pidl, nLen);
    *((USHORT*) (((LPBYTE) pidlNew) + nLen)) = 0;

    return pidlNew;
}
