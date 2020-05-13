
#ifndef __LITCTL_H__
#define __LITCTL_H__


// debugging functions
#ifdef _DEBUG
#define _SIDE_ASSERTE(b)    _ASSERTE(b)
#else
#define _SIDE_ASSERTE(b)    (b)
#endif  // !_DEBUG

#ifdef NOIMP
#undef NOIMP
#endif

#ifdef SAYOK
#undef SAYOK
#endif

#define NOIMP  {return E_NOTIMPL;}
#define SAYOK  {return S_OK;}

#ifdef NOVERBS
#undef NOVERBS
#endif

#define NOVERBS {return OLEOBJ_E_NOVERBS;}

#define DECLARE_STD_UNKNOWN   \
STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);  \
STDMETHOD_(ULONG, AddRef)(VOID);   \
STDMETHOD_(ULONG, Release)(VOID);

// the length of a guid once printed out with -'s, leading and trailing bracket,
// plus 1 for NULL
//
#define GUID_STR_LEN    40

const ULONG MAXCCHURL = INTERNET_MAX_URL_LENGTH;
const ULONG MAX_OLECMD_BUFFER_SIZE = 60;


//
// handy error macros, randing from cleaning up, to returning to clearing
// rich error information as well.
//
#define RETURN_ON_FAILURE(hr) if (FAILED(hr)) return hr
#define RETURN_ON_NULLALLOC(ptr) if (!(ptr)) return E_OUTOFMEMORY
#define CLEANUP_ON_FAILURE(hr) if (FAILED(hr)) goto CleanUp
#define CLEARERRORINFORET(hr) { SetErrorInfo(0, NULL); return hr; }
#define CLEARERRORINFORET_ON_FAILURE(hr) if (FAILED(hr)) { SetErrorInfo(0, NULL); return hr; }

#define CLEANUP_ON_ERROR(l)    if (l != ERROR_SUCCESS) goto CleanUp


int StringFromGuidA(REFIID, LPSTR);
BOOL RegisterUnknownObject(LPCSTR pszObjectName, REFCLSID riidObject);
BOOL DeleteKeyAndSubKeys(HKEY hkIn, LPSTR pszSubKey);
BOOL
UnregisterAutomationObject(
        LPCSTR   pszLibName,
        LPCSTR   pszObjectName,
        long     lVersion,
        REFCLSID riidObject);

BOOL UnregisterUnknownObject(REFCLSID riidObject);
BOOL
RegisterControlObject(
        LPCSTR   pszLibName,
        LPCSTR   pszObjectName,
        long     lVersion,
        REFCLSID riidLibrary,
        REFCLSID riidObject,
        DWORD    dwMiscStatus,
        WORD     wToolboxBitmapId);

BOOL RegisterAutomationObject(
        LPCSTR   pszLibName,
        LPCSTR   pszObjectName,
        long     lVersion,
        REFCLSID riidLibrary,
        REFCLSID riidObject);


// helper routines for doing late bound property gets
HRESULT _GetDISPID(LPDISPATCH pDisp, UINT uIDName, DISPID * pDispID);
HRESULT _GetDispProperty(LPDISPATCH pDisp, UINT uIDName, LPDISPATCH * ppDisp);
HRESULT _GetProperty(LPDISPATCH pDisp, UINT uID, VARTYPE vt, LPVARIANT pVar);

class CLiteCtlCF : public IClassFactory
{
public:
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
    STDMETHOD_(ULONG, AddRef)(VOID){return 1;}
    STDMETHOD_(ULONG, Release)(VOID){return 1;}

    STDMETHOD(CreateInstance)(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppv);
    STDMETHOD(LockServer)(BOOL fLock)SAYOK
};

class CLiteCtl;

class CDispatch : public IDispatch
{
public:
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
    STDMETHOD_(ULONG, AddRef)(VOID);
    STDMETHOD_(ULONG, Release)(VOID);

    // IDispatch stuff
    STDMETHOD(GetTypeInfoCount)(UINT *pctinfo);
    STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo ** pptinfo);
    STDMETHOD(GetIDsOfNames)(
         REFIID riid,
         LPOLESTR * rgszNames,
         UINT cNames,
         LCID lcid,
         DISPID * rgdispid);

    STDMETHOD(Invoke)(
         DISPID dispidMember,
         REFIID riid,
         LCID lcid,
         WORD wFlags,
         DISPPARAMS *pdispparams,
         VARIANT * pvarResult,
         EXCEPINFO * pexcepinfo,
         UINT * puArgErr);

    // dispinterface methods
    STDMETHOD(get_AnswerToTheUniverse)(PLONG plAnswer);
    STDMETHOD(put_AnswerToTheUniverse)(LONG lAnswer);
    STDMETHOD(IEToolBar)(VARIANT_BOOL fToolBar);

    CDispatch(CLiteCtl * pLiteCtl) :
            m_pLiteCtl(pLiteCtl),
            m_pTI(0)
    {
    }

   ~CDispatch(VOID)
    {
       if (m_pTI)
           m_pTI->Release();
    }

    HRESULT Init(VOID);

protected:
     LPTYPEINFO         m_pTI;
     CLiteCtl *         m_pLiteCtl;
};

class CLiteCtl : public IOleObject
{
friend class CDispatch;

public:
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
    STDMETHOD_(ULONG, AddRef)(VOID);
    STDMETHOD_(ULONG, Release)(VOID);

    // IOleObject stuff
    STDMETHOD(SetClientSite)(IOleClientSite  *pClientSite);
    STDMETHOD(GetClientSite)(IOleClientSite  **ppClientSite)NOIMP
    STDMETHOD(SetHostNames)(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)SAYOK
    STDMETHOD(Close)(DWORD dwSaveOption)SAYOK
    STDMETHOD(SetMoniker)(DWORD dwWhichMoniker, IMoniker  *pmk)NOIMP
    STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker  * *ppmk)NOIMP
    STDMETHOD(InitFromData)(IDataObject  *pDataObject, BOOL fCreation, DWORD dwReserved)NOIMP
    STDMETHOD(GetClipboardData)(DWORD dwReserved, IDataObject  * *ppDataObject)NOIMP
    STDMETHOD(DoVerb)(LONG iVerb, LPMSG lpmsg, IOleClientSite  *pActiveSite, LONG lindex,
                                     HWND hwndParent, LPCRECT lprcPosRect)NOVERBS
    STDMETHOD(EnumVerbs)(IEnumOLEVERB  * *ppEnumOleVerb)NOVERBS
    STDMETHOD(Update)(void)SAYOK
    STDMETHOD(IsUpToDate)(void)SAYOK
    STDMETHOD(GetUserClassID)(CLSID  *pClsid)
    {
        *pClsid = CLSID_LiteCtl;
        return S_OK;
    }

    STDMETHOD(GetUserType)(DWORD dwFormOfType, LPOLESTR  *pszUserType)
    {
        return OLE_S_USEREG;
    }
    STDMETHOD(SetExtent)(DWORD dwDrawAspect,SIZEL  *psizel)NOIMP
    STDMETHOD(GetExtent)(DWORD dwDrawAspect, SIZEL  *psizel)NOIMP
    STDMETHOD(Advise)(IAdviseSink  *pAdvSink, DWORD  *pdwConnection)NOIMP
    STDMETHOD(Unadvise)(DWORD dwConnection)NOIMP
    STDMETHOD(EnumAdvise)(IEnumSTATDATA  * *ppenumAdvise)NOIMP
    STDMETHOD(GetMiscStatus)(DWORD dwAspect, DWORD  *pdwStatus)
    {
        return OLEMISC_INVISIBLEATRUNTIME | OLEMISC_SETCLIENTSITEFIRST;
    }
    STDMETHOD(SetColorScheme)(LOGPALETTE  *pLogpal)NOIMP


    CLiteCtl(VOID);
   ~CLiteCtl(VOID);

    HRESULT Init(VOID);

protected:

    CDispatch           m_disp;
    LPOLECLIENTSITE     m_pCS;
    ULONG               m_ref;
};

#endif

