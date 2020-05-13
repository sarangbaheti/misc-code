// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__AA2B5095_89FC_11D0_AA8A_00A0C9055E55__INCLUDED_)
#define AFX_STDAFX_H__AA2B5095_89FC_11D0_AA8A_00A0C9055E55__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

/** next 4 lines are new **/
#include <sql.h>
#include <sqlext.h>
#define REPORTERROR(x) ReportODBCError(x)
#define SQLSUCCEEDED(x) (!((x)>>1))

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AA2B5095_89FC_11D0_AA8A_00A0C9055E55__INCLUDED)
