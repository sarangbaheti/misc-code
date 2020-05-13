//=============================================================
// Matt Pietrek
// Microsoft Systems Journal, November 1997
// FILE: TH32DEMO.C
//=============================================================
#define _WIN32_WINNT 0x0500     // Needed for call to AnimateWindow
#include <windows.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <tlhelp32.h>
#include "TH32DEMO.h"

typedef struct      // Information passed to the HeapWalk dialog in the LPARAM
{
    DWORD processID;
    DWORD heapID;
} PROCESSHEAP_IDS, *PPROCESSHEAP_IDS;

typedef struct      // One of these allocated for each in-use block displayed
{                   // in the HeapWalk dialog
    DWORD processID;
    DWORD address;
    DWORD dwSize;
} IN_USE_HEAP_BLOCK, *PIN_USE_HEAP_BLOCK;

// Helper functions
BOOL CALLBACK TH32DemoDlgProc(HWND, UINT, WPARAM, LPARAM);
void Handle_WM_COMMAND(HWND hWndDlg, WPARAM wParam, LPARAM lParam);
void Handle_WM_INITDIALOG(HWND hWndDlg);
void UpdateProcesses( HWND hWndDlg );
void Handle_ProcessSelection( HWND hWndDlg, DWORD processID );

BOOL CALLBACK TH32HeapWalkDlgProc(HWND, UINT, WPARAM, LPARAM);
void Handle_HeapWalkDlg_WM_INITDIALOG(HWND, WPARAM, LPARAM);
void Handle_HeapWalkDlg_WM_COMMAND(HWND, WPARAM, LPARAM);

unsigned lbprintf(HWND hWnd, char * format, ...);
unsigned GetListboxSelectedItemData( HWND hWndLb );

// ======================= Global Variables ===============================
HANDLE ghInstance;      // hInstance for this app
DWORD gCurrentProcess;  // Process ID of currently selected process

// ======================= Start of code ===============================

int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszCmdLine, int nCmdShow )
{
    WNDCLASS wndclass;
        
    // Kludge-0-Rama to make the dialog box use our own icon
    if ( !GetClassInfo( 0, MAKEINTRESOURCE(32770), &wndclass ) )
        return 0;
    wndclass.hInstance = ghInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance,"TH32DEMO_Icon");
    wndclass.lpszClassName = "TH32DEMO_DLG";
    if ( !RegisterClass(&wndclass) )
        return 0;
    
    // The user interface is a modal dialog box
    DialogBox( ghInstance, "TH32DEMO_DLG", 0, (DLGPROC)TH32DemoDlgProc );
    return 0;
}

// ================= Start of user interface code ========================

//
// Dialog proc for the main dialog
//
BOOL CALLBACK TH32DemoDlgProc(HWND hWndDlg, UINT msg,
                              WPARAM wParam, LPARAM lParam )
{
    switch ( msg )
    {
        case WM_COMMAND:
            Handle_WM_COMMAND(hWndDlg, wParam, lParam); return TRUE;
        case WM_INITDIALOG:
            Handle_WM_INITDIALOG(hWndDlg); return TRUE;
        case WM_CLOSE:
            EndDialog(hWndDlg, 0); return FALSE;
    }
    return FALSE;
}

void Handle_WM_COMMAND(HWND hWndDlg, WPARAM wParam, LPARAM lParam)
{
    switch ( LOWORD(wParam) )
    {
        case IDC_PUSHBUTTON_REFRESH:
            UpdateProcesses( hWndDlg );
            break;
            
        case IDC_LISTBOX_PROCESSES:
            // When the user clicks on or arrow-keys to a new process
            if ( HIWORD(wParam) == LBN_SELCHANGE )
            {
                // Get process ID we stored away in the listbox item data
                gCurrentProcess = GetListboxSelectedItemData( (HWND)lParam );
                Handle_ProcessSelection( hWndDlg, gCurrentProcess );
            }
            break;
            
        case IDC_LISTBOX_HEAPS:
            // For when the user double clicks on a process heap line
            if ( HIWORD(wParam) == LBN_DBLCLK )
            {
                PROCESSHEAP_IDS ph_ids;

                // Get the heap ID we stored away in the listbox item data
                ph_ids.heapID = GetListboxSelectedItemData( (HWND)lParam );
                ph_ids.processID = gCurrentProcess;

                // Invoke HeapWalk dialog
                DialogBoxParam( ghInstance, "HEAPWALK_DLG", hWndDlg,
                                (DLGPROC)TH32HeapWalkDlgProc,(LPARAM)&ph_ids );
            }
            break;
    }
    return;
}

void Handle_WM_INITDIALOG(HWND hWndDlg)
{
    DWORD tabStops = 20;

    // Set appropriate tab stops in all the listboxes of the main dialog
    SendDlgItemMessage( hWndDlg, IDC_LISTBOX_PROCESSES,
                        LB_SETTABSTOPS, 1, (LPARAM)&tabStops );
    SendDlgItemMessage( hWndDlg, IDC_LISTBOX_THREADS,
                        LB_SETTABSTOPS, 1, (LPARAM)&tabStops );
    SendDlgItemMessage( hWndDlg, IDC_LISTBOX_HEAPS,
                        LB_SETTABSTOPS, 1, (LPARAM)&tabStops );
    SendDlgItemMessage( hWndDlg, IDC_LISTBOX_MODULES,
                        LB_SETTABSTOPS, 1, (LPARAM)&tabStops );

    // Fill in the process listbox (and in a cascade reaction, update
    // all the other listboxes )
    UpdateProcesses( hWndDlg );

    // Set focus to the main listbox (the process list)
    SetFocus( GetDlgItem(hWndDlg, IDC_LISTBOX_PROCESSES) );

    // Cool blend in animation effect
    AnimateWindow( hWndDlg, 10, AW_BLEND | AW_ACTIVATE );
}

// Walks the process list and updates the top listbox in the main dialog
void UpdateProcesses( HWND hWndDlg )
{
    HWND hWndLb;
    HANDLE hSnapshot;
    BOOL fOK;
    PROCESSENTRY32 pe32;
    char szBuffer[32];
    unsigned cProcesses = 0;

    // Get the HWND for the process listbox, since we'll be using it a lot
    hWndLb = GetDlgItem( hWndDlg, IDC_LISTBOX_PROCESSES );

    // Clear out the process listbox
    SendMessage( hWndLb, LB_RESETCONTENT, 0, 0 );

    // create a process snapshot and walk through the process list, adding
    // each process to the top listbox
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if ( !hSnapshot )
        return;
    
    pe32.dwSize = sizeof(pe32);     // Gotta initialize dwSize!
    for ( fOK = Process32First( hSnapshot, &pe32 );
          fOK;
          fOK = Process32Next( hSnapshot, &pe32 ) )
    {
        unsigned lbIndex;
        lbIndex = lbprintf(hWndLb,"ID:%08X\t%s",
                            pe32.th32ProcessID,pe32.szExeFile);
                        
        // Use listbox item data to associate the process ID with each
        // line that we add to the listbox
        SendMessage( hWndLb, LB_SETITEMDATA, lbIndex, pe32.th32ProcessID );

        cProcesses++;   // Keep track of how many processes we saw
    }
    
    CloseHandle( hSnapshot );   // Done with this snapshot.  Free it

    // Update the title of the process listbox to reflect the # of processes
    wsprintf( szBuffer, "Processes: %u", cProcesses );
    SetDlgItemText( hWndDlg, IDC_STATIC_CPROCESSES, szBuffer );

    // Set the selection to the first process in the list and force the
    // other listboxes to update accordingly.
    SendMessage( hWndLb, LB_SETCURSEL, 0, 0 );
    gCurrentProcess = GetListboxSelectedItemData( hWndLb );
    Handle_ProcessSelection( hWndDlg, gCurrentProcess );
}

void UpdateThreadsListbox( HWND hWndDlg, DWORD processID )
{
    HWND hWndThreadsLb;
    HANDLE hSnapshot;
    BOOL fOK;
    THREADENTRY32 te32;
    char szBuffer[32];
    unsigned cThreads = 0;
    
    // Get the HWND for the threads listbox, since we'll be using it a lot
    hWndThreadsLb = GetDlgItem( hWndDlg, IDC_LISTBOX_THREADS );

    // Clear out the threads listbox
    SendMessage( hWndThreadsLb, LB_RESETCONTENT, 0, 0 );
    
    // create a threads snapshot and walk through the thread list, adding
    // each thread with the correct process ID to the threads listbox
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 );
    if ( !hSnapshot )
        return;
    
    te32.dwSize = sizeof(te32);     // Gotta initialize dwSize!
    for ( fOK = Thread32First( hSnapshot, &te32 );
          fOK;
          fOK = Thread32Next( hSnapshot, &te32 ) )
    {
        if ( te32.th32OwnerProcessID != processID )
            continue;
        
        lbprintf( hWndThreadsLb,"ID:%08X\tpri:%u",
                    te32.th32ThreadID, te32.tpBasePri + te32.tpDeltaPri );

        cThreads++;     // Keep track of how many processes we saw
    }
    
    CloseHandle( hSnapshot );   // Done with this snapshot.  Free it

    // Update the title of the threads listbox to reflect the # of threads
    wsprintf( szBuffer, "Threads: %u", cThreads );
    SetDlgItemText( hWndDlg, IDC_STATIC_CTHREADS, szBuffer );
}

void UpdateHeapsListbox( HWND hWndDlg, DWORD processID )
{
    HWND hWndHeapsLb;
    HANDLE hSnapshot;
    BOOL fOK;
    HEAPLIST32 hl32;
    
    // Get the HWND for the heaps listbox, since we'll be using it a lot
    hWndHeapsLb = GetDlgItem( hWndDlg, IDC_LISTBOX_HEAPS );

    // Clear out the heaps listbox
    SendMessage( hWndHeapsLb, LB_RESETCONTENT, 0, 0 );
    
    // create a process heap list snapshot and walk through the list, adding
    // each heap to the heaps listbox
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPHEAPLIST, processID );
    if ( !hSnapshot )
        return;
    
    hl32.dwSize = sizeof(hl32);     // Gotta initialize dwSize!
    for ( fOK = Heap32ListFirst( hSnapshot, &hl32 );
          fOK;
          fOK = Heap32ListNext( hSnapshot, &hl32 ) )
    {
        unsigned lbIndex;
        lbIndex = lbprintf( hWndHeapsLb,"ID:%08X\t%s %s",
                            hl32.th32HeapID,
                            hl32.dwFlags & HF32_DEFAULT ? "default" : "",
                            hl32.dwFlags & HF32_SHARED ? "Shared" : "" );

        // Use listbox item data to associate the heap ID with each
        // line that we add to the listbox
        SendMessage( hWndHeapsLb, LB_SETITEMDATA, lbIndex, hl32.th32HeapID );
    }
    
    CloseHandle( hSnapshot );   // Done with this snapshot.  Free it
}

void UpdateModulesListbox( HWND hWndDlg, DWORD processID )
{
    HWND hWndModsLb;
    HANDLE hSnapshot;
    BOOL fOK;
    MODULEENTRY32 me32;
    
    // Get the HWND for the modules listbox, since we'll be using it a lot
    hWndModsLb = GetDlgItem( hWndDlg, IDC_LISTBOX_MODULES );

    // Clear out the heaps listbox
    SendMessage( hWndModsLb, LB_RESETCONTENT, 0, 0 );
    
    // create a process module snapshot and walk through the list, adding
    // each module to the Modules listbox
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, processID );
    if ( !hSnapshot )
        return;
    
    me32.dwSize = sizeof(me32);     // Gotta initialize dwSize!
    for ( fOK = Module32First( hSnapshot, &me32 );
          fOK;
          fOK = Module32Next( hSnapshot, &me32 ) )
    {
        if ( 0 == me32.hModule )
            break;

        lbprintf( hWndModsLb,"Base:%08X\tRef:%02u\t%s",
                    me32.hModule, me32.ProccntUsage, me32.szExePath );
    }
    
    CloseHandle( hSnapshot );   // Done with this snapshot.  Free it
}

void Handle_ProcessSelection( HWND hWndDlg, DWORD processID )
{
    // Whenever a new process is selected in the top listbox, force an
    // update of the threads, heaps, and modules listboxes
    UpdateThreadsListbox( hWndDlg, processID );
    UpdateHeapsListbox( hWndDlg, processID );
    UpdateModulesListbox( hWndDlg, processID );
}

//========================== HeapWalkDlg code ===============================

// Dialog code for the child dialog that comes up after double clicking
// on a process heap in the main dialog.
BOOL CALLBACK TH32HeapWalkDlgProc(HWND hWndDlg, UINT msg,
                              WPARAM wParam, LPARAM lParam )
{
    switch ( msg )
    {
        case WM_COMMAND:
            Handle_HeapWalkDlg_WM_COMMAND( hWndDlg, wParam, lParam );
            return FALSE;

        case WM_INITDIALOG:
            Handle_HeapWalkDlg_WM_INITDIALOG( hWndDlg, wParam, lParam );
            return TRUE;

        case WM_DELETEITEM:
            if ( wParam == IDC_HEAP_LISTBOX )
            {
                // The listbox is being destroyed.  Free the memory whose
                // pointer we previously stored in the listbox's item data
                free( (PVOID)((LPDELETEITEMSTRUCT)lParam)->itemData );
                return TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hWndDlg, 0);
            return TRUE;
    }

    return FALSE;
}

void Handle_HeapWalkDlg_WM_INITDIALOG(  HWND hWndDlg,
                                        WPARAM wParam, LPARAM lParam )
{
    BOOL fOK;
    PPROCESSHEAP_IDS ph_ids = (PPROCESSHEAP_IDS)lParam;
    HEAPENTRY32 he32;
    HWND hWndLb;
    DWORD tabStops = 20;

    // Get the HWND for the heap blocks listbox, since we'll be using it a lot
    hWndLb = GetDlgItem( hWndDlg, IDC_HEAP_LISTBOX );

    // Clear out the heap blocks listbox
    SendMessage( hWndLb, LB_SETTABSTOPS, 1, (LPARAM)&tabStops );

    // Set the edit control at the bottom to use a fixed font (it looks
    // better when displaying hex data)
    SendDlgItemMessage( hWndDlg, IDC_EDIT_BLOCK_DATA, WM_SETFONT,
                        (WPARAM)GetStockObject(OEM_FIXED_FONT), 0 );

    // Walk through all the blocks in the specified heap, adding
    // each block's information to the top listbox
    he32.dwSize = sizeof(he32);     // Gotta initialize dwSize!
    for (fOK=Heap32First(&he32, ph_ids->processID, ph_ids->heapID); 
         fOK;
         fOK = Heap32Next(&he32) )
    {
        unsigned lbIndex;
        lbIndex = lbprintf( hWndLb, "Addr:%08X\tHndl:%08X\t%04u bytes %s",
                            he32.dwAddress, he32.hHandle, he32.dwBlockSize,
                            he32.dwFlags & LF32_FREE ? "Free":"");

        // If it's an in-use block, allocate memory and store off info
        // about the block so that we can display it's contents later.
        if ( 0 == (he32.dwFlags & LF32_FREE) )
        {
            PIN_USE_HEAP_BLOCK pBlock;
            if ( pBlock = malloc(sizeof(IN_USE_HEAP_BLOCK)) )
            {
                pBlock->processID = ph_ids->processID;
                pBlock->address = he32.dwAddress;
                pBlock->dwSize = he32.dwBlockSize;
                SendMessage( hWndLb, LB_SETITEMDATA, lbIndex, (LPARAM)pBlock );
            }
        }
    }   
}

void Handle_HeapWalkDlg_WM_COMMAND(HWND hWndDlg, WPARAM wParam, LPARAM lParam)
{
    switch( LOWORD(wParam) )
    {
        case IDOK:
            EndDialog(hWndDlg, 0);
            return;

        case IDC_HEAP_LISTBOX:
            // The user has clicked on or arrow-keyed to a new entry in
            // the heap block listbox.  Update the edit control at the
            // bottom of the dialog to show up to the first 32 bytes of
            // the block in hex format.
            if ( HIWORD(wParam) == LBN_SELCHANGE )
            {
                PIN_USE_HEAP_BLOCK pBlock;
                #define MAX_DATA_BYTES 32   
                unsigned cbMax, i = 0;
                char szBuffer[ 3 * MAX_DATA_BYTES + 128 ];
                PSTR pszBuffer;
                char data[MAX_DATA_BYTES];

                // clear out the bottom edit control
                SetDlgItemText( hWndDlg, IDC_EDIT_BLOCK_DATA, "" );

                // Now see if there's any info associated with this block.
                // If not, the edit control has already been cleared out,
                // so we can just bail out now.
                pBlock =(PIN_USE_HEAP_BLOCK)
                        GetListboxSelectedItemData( (HWND)lParam );
                if ( !pBlock )
                    return;

                // Read from the target process either the first 32 bytes of
                // the heap block or the total size of the heap block,
                // whichever is less.
                cbMax = min( pBlock->dwSize, MAX_DATA_BYTES );
                if ( !Toolhelp32ReadProcessMemory(  pBlock->processID,
                                                    (PVOID)pBlock->address,
                                                    data,
                                                    cbMax,
                                                    &cbMax ) )
                    return;

                // Gnarly code to format the hex dump data into a string.
                szBuffer[0] = 0;
                pszBuffer = szBuffer;
                while ( i < cbMax )
                {
                    // Show 8 bytes per line
                    if ( 0 == (i % 8) )
                        pszBuffer += wsprintf( pszBuffer,
                                                "%s%08X: ",
                                                i ? "\r\n" : "",
                                                pBlock->address + i );
                                            
                    pszBuffer += wsprintf( pszBuffer, "%02X ",
                                            *(PBYTE)(data + i) );
                    i++;
                }

                // Dump the formatted string into the bottom edit control
                SetDlgItemText( hWndDlg, IDC_EDIT_BLOCK_DATA, szBuffer );
            }
            break;
    }
}

//=================== General purpose helper routines ======================

// A printf for listboxes.  Acts just like printf, except that the first
// parameter is a listbox that the output should be appended to.
unsigned lbprintf(HWND hWnd, char * format, ...)
{
    char szBuffer[4096];
    va_list argptr;
          
    va_start(argptr, format);
    wvsprintf(szBuffer, format, argptr);
    va_end(argptr);

    return SendMessage( hWnd, LB_ADDSTRING, 0, (LPARAM)szBuffer );
}

// Get the item data associated with the currently selected item in a listbox
unsigned GetListboxSelectedItemData( HWND hWndLb )
{
    DWORD curSel;
    curSel = SendMessage( hWndLb, LB_GETCURSEL, 0, 0 );
    return SendMessage( hWndLb, LB_GETITEMDATA, curSel, 0);
}
