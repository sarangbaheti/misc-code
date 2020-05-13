/*----------------------------------------------------------------------
John Robbins
Microsoft Systems Journal, December 1997 - Bugslayer Column!
----------------------------------------------------------------------*/
#ifndef AFX_STDAFX_H__C1262E44_0186_11D1_B292_00AA004206E4__INCLUDED_
#define AFX_STDAFX_H__C1262E44_0186_11D1_B292_00AA004206E4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0400

// Keep this at apartment threaded so that you can use TraceSrv with
//  VB and not have any problems.
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to
//  override something, but do not change the name of _Module

// Always include the MSJ memory dumping, ASSERT and VERIFY macros.
//  See Bugslayer - Oct '97.
#include "MemDumperValidator.h"

class CServiceModule : public CComModule
{
public  :
    HRESULT RegisterServer ( BOOL bRegTypeLib , BOOL bService ) ;
    HRESULT UnregisterServer (  ) ;
    void Init ( _ATL_OBJMAP_ENTRY*  p ,
                HINSTANCE           h ,
                UINT nServiceNameID ) ;
    void Start (  ) ;
    void ServiceMain ( DWORD dwArgc , LPTSTR* lpszArgv ) ;
    void Handler ( DWORD dwOpcode ) ;
    void Run (  ) ;
    BOOL IsInstalled (  ) ;
    BOOL Install (  ) ;
    BOOL Uninstall (  ) ;
    LONG Unlock (  ) ;
    void LogEvent ( LPCTSTR pszFormat , ... ) ;
    void SetServiceStatus ( DWORD dwState ) ;
    void SetupAsLocalServer (  ) ;

//Implementation
private :
    static void WINAPI _ServiceMain ( DWORD dwArgc , LPTSTR* lpszArgv );
    static void WINAPI _Handler ( DWORD dwOpcode ) ;

// data members
public  :
    TCHAR                 m_szServiceName[ 256 ] ;
    SERVICE_STATUS_HANDLE m_hServiceStatus       ;
    SERVICE_STATUS        m_status               ;
    DWORD                 dwThreadID             ;
    BOOL                  m_bService             ;
};

extern CServiceModule _Module ;

#define _ATL_DEBUG_QI

// WHY CAN /W4 NOT BE USED ON THESE FILES?!!!
#pragma warning ( disable : 4510 4610 4100 )
#include <atlcom.h>
#include <atlctl.h>
#pragma warning ( default : 4510 4610 4100 )

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations
//  immediately before the previous line.

#endif
