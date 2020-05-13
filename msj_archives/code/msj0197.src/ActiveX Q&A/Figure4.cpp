#define _WIN32_DCOM 
#include <windows.h>
#include <initguid.h>

HANDLE g_heventDone = CreateEvent(0, TRUE, FALSE, 0);

inline void LockModule(void)
{
    CoAddRefServerProcess();
}

inline void UnlockModule(void)
{
    if (CoReleaseServerProcess() == 0)
        SetEvent(g_heventDone);
}

class CClassFactory : public IClassFactory
{
    HRESULT (*m_pfnCreate)(IUnknown **ppunk);
public:
    CClassFactory(HRESULT (*pfnCreate)(IUnknown **ppunk))
        : m_pfnCreate(pfnCreate)
    {
    }
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if (riid == IID_IUnknown || riid == IID_IClassFactory)
            *ppv = (IClassFactory*)this;
        else
        {
            *ppv = 0;
            return E_NOINTERFACE;
        }
        ((IUnknown*)*ppv)->AddRef();
        return S_OK;
    }

    STDMETHODIMP_(ULONG) AddRef(void)
    {
        return 2;
    }

    STDMETHODIMP_(ULONG) Release(void)
    {
        return 1;
    }

    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid,
                                void **ppv)
    {
// ensure that if server is shutting down, that we do
// not create a new object, but instead tell the SCM
// that we are going away by returning CO_E_SERVER_STOPPING.
        LockModule();
        HRESULT hr = CO_E_SERVER_STOPPING;
        *ppv = 0;
// check to see if shutdown event is set
        if (WaitForSingleObject(g_heventDone, 0) != WAIT_OBJECT_0)
        {
            if (pUnkOuter)
                return CLASS_E_NOAGGREGATION;
            IUnknown *pUnk = 0;
            hr = m_pfnCreate(&pUnk);
            if (SUCCEEDED(hr))
            {
                pUnk->AddRef();
                hr = pUnk->QueryInterface(riid, ppv);
                pUnk->Release();
            }
        }
        UnlockModule();
        return hr;
    }

    STDMETHODIMP LockServer(BOOL bLock)
    {
        if (bLock)
            LockModule();
        else
            UnlockModule();
        return S_OK;
    }
};

// {1E8B93D0-210B-11d0-B34B-0080C7BC7884}
DEFINE_GUID(CLSID_MTObject1, 
0x1e8b93d0, 0x210b, 0x11d0, 0xb3, 0x4b, 0x0, 0x80, 0xc7, 0xbc, 0x78, 0x84);

// {1E8B93D1-210B-11d0-B34B-0080C7BC7884}
DEFINE_GUID(CLSID_MTObject2, 
0x1e8b93d1, 0x210b, 0x11d0, 0xb3, 0x4b, 0x0, 0x80, 0xc7, 0xbc, 0x78, 0x84);

class CMTObjectBase : public IPersist
{
    LONG m_cRef;
public:
    CMTObjectBase(void)
        : m_cRef(0)
    {
        LockModule();
    }

    virtual ~CMTObjectBase(void)
    {
        UnlockModule();
    }

    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if (riid == IID_IUnknown || riid == IID_IPersist)
            *ppv = (IPersist*)this;
        else
        {
            *ppv = 0;
            return E_NOINTERFACE;
        }
        ((IUnknown*)*ppv)->AddRef();
        return S_OK;
    }

    STDMETHODIMP_(ULONG) AddRef(void)
    {
        InterlockedIncrement(&m_cRef);
        return m_cRef;
    }

    STDMETHODIMP_(ULONG) Release(void)
    {
        if (InterlockedDecrement(&m_cRef) != 0)
            return m_cRef;
        delete this;
        return 0;
    }
};

class CMTObject1 : public CMTObjectBase 
{
public:
    STDMETHODIMP GetClassID(CLSID *pclsid)
    {
        *pclsid = CLSID_MTObject1;
        return S_OK;
    }
    static HRESULT Create(IUnknown **ppunk) 
    {
        *ppunk = new CMTObject1;
        return *ppunk ? S_OK : E_OUTOFMEMORY;
    }
};

class CMTObject2 : public CMTObjectBase 
{
public:
    STDMETHODIMP GetClassID(CLSID *pclsid)
    {
        *pclsid = CLSID_MTObject2;
        return S_OK;
    }
    static HRESULT Create(IUnknown **ppunk) 
    {
        *ppunk = new CMTObject2;
        return *ppunk ? S_OK : E_OUTOFMEMORY;
    }
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR szCmdParam, int)
{
    if (strstr(szCmdParam, "/UnregServer") || strstr(szCmdParam, "-UnregServer"))
    {
        RegDeleteKeyA(HKEY_CLASSES_ROOT, "CLSID\\{1E8B93D0-210B-11d0-B34B-0080C7BC7884}\\LocalServer32");
        RegDeleteKeyA(HKEY_CLASSES_ROOT, "CLSID\\{1E8B93D0-210B-11d0-B34B-0080C7BC7884}");
        RegDeleteKeyA(HKEY_CLASSES_ROOT, "CLSID\\{1E8B93D1-210B-11d0-B34B-0080C7BC7884}\\LocalServer32");
        RegDeleteKeyA(HKEY_CLASSES_ROOT, "CLSID\\{1E8B93D1-210B-11d0-B34B-0080C7BC7884}");
        return 0;
    }

    char szFileName[MAX_PATH];
    GetModuleFileNameA(0, szFileName, MAX_PATH);
    RegSetValueA(HKEY_CLASSES_ROOT, "CLSID\\{1E8B93D0-210B-11d0-B34B-0080C7BC7884}",
                 REG_SZ, "MTObject1", 9);
    RegSetValueA(HKEY_CLASSES_ROOT, "CLSID\\{1E8B93D0-210B-11d0-B34B-0080C7BC7884}\\LocalServer32",
                 REG_SZ, szFileName, strlen(szFileName));
    RegSetValueA(HKEY_CLASSES_ROOT, "CLSID\\{1E8B93D1-210B-11d0-B34B-0080C7BC7884}",
                 REG_SZ, "MTObject2", 9);
    RegSetValueA(HKEY_CLASSES_ROOT, "CLSID\\{1E8B93D1-210B-11d0-B34B-0080C7BC7884}\\LocalServer32",
                 REG_SZ, szFileName, strlen(szFileName));

    if (strstr(szCmdParam, "/RegServer") || strstr(szCmdParam, "-RegServer"))
        return 0;

    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr))
        return int(hr);

    DWORD dw1, dw2;
    CClassFactory cf1(CMTObject1::Create);
    CClassFactory cf2(CMTObject2::Create);

    hr = CoRegisterClassObject(CLSID_MTObject1, &cf1,
                               CLSCTX_LOCAL_SERVER,
                               REGCLS_MULTIPLEUSE|REGCLS_SUSPENDED,
                               &dw1);
    if (SUCCEEDED(hr))
    {
        hr = CoRegisterClassObject(CLSID_MTObject2, &cf2,
                                   CLSCTX_LOCAL_SERVER,
                                   REGCLS_MULTIPLEUSE|REGCLS_SUSPENDED,
                                   &dw2);
        if (SUCCEEDED(hr))
        {
// all class objects registered suspended, so tell the SCM we are
// ready and wait for our internal shutdown notification
            hr = CoResumeClassObjects();
            if (SUCCEEDED(hr))
                WaitForSingleObject(g_heventDone, INFINITE);

            hr = CoRevokeClassObject(dw2);
        }
        hr = CoRevokeClassObject(dw1);
    }

    Sleep(500);
    CoUninitialize();
    return 0;
}
