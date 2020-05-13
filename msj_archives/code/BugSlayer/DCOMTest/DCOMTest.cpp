/*----------------------------------------------------------------------
John Robbins
Microsoft Systems Journal, December 1997 - Bugslayer Column!
----------------------------------------------------------------------*/
// Why won't windows.h compile with /W4?
#pragma warning ( disable : 4201 4514 )
#define INC_OLE2
#include <windows.h>
#include <stdio.h>
#include <OLE2.h>
#include "initguid.h"
#include "TraceSrv.h"
#include "TraceSrv_i.c"

void main ( void )
{
    HRESULT      hr ;
    ITrace *     lpTrace ;
    IUnknown *   lpUnknown ;


    // Initialize the OLE libraries.
    hr = CoInitializeEx ( NULL ,  COINIT_APARTMENTTHREADED ) ;
    if ( FAILED ( hr ) )
    {
        printf ( "Unable to initialize OLE\n" ) ;
        return ;
    }

    hr = CoCreateInstance ( CLSID_Trace     ,
                            NULL            ,
                            CLSCTX_SERVER   ,
                            IID_IUnknown    ,
                            (LPVOID*)&lpUnknown ) ;
    if ( FAILED ( hr ) )
    {
        LPVOID lpMsgBuf;

        FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        hr,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpMsgBuf,
                        0,
                        NULL );
        printf ( "CoCreateInstanceEx failed: 0x%08X\n" , hr ) ;
        printf ( "FormatMessage returned: %s\n" , lpMsgBuf ) ;
        return ;
    }

    hr = lpUnknown->QueryInterface ( IID_ITrace       ,
                                    (LPVOID*)&lpTrace  ) ;
    lpUnknown->Release ( ) ;
    if ( FAILED ( hr ) )
    {
        LPVOID lpMsgBuf;

        FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        hr,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpMsgBuf,
                        0,
                        NULL );
        printf ( "QueryInterface failed: 0x%08X\n" , hr ) ;
        printf ( "FormatMessage returned: %s\n" , lpMsgBuf ) ;
        return ;
    }


    OLECHAR * pszTemp ;

    pszTemp = SysAllocString (OLESTR("Hello from a C++ program!!!"));
    lpTrace->Trace ( pszTemp ) ;
    SysFreeString ( pszTemp ) ;


    lpTrace->Release ( ) ;

    CoUninitialize ( ) ;
}

