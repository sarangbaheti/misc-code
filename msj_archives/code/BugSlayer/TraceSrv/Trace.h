/*----------------------------------------------------------------------
John Robbins
Microsoft Systems Journal, December 1997 - Bugslayer Column!
----------------------------------------------------------------------*/
#ifndef __TRACE_H_
#define __TRACE_H_

#include "resource.h"

// The IDispatch proxy classes for the events.
#include "CorrectProxyTraceSrv.h"

// The fast BSTR class.
#include "FastBSTR.h"

// The following are the formatting sizes.  Since I arbitrarily chose to
//  wrap the item numbers at 100,000, so the number format was known in
//  advance, you can change those constants if you would like.  You will
//  need to change the handling code in TraceFull as well.
// Item Number - 6 (5 numbers + 1 space).
const int k_SIZE_ITEMNUMBER = 6 ;
// Time        - 9 (hh:mm:ss + 1 space)
//  BUG BUG
//  Double check that Chinese and Thai formats are really this size!
//  I think they might have characters on the front of the time but,
//  I'm not sure if the TIME_NOTIMEMARKER shuts them off.
const int k_SIZE_TIME       = 9 ;
// PID         - 7 ([XXXX] + 1 space)
const int k_SIZE_PID        = 7 ;
// CR/LF       - 2
const int k_SIZE_CRLF       = 2 ;
// TOTAL...
const int k_SIZE_FULLFORMAT = k_SIZE_ITEMNUMBER +
                              k_SIZE_TIME       +
                              k_SIZE_PID        +
                              k_SIZE_CRLF        ;
// The byte count is expressed in UNICODE characters since everything
//  sent to this class is in wide characters.
const int k_SIZE_FULLFORMATBYTES = k_SIZE_FULLFORMAT *
                                   sizeof ( wchar_t )   ;

// The minimum trace buffer size.
const int k_MIN_TRACE_BUFF_SIZE = 2048 ;

// The default values for the trace settings.  These are used in both
//  the constructor and in the INI reading code.  Note that -1 is TRUE
//  for VARIANT_BOOLS!
const int k_DEFVAL_SHOWTIMESTAMPS  = 0     ;
const int k_DEFVAL_SHOWTRACEASODS  = -1    ;
const int k_DEFVAL_SHOWITEMNUMBER  = 0     ;
const int k_DEFVAL_SHOWPID         = 0     ;
const int k_DEFVAL_ADDCRLF         = 0     ;

// The constant values for the INI where settings are stored.  These
//  do not need to be internationalized.
const LPCTSTR k_STR_INIFILE         = _T ( "TraceSrv.ini"   ) ;
const LPCTSTR k_STR_SECTION         = _T ( "Settings"       ) ;
const LPCTSTR k_STR_SHOWTIMESTAMPS  = _T ( "ShowTimeStamps" ) ;
const LPCTSTR k_STR_SHOWTRACEASODS  = _T ( "ShowTraceAsODS" ) ;
const LPCTSTR k_STR_SHOWITEMNUMBER  = _T ( "ShowItemNumber" ) ;
const LPCTSTR k_STR_SHOWPID         = _T ( "ShowPID"        ) ;
const LPCTSTR k_STR_ADDCRLF         = _T ( "AddCRLF"        ) ;

// Since there is no WritePrivateProfileInt, these are the string that
//  represent the integer values for all the settings.
const LPCTSTR k_STR_VBTRUE  = _T ( "-1" ) ;
const LPCTSTR k_STR_VBFALSE = _T ( "0"  ) ;

class ATL_NO_VTABLE CTrace :
        // The standard COM classes.
        public CComObjectRootEx<CComMultiThreadModel>   ,
        public CComCoClass<CTrace , &CLSID_Trace>       ,
        public ISupportErrorInfo                        ,
        public IDispatchImpl<ITrace              ,
                             &IID_ITrace         ,
                             &LIBID_TRACESRVLib> ,

        // This class holds ITraceEvent connection points.
        public IConnectionPointContainerImpl<CTrace>    ,
        // The actual event classes.
        public CProxyDITraceEvent<CTrace>               ,
        // Allows TraceSrv to be scriptable.
        public IObjectSafetyImpl<CTrace>
{
public  :

    CTrace( )
    {
        m_pUnkMarshaler     = NULL                    ;
        m_vbShowTimeStamps  = k_DEFVAL_SHOWTIMESTAMPS ;
        m_vbShowTraceAsODS  = k_DEFVAL_SHOWTRACEASODS ;
        m_vbShowItemNumber  = k_DEFVAL_SHOWITEMNUMBER ;
        m_vbShowPID         = k_DEFVAL_SHOWPID        ;
        m_vbAddCRLF         = k_DEFVAL_ADDCRLF        ;
        m_dwCurrCount       = 0                       ;

        LoadSettings ( ) ;
    }

    ~CTrace ( void )
    {
        SaveSettings ( ) ;
    }

DECLARE_REGISTRY_RESOURCEID(IDR_TRACE)
DECLARE_GET_CONTROLLING_UNKNOWN()

// Wow, it only took me an entire day to figure out that this was the
//  magic macro that forced a single instance!
DECLARE_CLASSFACTORY_SINGLETON(CTrace)

BEGIN_COM_MAP(CTrace)
    COM_INTERFACE_ENTRY(ITrace)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
    COM_INTERFACE_ENTRY_IMPL(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTrace)
    CONNECTION_POINT_ENTRY(DIID_DITraceEvent)
END_CONNECTION_POINT_MAP()

    // The memory debugging code.  See the Oct installment of
    //  Bugslayer!
    DECLARE_MEMDEBUG ( CTrace ) ;


    HRESULT FinalConstruct ( )
    {
        return ( CoCreateFreeThreadedMarshaler( GetControllingUnknown(),
                                                &m_pUnkMarshaler.p   ));
    }

    void FinalRelease ( )
    {
        m_pUnkMarshaler.Release ( ) ;
    }

    CComPtr<IUnknown> m_pUnkMarshaler;

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITrace
public      :
    STDMETHOD(Trace) ( BSTR bstrText ) ;
    STDMETHOD(FullTrace) ( BSTR       bstrText ,
                           long       dwPID     ) ;

    STDMETHOD(get_ShowTimeStamps) ( VARIANT_BOOL * pVal   ) ;
    STDMETHOD(put_ShowTimeStamps) ( VARIANT_BOOL   newVal ) ;

    STDMETHOD(get_ShowTraceAsODS) ( VARIANT_BOOL * pVal   ) ;
    STDMETHOD(put_ShowTraceAsODS) ( VARIANT_BOOL   newVal ) ;

    STDMETHOD(get_ShowItemNumber) ( VARIANT_BOOL * pVal   ) ;
    STDMETHOD(put_ShowItemNumber) ( VARIANT_BOOL   newVal ) ;

    STDMETHOD(get_ShowPID) ( VARIANT_BOOL * pVal   ) ;
    STDMETHOD(put_ShowPID) ( VARIANT_BOOL   newVal ) ;

    STDMETHOD(get_AddCRLF) ( VARIANT_BOOL * pVal   ) ;
    STDMETHOD(put_AddCRLF) ( VARIANT_BOOL   newVal ) ;

private     :

    void LoadSettings ( void ) ;
    void SaveSettings ( void ) ;

    // The real property values.
    VARIANT_BOOL m_vbShowTimeStamps  ;
    VARIANT_BOOL m_vbShowTraceAsODS  ;
    VARIANT_BOOL m_vbShowItemNumber  ;
    VARIANT_BOOL m_vbShowPID         ;
    VARIANT_BOOL m_vbAddCRLF         ;

    // The running trace count.
    DWORD m_dwCurrCount     ;

    // The fast BSTR class that holds the string buffer built up.
    CFastBSTR   m_cOutput   ;

    // The function that does all the actual work!  If this function
    //  returns S_OK, then the m_cOutput variable has the string to
    //  use as the parameter to Fire_TraceEvent.
    HRESULT ProcessTrace ( BSTR bstrText , long dwPID ) ;
} ;

#endif  //__TRACE_H_
