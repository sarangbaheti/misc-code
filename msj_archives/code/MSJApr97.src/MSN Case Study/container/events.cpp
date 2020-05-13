#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <crtdbg.h>
#include <olectl.h>
#include <docobj.h>
#include <servprov.h>
#include <exdisp.h>
#include <exdispid.h>
#include "winmain.h"
#include "events.h"
#include "ctr.h"


//+---------------------------------------------------------------------------
//
//  Member:     CEventMap::~CEventMap
//
//  Synopsis:   unhooks the event sink from the WebBrowser OC.
//
//----------------------------------------------------------------------------
CEventMap::~CEventMap(VOID)
{
   UnhookEvents();
}

//+---------------------------------------------------------------------------
//
//  Member:     CEventMap::UnhookEvents
//
//  Synopsis:   plumbing to unhook us from event source.
//
//----------------------------------------------------------------------------
VOID
CEventMap::UnhookEvents(VOID)
{
    if (m_pConnPt)
    {
        m_pConnPt->Unadvise(m_dwCookie);
        m_pConnPt->Release();
        m_pConnPt = 0;
    }
}

//+---------------------------------------------------------------------------
//
//  Member:     CEventMap::GetEventsFromCtrl
//
//  Synopsis:   Loads the typelib, gets the typeinfo for the eventset,
//              and uses IConnectionPointContainer protocol for hooking
//              up our implementation of IDispatch so it gets called
//              when events are fired.
//
//  Arguments:  [pOleCtl] -- the WebBrowser OC.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
CEventMap::GetEventsFromCtrl(LPOLECONTROL pOleCtl)
{
    HRESULT                    hr;
    LPCONNECTIONPOINTCONTAINER pConnCtr = 0;

    _ASSERTE(pOleCtl);

    // HOOKING UP EVENTS - let's get find the connection point and
    // set up the connection for events to be fired.
    hr = pOleCtl->QueryInterface(
                    IID_IConnectionPointContainer,
                    (LPVOID *) &pConnCtr);
    if (hr)
        goto Cleanup;

    // find the connectionpoint for us to hook up event sink
    hr = pConnCtr->FindConnectionPoint(DIID_DWebBrowserEvents, &m_pConnPt);
    if (hr)
        goto Cleanup;

    // hook up the event sink
    hr = m_pConnPt->Advise((LPUNKNOWN) this, &m_dwCookie);
    if (hr)
        goto Cleanup;

    // if we got this far, we should be receiving events now.

Cleanup:
    if (pConnCtr)
        pConnCtr->Release();

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CEventMap::Invoke
//
//  Synopsis:   This is our mondo event set handler, the thing the
//              WebBrowser OC calls when it fires an event.
//
//  Arguments:  standard IDispatch args per-spec.
//
//  Returns:    HRESULT - currently, all the members return S_OK
//              no matter what - probably the right thing to do in
//              an event handler.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CEventMap::Invoke(
        DISPID           dispidMember,
        REFIID           riid,
        LCID             lcid,
        WORD             wFlags,
        DISPPARAMS FAR * pdispparams,
        VARIANT    FAR * pvarResult,
        EXCEPINFO  FAR * pexcepinfo,
        UINT       FAR * puArgErr)
{
    switch (dispidMember)
    {
    case DISPID_BEFORENAVIGATE:
    {
        return _OnBeginNavigate(pdispparams, puArgErr);
        break;
    }

    case DISPID_NAVIGATECOMPLETE:
    {
        return _OnNavigate(pdispparams, puArgErr);
        break;
    }

    case DISPID_STATUSTEXTCHANGE:
    {
        return _OnStatusTextChange(pdispparams, puArgErr);
        break;
    }

    case DISPID_PROGRESSCHANGE:
    {
        return _OnProgress(pdispparams, puArgErr);
        break;
    }

    case DISPID_DOWNLOADCOMPLETE:
    {
        return m_pCtr->OnDownloadComplete();
        break;
    }

    case DISPID_COMMANDSTATECHANGE:
    {
        return _OnCommandStateChange(pdispparams, puArgErr);
        break;
    }

    case DISPID_DOWNLOADBEGIN:
    {
        return m_pCtr->OnDownloadBegin();
        break;
    }

    case DISPID_NEWWINDOW:
    {
        return m_pCtr->OnNewWindow();
        break;
    }

    case DISPID_QUIT:
    {
        return m_pCtr->OnQuit();
        break;
    }

    default:
        return S_OK;
        break;
    }
}

//+---------------------------------------------------------------------------
//
//  Member:     CEventMap::_OnBeginNavigate
//
//  Synopsis:   a little wrapper to get the argument passing
//              code out of the Invoke() above.  It extracts args
//              and calls CMSJOCCtr::OnBeginNavigate().
//
//  Arguments:  [pDP]      -- pointer to argument block
//              [puArgErr] -- on DispGetParam error, returns index to
//                            argument that caused the error.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
CEventMap::_OnBeginNavigate(DISPPARAMS * pDP, PUINT puArgErr)
{
    VARIANT varURL;
    HRESULT hr;

    ::VariantInit(&varURL);

    hr = ::DispGetParam(pDP, 0, VT_BSTR, &varURL, puArgErr);
    if (hr)
        return hr;

    hr =  m_pCtr->OnBeginNavigate(V_BSTR(&varURL));
    ::VariantClear(&varURL);

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CEventMap::_OnBeginNavigate
//
//  Synopsis:   a little wrapper to get the argument passing
//              code out of the Invoke() above.  It extracts args
//              and calls CMSJOCCtr::OnNavigate().
//
//  Arguments:  [pDP]      -- pointer to argument block
//              [puArgErr] -- on DispGetParam error, returns index to
//                            argument that caused the error.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
CEventMap::_OnNavigate(DISPPARAMS * pDP, PUINT puArgErr)
{
    // ByVal URL As String, ByVal Flags As Long,
    // ByVal TargetFrameName As String,
    // PostData As Variant, ByVal Headers As String,
    // ByVal Referrer As String

    VARIANT varURL;
    HRESULT hr;

    ::VariantInit(&varURL);

    hr = ::DispGetParam(pDP, 0, VT_BSTR, &varURL, puArgErr);
    if (hr)
        return hr;

    hr = m_pCtr->OnNavigate(V_BSTR(&varURL));
    ::VariantClear(&varURL);

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CEventMap::_OnCommandStateChange
//
//  Synopsis:   lets us determine whether and how to update the navbar
//
//  Arguments:  [pDP]      -- args
//              [puArgErr] -- err index returned from DispGetParam
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
CEventMap::_OnCommandStateChange(DISPPARAMS * pDP, PUINT puArgErr)
{
    HRESULT      hr;
    VARIANT      varlValue;
    VARIANT      varfEnable;

    // get the arguments.

    // this init is necessary for DispGetParam
    ::VariantInit(&varlValue);
    ::VariantInit(&varfEnable);

    hr = ::DispGetParam(pDP, 1, VT_BOOL, &varfEnable, puArgErr);
    if (hr)
        return hr;

    hr = ::DispGetParam(pDP, 0, VT_I4, &varlValue, puArgErr);
    if (hr)
        return hr;

    // pass them to the container
    return m_pCtr->OnCommandStateChange(V_BOOL(&varfEnable), V_I4(&varlValue));

}

HRESULT
CEventMap::_OnStatusTextChange(DISPPARAMS * pDP, PUINT puArgErr)
{
    _ASSERTE(pDP);

    if (pDP->cArgs != 1 || VT_BSTR != V_VT(&pDP->rgvarg[0]))
    {
        puArgErr = 0;  // zeroth arg had the error.
        return DISP_E_PARAMNOTFOUND;  // we didn't find the arg we expected.
    }

    return m_pCtr->OnStatusTextChange(V_BSTR(&pDP->rgvarg[0]));
}

HRESULT
CEventMap::_OnProgress(DISPPARAMS * pDP, PUINT puArgErr)
{
    _ASSERTE(V_VT(&pDP->rgvarg[0]) == VT_I4);
    _ASSERTE(V_VT(&pDP->rgvarg[1]) == VT_I4);
    return m_pCtr->OnProgress(V_I4(&pDP->rgvarg[1]), V_I4(&pDP->rgvarg[0]));
}

