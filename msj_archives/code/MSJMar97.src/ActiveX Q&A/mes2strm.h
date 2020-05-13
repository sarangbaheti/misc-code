///////////////////////////////////////////////
//
// mes2strm.h
// Copyright 1996-1997, Don Box
//
// This file defines a class (CMESToIStream) that thunks MIDL encoding
// service (MES) handles onto COM IStream interfaces for use in pickling
//
// MesEncodeIncrementalHandleCreate and MesDecodeIncrementalHandleCreate each
// take a cookie and one or two function pointers to thunk onto the user's
// serialization media. This class passes its this pointer as the cookie and
// uses static member functions to thunk the Read and Write requests onto the
// IStream interface passed to the thunk object's constructor.
//

#ifndef _CMES2STREAM_H
#define _CMES2STREAM_H

class CMESToIStream
{
    handle_t  m_hRpc;  // our MES handle
    IStream *m_pStrm;  // the IStream we write/read to
    char *m_pbBuffer;  // the last buffer we allocated
    DWORD m_cbBuffer;  // the size of the buffer

// routine called by encoder to allocate a buffer for serialization
    static void __RPC_USER Alloc (void *State, char **pBuffer, UINT *pSize)
    {
        CMESToIStream *pThis = (CMESToIStream *)State;
        *pBuffer = 0;
        if (*pSize > pThis->m_cbBuffer) // realloc
        {
            void *pv = CoTaskMemRealloc(pThis->m_pbBuffer, *pSize);
            if (pv == 0) return; // fail
            pThis->m_pbBuffer = (char*)pv;
        }
        *pBuffer = pThis->m_pbBuffer;
    }

// routine called by encoder to write a buffer to our medium (IStream)
    static void __RPC_USER Write (void *State, char *Buffer, UINT Size)
    {
        CMESToIStream *pThis = (CMESToIStream *)State;
        HRESULT hr = pThis->m_pStrm->Write(Buffer, Size, 0);
        if (FAILED(hr))
            RpcRaiseException(hr);
    }

// routine called by decoder to read a buffer from our medium (IStream)
    static void __RPC_USER Read (void *State, char **pBuffer, UINT *pSize)
    {
        CMESToIStream *pThis = (CMESToIStream *)State;
        Alloc(pThis, pBuffer, pSize);
        ULONG cbActual = 0;
        HRESULT hr = pThis->m_pStrm->Read(*pBuffer, *pSize, &cbActual);
        if (SUCCEEDED(hr))
            *pSize = cbActual;
        else
            *pSize = 0;
    }

public:
    CMESToIStream(IStream *pStrm, BOOL bEncode, RPC_STATUS &s)
        : m_pbBuffer(0), m_cbBuffer(0)
    {
        if (m_pStrm = pStrm)
            m_pStrm->AddRef();
        if (bEncode)
            s = MesEncodeIncrementalHandleCreate(this, Alloc, Write, &m_hRpc);
        else 
            s = MesDecodeIncrementalHandleCreate(this, Read, &m_hRpc);
        if (s != RPC_S_OK)
            m_hRpc = 0;
    }

    ~CMESToIStream(void)
    {
        if (m_pStrm)
            m_pStrm->Release();
        if (m_hRpc)
            MesHandleFree(m_hRpc);
        if (m_pbBuffer)
            CoTaskMemFree(m_pbBuffer);
    }

    handle_t GetHandle(void)
    { return m_hRpc; }

};
#endif
