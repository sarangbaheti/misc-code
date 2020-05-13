////////////////////////////////////////////////////////
//
// TerminateOnIdle.cpp - Copyright 1997, Don Box 
//
// A custom surrogate that terminates after 15 seconds of
// no activity. 
//
// Note: Be sure to configure your InprocServer to use this
//       process as a custom surrogate. Also, make sure that 
//       the AppID used in WinMain matches the one you wish to use.
//


#define _WIN32_WINNT  0x0402 
#include <windows.h>
#include <vector>
#include <assert.h>

#ifndef __ISurrogate_INTERFACE_DEFINED__
#error "You need SP2-compliant SDK headers to compile this file."
#endif        

// NOTE! The SP2 SDK patch did not contain an updated UUID.LIB file
// Once this library is patched, this definition should be removed.
const IID IID_ISurrogate = { 0x00000022, 0x0000, 0x0000,
            {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};

class CClassObjectWrapper : public IClassFactory,
                            public IMarshal
{
    LONG m_cRef;
    CLSID m_clsid;
    DWORD m_dwReg;
    friend class CSurrogate;
public:
    CClassObjectWrapper(REFCLSID rclsid);
    virtual ~CClassObjectWrapper(void);
    
// IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    
// IClassFactory methods
    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv);
    STDMETHODIMP LockServer(BOOL fLock);
    
// IMarshal methods
    STDMETHODIMP GetUnmarshalClass(REFIID riid, void *pv, DWORD dwDstCtx,
                                   void *pvDstCtx, DWORD flags, CLSID *pCid);
    STDMETHODIMP GetMarshalSizeMax(REFIID riid, void *pv, DWORD dwDstCtx,
                                    void *pvDstCtx, DWORD flags, DWORD *pSize);
    STDMETHODIMP MarshalInterface(IStream *pStm, REFIID riid, void *pv,
                                  DWORD dwDstCtx, void *pvDstCtx, DWORD flags);
    STDMETHODIMP UnmarshalInterface(IStream *pStm, REFIID riid, void **ppv);
    STDMETHODIMP ReleaseMarshalData(IStream *pStm);
    STDMETHODIMP DisconnectObject(DWORD dwReserved);
};
        
CClassObjectWrapper::CClassObjectWrapper(REFCLSID rclsid)
:   m_cRef(0)
{
    m_clsid = rclsid;
}

CClassObjectWrapper::~CClassObjectWrapper(void) { }

// IUnknown methods
STDMETHODIMP 
CClassObjectWrapper::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown || riid == IID_IClassFactory)
        *ppv = (IClassFactory*)this;
    else if (riid == IID_IMarshal)
        *ppv = (IMarshal*)this;
    else 
        return (*ppv = 0), E_NOINTERFACE;
    ((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
CClassObjectWrapper::AddRef(void)
{
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) 
CClassObjectWrapper::Release(void)
{
    ULONG result = InterlockedDecrement(&m_cRef);
    if (result == 0)
        delete this;
    return result;
}

// IClassFactory methods
STDMETHODIMP 
CClassObjectWrapper::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
// forward the call to the "real" inproc factory 
    return CoCreateInstance(m_clsid,pUnkOuter,CLSCTX_INPROC_SERVER,riid,ppv);
}


STDMETHODIMP 
CClassObjectWrapper::LockServer(BOOL fLock)
{
    return S_OK;
}


// IMarshal methods
STDMETHODIMP 
CClassObjectWrapper::GetUnmarshalClass(REFIID riid, void *pv, DWORD dwDstCtx,
                                     void *pvDstCtx, DWORD flags, CLSID *pCid)
{
    *pCid = CLSID_StdMarshal; // we hardwire the standard marshaler here
    return S_OK;
}

STDMETHODIMP 
CClassObjectWrapper::GetMarshalSizeMax(REFIID riid, void *pv, DWORD dwDstCtx,
                                     void *pvDstCtx, DWORD flags, DWORD *pSize)
{
// because we use the standard marshaler, we will never be asked to size a ptr.
    return E_UNEXPECTED;                                         
}

STDMETHODIMP 
CClassObjectWrapper::MarshalInterface(IStream *pStm, REFIID riid, void *pv,
                                   DWORD dwDstCtx, void *pvDstCtx, DWORD flags)
{
// this is called when the SCM needs a pointer to the inproc class object
// we need to return the inproc pointer marshaled into pStm
    IUnknown *pUnk = 0;
    HRESULT hr = CoGetClassObject(m_clsid, CLSCTX_INPROC_SERVER,
                     0, IID_IUnknown, (void**)&pUnk);
    if (SUCCEEDED(hr))
    {
        hr = CoMarshalInterface(pStm,riid,pUnk,dwDstCtx,pvDstCtx,flags);
        pUnk->Release();
    }
    return hr;                                         
}

STDMETHODIMP 
CClassObjectWrapper::UnmarshalInterface(IStream *pStm,REFIID riid,void **ppv)
{
    return E_UNEXPECTED;
}

STDMETHODIMP 
CClassObjectWrapper::ReleaseMarshalData(IStream *pStm)
{
    return CoReleaseMarshalData(pStm);                                         
}


STDMETHODIMP 
CClassObjectWrapper::DisconnectObject(DWORD dwReserved)
{
    return S_OK;
}

class CSurrogate : public ISurrogate
{
// we need to track all of our class objects and CoRevoke them at teardown time
    std::vector<CClassObjectWrapper *> m_rgClassObjects;
public:
    CSurrogate(void);
    virtual ~CSurrogate(void);
    
    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    
    // ISurrogate methods
    STDMETHODIMP LoadDllServer(REFCLSID rclsid);
    STDMETHODIMP FreeSurrogate();
};

CSurrogate::CSurrogate(void){}
CSurrogate::~CSurrogate(void){}

// IUnknown methods
STDMETHODIMP 
CSurrogate::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown || riid == IID_ISurrogate)
        *ppv = (ISurrogate*)this;
    else 
        return (*ppv = 0), E_NOINTERFACE;
    ((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
CSurrogate::AddRef(void)
{
    return 2;
}

STDMETHODIMP_(ULONG) 
CSurrogate::Release(void)
{
    return 1;
}

// ISurrogate methods
STDMETHODIMP 
CSurrogate::LoadDllServer(REFCLSID rclsid)
{
// create a wrapper class object
    CClassObjectWrapper *pcf = new CClassObjectWrapper(rclsid);
    if (!pcf)
        return E_OUTOFMEMORY;
// register the wrapper with COM using REGCLS_SURROGATE
    pcf->AddRef();
    HRESULT hr = CoRegisterClassObject(rclsid, (IClassFactory*)pcf,
                                       CLSCTX_LOCAL_SERVER, REGCLS_SURROGATE,
                                       &pcf->m_dwReg);
// keep track of class object to revoke later on
    if (SUCCEEDED(hr))
        m_rgClassObjects.push_back(pcf);
    else
        pcf->Release();
    return hr;
}

STDMETHODIMP 
CSurrogate::FreeSurrogate()
{
// tear down all connections with COM
    for (int i = 0; i < m_rgClassObjects.size(); i++)
    {
        CoRevokeClassObject(m_rgClassObjects[i]->m_dwReg);
        m_rgClassObjects[i]->Release();
    }
// release pointers to class object wrappers
    m_rgClassObjects.erase(m_rgClassObjects.begin(), m_rgClassObjects.end());
// terminate main thread
    PostQuitMessage(0);
    return S_OK;
}
        
        
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR szCmdParam, int)
{
// join a new single-threaded apartment
    HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    assert(hr == S_OK);

// pick up access permission settings from our AppID.
    const GUID APPID_Custom = { 0x5ae3AAAA, 0x79A0, 0x11D0,
                { 0x8B, 0xE7, 0x00, 0x80, 0xC7, 0x8C, 0x6C, 0x8C }};
    hr = CoInitializeSecurity((void*)&APPID_Custom, 0, 0, 0,
                                      0, 0, 0, EOAC_APPID, 0);
    assert(hr == S_OK);

// declare and register our implementation of ISurrogate
    CSurrogate sur;
    hr = CoRegisterSurrogate(&sur);
    assert(hr == S_OK);

// explicitly load/register the initial CLSID
// on input, we will receive the CLSID of the class that caused our surrogate 
// to load as a command line argument. We need to explicitly load and register
// this initial class ourselves.

    OLECHAR wszGUID[39];
    mbstowcs(wszGUID, szCmdParam, 39);
    wszGUID[38] = 0;  CLSID clsidInitialClass;
    hr = CLSIDFromString(wszGUID, &clsidInitialClass);
    assert(hr == S_OK);

    hr = sur.LoadDllServer(clsidInitialClass);
    assert(hr == S_OK);

// run a message pump that terminates after 15 seconds of inactivity.
// this is the "custom" behavior of our surrogate
    DWORD dwIdleTime = 15000; 
    MSG msg;
    HANDLE heventDone = CreateEvent(0, FALSE, FALSE, 0);
    while (MsgWaitForMultipleObjects(1, &heventDone, FALSE, dwIdleTime, 
                                     QS_ALLINPUT) == WAIT_OBJECT_0 + 1)
        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            if (msg.message != WM_QUIT)
                DispatchMessage(&msg);
            else
                SetEvent(heventDone);

// turn off COM, which will implicitly call our FreeSurrogate if
// it has not happened already
    CoUninitialize();
    return 0;
}
