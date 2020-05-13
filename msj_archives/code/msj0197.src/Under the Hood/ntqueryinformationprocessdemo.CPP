//==================================================
// NTQUERYINFORMATIONPROCESSDEMO - Matt Pietrek 1997
// Microsoft Systems Journal, January 1997
// FILE: NTQUERYINFORMATIONPROCESSDEMO.CPP
//==================================================
#include <windows.h>
#include <stdio.h>
#pragma hdrstop
#include "psapi.h"
#include "ntqueryinformationprocess.h"
#include "ntqueryinformationprocessdemo.h"

// Helper function prototypes
void    Handle_WM_COMMAND(HWND hDlg, WPARAM wParam, LPARAM lParam);
void    Handle_WM_INITDIALOG(HWND hDlg);
void    Handle_WM_CLOSE( HWND hDlg );
BOOL    CALLBACK NtQueryInformationProcessDemoDlgProc(HWND,UINT,WPARAM,LPARAM);
int     lbprintf(HWND hWnd, char * format, ...);
void    StrFromLONGLONG( LONGLONG val , PSTR szOut );
DWORD   GetDlgSelectedItemData( HWND hDlg, int ctlID );
void    FakeFirstLbItemSelection( HWND hDlg, int listboxID );
void    GetSetPositionInfoFromRegistry( BOOL fSave, POINT *lppt );

// ======================= String literals ===============================
char gszRegistryKey[]
    = "Software\\WheatyProductions\\NtQueryInformationProcessDemo";

char g_AboutMsgTxt[] =
    "NtQueryInformationProcessDemo shows processes information obtained "
    "from the NtQueryInformationProcess function";

char g_AboutTitleTxt[]
    = "NtQueryInformationProcessDemo - Matt Pietrek 1997, for MSJ";

// ======================= Start of code ===============================

//
// Wrapper function around NtQueryInformationProcess.  Lets you pass
// in a PID, and takes care of creating and closing a process handle.
// Also takes care of other housecleaning work.
//
BOOL QueryProcessInformation(   DWORD pid,
                                PROCESSINFOCLASS infoEnum,
                                void * pBuffer,
                                unsigned cbBuffer )
{
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, pid );
    if ( !hProcess )
        return FALSE;

    // Zero the input buffer that NtQueryInformationProcess sees
    memset( pBuffer, 0, cbBuffer );

    DWORD retLen;
    int retValue;

    retValue = NtQueryInformationProcess(   hProcess, infoEnum,
                                            pBuffer, cbBuffer, &retLen );

    CloseHandle( hProcess );

    if ( retValue < 0 ) // NtQueryInformationProcess returns a negative
        return FALSE;   // value if it fails

    return TRUE;
}

//
// Using functions from PSAPI.DLL, update the listbox in the upper left
// corner, and store the associated PID with each entry.
//
void UpdateProcessList( HWND hDlg )
{
    // Get the treeview's HWND, then clear it
    HWND hWnd = GetDlgItem( hDlg,IDC_LB_PROCESSES );

    // Get the list of process IDs
    DWORD aProcesses[1024], cbNeeded;
    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return;
    
    // Calculate how many process IDs were returned
    DWORD cProcesses = cbNeeded / sizeof(DWORD);

    // Spit out the information for each ID
    for ( unsigned i = 0; i < cProcesses; i++ )
    {
        char szProcessName[MAX_PATH] = "unknown";
        DWORD pid = aProcesses[i];
        
        HANDLE hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
                                        PROCESS_VM_READ,
                                        FALSE, pid );

        if ( !hProcess )    // OpenProcess failed...
            continue;

        HMODULE hMod;
        DWORD cbNeeded;
    
        // Get just the first module in the process.  This appears to
        // always be the executable file.    
        if ( EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                                sizeof(szProcessName) );
        }

        CloseHandle( hProcess );

        // Add the string to the process listbox, and associate the PID with it
        long lbIndex = lbprintf( hWnd, "%3X %s", pid, szProcessName );
        SendMessage( hWnd, LB_SETITEMDATA, lbIndex, pid );
    }
}

// Helper function called by UpdateProcessInfoFields
void UpdateProcessBasicInformation( HWND hDlg, DWORD pid )
{
    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_BASIC_INFO );
    SendMessage( hWndLb, LB_RESETCONTENT, 0, 0 );

    PROCESS_BASIC_INFORMATION pbi;
    if ( QueryProcessInformation(   pid, ProcessBasicInformation,
                                    &pbi, sizeof(pbi)) )
    {
        lbprintf( hWndLb, "ExitStatus: %X", pbi.ExitStatus );
        lbprintf( hWndLb, "PebBaseAddress: %08X", pbi.PebBaseAddress );
        lbprintf( hWndLb, "AffinityMask: %08X", pbi.AffinityMask );
        lbprintf( hWndLb, "BasePriority: %X", pbi.BasePriority );
        lbprintf( hWndLb, "UniqueProcessId: %X", pbi.UniqueProcessId );
        lbprintf( hWndLb, "InheritedFromProcessId: %X",
                            pbi.InheritedFromUniqueProcessId );
    }
}

// Helper function called by UpdateProcessInfoFields
void UpdateProcessMiscFields( HWND hDlg, DWORD pid )
{
    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_MISC );
    SendMessage( hWndLb, LB_RESETCONTENT, 0, 0 );

    DWORD dwVal;

    if ( QueryProcessInformation(pid, ProcessDebugPort, &dwVal, sizeof(dwVal)))
        lbprintf( hWndLb, "DebugPort: %08X", dwVal );

    if ( QueryProcessInformation(   pid, ProcessDefaultHardErrorMode,
                                    &dwVal, sizeof(dwVal)) )
        lbprintf( hWndLb, "DefaultHardErrorMode: %08X", dwVal );

    if ( QueryProcessInformation(   pid, ProcessWx86Information,
                                    &dwVal, sizeof(dwVal)))
        lbprintf( hWndLb, "Wx86Information: %08X", dwVal );

    if ( QueryProcessInformation(pid, ProcessHandleCount,&dwVal,sizeof(dwVal)))
        lbprintf( hWndLb, "HandleCount: %X", dwVal );

    if (QueryProcessInformation(pid,ProcessPriorityBoost,&dwVal,sizeof(dwVal)))
        lbprintf( hWndLb, "PriorityBoost: %X", dwVal );

}

// Helper function called by UpdateProcessInfoFields
void UpdateQuotaLimits( HWND hDlg, DWORD pid )
{
    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_QUOTA_LIMITS );
    SendMessage( hWndLb, LB_RESETCONTENT, 0, 0 );

    QUOTA_LIMITS ql;
    if ( QueryProcessInformation(pid, ProcessQuotaLimits, &ql, sizeof(ql)) )
    {
        lbprintf( hWndLb, "PagedPoolLimit: %08X", ql.PagedPoolLimit );
        lbprintf( hWndLb, "NonPagedPoolLimit: %08X", ql.NonPagedPoolLimit );
        lbprintf( hWndLb, "MinimumWorkingSetSize: %08X", ql.MinimumWorkingSetSize );
        lbprintf( hWndLb, "MaximumWorkingSetSize: %08X", ql.MaximumWorkingSetSize );
        lbprintf( hWndLb, "PagefileLimit: %08X", ql.PagefileLimit );

        char szTimeLimit[64];
        StrFromLONGLONG( ql.PagefileLimit, szTimeLimit );
        lbprintf( hWndLb, "TimeLimit: %s", szTimeLimit );
    }
}

// Helper function called by UpdateProcessInfoFields
void UpdateVmCounters( HWND hDlg, DWORD pid )
{
    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_VM_COUNTERS );
    SendMessage( hWndLb, LB_RESETCONTENT, 0, 0 );

    VM_COUNTERS vmc;
    if ( QueryProcessInformation( pid, ProcessVmCounters, &vmc, sizeof(vmc)) )
    {
        lbprintf( hWndLb, "PeakVirtualSize: %08X", vmc.PeakVirtualSize );
        lbprintf( hWndLb, "VirtualSize: %08X", vmc.VirtualSize );
        lbprintf( hWndLb, "PageFaultCount: %08X", vmc.PageFaultCount );
        lbprintf( hWndLb, "PeakWorkingSetSize: %08X", vmc.PeakWorkingSetSize );
        lbprintf( hWndLb, "WorkingSetSize: %08X", vmc.WorkingSetSize );
        lbprintf( hWndLb, "QuotaPeakPagedPoolUsage: %08X",
                    vmc.QuotaPeakPagedPoolUsage );
        lbprintf( hWndLb, "QuotaPagedPoolUsage: %08X",vmc.QuotaPagedPoolUsage );
        lbprintf( hWndLb, "QuotaPeakNonPagedPoolUsage: %08X",
                    vmc.QuotaPeakNonPagedPoolUsage );
        lbprintf( hWndLb, "QuotaNonPagedPoolUsage: %08X",
                    vmc.QuotaNonPagedPoolUsage );
        lbprintf( hWndLb, "PagefileUsage: %08X", vmc.PagefileUsage );
        lbprintf( hWndLb, "PeakPagefileUsage: %08X", vmc.PeakPagefileUsage );
    }
}

// Helper function called by UpdateProcessInfoFields
void UpdateTimes( HWND hDlg, DWORD pid )
{
    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_TIMES );
    SendMessage( hWndLb, LB_RESETCONTENT, 0, 0 );

    KERNEL_USER_TIMES times;
    if ( QueryProcessInformation( pid, ProcessTimes, &times, sizeof(times)) )
    {
        char szTimeStr[64];

        StrFromLONGLONG( times.CreateTime.QuadPart, szTimeStr );
        lbprintf( hWndLb, "CreateTime: %s", szTimeStr );

        StrFromLONGLONG( times.ExitTime.QuadPart, szTimeStr );
        lbprintf( hWndLb, "ExitTime: %s", szTimeStr );

        double d = ((double)times.KernelTime.QuadPart) / 10000;
        lbprintf( hWndLb, "Kernel Time: %.1lf MS", d );

        d = ((double)times.UserTime.QuadPart) / 10000;
        lbprintf( hWndLb, "User Time:   %.1lf MS", d );
    }
}

// Helper function called by UpdateProcessInfoFields
void PooledUsageAndLimits( HWND hDlg, DWORD pid )
{
    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_POOL_USAGE_AND_LIMITS );
    SendMessage( hWndLb, LB_RESETCONTENT, 0, 0 );

    POOLED_USAGE_AND_LIMITS pool;

    if ( QueryProcessInformation( pid, ProcessPooledUsageAndLimits,
                                    &pool, sizeof(pool) ) )
    {
        lbprintf( hWndLb, "PeakPagedPoolUsage: %08X", pool.PeakPagedPoolUsage );
        lbprintf( hWndLb, "PagedPoolUsage: %08X", pool.PagedPoolUsage );
        lbprintf( hWndLb, "PagedPoolLimit: %08X", pool.PagedPoolLimit );
        lbprintf( hWndLb, "PeakNonPagedPoolUsage: %08X",
                    pool.PeakNonPagedPoolUsage );
        lbprintf( hWndLb, "NonPagedPoolUsage: %08X", pool.NonPagedPoolUsage );
        lbprintf( hWndLb, "NonPagedPoolLimit: %08X", pool.NonPagedPoolLimit );
        lbprintf( hWndLb, "PeakPagefileUsage: %08X", pool.PeakPagefileUsage );
        lbprintf( hWndLb, "PagefileUsage: %08X", pool.PagefileUsage );
        lbprintf( hWndLb, "PagefileLimit: %08X", pool.PagefileLimit );
    }
}

// Called whenever a new process in the process listbox is selected
void UpdateProcessInfoFields( HWND hDlg, DWORD pid )
{
    UpdateProcessBasicInformation( hDlg, pid );
    UpdateProcessMiscFields( hDlg, pid );
    UpdateQuotaLimits( hDlg, pid );
    UpdateVmCounters( hDlg, pid );
    UpdateTimes( hDlg, pid );
    PooledUsageAndLimits( hDlg, pid );
}

// Called at startup, and whenever "Refresh Processes" button is selected
void RefreshViews( HWND hDlg )
{
    // Clear the contents of the process listbox
    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_PROCESSES );
    SendMessage( hWndLb, LB_RESETCONTENT, 0, 0 );

    UpdateProcessList( hDlg );
    FakeFirstLbItemSelection( hDlg, IDC_LB_PROCESSES  );
}

// ======================= Start of UI code ===============================

int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance,
                    PSTR lpszCmdLine, int nCmdShow )
{
    // Bring up the user interface
    DialogBox(  hInstance, MAKEINTRESOURCE(IDD_NTQUERYINFORMATIONPROCESS),
                0, (DLGPROC)NtQueryInformationProcessDemoDlgProc );
    return 0;
}

BOOL CALLBACK NtQueryInformationProcessDemoDlgProc(
                HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam )
{
    //
    // The dialog procedure for the main window
    //
    switch ( msg )
    {
        case WM_COMMAND:
            Handle_WM_COMMAND( hDlg, wParam, lParam ); return TRUE;
        case WM_INITDIALOG:
            Handle_WM_INITDIALOG( hDlg ); return TRUE;
        case WM_CLOSE:
            Handle_WM_CLOSE( hDlg ); break;
        // let everything else fall through
    }
    return FALSE;
}

void Handle_WM_COMMAND( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
    switch ( LOWORD(wParam) )
    {
        case IDC_BUTTON_REFRESH: RefreshViews( hDlg ); break;
        case IDC_BUTTON_EXIT: Handle_WM_CLOSE( hDlg ); break;
        case IDC_BUTTON_ABOUT:
            MessageBox( hDlg, g_AboutMsgTxt, g_AboutTitleTxt, MB_OK );
            break;
        case IDC_LB_PROCESSES:  // The user selected a new process
            if ( LBN_SELCHANGE == HIWORD(wParam) )
            {
                DWORD pid = GetDlgSelectedItemData(hDlg, IDC_LB_PROCESSES);
                UpdateProcessInfoFields( hDlg, pid );
            }
            break;
    }
}

void Handle_WM_INITDIALOG(HWND hDlg)
{
    // Get the window coordinates where the program was last running,
    // and move the window to that spot.
    POINT pt;
    GetSetPositionInfoFromRegistry( FALSE, &pt );
    SetWindowPos(hDlg, 0, pt.x, pt.y, 0, 0,
                 SWP_NOSIZE | SWP_NOREDRAW | SWP_NOZORDER | SWP_NOACTIVATE);

    RefreshViews( hDlg );   // Fills list with initial values
}

void Handle_WM_CLOSE( HWND hDlg )
{
    // Save off the window's X,Y coordinates for next time
    RECT rect;
    if ( GetWindowRect( hDlg, &rect ) )
        GetSetPositionInfoFromRegistry( TRUE, (LPPOINT)&rect );
    EndDialog(hDlg, 0);
}

// Like printf(), but appends output to end of specified listbox
// Returns the index of the new listbox entry
int lbprintf(HWND hWnd, char * format, ...)
{
    char szBuffer[4096];
    va_list argptr;

    va_start(argptr, format);
    vsprintf(szBuffer, format, argptr);
    va_end(argptr);

    // Add the string to the end.  Return value is the index of the added str
    return SendMessage( hWnd, LB_ADDSTRING, 0, (LPARAM)szBuffer );
}

// Converts a 64 bit value into an ASCII string (expressed in hex)
void StrFromLONGLONG( LONGLONG val , PSTR szOut )
{
    sprintf(szOut, "%08X%08X", (DWORD)(val >> 32), (DWORD)(val & 0xFFFFFFFF));
}

// Returns the DWORD of "item data" associated with the currently selected
// item in the listbox specified by the ctlID param
DWORD GetDlgSelectedItemData( HWND hDlg, int ctlID )
{
    LONG lbIndex = SendDlgItemMessage( hDlg, ctlID, LB_GETCURSEL, 0, 0 );
    return SendDlgItemMessage(hDlg, ctlID, LB_GETITEMDATA, lbIndex, 0 );
}

void FakeFirstLbItemSelection( HWND hDlg, int listboxID )
{
    // Set the selection to the first item in the list, then post a
    // WM_COMMAND message to make it look like the user selected something
    SendMessage( GetDlgItem( hDlg, listboxID ), LB_SETCURSEL, 0, 0 );
    PostMessage( hDlg, WM_COMMAND, MAKEWPARAM(listboxID, LBN_SELCHANGE), 0 );
}

void GetSetPositionInfoFromRegistry( BOOL fSave, POINT *lppt )
{
    //
    // Function that saves or restores the coordinates of a dialog box
    // in the system registry.  Handles the case where there's nothing there.
    //
    HKEY hKey;
    DWORD dataSize, err, disposition;
    char szKeyName[] = "DlgCoordinates";
    
    if ( !fSave )               // In case the key's not there yet, we'll
        lppt->x = lppt->y = 0;  // return 0,0 for the coordinates

    // Open the registry key (or create it if the first time being used)
    err = RegCreateKeyEx( HKEY_CURRENT_USER, gszRegistryKey, 0, 0,
                         REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                         0, &hKey, &disposition );
    if ( ERROR_SUCCESS != err )
        return;

    if ( fSave )            // Save out coordinates
    {
        RegSetValueEx(hKey,szKeyName, 0, REG_BINARY,(PBYTE)lppt,sizeof(*lppt));
    }
    else                    // read in coordinates
    {
        dataSize = sizeof(*lppt);
        RegQueryValueEx( hKey, szKeyName, 0, 0, (PBYTE)lppt, &dataSize );
    }

    RegCloseKey( hKey );
}

