///////////////////////////////////////////////
//
// mbv.cpp - Marshal By Value Aggregate
// Copyright 1995-1997, Don Box Inc.
//
// This file implements a COM aggregate that
// implements IMarshal in terms of the outer
// object's IPersistStream implementation
//

#include <windows.h>
#include "mbv.h"

extern void SvcLock(void);
extern void SvcUnlock(void);

IUnknown *CMarshalByValue::CreateAggregate(IUnknown *pUnkOuter)
{
// return the non-delegating unknown, per aggregation rules
    return (IUnknown*)(XIControlledInner*)new CMarshalByValue(pUnkOuter);
}

CMarshalByValue::CMarshalByValue(IUnknown *pUnkOuter)
:   m_cRef(0), 
    m_pUnkOuter(pUnkOuter)
{
    if (pUnkOuter == 0)
        pUnkOuter = (IUnknown*)(XIControlledInner*)this;
}

CMarshalByValue::~CMarshalByValue(void)
{
}

// Non-delegating IUnknown methods
STDMETHODIMP CMarshalByValue::InternalQueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = (XIControlledInner*)this;
    else if (riid == IID_IMarshal)
        *ppv = (IMarshal*)this;
    else
        return (*ppv = 0), E_NOINTERFACE;
    ((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) CMarshalByValue::InternalAddRef(void)
{
    if (m_cRef == 0)
        SvcLock();
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CMarshalByValue::InternalRelease(void)
{
    if (InterlockedDecrement(&m_cRef))
        return m_cRef;
    delete this;
    SvcUnlock();
    return 0;
}

// Delegating IUnknown methods
STDMETHODIMP CMarshalByValue::QueryInterface(REFIID riid, void **ppv)
{
    return m_pUnkOuter->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) CMarshalByValue::AddRef(void)
{
    return m_pUnkOuter->AddRef();
}

STDMETHODIMP_(ULONG) CMarshalByValue::Release(void)
{
    return m_pUnkOuter->Release();
}

// IMarshal methods
STDMETHODIMP CMarshalByValue::GetUnmarshalClass(REFIID riid, void *pv, 
                                    DWORD dwDestContext, void *pvDestContext, 
                                    DWORD mshlflags, CLSID *pCid)
{
// simply forward the call to the IPersistStream::GetClassID of
// our controlling outer
    IPersistStream *pps = 0;
    HRESULT hr = E_FAIL;
    if (SUCCEEDED(m_pUnkOuter->QueryInterface(IID_IPersistStream, (void**)&pps)))
    {
        hr = pps->GetClassID(pCid);
        pps->Release();
    }
    return hr;
}

STDMETHODIMP CMarshalByValue::GetMarshalSizeMax(REFIID riid, void *pv, 
                                     DWORD dwDestContext, void *pvDestContext, 
                                     DWORD mshlflags, DWORD *pSize)
{
// simply forward the call to the IPersistStream::GetSizeMax of
// our controlling outer
    IPersistStream *pps = 0;
    HRESULT hr = E_FAIL;
    if (SUCCEEDED(m_pUnkOuter->QueryInterface(IID_IPersistStream, (void**)&pps)))
    {
        ULARGE_INTEGER uli;
        hr = pps->GetSizeMax(&uli);
        if (SUCCEEDED(hr))
            *pSize = uli.LowPart;
        pps->Release();
    }
    return hr;
}

STDMETHODIMP CMarshalByValue::MarshalInterface(IStream *pStm, REFIID riid, 
                                               void *pv, DWORD dwDestContext,
                                             void *pvDestCtx, DWORD mshlflags)
{
// simply forward the call to the IPersistStream::Save of
// our controlling outer
    IPersistStream *pps = 0;
    HRESULT hr = E_FAIL;
    if (SUCCEEDED(m_pUnkOuter->QueryInterface(IID_IPersistStream, (void**)&pps)))
    {
        hr = pps->Save(pStm, FALSE);
        pps->Release();
    }
    return hr;
}

STDMETHODIMP CMarshalByValue::UnmarshalInterface(IStream *pStm, 
                                                 REFIID riid, void **ppv)
{
// simply forward the call to the IPersistStream::Load of
// our controlling outer and QueryInterface the outer for
// the resultant pointer
    IPersistStream *pps = 0;
    HRESULT hr = E_FAIL;
    if (SUCCEEDED(m_pUnkOuter->QueryInterface(IID_IPersistStream, (void**)&pps)))
    {
        hr = pps->Load(pStm);
        if (SUCCEEDED(hr))
            hr = pps->QueryInterface(riid, ppv);
        pps->Release();
    }
    return hr;
}

STDMETHODIMP CMarshalByValue::ReleaseMarshalData(IStream *pStm)
{
// marshaling does not cause us to acquire any resources
    return S_OK;
}

STDMETHODIMP CMarshalByValue::DisconnectObject(DWORD dwReserved)
{
// we have no notion of connected-ness
    return S_OK;
}

