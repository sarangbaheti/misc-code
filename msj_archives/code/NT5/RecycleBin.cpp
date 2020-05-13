//======================================================================
// Matt Pietrek
// Microsoft Systems Journal, November 1997
// FILE: RecycleBin.CPP
// To compile: CL </DUNICODE=1 /D_UNICODE=1> RecycleBin.CPP SHELL32.LIB
//======================================================================
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
    SHQUERYRBINFO shqbi = { sizeof(shqbi), -1, -1 };
    
    if ( S_OK != SHQueryRecycleBin( 0, &shqbi ) )
    {
        _tprintf( _T("Error!\n") );
        return 1;
    }
    
    _tprintf( _T("Items:%u  Bytes used:%u"),
                    (DWORD)shqbi.i64NumItems, (DWORD)shqbi.i64Size );

    SHEmptyRecycleBin( 0, 0, SHERB_NOPROGRESSUI );

    return 0;
}
