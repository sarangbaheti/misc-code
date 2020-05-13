///////////////////////////////////////////////
//
// mbv.h - Marshal By Value Aggregate
// Copyright 1995-1997, Don Box Inc.
//
// This file implements a COM aggregate that
// implements IMarshal in terms of the outer
// object's IPersistStream implementation
//

#ifndef _MBV_H
#define _MBV_H

// define an IUnknown clone to get a distinguished vptr
// for our non-delegating unknown
interface XIControlledInner
{
    STDMETHOD(InternalQueryInterface)(REFIID, void**) = 0;
    STDMETHOD_(ULONG,InternalAddRef)(void) = 0;
    STDMETHOD_(ULONG,InternalRelease)(void) = 0;
};

class CMarshalByValue : public IMarshal, 
                        public XIControlledInner
{
    LONG m_cRef;
    IUnknown *m_pUnkOuter;
public:
    CMarshalByValue(IUnknown *pUnkOuter);
    virtual ~CMarshalByValue(void);

// this function will be called by our class factory's CreateInstance
    static IUnknown *CreateAggregate(IUnknown *pUnkOuter);

// XIControlledInner methods (non-delegating unknown)
    STDMETHODIMP InternalQueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) InternalAddRef(void);
    STDMETHODIMP_(ULONG) InternalRelease(void);

// IUnknown methods (delegating unknown)
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

// IMarshal methods
    STDMETHODIMP GetUnmarshalClass(REFIID riid, void *pv, DWORD dwDestContext,
                           void *pvDestContext, DWORD mshlflags, CLSID *pCid);
    
    STDMETHODIMP GetMarshalSizeMax(REFIID riid, void *pv, DWORD dwDestContext,
                           void *pvDestContext, DWORD mshlflags, DWORD *pSize);
    
    STDMETHODIMP MarshalInterface(IStream *pStm, REFIID riid, void *pv,
                    DWORD dwDestContext, void *pvDestContext, DWORD mshlflags);
    
    STDMETHODIMP UnmarshalInterface(IStream *pStm, REFIID riid, void **ppv);
    
    STDMETHODIMP ReleaseMarshalData(IStream *pStm);
    
    STDMETHODIMP DisconnectObject(DWORD dwReserved);

};

#endif
