//===============================================================
// Matt Pietrek
// Microsoft Systems Journal, November 1997
// FILE: LongPathNameDemo.CPP
// To compile: CL </DUNICODE=1 /D_UNICODE=1> LongPathNameDemo.CPP 
//===============================================================
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

TCHAR g_szMyLongFilename[] = _T("ThisIsALongFileName.TXT");

int main()
{
    HKEY hKey;

    // Create a file with a long filename (see above)
    HANDLE hFile = CreateFile(  g_szMyLongFilename,
                                GENERIC_WRITE,
                                0,
                                0,
                                CREATE_NEW,
                                FILE_ATTRIBUTE_NORMAL,
                                0 );

    if ( hFile )            // If the file was opened, close
        CloseHandle( hFile );
    
    TCHAR szShortFilename[MAX_PATH];

    // Get the short version of the filename        
    GetShortPathName(   g_szMyLongFilename, szShortFilename,
                        sizeof(szShortFilename)/sizeof(TCHAR) );
    
    _tprintf( _T("Short pathname: %s\n"), szShortFilename );

    TCHAR szLongFilename[MAX_PATH];

    // Reverse the process, getting the long filename from the
    // short filename obtained earlier
    GetLongPathName(    szShortFilename, szLongFilename,
                        sizeof(szLongFilename)/sizeof(TCHAR) );
    
    _tprintf( _T("Long pathname: %s\n"), szLongFilename );
    
    if ( hFile )        // If we created a file earlier, delete it now
        DeleteFile( g_szMyLongFilename );

    return 0;
}                   