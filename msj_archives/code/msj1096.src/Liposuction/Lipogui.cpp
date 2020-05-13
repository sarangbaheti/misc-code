//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: LIPOGUI.CPP
//==========================================
#include <windows.h>
#include <shellapi.h>
#pragma hdrstop
#include "lipo32res.h"
#include "lipo32output.h"

//-------------------- Helper function prototypes ---------------------------
void Handle_WM_COMMAND(HWND hDlg, WPARAM wParam, LPARAM lParam);
void Handle_WM_INITDIALOG(HWND hDlg);
void Handle_WM_CLOSE( HWND hDlg );
void Handle_WM_DROPFILES( HWND hDlg, WPARAM wParam );
BOOL CALLBACK LipoSuction32DlgProc( HWND, UINT, WPARAM, LPARAM );
void HookUpToIMAGEHLP( void );
void ShowNoIMAGEHLPError( void );
void RemoveDebugInfo( void );
void RemoveRelocations( void );
void BindIt( void );

void AnalyzeFile( PSTR );   // In LIPO32.CPP

//--------------------------- Global Variables -------------------------------
HWND g_hDlg = 0;
char g_szFileName[MAX_PATH];
HMODULE g_hModIMAGEHLP = 0;

// Prototype 3 functions from IMAGEHLP.DLL.  We'll use LoadLibrary and
// GetProcAddress so that we don't have to implicitly link to IMAGEHLP.DLL
typedef BOOL (__stdcall *PFNSPLITSYMBOLS)( LPSTR, LPSTR, LPSTR, DWORD );
typedef BOOL (__stdcall *PFNBINDIMAGE)(LPSTR, LPSTR, LPSTR );
typedef BOOL (__stdcall *PFNREMOVERELOCATIONS)(LPSTR);

PFNSPLITSYMBOLS pfnSplitSymbols = 0;            // 3 function pointers for the
PFNBINDIMAGE pfnBindImage = 0;                  // IMAGEHLP.DLL functions.
PFNREMOVERELOCATIONS pfnRemoveRelocations = 0;

#define SPLITSYM_EXTRACT_ALL        0x00000002  // From IMAGEHLP.H

//--------------------------- Start of Code -----------------------------------

int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance,
                    PSTR lpszCmdLine, int nCmdShow )
{
    HookUpToIMAGEHLP(); // Load IMAGEHLP, call GetProcAddress for routines
    
    // Matt's user interface of choice
    DialogBox(  hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
                0, (DLGPROC)LipoSuction32DlgProc );
            
    if ( g_hModIMAGEHLP )       // If we loaded IMAGEHLP, get rid of it now.
        FreeLibrary( g_hModIMAGEHLP );

    return 0;
}

void HookUpToIMAGEHLP( void )
{
    // Load IMAGEHLP, call GetProcAddress for routines

    g_hModIMAGEHLP = LoadLibrary( "IMAGEHLP.DLL" );
    if ( g_hModIMAGEHLP )
    {
        pfnSplitSymbols = (PFNSPLITSYMBOLS)
                        GetProcAddress(g_hModIMAGEHLP, "SplitSymbols" );
        pfnBindImage = (PFNBINDIMAGE)
                        GetProcAddress(g_hModIMAGEHLP, "BindImage" );
        pfnRemoveRelocations = (PFNREMOVERELOCATIONS)
                        GetProcAddress(g_hModIMAGEHLP, "RemoveRelocations" );
    }
}

void ShowNoIMAGEHLPError( void )
{
    // Called if the user clicked one of the 3 bottom buttons, but IMAGEHLP
    // wasn't loaded.
    MessageBox( g_hDlg,
                "IMAGEHLP.DLL not found, or needed function not exported",
                0, MB_OK );
}

void RemoveDebugInfo( void )
{
    if ( !pfnSplitSymbols )     // Make sure we're hooked up to IMAGEHLP.DLL
    {
        ShowNoIMAGEHLPError();
        return;
    }

    // Warn the user about possible dire consequences
    int retCode = MessageBox( g_hDlg,
                "IMAGEHLP.DLL may not work with non-Microsoft debug "
                "information, and corrupt the file.  Are you sure you wish "
                "to do this?",  "LipoSuction32", MB_YESNO | MB_ICONWARNING );
    if ( IDYES != retCode )
        return;
        
    char szFileName[MAX_PATH];
    BOOL fOK;

    // Call SplitSymbols() in IMAGEHLP  
    fOK = pfnSplitSymbols(g_szFileName, NULL, szFileName, SPLITSYM_EXTRACT_ALL);

    if ( !fOK )
    {
        MessageBox( g_hDlg, "SplitSymbols failed", 0, MB_OK );
        return;
    }
    
    DeleteFile( szFileName );   // Delete the .DBG file that SplitSymbols makes
    
    // Copy the filename before AnalyzeFile trashes it
    lstrcpy( szFileName, g_szFileName );

    AnalyzeFile( szFileName );  // Refresh the display
}

void RemoveRelocations( void )
{
    if ( !pfnRemoveRelocations )// Make sure we're hooked up to IMAGEHLP.DLL
    {
        ShowNoIMAGEHLPError();
        return;
    }
    
    // Warn the user about possible dire consequences
    int retCode = MessageBox( g_hDlg,
                "Some versions of IMAGEHLP.DLL may corrupt the executable "
                "file.  You may want to have a backup file.  Are you sure you "
                "wish to do this?", "LipoSuction32", MB_YESNO|MB_ICONWARNING );
    if ( IDYES != retCode )
        return;
    
    BOOL fOK;

    // Call RemoveRelocations() in IMAGEHLP 
    fOK = pfnRemoveRelocations( g_szFileName );

    if ( !fOK )
    {
        MessageBox( g_hDlg, "RemoveRelocations failed", 0, MB_OK );
        return;
    }
    
    // Copy the filename before AnalyzeFile trashes it
    char szFileName[MAX_PATH];
    lstrcpy( szFileName, g_szFileName );

    AnalyzeFile( szFileName );  // Refresh the display
}

void BindIt( void )
{
    if ( !pfnBindImage )    // Make sure we're hooked up to IMAGEHLP.DLL
    {
        ShowNoIMAGEHLPError();
        return;
    }

    // Warn the user about possible dire consequences
    int retCode = MessageBox( g_hDlg,
                "Binding an image may cause the image to not run on Windows "
                "95.  Are you sure you wish to do this?",
                "LipoSuction32", MB_YESNO | MB_ICONWARNING );
    if ( IDYES != retCode )
        return;
    
    BOOL fOK;
    // Call BindImage() in IMAGEHLP 
    fOK = pfnBindImage( g_szFileName, NULL, NULL );
    
    if ( !fOK )
    {
        MessageBox( g_hDlg, "BindImage failed", 0, MB_OK );
        return;
    }
    
    // Copy the filename before AnalyzeFile trashes it
    char szFileName[MAX_PATH];
    lstrcpy( szFileName, g_szFileName );

    AnalyzeFile( szFileName );  // Refresh the display
}


//=================== Start of message handling routines ====================

BOOL CALLBACK LipoSuction32DlgProc( HWND hDlg, UINT msg,
                                    WPARAM wParam, LPARAM lParam)
{
    switch ( msg )
    {
        case WM_COMMAND:
            Handle_WM_COMMAND( hDlg, wParam, lParam ); return TRUE;
        case WM_INITDIALOG:
            Handle_WM_INITDIALOG( hDlg ); return TRUE;
        case WM_DROPFILES:
            Handle_WM_DROPFILES( hDlg, wParam ); return 0;
        case WM_CLOSE:
            Handle_WM_CLOSE( hDlg ); break;
    }
    return FALSE;
}

void Handle_WM_COMMAND( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
    WORD wNotifyCode = HIWORD(wParam);
    WORD wID = LOWORD(wParam);
    HWND hwndCtl = (HWND)lParam;

    switch ( wID )
    {
        case IDOK:
            {
                // If <enter> is hit, grab the text from the top listbox
                // and start the AnalyzeFile process
                char szFileName[MAX_PATH];
                GetDlgItemText( g_hDlg, IDC_FILENAME, szFileName, MAX_PATH );
                AnalyzeFile( szFileName );
            }
            break;

        case IDC_STRIP_DEBUG_INFO: RemoveDebugInfo(); break;    // Button 
                                                                // handlers
        case IDC_REMOVE_RELOCATIONS: RemoveRelocations(); break;
            
        case IDC_BIND: BindIt(); break;
    }
}

void Handle_WM_DROPFILES( HWND hDlg, WPARAM wParam )
{
    char szFileName[MAX_PATH];
    UINT cbFileName;

    // Get the name of the file that was dropped on us, then release the HDROP
    cbFileName = DragQueryFile((HDROP)wParam,0,szFileName,sizeof(szFileName));
    DragFinish( (HDROP)wParam );
        
    AnalyzeFile( szFileName );
}

void Handle_WM_INITDIALOG(HWND hDlg)
{
    g_hDlg = hDlg;
    OutputClearAllFields();     // Initialize the dialog fields to empty state

    // Set us up to accept dropped filenames
    DragAcceptFiles( hDlg, TRUE );
}

void Handle_WM_CLOSE( HWND hDlg )
{
    // Stop accepting dropped filenames
    DragAcceptFiles( hDlg, TRUE );

    EndDialog(hDlg, 0);
}

//======================= Output Functions =================================

void OutputClearAllFields( void )
{
    // Set the edit and static text controls appropriately
    SetDlgItemText( g_hDlg, IDC_FILENAME, "<no file>" );
    SetDlgItemText( g_hDlg, IDC_RELOCATIONS, "" );
    SetDlgItemText( g_hDlg, IDC_IMAGE_BOUND, "" );

    // Clear the listboxes
    SendDlgItemMessage(g_hDlg, IDC_INCREMENTAL_LINKING, LB_RESETCONTENT, 0, 0);
    SendDlgItemMessage(g_hDlg, IDC_UNOPTIMIZED_CODE, LB_RESETCONTENT, 0, 0);
    SendDlgItemMessage(g_hDlg, IDC_DEBUG_INFO, LB_RESETCONTENT, 0, 0);
    SendDlgItemMessage(g_hDlg, IDC_UNINITIALIZED_DATA, LB_RESETCONTENT, 0, 0);
    SendDlgItemMessage(g_hDlg, IDC_COMBINABLE_SECTIONS, LB_RESETCONTENT, 0, 0);
    SendDlgItemMessage(g_hDlg, IDC_LOAD_CONFLICTS, LB_RESETCONTENT, 0, 0);

    // Disable the buttons
    EnableWindow( GetDlgItem(g_hDlg, IDC_STRIP_DEBUG_INFO), FALSE );
    EnableWindow( GetDlgItem(g_hDlg, IDC_REMOVE_RELOCATIONS), FALSE );
    EnableWindow( GetDlgItem(g_hDlg, IDC_BIND), FALSE );

    g_szFileName[0] = 0;    // Set the name of the current executable to NULL
}

void OutputSetFileName( PSTR pszFileName )
{
    strcpy( g_szFileName, pszFileName );
    SetDlgItemText( g_hDlg, IDC_FILENAME, pszFileName );
}

void OutputSetRelocations( unsigned count, BOOL fDLL )
{
    char szBuffer[64];
    wsprintf( szBuffer, "Relocations: %u bytes (%s)",
                count, fDLL ? "DLL" : "EXE" );

    SetDlgItemText( g_hDlg, IDC_RELOCATIONS, szBuffer );

    // If there are relocations, and if not a DLL, enable the correct button
    if ( count && (!fDLL) )
        EnableWindow( GetDlgItem(g_hDlg, IDC_REMOVE_RELOCATIONS), TRUE );
}

void OutputAddIncrementalLinking( PSTR pszSection, DWORD index, DWORD count )
{
    char szBuffer[128];

    wsprintf( szBuffer, "Section %u (%s) has %u padded INT 3's",
                index, pszSection, count);

    SendDlgItemMessage( g_hDlg, IDC_INCREMENTAL_LINKING, LB_ADDSTRING,
                        0, (LPARAM) szBuffer );
}

void OutputAddUnoptimizedCode( PSTR pszSection, DWORD index, DWORD count )
{
    char szBuffer[128];

    wsprintf( szBuffer, "Section %u (%s) %u bytes of stupid JMPs",
                index, pszSection, count);

    SendDlgItemMessage( g_hDlg, IDC_UNOPTIMIZED_CODE, LB_ADDSTRING,
                        0, (LPARAM) szBuffer );
}

void OutputAddDebugInfo( PSTR pszType, DWORD cbSize )
{
    char szBuffer[128];

    wsprintf( szBuffer, "%u bytes (%s)", cbSize, pszType );

    SendDlgItemMessage( g_hDlg, IDC_DEBUG_INFO, LB_ADDSTRING,
                        0, (LPARAM) szBuffer );

    // Enable the Strip Debug Info button if not "Misc" info
    if ( 0 != strcmp(pszType, "MISC" ) )
        EnableWindow( GetDlgItem(g_hDlg, IDC_STRIP_DEBUG_INFO), TRUE );
}

void OutputBSSSection( PSTR pszSection, DWORD index )
{
    char szBuffer[128];

    wsprintf( szBuffer, "Section %u (%s) is uninitialized data",
                index, pszSection );

    SendDlgItemMessage( g_hDlg, IDC_UNINITIALIZED_DATA, LB_ADDSTRING,
                        0, (LPARAM) szBuffer );
}

void OutputAddCombinableSectionsStart( void )
{
    SendDlgItemMessage( g_hDlg, IDC_COMBINABLE_SECTIONS, LB_ADDSTRING,
                        0, (LPARAM)"The following sections can be combined:" );
}

void OutputAddCombinableSections( PSTR pszName, unsigned cbSize, DWORD flags )
{
    char szBuffer[128];

    wsprintf( szBuffer, "  %-8s %u bytes (flags: %08X)",
                pszName, cbSize, flags );

    SendDlgItemMessage( g_hDlg, IDC_COMBINABLE_SECTIONS, LB_ADDSTRING,
                        0, (LPARAM) szBuffer );
}

void OutputAddCombinableSectionsEnd( DWORD cCurrentPages, DWORD cMergedPages )
{
    char szBuffer[128];

    wsprintf( szBuffer, "  Current pages: %u  Merged pages: %u",
                cCurrentPages, cMergedPages );

    SendDlgItemMessage( g_hDlg, IDC_COMBINABLE_SECTIONS, LB_ADDSTRING,
                        0, (LPARAM) szBuffer );
}

void OutputLoadAddressConflicts(    PSTR pszName1,
                                    DWORD startRVA1, DWORD endRVA1,
                                    PSTR pszName2,
                                    DWORD startRVA2, DWORD endRVA2 )
{
    SendDlgItemMessage( g_hDlg, IDC_LOAD_CONFLICTS, LB_ADDSTRING,
                        0, (LPARAM)"Load address conflict:" );

    char szBuffer[MAX_PATH + 128];

    wsprintf( szBuffer, "  (0x%08X-0x%08X) %s", startRVA1, endRVA1, pszName1 );
    SendDlgItemMessage( g_hDlg, IDC_LOAD_CONFLICTS, LB_ADDSTRING,
                        0, (LPARAM)szBuffer );

    wsprintf( szBuffer, "  (0x%08X-0x%08X) %s", startRVA2, endRVA2, pszName2 );
    SendDlgItemMessage( g_hDlg, IDC_LOAD_CONFLICTS, LB_ADDSTRING,
                        0, (LPARAM)szBuffer );

    SendDlgItemMessage( g_hDlg, IDC_LOAD_CONFLICTS, LB_ADDSTRING,
                        0, (LPARAM)"" );
}

void OutputBindStatus( BOOL fBound )
{
    char szBuffer[64];
    wsprintf( szBuffer, "Image is %sbound\n", fBound ? "" : "not " );

    SetDlgItemText( g_hDlg, IDC_IMAGE_BOUND, szBuffer );

    // Always enable the "Bind" button...   
    EnableWindow( GetDlgItem(g_hDlg, IDC_BIND), TRUE );
}

void OutputError( PSTR pszErrString )
{
    // Called when there's some sort of error in the core routines
    MessageBox( g_hDlg, pszErrString, 0, MB_OK );
}
