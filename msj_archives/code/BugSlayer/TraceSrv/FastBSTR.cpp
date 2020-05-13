/*----------------------------------------------------------------------
John Robbins
Microsoft Systems Journal, December 1997 - Bugslayer Column!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "FastBSTR.h"

IMPLEMENT_MEMDEBUG ( CFastBSTR ) ;

// The memory dumping and validating code for this class.
#ifdef _DEBUG
void CFastBSTR :: ClassDumper ( const void * pData )
{
    CFastBSTR * pClass = (CFastBSTR*)pData ;
    _RPT1 ( _CRT_WARN                        ,
            " CFastBSTR instance : 0x%08X\n" ,
            pClass                            ) ;
    _RPT1 ( _CRT_WARN                        ,
            " CFastBSTR data     : %S\n"     ,
            pClass->m_szData                  ) ;
}

void CFastBSTR :: ClassValidator ( const void * ,
                                   const void *  )
{
    // The validator is not need for this class.
}
#endif

