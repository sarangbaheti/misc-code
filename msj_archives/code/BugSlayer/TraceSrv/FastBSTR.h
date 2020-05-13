/*----------------------------------------------------------------------
John Robbins
Microsoft Systems Journal, December 1997 - Bugslayer Column!
----------------------------------------------------------------------*/
#ifndef _FASTBSTR_
#define _FASTBSTR_

class CFastBSTR
{
////////////////////////////////////////////////////////////////////////
// Public construction and destruction.
////////////////////////////////////////////////////////////////////////
public      :

    // The memory debugging code.  See the Oct installment of
    //  Bugslayer!
    DECLARE_MEMDEBUG ( CFastBSTR ) ;

    CFastBSTR ( void )
    {
        m_szData        = NULL ;
        m_szWholeBuff   = NULL ;
        m_pdwStringSize = NULL ;
        m_uiBuffSize    = 0    ;
    }

    ~CFastBSTR ( void )
    {
        Free ( ) ;
    }

////////////////////////////////////////////////////////////////////////
// Public allocation and deallocation functions.
////////////////////////////////////////////////////////////////////////
public      :

    OLECHAR * Allocate ( UINT uiSize )
    {
        ASSERT ( 0 != uiSize ) ;
        if ( 0 == uiSize )
        {
            return ( NULL ) ;
        }
        // Free up any existing.
        if ( NULL != m_szWholeBuff )
        {
            delete [] m_szWholeBuff ;
        }
        m_szWholeBuff = new DWORD[ uiSize ] ;
        memset ( m_szWholeBuff , NULL , uiSize ) ;

        m_pdwStringSize = (LPDWORD)m_szWholeBuff ;
        *m_pdwStringSize = 0 ;

        m_szData = (OLECHAR*)(m_pdwStringSize + 1) ;
        m_uiBuffSize = uiSize ;
        return ( m_szData ) ;
    }

    void Free ( )
    {
        if ( NULL == m_szWholeBuff )
        {
            return ;
        }
        delete [] m_szWholeBuff ;
        m_szData        = NULL ;
        m_szWholeBuff   = NULL ;
        m_pdwStringSize = NULL ;
        m_uiBuffSize    = 0    ;
    }

////////////////////////////////////////////////////////////////////////
// Public length functions.
////////////////////////////////////////////////////////////////////////
public      :

    // Returns the length of the whole data buffer currently allocated.
    UINT BufferSize ( void ) const
    {
        return ( m_uiBuffSize ) ;
    }

    // Returns the byte length of the current string.  Call this before
    //  passing the data for this string to a function that needs a
    //  BSTR.  If the parameter is not zero, then that value will be
    //  used for the string size.  If this parameter is zero, then
    //  this returns the length of the string data.  (This means that
    //  the length will be up to the first NULL character.)
    UINT GetStringByteLength ( UINT uiLen = 0 )
    {
        ASSERT ( m_pdwStringSize != NULL ) ;
        if ( NULL == m_pdwStringSize )
        {
            return ( 0 ) ;
        }
        if ( 0 == uiLen )
        {
            uiLen = lstrlenW ( m_szData ) * sizeof ( OLECHAR ) ;
        }
        *m_pdwStringSize = uiLen ;
        return ( uiLen ) ;
    }

////////////////////////////////////////////////////////////////////////
// Public data access members and operators.
////////////////////////////////////////////////////////////////////////
public      :

    OLECHAR * GetDataBuffer ( ) const
    {
        return ( m_szData ) ;
    }

    operator BSTR ( ) const
    {
        return ( m_szData ) ;
    }


////////////////////////////////////////////////////////////////////////
// Private data members.
////////////////////////////////////////////////////////////////////////
private     :
    // The whole actual buffer.
    LPDWORD     m_szWholeBuff   ;
    // The string size portion of the buffer.
    LPDWORD     m_pdwStringSize ;
    // The data portion of the buffer.
    OLECHAR *   m_szData        ;
    // The buffer size.
    DWORD       m_uiBuffSize    ;

} ;


#endif      // _FASTBSTR_


