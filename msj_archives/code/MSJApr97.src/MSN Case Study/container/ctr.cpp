#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <wchar.h>
#include <crtdbg.h>
#include <shlobj.h>
#include <docobj.h>
#include <servprov.h>
#include <exdisp.h>
#include <olectl.h>
#include <urlmon.h>
#include <stdio.h>
#include <wininet.h>
#include <exdisp.h>
#include "resource.h"

#include "winmain.h"
#include "events.h"
#include "ctr.h"

// macros used to reduce verbiage in RECT handling.
#define WIDTH(r)  (r.right - r.left)
#define HEIGHT(r) (r.bottom - r.top)

// max size for LoadString.
const ULONG MAX_ERR_STR_SIZE = 512;

// string constants
const WCHAR g_awchHostName[] = L"MSJ WebBrowser OC Container";
const WCHAR g_awchHTML[] = L"HTML";

//+--------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::CMSJOCCtr
//
//  Synopsis:   ctor for the OLE Controls container class.
//
//  Arguments:  [hWnd] -- hWnd for the main browser
//
//----------------------------------------------------------------------------
#pragma warning(disable:4355) // this used in initialization list
CMSJOCCtr::CMSJOCCtr(const HWND hWndBrowser) :
    m_hWndBrowser(hWndBrowser),
    m_hWndFrame(0),
    m_CS(this),
    m_AS(this),
    m_IPF(this),
    m_IPS(this),
    m_SP(this),
    m_OCtr(this),
    m_OCT(this),
    m_EvtMap(this),
    m_pActiveObj(0),
    m_Ref(1),
    m_pUnk(0),
    m_pWB(0),
    m_pOC(0),
    m_pVO(0),
    m_pOO(0),
    m_pIPO(0),
    m_pDisp(0),
    m_iZoomMin(0),
    m_iZoomMost(0),
    m_iZoom(0),
    m_state(OS_PASSIVE),
    m_dwMiscStatus(0),
    m_fModelessEnabled(TRUE),
    m_hPal(0)
{
    ::memset(&m_rcToolSpace, 0, sizeof m_rcToolSpace);
    InitPixelsPerInch(); // initialize the HIMETRIC routines
}
#pragma warning(default:4355)


CMSJOCCtr::~CMSJOCCtr(VOID)
{
    if (m_hPal)
        ::DeleteObject(m_hPal);
}


LRESULT
CMSJOCCtr::PaletteChanged(WPARAM wParam)
{
    HWND hWnd = GetFrameWindow();

    if (hWnd != (HWND) wParam)
        _RealizePalette();

    return 0;
}


BOOL
CMSJOCCtr::QueryNewPalette(VOID)
{
    return _RealizePalette() ? TRUE : FALSE;
}


INT
CMSJOCCtr::_RealizePalette(VOID)
{
    HDC         hDC;
    HPALETTE    hPalOld;
    INT         iRC;

    HWND hWnd = GetFrameWindow();

    if (!hWnd || !m_hPal)
        return 0;

    hDC = ::GetDC(hWnd);
    hPalOld = ::SelectPalette(hDC, m_hPal, FALSE);
    iRC  = ::RealizePalette(hDC);

    if (iRC)
        ::InvalidateRect(hWnd, 0, TRUE);

    ::SelectPalette(hDC, hPalOld, FALSE);
    ::RealizePalette(hDC);

    ::ReleaseDC(hWnd, hDC);
    return iRC;
}


//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::ShutDown
//
//  Synopsis:   cleanup all the OLE stuff.
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::ShutDown(VOID)
{
    m_EvtMap.UnhookEvents();

    if (m_pWB)
        m_pWB->Release();
    if (m_pOC)
        m_pOC->Release();
    if (m_pIPO)
    {
        _ASSERTE(m_state == OS_UIACTIVE || m_state == OS_INPLACE);
        if (m_state == OS_UIACTIVE)
        {
            m_pIPO->UIDeactivate();
            // m_state = OS_INPLACE; // for documentation purposes
        }

        m_pIPO->InPlaceDeactivate();
        // m_state = OS_RUNNING;
    }
    if (m_pVO)
    {
        // kill the advisory connection
        m_pVO->SetAdvise(DVASPECT_CONTENT, 0, 0);
        m_pVO->Release();
    }
    if (m_pOO)
    {
        m_pOO->Close(OLECLOSE_NOSAVE);
        m_pOO->SetClientSite(0);
        m_pOO->Release();
    }
    if (m_pDisp)
        m_pDisp->Release();
    if (m_pUnk)
        m_pUnk->Release();

    _ASSERTE(!m_pActiveObj);

    m_pWB        = 0;
    m_pDisp      = 0;
    m_pOC        = 0;
    m_pIPO       = 0;
    m_pActiveObj = 0;
    m_pVO        = 0;
    m_pOO        = 0;
    m_pUnk       = 0;
    m_state      = OS_PASSIVE;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::AddRef
//
//  Synopsis:   bump refcount up on container.  Note that all the
//              interfaces handed out delegate to this one.
//
//----------------------------------------------------------------------------
STDMETHODIMP_(ULONG)
CMSJOCCtr::AddRef(VOID)
{
    return ++m_Ref;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::Release
//
//  Synopsis:   decrement the refcount on container, and delete when it
//              hits 0 - note that all the interfaces handed out delegate
//              to this one.
//
//----------------------------------------------------------------------------
STDMETHODIMP_(ULONG)
CMSJOCCtr::Release(VOID)
{
    ULONG ulRC = --m_Ref;

    if (!ulRC)
    {
        delete this;
    }
    return ulRC;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::QueryInterface
//
//  Synopsis:   this is where we hand out all the interfaces.  All the
//              interfaces delegate back to this.
//
//  Arguments:  [riid] -- IID of interface desired.
//              [ppv]  -- interface returned.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CMSJOCCtr::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    *ppv = 0;

    LPUNKNOWN pUnk;

    if (::IsEqualIID(riid, IID_IOleClientSite))
        pUnk = &m_CS;
    else if (::IsEqualIID(riid, IID_IAdviseSink))
        pUnk = &m_AS;
    else if (::IsEqualIID(riid, IID_IUnknown))
        pUnk = this;
    else if (::IsEqualIID(riid, IID_IOleInPlaceFrame) ||
             ::IsEqualIID(riid, IID_IOleInPlaceUIWindow))
        pUnk = &m_IPF;
    else if (::IsEqualIID(riid, IID_IOleInPlaceSite))
        pUnk = &m_IPS;
    else if (::IsEqualIID(riid, IID_IServiceProvider))
        pUnk = &m_SP;
    else if (::IsEqualIID(riid, IID_IOleCommandTarget))
        pUnk = &m_OCT;
    else
        return E_NOINTERFACE;

    pUnk->AddRef();

    *ppv = pUnk;

    return S_OK;
}


//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::CreateBrowserOC
//
//  Synopsis:   Creates an instance of the Web Browser OC, embedding it in
//              our container.  QIs for all the relevant pointers and
//              transitions the control to the UIActive state.
//
//  Arguments:  [hWndEdit] -- hWnd to the address bar so we can change its
//                            content as we nav to different URLs
//
//              [hAccelBrowser] - HACCEL for the main browser wnd - so
//                                COleInPlaceFrame::TranslateAccelerator()
//                                can call ::TranslateAccelerator() on it.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::CreateBrowserOC(HWND hWndEdit)
{
    HRESULT hr;
    RECT    rc;
    LPSHELLFOLDER pSF = 0;

    // GetFrameWindow() also asserts that hwnd ::IsWindow()
    _ASSERTE(GetFrameWindow());

    // set this so we can update in when we navigate to URL's
    SetEditWindow(hWndEdit);

    HDC hdc = ::GetDC(0);

    m_hPal = ::CreateHalftonePalette(hdc);
    ::ReleaseDC(0, hdc);

    if (!m_hPal)
        return E_FAIL;

    // create the OC
    hr = ::CoCreateInstance(
            CLSID_WebBrowser,
            0,
            CLSCTX_INPROC_SERVER,
            IID_IUnknown,
            (LPVOID *) &m_pUnk);

    if (hr)
        goto Cleanup;

    m_state = OS_RUNNING;

    // get the View object - although we rarely draw the OC thru this.
    // since we immediately transition it to the UIActive state, it
    // usually draws itself through its own wndproc.
    hr = m_pUnk->QueryInterface(IID_IViewObject, (LPVOID FAR *) &m_pVO);
    if (hr)
        goto Cleanup;

    // get the IOleObject pointer - the main interface through which
    // we handle the basic OLE object state transition stuff
    // for the Web Browser OC
    hr = m_pUnk->QueryInterface(IID_IOleObject, (LPVOID FAR *) &m_pOO);
    if (hr)
        goto Cleanup;

    // get status bits on the OC - we're not currently doing anything
    // with them.
    hr = m_pOO->GetMiscStatus(DVASPECT_CONTENT, &m_dwMiscStatus);
    if (hr)
        goto Cleanup;

    // set our client site into the oleobject
    hr = m_pOO->SetClientSite(&m_CS);
    if (hr)
        goto Cleanup;

    // set our advise sink into the view object, so we
    // get notifications that we need to redraw.
    hr = m_pVO->SetAdvise(DVASPECT_CONTENT, 0, &m_AS);
    if (hr)
        goto Cleanup;

    // standard OLE protocol stuff.
    hr = ::OleSetContainedObject(m_pUnk, TRUE);
    if (hr)
        goto Cleanup;

    // ditto
    hr = m_pOO->SetHostNames(g_awchHostName, 0);
    if (hr)
        goto Cleanup;

    // get the IWebBrowser interface - we can drive the OC late-bound,
    // but it's a lot easier (and higher performance, to some degree) to
    // do so early bound.
    hr = m_pUnk->QueryInterface(IID_IWebBrowser, (LPVOID FAR *) &m_pWB);
    if (hr)
        goto Cleanup;

    // get the IDispatch for the control.  This is for late-bound
    // access to the properties and methods.  You probably don't
    // need both IWebBrowser and IDispatch - shown here for example only.
    hr = m_pUnk->QueryInterface(IID_IDispatch, (LPVOID FAR *) &m_pDisp);
    if (hr)
        goto Cleanup;

    // get the IOleControl interface; although we use it for very little.
    hr = m_pUnk->QueryInterface(IID_IOleControl, (LPVOID FAR *) &m_pOC);
    if (hr)
        goto Cleanup;

    // transition the control to the inplace-active state - it will have
    // an hWnd after it returns from DoVerb, and will begin drawing
    // itself.

    _GetDoVerbRect(&rc); // get rect for firing verbs.

    hr = m_pOO->DoVerb(OLEIVERB_INPLACEACTIVATE, 0, &m_CS, 0, GetFrameWindow(), &rc);
    if (hr)
        goto Cleanup;

    // go ahead and UI activate it.  This will cause it to QI for our
    // IOleInPlaceFrame and call SetActiveObject, which we will store
    // in m_pActiveObj
    hr = m_pOO->DoVerb(OLEIVERB_UIACTIVATE, 0, &m_CS, 0, GetFrameWindow(), &rc);
    if (hr)
        return hr;

    // now get the eventset.
    hr = m_EvtMap.GetEventsFromCtrl(m_pOC);
    if (hr)
        goto Cleanup;

Cleanup:
    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::_AdjustForTools
//
//  Synopsis:   adjusts the rect passed in for any toolspace claimed by the
//              WebBrowser OC.  Currently, the WebBrowser OC always just
//              passed in a rect with four zeros in it - but if it ever
//              does decide to do this, we're ready :).
//
//  Arguments:  [prc] -- the rect we want to reduce by the BORDERWIDTHS
//                       stored in m_rcToolSpace.
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::_AdjustForTools(LPRECT prc)
{
    prc->left += m_rcToolSpace.left;
    prc->top += m_rcToolSpace.top;
    prc->bottom -= m_rcToolSpace.bottom;
    prc->right -= m_rcToolSpace.right;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::GetSize
//
//  Synopsis:   returns the size, in pixels, of the WebBrowser OC.
//
//  Arguments:  [prc] --  returned size.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::GetSize(LPRECT prc)
{
    _ASSERTE(m_pOO);
    HRESULT hr;

    // if we're inplace active, just ask the frame window.
    if (m_state >= OS_INPLACE)
    {
        _ASSERTE(m_pIPO);
        ::GetClientRect(GetFrameWindow(), prc);
        hr = S_OK;
    }
    else  // not inplace active - probably this is never hit.
    {
        SIZEL sizel;
        hr = m_pOO->GetExtent(DVASPECT_CONTENT, &sizel);
        if (!hr)
        {
            prc->left = 0;
            prc->top = 0;
            prc->right = ::HPixFromHimetric(sizel.cx);
            prc->bottom = ::VPixFromHimetric(sizel.cy);
        }
    }

    // adjust the borders for any tools that a UIActive object
    // wants to place there.
    if (!hr)
        _AdjustForTools(prc);

    return hr;
}


//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::DoLayout
//
//  Synopsis:   manages the vertical layout of things -
//              sizes the OC container itself.
//
//  Arguments:  [cxMain] -- width
//              [cyMain] -- height
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::DoLayout(INT cxMain, INT cyMain)
{
    RECT        rect = {0, CYEDIT, cxMain, cyMain};

    SetSize(&rect, TRUE);
}

HRESULT
CMSJOCCtr::_SetExtent(LPRECT prc)
{
    SIZEL   sizel;
    HRESULT hr;

    sizel.cx = ::HimetricFromHPix(prc->right - prc->left);
    sizel.cy = ::HimetricFromVPix(prc->bottom - prc->top);

    _ASSERTE(m_pOO);

    hr = m_pOO->SetExtent(DVASPECT_CONTENT, &sizel);
    if (hr)
        goto cleanup;

    hr = m_pOO->GetExtent(DVASPECT_CONTENT, &sizel);
    if (hr)
        goto cleanup;

    prc->right = ::HPixFromHimetric(sizel.cx);
    prc->bottom = ::VPixFromHimetric(sizel.cy);

cleanup:
    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::SetSize
//
//  Synopsis:   sets the size of the WebBrowser OC space (the HTML area)
//
//  Effects:    if fMoveFrameWindow is TRUE, then it moves the whole
//              framewindow around, otherwise, it just readjusts how much
//              of the framewindow space is used by the OC itself.
//              In reality, what happens is that the OC calls us to
//              set some border space (although at this writing it still
//              is setting BORDERWIDTHS of 0,0,0,0), we allow that
//              much space, then call IOleInPlaceObject->SetObjectRects
//              to resize the object to whatever's left.
//              Otherwise, if the object is not yet active, we just
//              call IOleObject::SetExtent().
//
//  Arguments:  [prc]              -- size to set object to
//              [fMoveFrameWindow] -- is the hwnd size changing, or just
//                                    the object within?
//
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::SetSize(LPRECT prc, BOOL fMoveFrameWindow)
{
    HRESULT hr;
    RECT    rcClient;
    RECT    rcExtent;

     // get client coords.
    rcClient = *prc;
    ::MoveRect(&rcClient, -rcClient.left, -rcClient.top);

    if (fMoveFrameWindow)
    {
        ::SetWindowPos(
                GetFrameWindow(),
                0,
                prc->left,
                prc->top,
                prc->right - prc->left,
                prc->bottom - prc->top,
                SWP_NOZORDER | SWP_NOACTIVATE);

         if (m_pActiveObj)
            m_pActiveObj->ResizeBorder(&rcClient, &m_IPF, TRUE);
    }

    // subtract off any tools the client has around .
    _AdjustForTools(&rcClient);

    rcExtent = rcClient;
    hr = _SetExtent(&rcExtent);
    if (hr)
        goto cleanup;

    // now we need to call SetObjectRects
    if (m_pIPO && m_state >= OS_INPLACE)
        hr = m_pIPO->SetObjectRects(&rcExtent, &rcClient);

cleanup:
    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::Paint
//
//  Synopsis:   Paint with no parameters
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::Paint(VOID)
{
    PAINTSTRUCT ps;
    RECT        rc;

    // we don't need to call IViewObject if the object is activated.
    // it's got an hWnd and is receiving paint messages of its own.
    if (m_state < OS_INPLACE)
    {
        if (!GetSize(&rc))
        {
            ::BeginPaint(GetFrameWindow(), &ps);
              Paint(ps.hdc, &rc);
            ::EndPaint(GetFrameWindow(), &ps);
        }
    }
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::Paint
//
//  Synopsis:   paint with the hdc and rect passed in.  Uses
//              IViewObject::Draw()
//
//  Arguments:  [hDC] -- dc to draw to - can be container's or
//                       even print dc (never is a print dc in
//                       our scenario - we use IOleCommandTarget
//                       to print the document.
//              [lpr] -- rect for painting.
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::Paint(HDC hDC, LPRECT lpr)
{
    // adjust the borders in to allow for any tools the OC
    // wanted to insert - so far it never does.
    _AdjustForTools(lpr);

    // have to use a RECTL instead of RECT - remnant of the
    // OLE 16 bit days.
    RECTL rcl = {lpr->left, lpr->top, lpr->right, lpr->bottom};
    if (m_pVO)
        m_pVO->Draw(DVASPECT_CONTENT, -1, 0, 0, 0, hDC, &rcl, 0, 0, 0);
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::Back
//
//  Synopsis:   invoke the browser OC 'Back' method
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::Back(VOID)
{
    return m_pWB->GoBack();
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::Forward
//
//  Synopsis:   Invoke the Browser OC 'forward' method.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::Forward(VOID)
{
    return m_pWB->GoForward();
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::Stop
//
//  Synopsis:   Invoke the Browser OC 'Stop' method
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::Stop(VOID)
{
    return m_pWB->Stop();
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::Refresh
//
//  Synopsis:   Invoke the Browser OC 'Refresh' method
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::Refresh(VOID)
{
    return m_pWB->Refresh();
}

HRESULT
CMSJOCCtr::Busy(BOOL *pfBusy)
{
    VARIANT_BOOL vb;
    HRESULT hr = m_pWB->get_Busy(&vb);
    *pfBusy = (vb == VARIANT_TRUE) ? TRUE : FALSE;
    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::Navigate
//
//  Synopsis:   most used method of the Web Browser OC.  This
//              is how we navigate to a URL.
//
//  Arguments:  [pszURL] -- string name of the url, including
//                          the "http", or "file" or whatever.
//
//  Returns:    HRESULT - this is asynchronous.  control
//                        returns long before the page is
//                        displayed in the Web Browser OC.
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::Navigate(LPSTR pszURL)
{
    WCHAR      awch[CCHMAXURL];

    // it's gotta be wide - OLE only takes wide strings. - it's not
    // localizable though, it's a URL.

    if (!::MultiByteToWideChar(
            CP_ACP,
            0,
            pszURL,
            -1,
            awch,
            NElems(awch)))
    {
        return E_FAIL;
    }

    // ok, now navigate!
    return m_pWB->Navigate(awch, 0, 0, 0, 0);
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::_GetOleCommandTarget
//
//  Synopsis:   Get the IOleCommandTarget interface from the
//              current docobj (including the HTML docobj).
//
//  Arguments:  [ppOleCmdTgt] -- returned LPOLECOMMANDTARGET
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::_GetOleCommandTarget(LPOLECOMMANDTARGET * ppOleCmdTgt)
{
    LPDISPATCH pDoc = 0;
    HRESULT    hr;

    *ppOleCmdTgt = 0;

    // get the current Docobj
    hr = m_pWB->get_Document(&pDoc);
    if (hr)
        goto cleanup;

    hr = pDoc->QueryInterface(IID_IOleCommandTarget, (LPVOID *) ppOleCmdTgt);

cleanup:
    if (pDoc)
        pDoc->Release();

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnActivateApp
//
//  Synopsis:   all WM_ACTIVATE messages (forwarded from
//              main browser hWnd wndproc) must call
//              IOleInPlaceActiveObject::OnFrameWindowActivate(),
//              per the OLE compound document spec.
//
//  Arguments:  [wParam] -- whatever the WM_ACTIVATE msg passed
//              [lParam] -- ditto
//
//  Returns:    0 - to say we handled the message.
//
//----------------------------------------------------------------------------
LRESULT
CMSJOCCtr::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
    if (m_pActiveObj)
        m_pActiveObj->OnFrameWindowActivate((BOOL)wParam);

    return 0;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::PrintCurrentPage
//
//  Synopsis:   Prints the current docobject.  Does this by getting
//              the IOleCommandTarget for the docobject, and firing
//              the OLECMDID_PRINT command at it.  Note that it is
//              the responsibility of the docobject server itself
//              (whatever it might be) to handle printing thereafter.
//
//  Requires:   The current document must support IOleCommandTarget
//
//  Returns:    HRESULT.
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::PrintCurrentPage(VOID)
{
    HRESULT            hr;
    LPOLECOMMANDTARGET pCT  = 0;

    _ASSERTE(m_pDisp);

    hr = _GetOleCommandTarget(&pCT);
    if (hr)
        goto cleanup;

    hr = pCT->Exec(0, OLECMDID_PRINT, 0, 0, 0);
    if (hr)
        goto cleanup;

cleanup:
    if (pCT)
        pCT->Release();
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::ZoomIn
//
//  Synopsis:   Zooms in one - whenever we navigate to a new document,
//              we get the zoom range for that document.  ZoomIn will
//              cycle thru that zoom range, from small to large, wrapping
//              back to smallest again.
//
//  Returns:    nothing, fails quietly (by design).
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::ZoomIn(VOID)
{
    INT iZoomNew = m_iZoom + 1;

    if (iZoomNew > m_iZoomMost)
        iZoomNew = m_iZoomMin;

    if (SUCCEEDED(_Zoom(iZoomNew)))
        m_iZoom = iZoomNew;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::ZoomOut
//
//  Synopsis:   Zooms out one - whenever we navigate to a new document,
//              we get the zoom range for that document.  ZoomOut will
//              cycle thru that zoom range, from large to small, wrapping
//              back to largest again.
//
//  Returns:    nothing, fails quietly (by design).
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::ZoomOut(VOID)
{
    INT iZoomNew = m_iZoom - 1;

    if (iZoomNew < m_iZoomMin)
        iZoomNew = m_iZoomMost;

    if (SUCCEEDED(_Zoom(iZoomNew)))
        m_iZoom = iZoomNew;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::_Zoom
//
//  Synopsis:   helper function that manages zoomin and zoomout.
//
//  Arguments:  [iZoom] -- value for new zoom.
//
//  Requires:   iZoom needs to be in a valid range for the current docobj.
//              current docobj must support IOleCommandTarget
//              it will fail if current docobj doesn't respond to
//              OLECMDID_ZOOM.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::_Zoom(INT iZoom)
{
    LPOLECOMMANDTARGET pCT  = 0;
    HRESULT            hr;
    VARIANTARG         varIn;
    VARIANTARG         varOut;

    // get the commandtarget
    hr = _GetOleCommandTarget(&pCT);
    if (hr)
        goto cleanup;

    // initialize the argument to Exec.
    ::VariantInit(&varIn);
    V_VT(&varIn) = VT_I4;
    V_I4(&varIn) = iZoom;

    // init the out variant.  This probably isn't necessary, but
    // doesn't hurt - it's defensive as opposed to passing 0.
    ::VariantInit(&varOut);

    hr = pCT->Exec(
            0,
            OLECMDID_ZOOM,
            OLECMDEXECOPT_DONTPROMPTUSER,
            &varIn,
            &varOut);

cleanup:
    if (pCT)
        pCT->Release();

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::SetFocus
//
//  Synopsis:   transfers focus from framewindow to the current
//              in-place active object.  Per OLE Compound Document spec.
//
//----------------------------------------------------------------------------
LRESULT
CMSJOCCtr::SetFocus(VOID)
{
    HWND hWnd   = NULL;
    LPOLEINPLACEACTIVEOBJECT pAO = GetIPAObject();

    if (pAO)
    {
        if (!pAO->GetWindow(&hWnd))
        {
            if (hWnd && !::IsWindow(hWnd))
                hWnd = NULL;
        }
    }

    // if no inplaceactive object, set focus to frame window.
    if (!hWnd)
        hWnd = GetFrameWindow();

    ::SetFocus(hWnd);
    return 0;
}

//+---------------------------------------------------------------------------
//
//  Class:      CAdviseSink implementations
//
//  Purpose:    to implement IAdviseSink for CMSJOCCtr
//
//  Notes:      we don't do much with this interface - it's required
//              for contractual reasons only.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CAdviseSink::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    return m_pCtr->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG)
CAdviseSink::AddRef(VOID)
{
    return m_pCtr->AddRef();
}

STDMETHODIMP_(ULONG)
CAdviseSink::Release(VOID)
{
    return m_pCtr->Release();
}

CAdviseSink::CAdviseSink(LPMSJOCCtr pCtr) : m_pCtr(pCtr)
{
}

STDMETHODIMP_(VOID)
CAdviseSink::OnDataChange(LPFORMATETC pFEIn, LPSTGMEDIUM pSTM)
{
    return;
}

//+---------------------------------------------------------------------------
//
//  Member:     CAdviseSink::OnViewChange
//
//  Synopsis:   IAdviseSink::OnViewChange() - we do get called with this
//              occasionally, but it appears that we're better off just
//              letting the control's wndproc paint it.
//              Calling this was causing extra flicker.
//
//----------------------------------------------------------------------------
STDMETHODIMP_(VOID)
CAdviseSink::OnViewChange(DWORD dwAspect, LONG lIndex)
{
    return;
}

STDMETHODIMP_(VOID)
CAdviseSink::OnRename(LPMONIKER pmk)
{

}

STDMETHODIMP_(VOID)
CAdviseSink::OnSave(VOID)
{

}

STDMETHODIMP_(VOID)
CAdviseSink::OnClose(VOID)
{

}

//+---------------------------------------------------------------------------
//
//  Class:      COleClientSite ()
//
//  Purpose:    our implementation of IOleClientSite
//
//  Interface:  COleClientSite         -- ctor
//              QueryInterface         -- gimme an interface!
//              AddRef                 -- bump up refcount
//              Release                -- bump down refcount
//              SaveObject             -- returns E_FAIL
//              GetMoniker             -- E_NOTIMPL
//              GetContainer           -- returns our COleContainer impl
//              ShowObject             -- just say OK
//              OnShowWindow           -- just say OK
//              RequestNewObjectLayout -- E_NOTIMPL
//
//  Notes:      probably the most important thing our IOleClientSite
//              implementation does is hand off our IOleContainer
//              implementation when GetContainer() is called.
//
//----------------------------------------------------------------------------
COleClientSite::COleClientSite(LPMSJOCCtr pCtr) : m_pCtr(pCtr)
{
}

STDMETHODIMP
COleClientSite::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    return m_pCtr->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG)
COleClientSite::AddRef(VOID)
{
    return m_pCtr->AddRef();
}

STDMETHODIMP_(ULONG)
COleClientSite::Release(VOID)
{
    return m_pCtr->Release();
}

//+---------------------------------------------------------------------------
//
//  Member:     COleClientSite::SaveObject
//
//  Synopsis:   not implemented - makes no sense in this scenario.
//
//----------------------------------------------------------------------------
STDMETHODIMP
COleClientSite::SaveObject(VOID)
{
    return E_FAIL;
}

//+---------------------------------------------------------------------------
//
//  Member:     COleClientSite::GetMoniker
//
//  Synopsis:   Not yet implemented; never will be implemented.
//
//----------------------------------------------------------------------------
STDMETHODIMP
COleClientSite::GetMoniker(DWORD dwAssign, DWORD dwWhich, LPMONIKER FAR * ppmk)
{
    *ppmk = 0;
    return E_NOTIMPL;
}

//+---------------------------------------------------------------------------
//
//  Member:     COleClientSite::GetContainer
//
//  Synopsis:   returns our implementation of IOleContainer.  For some
//              reason, unless we do this, frames don't work.  Note that
//              our IOleContainer implementation is stubbed out with
//              E_NOTIMPL (it seems kind of silly to implement this for
//              a container with one embedding).  But it turns out the
//              WebBrowser OC has a bug in it's error handling - it
//              QIs for IOleContainer, then QIs from that for
//              IQueryService.  In truth, we'll hand out our implementation
//              of IQueryService, from any interface - we're easy :).
//              We *want* to provide every service the OC asks for.
//              Anyway, when it can't get IOleContainer, the OC's failure
//              path seems to be constructed in such a way that frames
//              don't work thereafter.
//
//  Arguments:  [ppCtr] -- returned IOleContainer
//
//  Returns:    S_OK.  Never fails.
//
//----------------------------------------------------------------------------
STDMETHODIMP
COleClientSite::GetContainer(LPOLECONTAINER FAR * ppCtr)
{
    *ppCtr = &m_pCtr->m_OCtr;
    (*ppCtr)->AddRef();

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     COleClientSite::ShowObject
//
//  Synopsis:   IOleClientSite::ShowObject implementation.  To quote the docs:
//              "Tells the container to position the object so it is visible
//              to the user. This method ensures that the container itself
//              is visible and not minimized."
//
//              In short, we ignore it.  We're not going to un-minimize
//              the container on the embeddings' whim :).
//
//----------------------------------------------------------------------------
STDMETHODIMP
COleClientSite::ShowObject(VOID)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     COleClientSite::OnShowWindow
//
//  Synopsis:   fine with us, return S_OK.
//
//----------------------------------------------------------------------------
STDMETHODIMP
COleClientSite::OnShowWindow(BOOL bShow)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     COleClientSite::RequestNewObjectLayout
//
//  Synopsis:   not being called by WebBrower OC, so do not implement.
//
//----------------------------------------------------------------------------
STDMETHODIMP
COleClientSite::RequestNewObjectLayout(VOID)
{
    return E_NOTIMPL;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::CInPlaceFrame
//
//  Synopsis:   inits m_pCtr - pointer to MSNOCCtr
//
//----------------------------------------------------------------------------
CInPlaceFrame::CInPlaceFrame(LPMSJOCCtr pCtr) : m_pCtr(pCtr)
{
}

STDMETHODIMP
CInPlaceFrame::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    return m_pCtr->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG)
CInPlaceFrame::AddRef(VOID)
{
    return m_pCtr->AddRef();
}

STDMETHODIMP_(ULONG)
CInPlaceFrame::Release(VOID)
{
    return m_pCtr->Release();
}

// IOleWindow stuff

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::GetWindow
//
//  Synopsis:   returns frame window
//
//  Arguments:  [phwnd] -- place to return window
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::GetWindow(HWND * phwnd)
{
    _ASSERTE(phwnd);

    // this can never fail if we've gotten this far.
    *phwnd = m_pCtr->GetFrameWindow();
    _ASSERTE(*phwnd);

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::ContextSensitiveHelp
//
//  Synopsis:   This is not implemented by design - this is for
//              the SHift+F1 context sensitive help mode and Esc
//              to exit.  Esc is already being used in the main
//              accelerator table to mean 'stop browsing' to be
//              like IE3.  We do not do help this way.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::ContextSensitiveHelp(BOOL fEnterMode)
{
    return E_NOTIMPL;
}

// IOleInPlaceUIWindow stuff

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::GetBorder
//
//  Synopsis:   IOleInPlaceFrame::GetBorder() - let's us restrict where
//              the server can put tools.  We don't care, they can put
//              them anywhere.
//
//  Arguments:  [lprectBorder] -- return border info in here.
//
//  Returns:    S_OK always with entire frame client rect -
//              we place no restrictions.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::GetBorder(LPRECT lprectBorder)
{
    // we have no restrictions about where the server can put tools.
    ::GetClientRect(m_pCtr->GetFrameWindow(), lprectBorder);

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::RequestBorderSpace
//
//  Synopsis:   IOleInPlaceFrame::RequestBorderSpace()
//              inplace object actually requests border space - if
//              we can satisfy the request, we return S_OK, otherwise
//              INPLACE_E_NOTOOLSPACE.  It doesn't actually use the
//              borderspace until it calls
//              IOleInPlaceFrame::SetBorderSpace().  This is used for
//              negotiation.
//
//  Arguments:  [pborderwidths] -- structure (actually a RECT) that is
//                                 interpreted differently from a RECT.
//                                 The left.top.bottom.right members
//                                 represent space on each of our four
//                                 borders the server would like to use.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::RequestBorderSpace(LPCBORDERWIDTHS pborderwidths)
{
    RECT rc;
    RECT rcBorder = *pborderwidths;

    if (GetBorder(&rc))
        return INPLACE_E_NOTOOLSPACE;

    if (rcBorder.left + rcBorder.right > WIDTH(rc) ||
        rcBorder.top + rcBorder.bottom > HEIGHT(rc))
        return INPLACE_E_NOTOOLSPACE;

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::SetBorderSpace
//
//  Synopsis:   Sets border space for tools - for some reason, the
//              WebBrowser OC always calls this with a pborderwidths
//              consisting of four zeros - it never actually uses any
//              border space (sigh).  Well, the code is here for this
//              to work.  We do a SetSize() to relayout stuff when
//              it does this.
//
//  Arguments:  [pborderwidths] --  space the OC wants to use.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::SetBorderSpace(LPCBORDERWIDTHS pborderwidths)
{
    RECT rc;

    if (RequestBorderSpace(pborderwidths))
        return OLE_E_INVALIDRECT;

    // we get the entire client space to pass to setSize().
    ::GetClientRect(m_pCtr->GetFrameWindow(), &rc);
     m_pCtr->m_rcToolSpace = *pborderwidths;

    return m_pCtr->SetSize(&rc, FALSE);
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::SetActiveObject
//
//  Synopsis:   IOleInPlaceFrame::SetActiveObject().  The server calls
//              this normally whenever it transitions to the UIActive
//              state.  There can only be one UIActive object at a time.
//              This UIACtive object is represented by its
//              IOleInPlaceActiveObject implementation.  We call this
//              object's implementation of TranslateAccelerator() right
//              in the main message loop to give the current embedding
//              first shot at keyboard messages.
//
//              Normally, this is only called when the container transitions
//              an object to UIActive by calling
//              IOleObject::DoVerb(OLEIVERB_UIACTIVE) for the object,
//              transitioning all the other objects (we don't have any :))
//              to OS_INPLACE (if they're OLEMISC_ACTIVATEWHENVISIBLE is set)
//              or even just OS_RUNNING.
//
//              But the MSJ container only has *one* embedding, the Web
//              Browser OC.  And this OC keeps calling this thing all the time,
//              every time it navigates to a new site (new docobject, I guess),
//              *and*, after the first time it navgs to a new site, whenever
//              the user clicks on the HTML region.
//
//  Effects:    sets a new active object in m_pActiveObj.  Releases the
//              old one, if any.
//
//  Arguments:  [pActiveObject] -- new active object
//              [pszObjName]    -- name of object - we don't use this.
//
//  Returns:    S_OK always.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::SetActiveObject(
        IOleInPlaceActiveObject * pActiveObject,
        LPCOLESTR                 pszObjName)
{
    // reset the toolspace rect in case the last inplacactive object
    // forgot to.
    m_pCtr->_ResetToolSpace();

    // if it was already set, save it so we can release
    // it.  We don't want to release it before we addref
    // the new one in case they're the same thing.
    LPOLEINPLACEACTIVEOBJECT pOld = m_pCtr->m_pActiveObj;

    m_pCtr->m_pActiveObj = pActiveObject;
    if (pActiveObject)
    {
        _ASSERTE(OS_UIACTIVE == m_pCtr->GetState());
        m_pCtr->m_pActiveObj->AddRef();
    }

    if (pOld)
        pOld->Release();

    return S_OK;
}

// IOleInPlaceFrame stuff
//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::InsertMenus
//
//  Synopsis:   OC calling us when it wants to do menu negotiation
//              It calls us with a blank hmenu that we're supposed to
//              add items to and fille out the OLEMENUGROUPWIDTHS
//              structure to let it know what we did.
//              We're not adding items to it currently.
//
//  Arguments:  [hmenuShared] -- menu to append to
//              [pMGW]        -- OLEMENUGROUPWIDTHS struct to fill out.
//
//  Returns:    S_OK
//
//
//  Note:       OC doesn't call this.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::InsertMenus(HMENU hmenuShared, LPOLEMENUGROUPWIDTHS pMGW)
{
    // we're not inserting anything of our own to this menu.
    pMGW->width[0] = 0;  // 'File' menu
    pMGW->width[2] = 0;  // 'View' menu
    pMGW->width[4] = 0;  // 'Window' menu
    pMGW->width[5] = 0;  // 'Help' menu merging is done since doboject.
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::SetMenu
//
//  Synopsis:   This is the OC calling the container asking us to
//              set the shared menu in its frame.  We're supposed to
//              use the HOLEMENU object passed in and the
//              hWndActiveObject to call OleSetMenuDescriptor() so
//              that OLE can do message filtering and route WM_COMMAND
//              messages.
//
//              Bottom line - the WebBrowser OC only calls this once with
//                            a 0 HMENU.  If this changes, fix this code
//                            to do menu negotiation if desired.
//
//
//  Arguments:  [hmenuShared]      --  shared menu.
//              [holemenu]         --  ole menu descriptor thingy
//              [hwndActiveObject] --  hwnd of server who's merging menus
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::SetMenu(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject)
{
    _ASSERTE(!hmenuShared);  // only called once with 0
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::RemoveMenus
//
//  Synopsis:   IOleInPlaceFrame::RemoveMenus(), this is where the
//              server gives us a chance to remove all our items from
//              the hMenu.  We're not adding any, so we don't remove any.
//
//  Arguments:  [hmenuShared] -- menu to clean up.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::RemoveMenus(HMENU hmenuShared)
{
    // we aren't adding anything to this thing anyway.
    return S_OK;
}


//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::SetStatusText
//
//  Synopsis:   called by the WebBrowser OC to put text in our status
//              text area.
//
//  Returns:    HRESULT
//
//  Arguments:  [pszStatusText] -- text to display
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::SetStatusText(LPCOLESTR pszStatusText)
{
    return m_pCtr->_DisplayStatusText(pszStatusText);
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::_DisplayStatusText
//
//  Synopsis:   helper that displays status text.
//
//  Arguments:  [pszStatusText] -- text to display
//
//
//  Returns:    S_OK or HRESULT_FROM_WIN32(::GetLastError());
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::_DisplayStatusText(LPCOLESTR pszStatusText)
{
    CHAR ach[MAX_STATUS_TEXT];

    if (::WideCharToMultiByte(
            CP_ACP,
            0,
            pszStatusText,
            -1,
            ach,
            NElems(ach),
            0,
            0))
    {
        // put the status text somewhere.
        return S_OK;
    }
    else
    {
        return HRESULT_FROM_WIN32(::GetLastError());
    }
}


//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::EnableModeless
//
//  Synopsis:   this is called by the embedding to let us know it's
//              putting up a modal dialog box - we should 'grey' out
//              any of our modeless dialogs.  It delegates to
//              CMSJOCCtr::EnableModeless()
//
//  Arguments:  [fEnable] -- enable or disable.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::EnableModeless(BOOL fEnable)
{
    return m_pCtr->EnableModeless(fEnable);
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::EnableModeless
//
//  Synopsis:   delegated to from CInPlaceFrame::EnableModeless().
//              always returns S_OK - we don't have any modeless
//              dialogs (yet).
//
//  Arguments:  [fEnable] -- enable or disable.
//
//  Returns:    S_OK
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::EnableModeless(BOOL fEnable)
{
    m_fModelessEnabled = fEnable;  // in case anyone wants to know.
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceFrame::TranslateAccelerator
//
//  Synopsis:   The current active object's
//              IOleInPlaceActiveObject::TranslateAccelerator() is being
//              called at the top of our main message loop.  If it
//              does *not* want to handle a message, it will call
//              this method of ours to pass the keyboard message back to
//              us.  We call ::TranslateAccelerator on the global main
//              haccel, and, if it's handled (by returning TRUE - 1),
//              we indicate it's handled by returning S_OK (0 :).
//              On the other hand, if it's *not* handled, we return
//              S_FALSE.
//
//  Arguments:  [lpmsg] -- keyboard msg to handle
//              [wID]   -- command identifier value - per spec.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceFrame::TranslateAccelerator(LPMSG lpmsg, WORD wID)
{
    // note this should never be called - only local servers
    // (out of process) should call this by using
    // OleTranslateAccelerator().
    return m_pCtr->_TransAccelerator(lpmsg, wID);
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::_TransAccelerator
//
//  Synopsis:   handle accelerator messages coming from
//              either IOleInplaceFrame::TranslateAccelerator, or
//              IOleControlSite::TranslateAccelerator.
//
//  Effects:    forwards them to the main accelerator table.
//
//  Arguments:  [lpmsg] -- keyboard msg.
//              [wID]   -- per spec.
//
//  Returns:    S_OK if we handled it, S_FALSE otherwise.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::_TransAccelerator(LPMSG lpmsg, WORD wID)
{
    // the docs suggest that this method might need to return E_INVALIDARG.
    // anyway, this is defensive.  If the WebBrowser OC
    // calls us with an 0 ptr, we just return error
    if (!lpmsg)
        return E_INVALIDARG;

    // forward the keystroke to the main accelerator table, if you have one.
    // if you handle it, say S_OK.

#if 0
    // this sample has no main accelerator table.
    if (::TranslateAccelerator(GetMainWindow(),GetMainAccel(), lpmsg))
    {
        return S_OK;      // we handled it
    }
    else
#endif
    {
        return S_FALSE;   // we didn't.
    }
}

//+---------------------------------------------------------------------------
//
//  Class:      CInPlaceSite ()
//
//  Purpose:    IOleInPlaceSite implementation.
//
//  Interface:  CInPlaceSite         -- ctor
//              QueryInterface       -- get a new interface
//              AddRef               -- bump ref count
//              Release              -- decrement ref count
//              GetWindow            -- returns frame window
//              ContextSensitiveHelp -- not implemented by design
//              CanInPlaceActivate   -- returns S_OK.
//              OnInPlaceActivate    -- caches IOleInPlaceObject ptr
//              OnUIActivate         -- returns S_OK  - sets state
//              GetWindowContext     -- returns IOleInPlaceFrame,
//                                              IOleInPlaceUIWindow,
//                                              PosRect and ClipRect
//              Scroll               -- not implemented ever
//              OnUIDeactivate       -- kills objmenu
//              OnInPlaceDeactivate  -- releases cached IOleInPlaceObject
//              DiscardUndoState     -- returns S_OK
//              DeactivateAndUndo    -- deactivates in place active object
//              OnPosRectChange      -- never implemented.
//
//----------------------------------------------------------------------------
CInPlaceSite::CInPlaceSite(LPMSJOCCtr pCtr) : m_pCtr(pCtr)
{
}

STDMETHODIMP
CInPlaceSite::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    return m_pCtr->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG)
CInPlaceSite::AddRef(VOID)
{
    return m_pCtr->AddRef();
}

STDMETHODIMP_(ULONG)
CInPlaceSite::Release(VOID)
{
    return m_pCtr->Release();
}


// IOleWindow stuff

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::GetWindow
//
//  Synopsis:   returns frame window.
//
//  Arguments:  [phwnd] -- return window *here*
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::GetWindow(HWND * phwnd)
{
    // just reuse the CInPlaceFrame impl
    return m_pCtr->m_IPF.GetWindow(phwnd);
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::ContextSensitiveHelp
//
//  Synopsis:   This is not implemented by design - this is for
//              the SHift+F1 context sensitive help mode and Esc
//              to exit.  Esc is already being used in the main
//              accelerator table to mean 'stop browsing' to be
//              like IE3.  We do not do help this way.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::ContextSensitiveHelp(BOOL fEnterMode)
{
    return E_NOTIMPL;
}

// IOleInPlaceSite stuff

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::CanInPlaceActivate
//
//  Synopsis:   just say yes.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::CanInPlaceActivate(VOID)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::OnInPlaceActivate
//
//  Synopsis:   caches the IOleInPlaceObject pointer.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::OnInPlaceActivate(VOID)
{
    HRESULT hr = m_pCtr->m_pOO->QueryInterface(
                         IID_IOleInPlaceObject,
                         (LPVOID *) &m_pCtr->m_pIPO);

    if (!hr)
        m_pCtr->SetState(OS_INPLACE);

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::OnUIActivate
//
//  Synopsis:   just sets state bit
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::OnUIActivate(VOID)
{
    m_pCtr->SetState(OS_UIACTIVE);
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::GetWindowContext
//
//  Synopsis:   returns a bunch of interfaces and positioning interface
//              the inplace-active object needs to do its thang.
//
//  Arguments:  [ppFrame]     -- return our IOleInPlaceFrame implementation
//              [ppDoc]       -- return our IOleInPlaceUIWindow impl.
//              [prcPosRect]  -- position info
//              [prcClipRect] -- clip info - same as pos info for this case
//              [pFrameInfo]  -- return 0 - inproc object doesn't use this.
//
//  Notes:      note that ppFrame and ppDoc are really just the same
//              object because we're an SDI app.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::GetWindowContext(
       IOleInPlaceFrame    **ppFrame,
       IOleInPlaceUIWindow **ppDoc,
       LPRECT                prcPosRect,
       LPRECT                prcClipRect,
       LPOLEINPLACEFRAMEINFO pFrameInfo)
{
    // get the frame
    HRESULT hr = m_pCtr->QueryInterface(
                            IID_IOleInPlaceFrame,
                            (LPVOID *)ppFrame);

    _ASSERTE(!hr);

    // return the frame again :) - this is all per-spec.
    hr = m_pCtr->QueryInterface(
                        IID_IOleInPlaceUIWindow,
                        (LPVOID *) ppDoc);

    _ASSERTE(!hr);

    // get the clip and pos rect - same for this application.
    HWND hWnd = m_pCtr->GetMainWindow();
    _ASSERTE(hWnd);
    HWND hWndFrame = m_pCtr->GetFrameWindow();

    ::GetClientRect(hWndFrame, prcPosRect);
    ::MapWindowPoints(hWndFrame, hWnd, (LPPOINT)prcPosRect, 2);
    *prcClipRect = *prcPosRect;

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::Scroll
//
//  Synopsis:   never implement this for WebBrowser OC.  This has
//              nothing to do with the scrollbars you see on the HTML.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::Scroll(SIZE scrollExtent)
{
    return E_NOTIMPL;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::OnUIDeactivate
//
//  Synopsis:   set state bits
//
//  Arguments:  [fUndoable] -- not used
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::OnUIDeactivate(BOOL fUndoable)
{
    m_pCtr->SetState(OS_INPLACE);
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::OnInPlaceDeactivate
//
//  Synopsis:   releases the IOleInPlaceObject pointer we were
//              caching for the object, and sets state to OS_RUNNING.
//              Also fires the OLEIVERB_DISCARDUNDOSTATE at the control
//              to tell it to release any undo state it's holding onto.
//              I very much doubt the WebBrowser OC has any undo state,
//              but, this is the protocol.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::OnInPlaceDeactivate(VOID)
{
    RECT rc;

    if (m_pCtr->m_pIPO)
    {
        m_pCtr->m_pIPO->Release();
        m_pCtr->SetState(OS_RUNNING);
        m_pCtr->m_pIPO = 0;
    }

    if (m_pCtr->m_pOO)
    {
        m_pCtr->_GetDoVerbRect(&rc); // get rect for firing verbs.
        m_pCtr->m_pOO->DoVerb(
            OLEIVERB_DISCARDUNDOSTATE,
            0,
            &m_pCtr->m_CS,
            0,
            m_pCtr->GetFrameWindow(),
            0);
    }

    return S_OK;
}


//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::_GetDoVerbRect
//
//  Synopsis:   whenever firing DoVerb(), we need a rect for the object
//              that describes the area for the object in parent client coords.
//
//  Arguments:  [prc] -- rect returned.
//
//----------------------------------------------------------------------------
VOID
CMSJOCCtr::_GetDoVerbRect(LPRECT prc)
{
    _ASSERTE(m_hWndBrowser && m_hWndFrame);
    ::GetClientRect(GetFrameWindow(), prc);
    ::MapWindowPoints(GetFrameWindow(), GetMainWindow(), (LPPOINT)prc, 2);
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::DiscardUndoState
//
//  Synopsis:   just say OK - we don't hold any undo state for
//              object.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::DiscardUndoState(VOID)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::DeactivateAndUndo
//
//  Synopsis:   absolutely minimum implementation of deactivateandundo.
//              just calls IOleInPlaceObject::InPlaceDeactivate().
//
//  Returns:    S_OK always.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::DeactivateAndUndo(VOID)
{
    if (m_pCtr->m_pIPO)
        m_pCtr->m_pIPO->InPlaceDeactivate();

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CInPlaceSite::OnPosRectChange
//
//  Synopsis:   never implement this.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CInPlaceSite::OnPosRectChange(LPCRECT lprcPosRect)
{
    return E_NOTIMPL;
}



STDMETHODIMP
CServiceProvider::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    return m_pCtr->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG)
CServiceProvider::AddRef(VOID)
{
    return m_pCtr->AddRef();
}


STDMETHODIMP_(ULONG)
CServiceProvider::Release(VOID)
{
    return m_pCtr->Release();
}

CServiceProvider::CServiceProvider(LPMSJOCCtr pCtr) : m_pCtr(pCtr)
{

}

#if 0
// define your own guid here, or actually, put it in a header file to be included by
// any OCs that you want to have special communication with your browser frame.

DEFINE_GUID(SID_SMSJBrowser, something)
DEFINE_GUID(DIID_MSJBrowser, something)

Note that if you hand off an IDispatch to an OC in page, it will be in a different
thread from you, so you'll need to synchronize incoming calls, probably by
posting a message to your main hwnd to handle the call.

#endif

//+---------------------------------------------------------------------------
//
//  Member:     CServiceProvider::QueryService
//
//  Synopsis:   This is here as a possible way to expose
//              interfaces privately to OCs
//
//  Arguments:  [rsid]   -- service ID
//              [iid]    -- interface ID requested
//              [ppvObj] -- interface returned.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CServiceProvider::QueryService(REFGUID rsid, REFIID iid, LPVOID *ppvObj)
{
    *ppvObj = 0;

#if 0
    if (IsEqualIID(rsid, SID_SMSJBrowser) && IsEqualIID(iid, DIID_MSJBrowser))
    {
        //
        return S_OK;
    }
#endif

    return E_NOINTERFACE;
}

//+---------------------------------------------------------------------------
//
//  Class:      COleContainer ()
//
//  Purpose:    our implementation of IOleContainer.  does nothing.  But the
//              WebBrowser OC needs to see it or frames don't work - bug in
//              their error path.
//
//----------------------------------------------------------------------------
STDMETHODIMP
COleContainer::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    return m_pCtr->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG)
COleContainer::AddRef(VOID)
{
    return m_pCtr->AddRef();
}

STDMETHODIMP_(ULONG)
COleContainer::Release(VOID)
{
    return m_pCtr->Release();
}

COleContainer::COleContainer(LPMSJOCCtr pCtr) : m_pCtr(pCtr)
{

}

STDMETHODIMP
COleContainer::EnumObjects(DWORD grfFlags, IEnumUnknown **ppenum)
{
    _ASSERTE(FALSE);   // never called
    return E_NOTIMPL;
}

STDMETHODIMP
COleContainer::LockContainer(BOOL fLock)
{
    _ASSERTE(FALSE);  // never called
    return S_OK;
}

STDMETHODIMP
COleContainer::ParseDisplayName(
                  IBindCtx *pbc,
                  LPOLESTR pszDisplayName,
                  ULONG *pchEaten,
                  IMoniker **ppmkOut)
{
    return E_NOTIMPL;
}

//+---------------------------------------------------------------------------
//
//  Class:      CCommandTarget ()
//
//  Purpose:    IOleCommandTarget.  It turns out the WebBrowser OC
//              communicates some of its status messages by calling
//              IOleCommandTarget->Exec(OLECMDID_SETPROGRESSTEXT);
//
//  Interface:  CCommandTarget -- ctor
//              QueryInterface -- gimme an interface
//              AddRef         -- bump up refcount
//              Release        -- release refcount
//              QueryStatus    -- what cmds do you support?
//              Exec           -- execute a command.
//
//----------------------------------------------------------------------------
CCommandTarget::CCommandTarget(LPMSJOCCtr pCtr) : m_pCtr(pCtr)
{
}


STDMETHODIMP
CCommandTarget::QueryInterface(REFIID riid, LPVOID FAR * ppv)
{
    return m_pCtr->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG)
CCommandTarget::AddRef(VOID)
{
    return m_pCtr->AddRef();
}

STDMETHODIMP_(ULONG)
CCommandTarget::Release(VOID)
{
    return m_pCtr->Release();
}

//+---------------------------------------------------------------------------
//
//  Member:     CCommandTarget::QueryStatus
//
//  Synopsis:   queries for what commands we support.  We only support
//              the OLECMDID_SETPROGRESSTEXT command.
//
//  Arguments:  [pguidCmdGroup] -- should be 0
//              [cCmds]         -- number of commands
//              [aCmds]         -- array of commands
//              [pCmdText]      -- returned status text - we set this to 0.
//
//  Returns:    S_OK - always succeeds.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CCommandTarget::QueryStatus(
        const GUID * pguidCmdGroup,
        ULONG        cCmds,
        OLECMD       aCmds[],
        OLECMDTEXT * pCmdText)
{
    ULONG  i;

    // we only support the default (NULL) group
    if (pguidCmdGroup)
        return OLECMDERR_E_UNKNOWNGROUP;

    for (i = 0; i < cCmds; i++)
    {
        switch (aCmds[i].cmdID)
        {
        case OLECMDID_SETPROGRESSTEXT:
            aCmds[i].cmdf = OLECMDF_ENABLED;
            break;
        default:
            break;
        }
    }

    if (pCmdText)
    {
        pCmdText->cmdtextf = OLECMDTEXTF_NONE;
        pCmdText->cwActual = 0;
        if (pCmdText->rgwz && pCmdText->cwBuf > 0)
            *pCmdText->rgwz = L'\0';
    }
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CCommandTarget::Exec
//
//  Synopsis:   execute a command.  We only support OLECMDID_SETPROGRESSTEXT.
//
//  Arguments:  [pguidCmdGroup] --  should be 0
//              [nCmdID]        --  cmd ID
//              [nCmdexecopt]   --  not used
//              [pVarIn]        --  this has the text to display
//              [pVarOut]       --  not used
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
STDMETHODIMP
CCommandTarget::Exec(
        const GUID * pguidCmdGroup,
        DWORD        nCmdID,
        DWORD        nCmdexecopt,
        LPVARIANTARG pVarIn,
        LPVARIANTARG pVarOut)
{
    // we only support the default group.
    if (pguidCmdGroup)
        return OLECMDERR_E_UNKNOWNGROUP;

    switch (nCmdID)
    {
    case OLECMDID_SETPROGRESSTEXT:
        if (VT_BSTR != V_VT(pVarIn))
            return E_FAIL;

        return m_pCtr->_DisplayStatusText(V_BSTR(pVarIn));
        break;

    default:
        break;
    }

    return OLECMDERR_E_NOTSUPPORTED;  // we don't support that command.
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::WndProc, static
//
//  Synopsis:   wndproc for the frame.
//
//----------------------------------------------------------------------------
LRESULT CALLBACK
CMSJOCCtr::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LPMSJOCCtr pCtr;

    if (WM_NCCREATE == msg)
    {
        pCtr = (LPMSJOCCtr) ((LPCREATESTRUCT) lParam)->lpCreateParams;
        pCtr->SetFrameWindow(hWnd);
        ::SetWindowLong(hWnd, GWL_USERDATA, (LONG) pCtr);
        return TRUE;
    }
    else
    {
        pCtr =  (LPMSJOCCtr) ::GetWindowLong(hWnd, GWL_USERDATA);
        _ASSERTE(pCtr);

        switch (msg)
        {
        case WM_SETFOCUS:
            return pCtr->SetFocus();
            break;

        case WM_ERASEBKGND:
            return TRUE;
            break;

        case WM_NCDESTROY:
            // destruction handled by main window
            ::SetWindowLong(hWnd, GWL_USERDATA, 0);
            break;

        default:
            return ::DefWindowProc(hWnd, msg, wParam, lParam);
        }
    }

    return 0;
}

// event handlers

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnBeginNavigate
//
//  Synopsis:   this is called when OC first starts to navigate.
//
//  Arguments:  [bstrURL] -- URL we're about to navigate to.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnBeginNavigate(BSTR bstrURL)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnNavigate
//
//  Synopsis:   This is fired after we already navigated to a url.  We take
//              this opportunity to figure out what type of document we
//              navigated to.  If it's HTML, then turn the ObjMenu off.
//              We'll also take the opportunity to get the zoom range.
//
//  Effects:    turns objmenu off or on, and sets m_iZoomMin and Most.
//
//  Arguments:  [bstrURL] --  string name of URL we navigated to.
//
//  Returns:    S_OK - we always return S_OK from event firings.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnNavigate(BSTR bstrURL)
{
    CHAR achURL[CCHMAXURL];

    ::memset(achURL, 0, sizeof achURL);
    _ASSERTE(m_pIPO);

    // convert bstrURL to ANSI so we can display it in the combobox.
    _SIDE_ASSERT(::WideCharToMultiByte(
                    CP_ACP,
                    0,
                    bstrURL,
                    -1,
                    achURL,
                    NElems(achURL),
                    0,
                    0));

    // set the text into the address bar.
    if (!::SetWindowText(GetEditWindow(), achURL))
        return HRESULT_FROM_WIN32(::GetLastError());

    // try to get the zoom minMost now - do not check for error - we
    // are not going to return it to the firer of this event (WebBrowserOC)
    // it wouldn't know what to do with it.
    _GetZoomMinMost();

    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::_GetZoomMinMost
//
//  Synopsis:   sets m_iZoomMin, and Most - gets called whenever we
//              navigate to a document.  Note that many document types
//              do not support Zoom, and so this fails.  This is OK,
//              and expected.
//
//  Returns:    HRESULT
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::_GetZoomMinMost(VOID)
{
    VARIANT            vararg;
    HRESULT            hr;
    LPOLECOMMANDTARGET pCT = 0;

    ::VariantClear(&vararg);
    V_VT(&vararg) = VT_I4;
    V_I4(&vararg) = 0;

    m_iZoom = m_iZoomMin = m_iZoomMost = 0;

    hr = _GetOleCommandTarget(&pCT);
    if (hr)
        goto cleanup;

    hr = pCT->Exec(
            0,
            OLECMDID_ZOOM,
            OLECMDEXECOPT_DONTPROMPTUSER,
            0,
            &vararg);

    if (hr)
        goto cleanup;

    if (VT_I4 == V_VT(&vararg))
        m_iZoom = V_I4(&vararg);

    ::VariantClear(&vararg);
    V_VT(&vararg) = VT_I4;
    V_I4(&vararg) = 0;

    hr = pCT->Exec(
            0,
            OLECMDID_GETZOOMRANGE,
            OLECMDEXECOPT_DONTPROMPTUSER,
            0,
            &vararg);

    if (hr)
        goto cleanup;

    if (VT_I4 == V_VT(&vararg))
    {
        // I looked at the IE code for this - this cast is necessary.
        m_iZoomMin = (INT)(SHORT)LOWORD(V_I4(&vararg));
        m_iZoomMost = (INT)(SHORT)HIWORD(V_I4(&vararg));
    }

cleanup:
    if (pCT)
        pCT->Release();

    return hr;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnStatusTextChange
//
//  Synopsis:   tess us status text changed
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnStatusTextChange(BSTR bstrStatusText)
{
    return _DisplayStatusText(bstrStatusText);
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnProgress
//
//  Synopsis:   We're not doing anything with this yet.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnProgress(LONG lProgress, LONG lProgressMax)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnDownloadBegin
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnDownloadBegin(VOID)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnDownloadComplete
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnDownloadComplete(VOID)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnCommandStateChange
//
//  Synopsis:   responds to the OnCommandStateChange event by disabling
//              or enabling back and forward buttons.
//
//  Arguments:  [vbEnable] -- VARIANT_TRUE or VARIANT_FALSE - enabled?
//              [lValue]   -- CSC_NAVIGATEFORWARD, BACK, or UPDATECOMMANDS
//
//  Returns:    S_OK, what else?
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnCommandStateChange(VARIANT_BOOL vbEnable, LONG lValue)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnNewWindow
//
//  Synopsis:   not doing anything with it.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnNewWindow(VOID)
{
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  Member:     CMSJOCCtr::OnQuit
//
//  Synopsis:   not doing anything witht it yet.
//
//----------------------------------------------------------------------------
HRESULT
CMSJOCCtr::OnQuit(VOID)
{
    return S_OK;
}



