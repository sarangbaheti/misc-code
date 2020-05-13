#include <windows.h>
#include <olectl.h>
#include <crtdbg.h>
#include <wininet.h>
#include <servprov.h>
#include <docobj.h>
#include "cathelp.h"
#include "guids.h"
#include "litctl.h"
#include "resource.h"

HINSTANCE g_hInst = 0;

#define NElems(_rg)   (sizeof(_rg) / sizeof(_rg[0]))

CRITICAL_SECTION g_cs;
ULONG            g_cObj = 0;  // global object count for dll.

CLiteCtlCF g_CF;

const CATID CATID_SafeForScripting        = {0x7dd95801,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}};
const CATID CATID_SafeForInitializing    = {0x7dd95802,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}};

//+---------------------------------------------------------------------------
//
//  Member:     CLiteCtlCF::QueryInterface
//
//  Synopsis:   Class Factory QI - we just support IClassFactory and
//              IUnknown
//
//  Arguments:  [riid] -- interface desired
//              [ppv]  -- interface returned
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CLiteCtlCF::QueryInterface(REFIID riid, LPVOID * ppv)
{
    *ppv = 0;

    if (::IsEqualIID(riid, IID_IClassFactory) ||
        ::IsEqualIID(riid, IID_IUnknown))
    {
        *ppv = &g_CF;
        return S_OK;
    }

    return E_NOINTERFACE;
}

//+---------------------------------------------------------------------------
//
//  Member:     CLiteCtlCF::CreateInstance
//
//  Synopsis:   IClassFactory::CreateInstance() - this is where we
//              create 'instances' of CLiteCtl.
//
//  Arguments:  [pUnkOuter] -- controlling unknown
//              [riid]      -- interface to return
//              [ppv]       -- place to return it
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CLiteCtlCF::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppv)
{
    HRESULT       hr;
    CLiteCtl * pLiteCtl = 0;

    // we don't support aggregation.
    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    if (!ppv)
        return E_INVALIDARG;

    *ppv = 0;  // init in case of failure.

    // note CLiteCtl::QueryInterface is reentrant and must remain so
    // or we need to bracket this with critsec.
    pLiteCtl = new CLiteCtl;
    if (!pLiteCtl)
        return E_OUTOFMEMORY;

    hr = pLiteCtl->Init();
    if (hr)
        goto cleanup;

    hr = pLiteCtl->QueryInterface(riid, ppv);
    if (hr)
        goto cleanup;

cleanup:
    // if pLiteCtl exists, it needs to be released, because the only refcount on it
    // should be the one created at QI time.
    if (pLiteCtl)
        pLiteCtl->Release();

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Function:   DllMain
//
//  Synopsis:   sets up g_hInst and disables threadlibrary calls
//
//----------------------------------------------------------------------------
BOOL APIENTRY
DllMain(HINSTANCE hInst, DWORD  dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        ::DisableThreadLibraryCalls(hInst);
        ::InitializeCriticalSection(&g_cs);
        g_hInst = hInst;
        break;

    case DLL_PROCESS_DETACH:
        ::DeleteCriticalSection(&g_cs);
        break;
    }
    return TRUE;
}

//+---------------------------------------------------------------------------
//
//  Function:   DllRegisterServer
//
//  Synopsis:   registers our server. 
//
//----------------------------------------------------------------------------
STDAPI DllRegisterServer(VOID)
{
    HRESULT  hr;
    LPTYPELIB pTL = 0;
    CHAR      ach[MAX_PATH];
    WCHAR     awch[MAX_PATH];

    if (!::GetModuleFileName(g_hInst, ach, NElems(ach)))
        return HRESULT_FROM_WIN32(::GetLastError());

    if (!::MultiByteToWideChar(CP_ACP, 0, ach, -1, awch, NElems(awch)))
        return HRESULT_FROM_WIN32(::GetLastError());

    hr = ::LoadTypeLib(awch, &pTL);
    if (hr)
        goto cleanup;

    hr = ::RegisterTypeLib(pTL, awch, 0);
    if (hr)
        goto cleanup;


    hr = ::RegisterControlObject(
                    "LiteCtl",
                    "MSJLiteCtl",
                    1,
                    TLID_LiteCtl,
                    CLSID_LiteCtl,
                    OLEMISC_INVISIBLEATRUNTIME | OLEMISC_SETCLIENTSITEFIRST,
                    0)
                    ? S_OK : E_FAIL;

    if (hr)
        goto cleanup;

    hr = ::CreateComponentCategory(
               CATID_SafeForScripting,
               L"Controls that are safely scriptable");
    if (hr)
        goto cleanup;

    hr = ::RegisterCLSIDInCategory(CLSID_LiteCtl, CATID_SafeForScripting);
    if (hr)
        goto cleanup;

cleanup:
    if (pTL)
        pTL->Release();

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Function:   DllUnregisterServer
//
//  Synopsis:   unregister the thing
//
//----------------------------------------------------------------------------
STDAPI DllUnregisterServer(VOID)
{
    return (::UnregisterAutomationObject(
                  "LiteCtl",
                  "MSJLiteCtl",
                  1,
                  CLSID_LiteCtl) ? S_OK : E_FAIL);
}

//+---------------------------------------------------------------------------
//
//  Function:   DllGetClassObject
//
//  Synopsis:   standard OLE entry point - returns class factory.
//              we just return a pointer to our one and only class
//              factory.
//
//  Arguments:  [clsid] -- CLSID of object desired
//              [iid]   -- Interface from object desired
//              [ppv]   -- returned interface
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDAPI
DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID *ppv)
{
    if (::IsEqualIID(clsid, CLSID_LiteCtl))
        return g_CF.QueryInterface(iid, ppv);
    else
        return CLASS_E_CLASSNOTAVAILABLE;
}

//+---------------------------------------------------------------------------
//
//  Function:   DllCanUnloadNow
//
//  Synopsis:   let system know if it's OK to unload us.
//
//----------------------------------------------------------------------------
STDAPI
DllCanUnloadNow(VOID)
{
    return g_cObj ? S_FALSE : S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CLiteCtl::CLiteCtl
//
//  Synopsis:   ctor for our control
//
//  Effects:    initializes data -ups global dll object count
//
//----------------------------------------------------------------------------
#pragma warning(disable:4355) // this used in initialization list
CLiteCtl::CLiteCtl(VOID) :
            m_pCS(0),
            m_ref(1),
            m_disp(this)
{
    ::EnterCriticalSection(&g_cs);
    g_cObj++;
    ::LeaveCriticalSection(&g_cs);
}
#pragma warning(default:4355)

//+---------------------------------------------------------------------------
//
//  Member:     CLiteCtl::~CLiteCtl
//
//  Synopsis:   dtor - releases IOleClientSite and decrements dll global
//              object count.
//
//----------------------------------------------------------------------------
CLiteCtl::~CLiteCtl(VOID)
{
    if (m_pCS)
       m_pCS->Release();

    ::EnterCriticalSection(&g_cs);
    g_cObj--;
    ::LeaveCriticalSection(&g_cs);
}

//+---------------------------------------------------------------------------
//
//  Member:     CLiteCtl::QueryInterface
//
//  Synopsis:   standard deal - returns our four interfaces.
//
//  Arguments:  [riid] -- iid of interface to return
//              [ppv]  -- pointer to returned interface
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CLiteCtl::QueryInterface(REFIID riid, LPVOID * ppv)
{
    *ppv = 0;

    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IOleObject))
        *ppv = this;
    else if (IsEqualIID(riid, IID_IDispatch) || IsEqualIID(riid, DIID_DLiteCtl))
        *ppv = &m_disp;
    else
        return E_NOINTERFACE;

    AddRef();

    return S_OK;
}

STDMETHODIMP_(ULONG)
CLiteCtl::AddRef(VOID)
{
    return ++m_ref;
}

STDMETHODIMP_(ULONG)
CLiteCtl::Release(VOID)
{
    ULONG ulRC;

    m_ref--;

    ulRC = m_ref;
    if (!m_ref)
        delete this;

    return ulRC;
}

//+---------------------------------------------------------------------------
//
//  Member:     CLiteCtl::Init
//
//  Synopsis:   calls dispatch object to initialize typeinfo
//----------------------------------------------------------------------------
HRESULT
CLiteCtl::Init(VOID)
{
    return m_disp.Init();
}

//+---------------------------------------------------------------------------
//
//  Function:   _GetProperty
//
//  Synopsis:   Generalized property retrieval routine, takes the
//              stringtable ID of the name of the property, the type
//              of the property, and a variant, and returns the
//              property value in the variant.
//
//  Effects:    Some property types allocate memory.  VariantClear()
//              should be used on the pVar returned (or, a more specific
//              deallocation method if desired).
//
//  Arguments:  [uIDName] -- stringtable ID of property
//              [vt]      -- type of property
//              [pVar]    -- variant with property returned in it.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
_GetProperty(
        LPDISPATCH pDisp,
        UINT       uIDName,
        VARTYPE    vt,
        LPVARIANT  pVar)
{
    DISPID     id;
    EXCEPINFO  excep;
    HRESULT    hr;
    UINT       uArgErr;
    DISPPARAMS dispparams = {0,0,0,0};

    _ASSERTE(pDisp);

    // Map the property name to a dispid.
    hr = _GetDISPID(pDisp, uIDName, &id);
    if (hr)
        return hr;

    // setup the variant for the property to be returned in it.
    ::VariantInit(pVar);
    V_VT(pVar) = vt;

    // get the property.
    return pDisp->Invoke(
                    id,
                    IID_NULL,
                    LOCALE_SYSTEM_DEFAULT,
                    DISPATCH_PROPERTYGET,
                    &dispparams,
                    pVar,
                    &excep,
                    &uArgErr);
}

//+---------------------------------------------------------------------------
//
//  Function:   _GetDispProperty
//
//  Synopsis:   helper wrapper for _GetProperty() for returning
//              LPDISPATCH - values properties.
//
//  Effects:    on success, *ppDisp points to an implementation of
//              IDispatch that must be Release()ed when done.
//
//  Arguments:  [uIDName] -- stringtable ID for name of property
//              [ppDisp]  -- LPDISPATCH returned on success.
//
//  Requires:   uIDName must point to a valid stringtable entry that
//              is the exact string value for the desired property
//              for IE.
//
//  Returns:    HRESULT - on failure, ppDisp is 0
//
//----------------------------------------------------------------------------
HRESULT
_GetDispProperty(
        LPDISPATCH   pDisp,
        UINT         uIDName,
        LPDISPATCH * ppDisp)
{
    HRESULT  hr;
    VARIANT var;

    _ASSERTE(pDisp);
    _ASSERTE(ppDisp);  // precondition

    *ppDisp = 0;

    hr = _GetProperty(pDisp, uIDName, VT_DISPATCH, &var);
    if (hr)
        return hr;

    // if not VT_DISPATCH returned, then bail out.  Don't permit this.
    if (VT_DISPATCH != V_VT(&var))
    {
        ::VariantClear(&var);
        return E_FAIL;
    }

    // make sure it's a nonzero pointer.
    *ppDisp = V_DISPATCH(&var);
    if (!*ppDisp)
        return E_FAIL;

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Function:   _GetDISPID
//
//  Synopsis:   reduce verbosity of GetIDsOfNames
//
//  Arguments:  [uIDName] -- stringtable ID for localized name of
//                           property or method.
//              [pDispId] -- dispid returned
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
_GetDISPID(
        LPDISPATCH pDisp,
        UINT       uIDName,
        DISPID *   pDispId)
{
    OLECHAR aOleCh[MAX_OLECMD_BUFFER_SIZE];
    OLECHAR * pOleCh = aOleCh;  // because GetIDsOfNames needs this.
    CHAR    ach[MAX_OLECMD_BUFFER_SIZE];
    INT     cch;

    _ASSERTE(pDisp);
    // explicitly ask for LoadStringA - because this is all that exists
    // on W95.  Get the localized string name of the OLE Automation
    // member from the stringtable.
    cch = ::LoadStringA(g_hInst, uIDName, ach, NElems(ach));
    if (!cch)
        return HRESULT_FROM_WIN32(::GetLastError());

    // convert the ANSI string to wide
    cch = ::MultiByteToWideChar(
                CP_ACP,
                0,
                ach,
                -1,
                aOleCh,
                NElems(aOleCh));

    if (!cch)
        return E_FAIL;

    _ASSERTE(cch > 0);
    _ASSERTE(cch <= MAX_OLECMD_BUFFER_SIZE);

    // map the string name to a dispid
    return pDisp->GetIDsOfNames(
                    IID_NULL,
                    &pOleCh,
                    1,
                    LOCALE_SYSTEM_DEFAULT,
                    pDispId);
}

//+---------------------------------------------------------------------------
//
//  Member:     CDispatch::Init
//
//  Synopsis:   initializes m_TI member - pointer to our typeinfo that
//              we use to implement IDispatch.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
CDispatch::Init(VOID)
{
    HRESULT hr;
    CHAR ach[MAX_PATH];
    WCHAR awch[MAX_PATH];
    LPTYPELIB pTL = 0;

    hr = ::LoadRegTypeLib(TcLID_LiteCtl, 1, 0, LOCALE_SYSTEM_DEFAULT, &pTL);
    if (hr)
    {
        // get the name of this binary.
        _SIDE_ASSERTE(::GetModuleFileName(g_hInst, ach, (sizeof ach / sizeof ach[0]) - 1));

        // convert the ANSI string to wide
        _SIDE_ASSERTE(::MultiByteToWideChar(
                    CP_ACP,
                    0,
                    ach,
                    -1,
                    awch,
                    NElems(awch)));

        // load the typelib from the binary
        hr = ::LoadTypeLib(awch, &pTL);
        if (hr)
            goto Cleanup;
    }

    _ASSERTE(pTL);

    hr = pTL->GetTypeInfoOfGuid(DIID_DLiteCtl, &m_pTI);

Cleanup:
    if (pTL)
        pTL->Release();

    return hr;

}

//+---------------------------------------------------------------------------
//
//  Member:     CLiteCtl::SetClientSite
//
//  Synopsis:   sets our client site - we'll use it later to get
//              IOleInPlaceSite, and from that, and hWnd to use for
//              parenting dialogs.
//
//  Arguments:  [pCS] -- pointer to IOleClientSite
//
//  Returns:    HRESULT - always returns S_OK.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CLiteCtl::SetClientSite(LPOLECLIENTSITE pCS)
{
    if (m_pCS)
    {
        m_pCS->Release();
        m_pCS = 0;
    }

    if (pCS)
    {
        m_pCS = pCS;
        pCS->AddRef();

    }

    return S_OK;
}

STDMETHODIMP
CDispatch::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    return m_pLiteCtl->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG)
CDispatch::AddRef(VOID)
{
    return m_pLiteCtl->AddRef();
}

STDMETHODIMP_(ULONG)
CDispatch::Release(VOID)
{
    return m_pLiteCtl->Release();
}

STDMETHODIMP
CDispatch::GetTypeInfoCount(UINT *pctinfo)
{
    *pctinfo = 1;
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CDispatch::GetTypeInfo
//
//  Synopsis:   just return m_pTI
//
//----------------------------------------------------------------------------
STDMETHODIMP
CDispatch::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo ** ppTI)
{
    // We do not support localized member names, so the lcid is ignored.
    if (!ppTI)
        return E_POINTER;

    *ppTI = 0;

    if (0 != itinfo)
        return TYPE_E_ELEMENTNOTFOUND;

    _ASSERT(m_pTI);

    m_pTI->AddRef();

    *ppTI = m_pTI;
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CDispatch::GetIDsOfNames
//
//  Synopsis:   use m_pTI to do this for us.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CDispatch::GetIDsOfNames(
         REFIID riid,
         LPOLESTR * rgszNames,
         UINT cNames,
         LCID lcid,
         DISPID * rgdispid)
{
    _ASSERTE(m_pTI);
    return ::DispGetIDsOfNames(m_pTI, rgszNames, cNames, rgdispid);
}

//+---------------------------------------------------------------------------
//
//  Member:     CDispatch::Invoke
//
//  Synopsis:   use m_pTI to do this for us.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CDispatch::Invoke(
         DISPID dispidMember,
         REFIID riid,
         LCID lcid,
         WORD wFlags,
         DISPPARAMS *pdispparams,
         VARIANT * pvarResult,
         EXCEPINFO * pexcepinfo,
         UINT * puArgErr)
{
    if (IID_NULL != riid)
        return DISP_E_UNKNOWNINTERFACE;

    _ASSERTE(m_pTI);

    // clear the errorinfo object.
    ::SetErrorInfo(0, 0);

    return m_pTI->Invoke(
                this,
                dispidMember,
                wFlags,
                pdispparams,
                pvarResult,
                pexcepinfo,
                puArgErr);
}

// our custom properties and methods.  

//+---------------------------------------------------------------------------
//
//  Member:     CDispatch::get_AnswerToTheUniverse
//
//  Synopsis:   returns 42 always.
//
//  Arguments:  [plAnswer] -- place to return it.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CDispatch::get_AnswerToTheUniverse(PLONG plAnswer)
{
    *plAnswer = 42;
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CDispatch::put_AnswerToTheUniverse
//
//  Synopsis:   only allows you to enter 42.
//
//  Arguments:  [lAnswer] -- answer to the universe - must be 42.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CDispatch::put_AnswerToTheUniverse(LONG lAnswer)
{
    if (lAnswer != 42)
        return E_FAIL;

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CDispatch::IEToolBar
//
//  Synopsis:   turns the IE toolbar on or off - the main purpose of this
//              is just to demonstrate as an ancillary issue how to
//              use the IOleClientSite pointer to do interesting things
//              to the browser.  The entire reason we implement IOleObject
//              is so we can get a pointer to the site.
//
//  Arguments:  [fToolBar] -- turn toolbar on or off.
//
//  Requires:   ClientSite must be set
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CDispatch::IEToolBar(VARIANT_BOOL fToolBar)
{
    LPSERVICEPROVIDER pSP              = 0;
    LPDISPATCH        pDisp            = 0;
    LPDISPATCH        pDispScript      = 0;
    LPDISPATCH        pDispWebBrowser  = 0;
    HRESULT           hr;
    VARIANT_BOOL      vb = fToolBar ? VARIANT_TRUE : VARIANT_FALSE;
    EXCEPINFO         excep;
    VARIANTARG        vararg;
    DISPID            idPut = DISPID_PROPERTYPUT;
    DISPID            id;
    DISPPARAMS        dp;

    // client site's gotta be set to do this.
    if (!m_pLiteCtl->m_pCS)
        return E_FAIL;

    // get the service provider from clientsite
    hr = m_pLiteCtl->m_pCS->QueryInterface(IID_IServiceProvider, (LPVOID *)&pSP);
    if (hr)
        goto cleanup;

    // queryservice for SID_SContainerDispatch
    hr = pSP->QueryService(
            SID_SContainerDispatch,
            IID_IDispatch,
            (LPVOID *)&pDisp);

    if (hr)
        goto cleanup;

    // from the dispatch obtained, get the "Script" property
    hr = _GetDispProperty(pDisp, IDS_SCRIPT, &pDispScript);
    if (hr)
        goto cleanup;

    // from the script object, get the "explorer" object property.
    hr = _GetDispProperty(pDispScript, IDS_EXPLORER, &pDispWebBrowser);
    if (hr)
        goto cleanup;

    // get the "ToolBar" property ID.
    hr = _GetDISPID(pDispWebBrowser, IDS_TOOLBAR, &id);
    if (hr)
        goto cleanup;

    // now setup dispparams structure to set the ToolBar property to False
    V_VT(&vararg) = VT_BOOL;
    V_BOOL(&vararg) = vb;
    dp.rgvarg = &vararg;
    dp.cArgs = 1;
    dp.cNamedArgs = 1;
    dp.rgdispidNamedArgs = &idPut;

    // set the property.
    hr = pDispWebBrowser->Invoke(
                 id,
                 IID_NULL,
                 LOCALE_SYSTEM_DEFAULT,
                 DISPATCH_PROPERTYPUT,
                 &dp,
                 0,
                 &excep,
                 0);

    if (hr)
        goto cleanup;

cleanup:
    if (pDispWebBrowser)
        pDispWebBrowser->Release();
    if (pDispScript)
        pDispScript->Release();
    if (pDisp)
        pDisp->Release();
    if (pSP)
        pSP->Release();

    return hr;
}

//=--------------------------------------------------------------------------=
// RegisterUnknownObject
//=--------------------------------------------------------------------------=
// registers a simple CoCreatable object.  nothing terribly serious.
// we add the following information to the registry:
//
// HKEY_CLASSES_ROOT\CLSID\<CLSID> = <ObjectName> Object
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\InprocServer32 = <path to local server>
//
// Parameters:
//    LPCSTR       - [in] Object Name
//    REFCLSID     - [in] CLSID of the object
//
// Output:
//    BOOL         - FALSE means couldn't register it all
//
// Notes:
//
BOOL
RegisterUnknownObject(LPCSTR pszObjectName, REFCLSID riidObject)
{
    HKEY  hk = NULL, hkSub = NULL;
    char  szGuidStr[GUID_STR_LEN];
    DWORD dwPathLen, dwDummy;
    char  szScratch[MAX_PATH];
    long  l;

    // clean out any garbage
    //
//    UnregisterUnknownObject(riidObject);

    // HKEY_CLASSES_ROOT\CLSID\<CLSID> = <ObjectName> Object
    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\InprocServer32 = <path to local server>
    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\InprocServer32  @ThreadingModel = Apartment
    //
    if (!StringFromGuidA(riidObject, szGuidStr)) goto CleanUp;
    wsprintf(szScratch, "CLSID\\%s", szGuidStr);
    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szScratch, 0, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s Object", pszObjectName);
    l = RegSetValueEx(hk, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "InprocServer32", 0, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    dwPathLen = GetModuleFileName(g_hInst, szScratch, sizeof(szScratch));
    if (!dwPathLen) goto CleanUp;

    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szScratch, dwPathLen + 1);
    CLEANUP_ON_ERROR(l);

    l = RegSetValueEx(hkSub, "ThreadingModel", 0, REG_SZ, (BYTE *)"Apartment", sizeof("Apartment"));
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    RegCloseKey(hk);

    return TRUE;

    // we are not very happy!
    //
  CleanUp:
    if (hk) RegCloseKey(hk);
    if (hkSub) RegCloseKey(hkSub);
    return FALSE;

}

//=--------------------------------------------------------------------------=
// RegisterAutomationObject
//=--------------------------------------------------------------------------=
// given a little bit of information about an automation object, go and put it
// in the registry.
// we add the following information in addition to that set up in
// RegisterUnknownObject:
//
//
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName> = <ObjectName> Object
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\CLSID = <CLSID>
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\CurVer = <ObjectName>.Object.<VersionNumber>
//
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber> = <ObjectName> Object
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber>\CLSID = <CLSID>
//
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\TypeLib = <LibidOfTypeLibrary>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\ProgID = <LibraryName>.<ObjectName>.<VersionNumber>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\VersionIndependentProgID = <LibraryName>.<ObjectName>
//
// Parameters:
//    LPCSTR       - [in] Library Name
//    LPCSTR       - [in] Object Name
//    long         - [in] Version Number
//    REFCLSID     - [in] LIBID of type library
//    REFCLSID     - [in] CLSID of the object
//
// Output:
//    BOOL         - FALSE means not all of it was registered
//
// Notes:
//
BOOL RegisterAutomationObject
(
    LPCSTR   pszLibName,
    LPCSTR   pszObjectName,
    long     lVersion,
    REFCLSID riidLibrary,
    REFCLSID riidObject
)
{
    HKEY  hk = NULL, hkSub = NULL;
    char  szGuidStr[GUID_STR_LEN];
    char  szScratch[MAX_PATH];
    long  l;
    DWORD dwDummy;

    // first register the simple Unknown stuff.
    //
    if (!RegisterUnknownObject(pszObjectName, riidObject)) return FALSE;

    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName> = <ObjectName> Object
    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\CLSID = <CLSID>
    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\CurVer = <ObjectName>.Object.<VersionNumber>
    //
    lstrcpy(szScratch, pszLibName);
    lstrcat(szScratch, ".");
    lstrcat(szScratch, pszObjectName);

    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szScratch, 0L, "",
                       REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE,
                       NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s Object", pszObjectName);
    l = RegSetValueEx(hk, NULL, 0L, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch)+1);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "CLSID", 0L, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    if (!StringFromGuidA(riidObject, szGuidStr))
        goto CleanUp;

    l = RegSetValueEx(hkSub, NULL, 0L, REG_SZ, (BYTE *)szGuidStr, lstrlen(szGuidStr) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    l = RegCreateKeyEx(hk, "CurVer", 0, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s.%s.%ld", pszLibName, pszObjectName, lVersion);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    RegCloseKey(hk);

    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber> = <ObjectName> Object
    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber>\CLSID = <CLSID>
    //
    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szScratch, 0, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s Object", pszObjectName);
    l = RegSetValueEx(hk, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "CLSID", 0, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szGuidStr, lstrlen(szGuidStr) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    RegCloseKey(hk);

    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\ProgID = <LibraryName>.<ObjectName>.<VersionNumber>
    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\VersionIndependentProgID = <LibraryName>.<ObjectName>
    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\TypeLib = <LibidOfTypeLibrary>
    //
    if (!StringFromGuidA(riidObject, szGuidStr)) goto CleanUp;
    wsprintf(szScratch, "CLSID\\%s", szGuidStr);

    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szScratch, 0, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ|KEY_WRITE, NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "VersionIndependentProgID", 0, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s.%s", pszLibName, pszObjectName);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);

    l = RegCreateKeyEx(hk, "ProgID", 0, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s.%s.%ld", pszLibName, pszObjectName, lVersion);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    l = RegCreateKeyEx(hk, "TypeLib", 0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE,
                       NULL, &hkSub, &dwDummy);

    if (!StringFromGuidA(riidLibrary, szGuidStr)) goto CleanUp;

    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szGuidStr, lstrlen(szGuidStr) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    RegCloseKey(hk);
    return TRUE;

  CleanUp:
    if (hk) RegCloseKey(hkSub);
    if (hk) RegCloseKey(hk);
    return FALSE;
}

//=--------------------------------------------------------------------------=
// RegisterControlObject.
//=--------------------------------------------------------------------------=
// in addition to writing out automation object information, this function
// writes out some values specific to a control.
//
// What we add here:
//
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\Control
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\MiscStatus\1 = <MISCSTATUSBITS>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\ToolboxBitmap32 = <PATH TO BMP>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\Version = <VERSION>
//
// Parameters:
//    LPCSTR       - [in] Library Name
//    LPCSTR       - [in] Object Name
//    long         - [in] Version Number
//    REFCLSID     - [in] LIBID of type library
//    REFCLSID     - [in] CLSID of the object
//    DWORD        - [in] misc status flags for ctl
//    WORD         - [in] toolbox id for control
//
// Output:
//    BOOL
//
//
BOOL
RegisterControlObject(
        LPCSTR   pszLibName,
        LPCSTR   pszObjectName,
        long     lVersion,
        REFCLSID riidLibrary,
        REFCLSID riidObject,
        DWORD    dwMiscStatus,
        WORD     wToolboxBitmapId)
{
    HKEY    hk, hkSub = NULL, hkSub2 = NULL;
    char    szTmp[MAX_PATH];
    char    szGuidStr[GUID_STR_LEN];
    DWORD   dwDummy;
    LONG    l;

    // first register all the automation information for this sucker.
    //
    if (!RegisterAutomationObject(pszLibName, pszObjectName, lVersion, riidLibrary, riidObject)) return FALSE;

    // then go and register the control specific stuff.
    //
    StringFromGuidA(riidObject, szGuidStr);
    wsprintf(szTmp, "CLSID\\%s", szGuidStr);
    l = RegOpenKeyEx(HKEY_CLASSES_ROOT, szTmp, 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    // create the control flag.
    //
    l = RegCreateKeyEx(hk, "Control", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    // now set up the MiscStatus Bits...
    //
    RegCloseKey(hkSub);
    hkSub = NULL;
    l = RegCreateKeyEx(hk, "MiscStatus", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    szTmp[0] = '0';
    szTmp[1] = '\0';
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, 2);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hkSub, "1", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub2, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szTmp, "%d", dwMiscStatus);
    l = RegSetValueEx(hkSub2, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);
    RegCloseKey(hkSub2);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);

    // now set up the toolbox bitmap
    //
    GetModuleFileName(g_hInst, szTmp, MAX_PATH);
    wsprintf(szGuidStr, ", %d", wToolboxBitmapId);
    lstrcat(szTmp, szGuidStr);

    l = RegCreateKeyEx(hk, "ToolboxBitmap32", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);
    CLEANUP_ON_ERROR(l);

    // now set up the version information
    //
    RegCloseKey(hkSub);
    l = RegCreateKeyEx(hk, "Version", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szTmp, "%ld.0", lVersion);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);

  CleanUp:
    if (hk)
        RegCloseKey(hk);
    if (hkSub)
        RegCloseKey(hkSub);

    return (l == ERROR_SUCCESS) ? TRUE : FALSE;
}

//=--------------------------------------------------------------------------=
// StringFromGuidA
//=--------------------------------------------------------------------------=
// returns an ANSI string from a CLSID or GUID
//
// Parameters:
//    REFIID               - [in]  clsid to make string out of.
//    LPSTR                - [in]  buffer in which to place resultant GUID.
//
// Output:
//    int                  - number of chars written out.
//
// Notes:
//
INT
StringFromGuidA(REFIID riid, LPSTR pszBuf)
{
    return wsprintf((char *)pszBuf, "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", riid.Data1,
            riid.Data2, riid.Data3, riid.Data4[0], riid.Data4[1], riid.Data4[2],
            riid.Data4[3], riid.Data4[4], riid.Data4[5], riid.Data4[6], riid.Data4[7]);

}

//=--------------------------------------------------------------------------=
// UnregisterUnknownObject
//=--------------------------------------------------------------------------=
// cleans up all the stuff that RegisterUnknownObject puts in the
// registry.
//
// Parameters:
//    REFCLSID     - [in] CLSID of the object
//
// Output:
//    BOOL         - FALSE means not all of it was registered
//
// Notes:
//    - WARNING: this routine will blow away all other keys under the CLSID
//      for this object.  mildly anti-social, but likely not a problem.
//
BOOL UnregisterUnknownObject
(
    REFCLSID riidObject
)
{
    char szScratch[MAX_PATH];
    HKEY hk;
    BOOL f;
    long l;

    // delete everybody of the form
    //   HKEY_CLASSES_ROOT\CLSID\<CLSID> [\] *
    //
    if (!StringFromGuidA(riidObject, szScratch))
        return FALSE;

    l = RegOpenKeyEx(HKEY_CLASSES_ROOT, "CLSID", 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    f = DeleteKeyAndSubKeys(hk, szScratch);
    RegCloseKey(hk);

    return f;
}

//=--------------------------------------------------------------------------=
// UnregisterAutomationObject
//=--------------------------------------------------------------------------=
// unregisters an automation object, including all of it's unknown object
// information.
//
// Parameters:
//    LPCSTR       - [in] Library Name
//    LPCSTR       - [in] Object Name
//    long         - [in] Version Number
//    REFCLSID     - [in] CLSID of the object
//
// Output:
//    BOOL         - FALSE means couldn't get it all unregistered.
//
// Notes:
//
BOOL UnregisterAutomationObject
(
    LPCSTR   pszLibName,
    LPCSTR   pszObjectName,
    long     lVersion,
    REFCLSID riidObject
)
{
    char szScratch[MAX_PATH];
    BOOL f;

    // first thing -- unregister Unknown information
    //
    f = UnregisterUnknownObject(riidObject);
    if (!f) return FALSE;

    // delete everybody of the form:
    //   HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName> [\] *
    //
    wsprintf(szScratch, "%s.%s", pszLibName, pszObjectName);
    f = DeleteKeyAndSubKeys(HKEY_CLASSES_ROOT, szScratch);
    if (!f) return FALSE;

    // delete everybody of the form
    //   HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber> [\] *
    //
    wsprintf(szScratch, "%s.%s.%ld", pszLibName, pszObjectName, lVersion);
    f = DeleteKeyAndSubKeys(HKEY_CLASSES_ROOT, szScratch);
    if (!f) return FALSE;

    return TRUE;
}

//=--------------------------------------------------------------------------=
// UnregisterTypeLibrary
//=--------------------------------------------------------------------------=
// blows away the type library keys for a given libid.
//
// Parameters:
//    REFCLSID        - [in] libid to blow away.
//
// Output:
//    BOOL            - TRUE OK, FALSE bad.
//
// Notes:
//    - WARNING: this function just blows away the entire type library section,
//      including all localized versions of the type library.  mildly anti-
//      social, but not killer.
//
BOOL UnregisterTypeLibrary
(
    REFCLSID riidLibrary
)
{
    HKEY hk;
    char szScratch[GUID_STR_LEN];
    long l;
    BOOL f;

    // convert the libid into a string.
    //
    if (!StringFromGuidA(riidLibrary, szScratch))
        return FALSE;

    l = RegOpenKeyEx(HKEY_CLASSES_ROOT, "TypeLib", 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    f = DeleteKeyAndSubKeys(hk, szScratch);
    RegCloseKey(hk);
    return f;
}


//=--------------------------------------------------------------------------=
// DeleteKeyAndSubKeys
//=--------------------------------------------------------------------------=
// delete's a key and all of it's subkeys.
//
// Parameters:
//    HKEY                - [in] delete the descendant specified
//    LPSTR               - [in] i'm the descendant specified
//
// Output:
//    BOOL                - TRUE OK, FALSE baaaad.
//
// Notes:
//    - Despite the win32 docs claiming it does, RegDeleteKey doesn't seem to
//      work with sub-keys under windows 95.
//
BOOL DeleteKeyAndSubKeys
(
    HKEY    hkIn,
    LPSTR   pszSubKey
)
{
    HKEY  hk;
    char  szTmp[MAX_PATH];
    DWORD dwTmpSize;
    long  l;
    BOOL  f;

    l = RegOpenKeyEx(hkIn, pszSubKey, 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    // loop through all subkeys, blowing them away.
    //
    f = TRUE;

    while (f)
    {
        dwTmpSize = MAX_PATH;
        l = RegEnumKeyEx(hk, 0, szTmp, &dwTmpSize, 0, NULL, NULL, NULL);
        if (l != ERROR_SUCCESS) break;
        f = DeleteKeyAndSubKeys(hk, szTmp);
    }

    // there are no subkeys left, [or we'll just generate an error and return FALSE].
    // let's go blow this dude away.
    //
    RegCloseKey(hk);
    l = RegDeleteKey(hkIn, pszSubKey);

    return (l == ERROR_SUCCESS) ? TRUE : FALSE;
}

