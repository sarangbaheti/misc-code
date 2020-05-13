///////////////////////////////////////////////
//
// RectByVal.h
// Copyright 1997, Don Box Inc.
//
// This file implements the a COM rectangle that marshals by value
//

#include "irect.h"
#include "mbvguid.h"
extern void SvcLock(void); extern void SvcUnlock(void);

class CRectByValue : public IRect,  public IPersistStream
{
    LONG m_cRef;                    // for IUnknown
    ITypeInfo *m_pTypeInfo;         // for IDispatch
    RECT m_rect;                    // for IRect
    BOOL m_bIsDirty;                // for IPersistStream
    IUnknown *m_pUnkInnerMarshal;   // for IMarshal
public:
// helper routine called from QI to create aggregate if not already created.
    HRESULT GetIMarshal(void **ppv) {
        HRESULT hr = S_OK;
    // create the inner object the first time through
        if (m_pUnkInnerMarshal == 0)
            hr = CoCreateInstance(CLSID_MarshalByValue, (IRect*)this, 
                                  CLSCTX_INPROC_SERVER, IID_IUnknown, 
                                  (void**)&m_pUnkInnerMarshal);

    // return the inner object's IMarshal interface
        if (m_pUnkInnerMarshal)
            hr = m_pUnkInnerMarshal->QueryInterface(IID_IMarshal, ppv);
        return hr;
    }

    CRectByValue(void)
    :   m_cRef(0), m_pTypeInfo(0), m_bIsDirty(FALSE), m_pUnkInnerMarshal(0)
    {
        ZeroMemory(&m_rect, sizeof(m_rect));
        ITypeLib *ptl = 0;
        HRESULT hr = LoadRegTypeLib(LIBID_RectByValLib, 1, 0, 9, &ptl);
        if (SUCCEEDED(hr))
        {
            hr = ptl->GetTypeInfoOfGuid(IID_IRect, &m_pTypeInfo);
            ptl->Release();
        }
    }

    virtual ~CRectByValue(void)
    {
        if (m_pUnkInnerMarshal)
            m_pUnkInnerMarshal->Release();
        if (m_pTypeInfo)
            m_pTypeInfo->Release();
    }

// Non-delegating IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if (riid == IID_IRect)               *ppv = (IRect*)this;
        else if (riid == IID_IDispatch)      *ppv = (IRect*)this;
        else if (riid == IID_IUnknown)       *ppv = (IRect*)this;
        else if (riid == IID_IPersistStream) *ppv = (IPersistStream*)this;
        else if (riid == IID_IPersist)       *ppv = (IPersistStream*)this;
    // use the inner object's IMarshal interface
        else if (riid == IID_IMarshal)       return this->GetIMarshal(ppv);
        else                                 return (*ppv = 0), E_NOINTERFACE;
        ((IUnknown*)*ppv)->AddRef();
        return S_OK;
    }

    STDMETHODIMP_(ULONG) AddRef(void)
    {
        if (m_cRef == 0) SvcLock();
        return InterlockedIncrement(&m_cRef);
    }

    STDMETHODIMP_(ULONG) Release(void)
    {
        if (InterlockedDecrement(&m_cRef))
            return m_cRef;
        delete this;
        SvcUnlock();
        return 0;
    }

// IPersist methods
    STDMETHODIMP GetClassID(CLSID *pclsid) // aka GetUnmarshalClass
    {
        *pclsid = CLSID_RectByValue;
        return S_OK;
    }

// IPersistStream methods
    STDMETHODIMP Load(IStream *pStm) // aka UnmarshalInterface
    {
        m_bIsDirty = FALSE;
        return pStm->Read(&m_rect, sizeof(m_rect), 0);
    }

    STDMETHODIMP Save(IStream *pStm, BOOL fClearDirty) // aka MarshalInterface
    {
        if (fClearDirty) m_bIsDirty = FALSE;
        return pStm->Write(&m_rect, sizeof(m_rect), 0);
    }

    STDMETHODIMP GetSizeMax(ULARGE_INTEGER *pcbSize) // aka GetMarshalSizeMax
    {
        pcbSize->HighPart = 0;
        pcbSize->LowPart = sizeof(m_rect);
        return S_OK;
    }

    STDMETHODIMP IsDirty(void) // not used by IMarshal
    {  return m_bIsDirty ? S_OK : S_FALSE;  }

// IDispatch methods
    STDMETHODIMP GetTypeInfoCount(UINT *pctinfo)
    { *pctinfo = 1; return S_OK; }

    STDMETHODIMP GetTypeInfo(UINT i, LCID lcid, ITypeInfo **ppti)
    { (*ppti = m_pTypeInfo)->AddRef(); return S_OK; }

    STDMETHODIMP GetIDsOfNames(REFIID riid, OLECHAR **rgpszNames, 
                               UINT cNames, LCID lcid, DISPID *rgids)
    { return m_pTypeInfo->GetIDsOfNames(rgpszNames, cNames, rgids); }

    STDMETHODIMP Invoke(DISPID id, REFIID, LCID, WORD w,
                      DISPPARAMS *pdp, VARIANT *pvr, EXCEPINFO *pei, UINT *pu)
    { return m_pTypeInfo->Invoke((IRect*)this, id, w, pdp, pvr, pei, pu); }

// IRect methods
    STDMETHODIMP put_Top(long val)
    {  m_bIsDirty = TRUE; m_rect.top = val; return S_OK; }

    STDMETHODIMP get_Top(long *pval)
    {  *pval = m_rect.top; return S_OK;  }

    STDMETHODIMP put_Left(long val)
    {  m_bIsDirty = TRUE; m_rect.left = val; return S_OK; }

    STDMETHODIMP get_Left(long *pval)
    {  *pval = m_rect.left; return S_OK;  }

    STDMETHODIMP put_Bottom(long val)
    {  m_bIsDirty = TRUE; m_rect.bottom = val; return S_OK; }

    STDMETHODIMP get_Bottom(long *pval)
    {  *pval = m_rect.bottom; return S_OK;  }

    STDMETHODIMP put_Right(long val)
    { m_bIsDirty = TRUE; m_rect.right = val; return S_OK; }

    STDMETHODIMP get_Right(long *pval)
    { *pval = m_rect.right; return S_OK; }
};
