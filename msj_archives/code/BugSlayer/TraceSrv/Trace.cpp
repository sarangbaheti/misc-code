/*----------------------------------------------------------------------
John Robbins
Microsoft Systems Journal, December 1997 - Bugslayer Column!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "TraceSrv.h"
#include "Trace.h"

IMPLEMENT_MEMDEBUG ( CTrace ) ;

// The memory dumping and validating code for this class.
#ifdef _DEBUG
void CTrace :: ClassDumper ( const void * pData )
{
    CTrace * pClass = (CTrace*)pData ;
    _RPT1 ( _CRT_WARN                     ,
            " CTrace instance : 0x%08X\n" ,
            pClass                         ) ;
}

void CTrace :: ClassValidator ( const void * ,
                                const void *  )
{
    // The validator is not need for this class.
}
#endif

STDMETHODIMP CTrace :: InterfaceSupportsErrorInfo ( REFIID riid )
{
    ASSERT ( this ) ;

    static const IID* arr[] =
    {
        &IID_ITrace,
    } ;

    for ( int i = 0 ; i < (sizeof(arr)/sizeof(arr[0])) ; i++ )
    {
        if ( InlineIsEqualGUID ( *arr[ i ] , riid ) )
        {
            return ( S_OK ) ;
        }
    }
    return ( S_FALSE ) ;
}

STDMETHODIMP CTrace :: Trace ( BSTR bstrText )
{
    ASSERT ( this ) ;
    return ( FullTrace ( bstrText , 0 ) ) ;
}

STDMETHODIMP CTrace :: FullTrace ( BSTR bstrText ,
                                   long dwPID     )
{
    ASSERT ( this ) ;
    return ( ProcessTrace ( bstrText , dwPID ) ) ;
}

STDMETHODIMP CTrace :: get_ShowTimeStamps ( VARIANT_BOOL * pVal )
{
    ASSERT ( this ) ;
    *pVal = m_vbShowTimeStamps ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: put_ShowTimeStamps ( VARIANT_BOOL newVal )
{
    ASSERT ( this ) ;
    m_vbShowTimeStamps = newVal ;
    Fire_ChangeShowTimeStamps ( newVal ) ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: get_ShowTraceAsODS ( VARIANT_BOOL * pVal )
{
    ASSERT ( this ) ;
    *pVal = (VARIANT_BOOL)m_vbShowTraceAsODS ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: put_ShowTraceAsODS ( VARIANT_BOOL newVal )
{
    ASSERT ( this ) ;
    m_vbShowTraceAsODS = newVal ;
    Fire_ChangeShowTraceAsODS ( newVal ) ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: get_ShowItemNumber ( VARIANT_BOOL * pVal )
{
    ASSERT ( this ) ;
    *pVal = (VARIANT_BOOL)m_vbShowItemNumber ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: put_ShowItemNumber ( VARIANT_BOOL newVal )
{
    ASSERT ( this ) ;
    m_vbShowItemNumber = newVal ;
    Fire_ChangeShowItemNumber ( newVal ) ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: get_ShowPID ( VARIANT_BOOL * pVal )
{
    ASSERT ( this ) ;
    *pVal = (VARIANT_BOOL)m_vbShowPID ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: put_ShowPID ( VARIANT_BOOL newVal )
{
    ASSERT ( this ) ;
    m_vbShowPID = newVal ;
    Fire_ChangeShowPID ( newVal ) ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: get_AddCRLF ( VARIANT_BOOL * pVal )
{
    ASSERT ( this ) ;
    *pVal = (VARIANT_BOOL)m_vbAddCRLF ;
    return ( S_OK ) ;
}

STDMETHODIMP CTrace :: put_AddCRLF ( VARIANT_BOOL newVal )
{
    ASSERT ( this ) ;
    m_vbAddCRLF = newVal ;
    Fire_ChangeAddCRLF ( newVal ) ;
    return ( S_OK ) ;
}


HRESULT CTrace :: ProcessTrace ( BSTR bstrText , long dwPID )
{
    // Always double check everything.  Trust nothing.
    ASSERT ( this ) ;
    ASSERT ( NULL != bstrText ) ;

    // The length of the input string.  This is read after the pointer
    //  is validated and for everyone else to use.
    int iInputLen = 0 ;

    if ( NULL == bstrText )
    {
        return ( Error ( IDS_NULLSTRINGPASSED ,
                         GUID_NULL            ,
                         E_INVALIDARG          ) ) ;
    }

    // We have some form of pointer in bstrText. Make sure what it holds
    //  is valid.
    ASSERT ( FALSE == IsBadReadPtr ( bstrText , sizeof ( BSTR ) ) ) ;
    ASSERT ( L'\0' != *bstrText ) ;

    if ( ( TRUE == IsBadReadPtr ( bstrText , sizeof ( BSTR ) ) ) ||
         ( L'\0' == *bstrText                                  )   )
    {
        return ( Error ( IDS_INVALIDSTRING ,
                         GUID_NULL         ,
                         E_INVALIDARG       ) ) ;
    }

    // Get the input length now that the pointer is validated.
    iInputLen = lstrlenW ( bstrText ) ;

    // Could this string blow the buffer?
    UINT uiSize = ( iInputLen * sizeof ( OLECHAR) ) +
                  k_SIZE_FULLFORMATBYTES  ;

    // If this is the first time through, then m_lBuffSize is zero so
    //  this serves as the initial allocation point.
    if ( uiSize >= m_cOutput.BufferSize ( ) )
    {
        // Delete the existing buffer and allocate a bigger one.
        m_cOutput.Free ( ) ;

        UINT uiAllocSize = uiSize * 2 ;

        // Make sure we get a minimum buffer size.
        if ( k_MIN_TRACE_BUFF_SIZE > uiAllocSize )
        {
            uiAllocSize = k_MIN_TRACE_BUFF_SIZE ;
        }
        OLECHAR * pTemp = m_cOutput.Allocate ( uiAllocSize ) ;
        ASSERT ( NULL != pTemp ) ;
        if ( NULL == pTemp )
        {
            return ( Error ( IDS_OUTOFMEMORY ,
                             GUID_NULL       ,
                             E_OUTOFMEMORY    ) ) ;
        }
    }

    // Now start the real work, everything checked out.

    // Increment the total.
    m_dwCurrCount++ ;

    // Is it time to wrap?
    if ( 100000 == m_dwCurrCount )
    {
        m_dwCurrCount = 0 ;
    }

    // Have the marker pointer start at the beginning of the output
    //  buffer.
    OLECHAR * pCurr = m_cOutput.GetDataBuffer ( ) ;

    if ( -1 == m_vbShowItemNumber )
    {
        pCurr += wsprintfW ( pCurr , L"%05d " , m_dwCurrCount ) ;
    }

    if ( -1 == m_vbShowTimeStamps )
    {
        // Show the timestamp based on the user's local (here at the
        //  server, not at the client!).  It is forced to just be the
        //  24 hour military time.
        int iLen = GetTimeFormatW ( LOCALE_USER_DEFAULT          ,
                                    LOCALE_NOUSEROVERRIDE      |
                                        TIME_FORCE24HOURFORMAT |
                                        TIME_NOTIMEMARKER        ,
                                    NULL                         ,
                                    NULL                         ,
                                    pCurr                        ,
                                    m_cOutput.BufferSize ( ) -
                                         k_SIZE_FULLFORMATBYTES   ) ;
        // BUG BUG
        //  I need more error checking here.
        ASSERT ( 0 != iLen ) ;

        // Move the pointer along but remember to account for the
        //  null character counted item.
        pCurr += ( iLen - 1 ) ;

        // GetTimeFormat does not stick in the extra space on the end
        //  so do it now.
        *pCurr = L' ' ;
        pCurr++ ;
    }

    if ( -1 == m_vbShowPID )
    {
        pCurr += wsprintfW ( pCurr , L"[%04X] " , dwPID ) ;
    }

    // Now put the actual message in and copy the NULL terminator as
    //  well.
    lstrcpynW ( pCurr , bstrText , iInputLen + 1 ) ;

    // Move pCurr to point at the NULL terminator.
    pCurr += iInputLen ;

    // Finally check if the string needs CRLFs.
    if ( -1 == m_vbAddCRLF )
    {
        if ( ( L'\x0D' != *(pCurr - 2) ) ||
             ( L'\x0A' != *(pCurr - 1) )   )
        {
            *(pCurr) = L'\x0D' ;
            *(pCurr + 1) = L'\x0A' ;
            pCurr += 2 ;
            *pCurr = L'\0' ;
        }
    }

    // Is it supposed to get shot to a kernel debugger?
    if ( -1 == m_vbShowTraceAsODS )
    {
        OutputDebugStringW ( (BSTR)m_cOutput ) ;
    }

    // Calculate the actual string length for the string.
    m_cOutput.GetStringByteLength ( ) ;

    // Finally, let any viewers know.
    Fire_TraceEvent ( m_cOutput ) ;

    return ( S_OK ) ;
}

void CTrace :: LoadSettings ( void )
{
    ASSERT ( this ) ;

    m_vbShowTimeStamps =
           (VARIANT_BOOL)GetPrivateProfileInt ( k_STR_SECTION        ,
                                                k_STR_SHOWTIMESTAMPS ,
                                                k_DEFVAL_SHOWTIMESTAMPS,
                                                k_STR_INIFILE         );
    m_vbShowTraceAsODS =
           (VARIANT_BOOL)GetPrivateProfileInt ( k_STR_SECTION        ,
                                                k_STR_SHOWTRACEASODS ,
                                                k_DEFVAL_SHOWTRACEASODS,
                                                k_STR_INIFILE         );
    m_vbShowItemNumber =
           (VARIANT_BOOL)GetPrivateProfileInt ( k_STR_SECTION        ,
                                                k_STR_SHOWITEMNUMBER ,
                                                k_DEFVAL_SHOWITEMNUMBER,
                                                k_STR_INIFILE         );
    m_vbShowPID =
           (VARIANT_BOOL)GetPrivateProfileInt ( k_STR_SECTION       ,
                                                k_STR_SHOWPID       ,
                                                k_DEFVAL_SHOWPID    ,
                                                k_STR_INIFILE        );
    m_vbAddCRLF =
           (VARIANT_BOOL)GetPrivateProfileInt ( k_STR_SECTION       ,
                                                k_STR_ADDCRLF       ,
                                                k_DEFVAL_ADDCRLF    ,
                                                k_STR_INIFILE        );
}

void CTrace :: SaveSettings ( void )
{
    ASSERT ( this ) ;

    WritePrivateProfileString ( k_STR_SECTION        ,
                                k_STR_SHOWTIMESTAMPS ,
                                ( m_vbShowTimeStamps == -1 ) ?
                                    k_STR_VBTRUE : k_STR_VBFALSE ,
                                k_STR_INIFILE         );
    WritePrivateProfileString ( k_STR_SECTION        ,
                                k_STR_SHOWTRACEASODS ,
                                ( m_vbShowTraceAsODS == -1 )  ?
                                    k_STR_VBTRUE : k_STR_VBFALSE ,
                                k_STR_INIFILE         );
    WritePrivateProfileString ( k_STR_SECTION        ,
                                k_STR_SHOWITEMNUMBER ,
                                ( m_vbShowItemNumber == -1 )  ?
                                    k_STR_VBTRUE : k_STR_VBFALSE ,
                                k_STR_INIFILE         );
    WritePrivateProfileString ( k_STR_SECTION       ,
                                k_STR_SHOWPID       ,
                                ( m_vbShowPID == -1 )  ?
                                    k_STR_VBTRUE : k_STR_VBFALSE ,
                                k_STR_INIFILE        );
    WritePrivateProfileString ( k_STR_SECTION       ,
                                k_STR_ADDCRLF       ,
                                ( m_vbAddCRLF == -1 )  ?
                                    k_STR_VBTRUE : k_STR_VBFALSE ,
                                k_STR_INIFILE        );
}

