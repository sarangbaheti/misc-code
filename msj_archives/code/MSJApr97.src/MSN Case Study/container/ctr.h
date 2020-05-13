#ifndef __CTR_H_DEFINED__
#define __CTR_H_DEFINED__

//---------------------------------------------------------------
//  IOleObject
//---------------------------------------------------------------

enum OLE_SERVER_STATE
{
    OS_PASSIVE,
    OS_LOADED,                          // handler but no server
    OS_RUNNING,                         // server running, invisible
    OS_INPLACE,                         // server running, inplace-active, no U.I.
    OS_UIACTIVE,                        // server running, inplace-active, w/ U.I.
    OS_OPEN                             // server running, open-edited
};


// prototypes for HIMETRIC stuff.
//

void
InitPixelsPerInch(VOID);

int
HPixFromHimetric(long lHi);

int
VPixFromHimetric(long lHi);

long
HimetricFromHPix(int iPix);

long
HimetricFromVPix(int iPix);


class CMSJOCCtr;
typedef CMSJOCCtr FAR * LPMSJOCCtr;

//+---------------------------------------------------------------------------
//
//  Class:      COleContainer ()
//
//  Purpose:    our implementation of IOleContainer.  does nothing.  But the
//              WebBrowser OC needs to see it or frames don't work.  This is
//              their bug.
//
//----------------------------------------------------------------------------
class COleContainer : public IOleContainer
{
public:
    // IUnknown stuff
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
    STDMETHOD_(ULONG, AddRef)(VOID);
    STDMETHOD_(ULONG, Release)(VOID);

    STDMETHOD(EnumObjects)(DWORD grfFlags, IEnumUnknown **ppenum);
    STDMETHOD(LockContainer)(BOOL fLock);
    STDMETHOD(ParseDisplayName)(
                      IBindCtx *pbc,
                      LPOLESTR pszDisplayName,
                      ULONG *pchEaten,
                      IMoniker **ppmkOut);

    COleContainer(LPMSJOCCtr pCtr);

protected:
    LPMSJOCCtr  m_pCtr;
};

//+---------------------------------------------------------------------------
//
//  Class:      CServiceProvider ()
//
//  Purpose:    new interface for exposing interfaces from logically
//              disparate objects.  Still is not clear what
//              we will expose from this - we may use it to hook
//              up private interfaces to OCs in the page.
//
//  Interface:  QueryInterface   -- standard IUnknown
//              AddRef           -- ditto
//              Release          -- ditto
//              QueryService     -- Get me an interface from another object.
//
//----------------------------------------------------------------------------
class CServiceProvider : public IServiceProvider
{
public:
    // IUnknown stuff
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
    STDMETHOD_(ULONG, AddRef)(VOID);
    STDMETHOD_(ULONG, Release)(VOID);

    STDMETHOD(QueryService)(REFGUID rsid, REFIID iid, LPVOID *ppvObj);

    CServiceProvider(LPMSJOCCtr pCtr);

protected:
    LPMSJOCCtr  m_pCtr;
};

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
class COleClientSite : public IOleClientSite
{
public:
    COleClientSite(LPMSJOCCtr pCtr);

    // IUnknown stuff
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
    STDMETHOD_(ULONG, AddRef)(VOID);
    STDMETHOD_(ULONG, Release)(VOID);


    // IOleClientSite stuff
    STDMETHOD(SaveObject)(VOID);
    STDMETHOD(GetMoniker)(
                 DWORD           dwAssign,
                 DWORD           dwWhichMoniker,
                 LPMONIKER FAR * ppmk);
    STDMETHOD(GetContainer)(LPOLECONTAINER FAR * pOleCtr);
    STDMETHOD(ShowObject)(VOID);
    STDMETHOD(OnShowWindow)(BOOL bShow);
    STDMETHOD(RequestNewObjectLayout)(VOID);

protected:
    LPMSJOCCtr  m_pCtr;   // pointer to the CMSJOCCtr object.
};

//+---------------------------------------------------------------------------
//
//  Class:      CAdviseSink ()
//
//  Purpose:    IAdviseSink implementation
//
//  Notes:      It turns out we're not doing anything with this
//              currently, but it would be a bad idea to remove this.
//              The WebBrowser OC *does* ask for this, and calls the
//              OnViewChange() from time to time, although we've found
//              it best to just let the OC handle it's own visual state.
//
//----------------------------------------------------------------------------
class CAdviseSink : public IAdviseSink
{
public:
    CAdviseSink(LPMSJOCCtr pCtr);

   // IUnknown stuff
   STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
   STDMETHOD_(ULONG, AddRef)(VOID);
   STDMETHOD_(ULONG, Release)(VOID);

   // IAdviseSink stuff
   STDMETHOD_(VOID, OnDataChange)(LPFORMATETC pFE, LPSTGMEDIUM pStgMedium);
   STDMETHOD_(VOID, OnViewChange)(DWORD dwAspect, LONG lIndex);
   STDMETHOD_(VOID, OnRename)(LPMONIKER pmkNew);
   STDMETHOD_(VOID, OnSave)(VOID);
   STDMETHOD_(VOID, OnClose)(VOID);

protected:
    LPMSJOCCtr  m_pCtr;   // pointer to the CMSJOCCtr object.
    LPUNKNOWN   m_pUnkOuter;  // pointer to CMSJOCCtr's IUnknown
};

//+---------------------------------------------------------------------------
//
//  Class:      CInPlaceFrame ()
//
//  Purpose:
//
//  Interface:  CInPlaceFrame        -- ctor
//              QueryInterface       -- gimme an interface!
//              AddRef               -- bump up refcount
//              Release              -- decrement refcount
//              GetWindow            -- from IOleWindow - returns frame hWnd
//              ContextSensitiveHelp -- never implemented by design
//              GetBorder            -- for toolbar negotiation
//              RequestBorderSpace   -- ditto
//              SetBorderSpace       -- ditto
//              SetActiveObject      -- called whenever URL changes
//              InsertMenus          -- menu negotiation
//              SetMenu              -- ditto
//              RemoveMenus          -- ditto
//              SetStatusText        -- called by OC to set status text
//              EnableModeless       -- we have no modeless dlgs.
//              TranslateAccelerator -- calls ::TranslateAccelerator
//
//----------------------------------------------------------------------------
class CInPlaceFrame : public IOleInPlaceFrame
{
public:
    CInPlaceFrame(LPMSJOCCtr pCtr);

   // IUnknown stuff
   STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
   STDMETHOD_(ULONG, AddRef)(VOID);
   STDMETHOD_(ULONG, Release)(VOID);

   // IOleWindow stuff
   STDMETHOD(GetWindow)(HWND * phwnd);
   STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);

   // IOleInPlaceUIWindow stuff
   STDMETHOD(GetBorder)(LPRECT lprectBorder);
   STDMETHOD(RequestBorderSpace)(LPCBORDERWIDTHS pborderwidths);
   STDMETHOD(SetBorderSpace)(LPCBORDERWIDTHS pborderwidths);
   STDMETHOD(SetActiveObject)(
        IOleInPlaceActiveObject * pActiveObject,
        LPCOLESTR                 pszObjName);

   // IOleInPlaceFrame stuff
   STDMETHOD(InsertMenus)(
        HMENU                hmenuShared,
        LPOLEMENUGROUPWIDTHS lpMenuWidths);

   STDMETHOD(SetMenu)(
        HMENU    hmenuShared,
        HOLEMENU holemenu,
        HWND     hwndActiveObject);

   STDMETHOD(RemoveMenus)(HMENU hmenuShared);
   STDMETHOD(SetStatusText)(LPCOLESTR pszStatusText);
   STDMETHOD(EnableModeless)(BOOL fEnable);
   STDMETHOD(TranslateAccelerator)(LPMSG lpmsg, WORD wID);

protected:
    LPMSJOCCtr  m_pCtr;   // pointer to the CMSJOCCtr object.
};

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
//              ContextSensitiveHelp -- never implemented by design
//              CanInPlaceActivate   -- returns S_OK.
//              OnInPlaceActivate    -- caches IOleInPlaceObject ptr
//              OnUIActivate         -- returns S_OK  - sets state
//              GetWindowContext     -- returns IOleInPlaceFrame,
//                                              IOleInPlaceUIWindow,
//                                              PosRect and ClipRect
//              Scroll               -- never implemented by design.
//              OnUIDeactivate       -- obvious
//              OnInPlaceDeactivate  -- releases cached IOleInPlaceObject
//              DiscardUndoState     -- returns S_OK.
//              DeactivateAndUndo    -- deactivates in place active object
//              OnPosRectChange      -- never implemented by design
//
//----------------------------------------------------------------------------
class CInPlaceSite : public IOleInPlaceSite
{
public:
    CInPlaceSite(LPMSJOCCtr pCtr);

   // IUnknown stuff
   STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
   STDMETHOD_(ULONG, AddRef)(VOID);
   STDMETHOD_(ULONG, Release)(VOID);

   // IOleWindow stuff
   STDMETHOD(GetWindow)(HWND * phwnd);
   STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);

   // IOleInPlaceSite stuff
   STDMETHOD(CanInPlaceActivate)(VOID);
   STDMETHOD(OnInPlaceActivate)(VOID);
   STDMETHOD(OnUIActivate)(VOID);
   STDMETHOD(GetWindowContext)(
       IOleInPlaceFrame    **ppFrame,
       IOleInPlaceUIWindow **ppDoc,
       LPRECT                prcPosRect,
       LPRECT                prcClipRect,
       LPOLEINPLACEFRAMEINFO pFrameInfo);

   STDMETHOD(Scroll)(SIZE scrollExtant);
   STDMETHOD(OnUIDeactivate)(BOOL fUndoable);
   STDMETHOD(OnInPlaceDeactivate)(VOID);
   STDMETHOD(DiscardUndoState)(VOID);
   STDMETHOD(DeactivateAndUndo)(VOID);
   STDMETHOD(OnPosRectChange)(LPCRECT lprcPosRect);

protected:
    LPMSJOCCtr  m_pCtr;   // pointer to the CMSJOCCtr object.
};

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
class CCommandTarget : public IOleCommandTarget
{
public:
    CCommandTarget(LPMSJOCCtr pCtr);

    // IUnknown stuff
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
    STDMETHOD_(ULONG, AddRef)(VOID);
    STDMETHOD_(ULONG, Release)(VOID);

    // IOleCommandTarget stuff
    STDMETHOD(QueryStatus)(const GUID * pguidCmdGroup,
                           ULONG        cCmds,
                           OLECMD       aCmds[],
                           OLECMDTEXT * pCmdText);

    STDMETHOD(Exec)(const GUID * pguidCmdGroup,
                   DWORD         nCmdID,
                   DWORD         nCmdexecopt,
                   LPVARIANTARG  pVarIn,
                   LPVARIANTARG  pVarOut);

protected:
    LPMSJOCCtr  m_pCtr;   // pointer to the CMSJOCCtr object.
};

//+---------------------------------------------------------------------------
//
//  Class:      CMSJOCCtr ()
//
//  Purpose:    This is the one, the big kahuna.  CMSJOCCtr is the
//              MSJ OLE Controls container that contains a single
//              OLE Control, the WebBrowser OC.  It contains
//              sub-objects which implement the various interfaces
//              we have to support (could have used multiple inheritance,
//              but this seemed more straightforward for our needs).
//
//              Conventions:  Interfaces we implement are contained objects
//                            of a class trivially derived from the interface,
//                            e.g., IOleInPlaceFrame is a contained
//                            instance of CInPlaceFrame called m_IPF.
//
//                            Interfaces we hold on the WebBrowser OC
//                            are pointers to the actual OLE interface.
//                            e.g., our pointer to the control's
//                            IOleControl interface is m_pOC.
//
//                            The contained sub-objects are all friends
//                            of the container - they are all conceptually
//                            the same object, but are implemented
//                            separately so as to cause the compiler to
//                            generate the correct vtable.
//
//----------------------------------------------------------------------------
class CMSJOCCtr : public IUnknown
{
public:
    friend CInPlaceSite;
    friend CInPlaceFrame;
    friend COleClientSite;
    friend CServiceProvider;
    friend CCommandTarget;

    // IUnknown stuff
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR * ppv);
    STDMETHOD_(ULONG, AddRef)(VOID);
    STDMETHOD_(ULONG, Release)(VOID);

    LRESULT PaletteChanged(WPARAM wParam);
    BOOL    QueryNewPalette(VOID);
    VOID    Paint(HDC hDC, LPRECT lpr);
    VOID    Paint(VOID);
    HRESULT CreateBrowserOC(HWND hWndEdit);
    HRESULT GetSize(LPRECT prc);
    HRESULT SetSize(LPRECT prc, BOOL fMoveFrameWindow = TRUE);
    VOID    SetFrameWindow(HWND hWndFrame){m_hWndFrame = hWndFrame;}
    VOID    SetEditWindow(HWND hWndEdit){m_hWndEdit = hWndEdit;}
    HWND    GetFrameWindow(VOID)
    {
        _ASSERTE(m_hWndFrame && ::IsWindow(m_hWndFrame));
        return m_hWndFrame;
    }

    HWND    GetEditWindow(VOID)
    {
        _ASSERTE(m_hWndEdit && ::IsWindow(m_hWndEdit));
        return m_hWndEdit;
    }

    HWND    GetMainWindow(VOID)
    {
        _ASSERTE(m_hWndBrowser && ::IsWindow(m_hWndBrowser));
        return m_hWndBrowser;
    }

    HRESULT Navigate(LPSTR pszURL);
    VOID    PrintCurrentPage(VOID);
    VOID    ZoomIn(VOID);
    VOID    ZoomOut(VOID);
    HRESULT Back(VOID);
    HRESULT Forward(VOID);
    HRESULT Stop(VOID);
    HRESULT Refresh(VOID);
    HRESULT Options(VOID);
    HRESULT Busy(BOOL * pfBusy);
    LRESULT OnActivateApp(WPARAM wParam, LPARAM lParam);

    //
    //  Whenever we display a modal dialog, we need to let
    //  our embeddings (the WebBrowser OC) know to disable
    //  any modeless dialogs the embedding is displaying.
    //
    VOID    EnableEmbeddingModelessDlgs(BOOL fEnable)
    {
        LPOLEINPLACEACTIVEOBJECT pIPAO = GetIPAObject();
        if (pIPAO)
            pIPAO->EnableModeless(fEnable);
    }

    VOID    DoLayout(INT cxMain, INT cyMain);

    CMSJOCCtr(const HWND hWnd);
   ~CMSJOCCtr(VOID);
    VOID ShutDown(VOID);

    HRESULT NormalizeURL(LPSTR szPathIn, LPSTR szPathOut);

    // event handlers
    HRESULT OnBeginNavigate(BSTR bstrURL);
    HRESULT OnNavigate(BSTR bstrURL);
    HRESULT OnStatusTextChange(BSTR bstrStatusText);
    HRESULT OnDownloadComplete(VOID);
    HRESULT OnCommandStateChange(VARIANT_BOOL fEnable, LONG lValue);
    HRESULT OnDownloadBegin(VOID);
    HRESULT OnNewWindow(VOID);
    HRESULT OnProgress(LONG lProgress, LONG lProgressMax);
    HRESULT OnQuit(VOID);

    OLE_SERVER_STATE GetState(VOID) {return m_state;}
    VOID             SetState(OLE_SERVER_STATE state) {m_state = state;}
    HRESULT          EnableModeless(BOOL fEnable);
    BOOL             ModelessEnabled(VOID){return m_fModelessEnabled;}
    LRESULT          SetFocus(VOID);

    LPOLEINPLACEACTIVEOBJECT GetIPAObject(VOID) {return m_pActiveObj;}

    static LRESULT CALLBACK
    WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
    INT     _RealizePalette(VOID);
    HRESULT _SetExtent(LPRECT prc);
    HRESULT _DisplayStatusText(LPCOLESTR pStrStatusText);
    VOID    _ResetToolSpace(VOID)
    {
        ::memset(&m_rcToolSpace, 0, sizeof m_rcToolSpace);
    }
    VOID    _AdjustForTools(LPRECT prc);

    HRESULT _GetOleCommandTarget(LPOLECOMMANDTARGET * ppOleCmdTgt);
    HRESULT _Zoom(INT iZoom);
    HRESULT _GetZoomMinMost(VOID);
    VOID    _DeactivateControl(VOID);
    VOID    _DisplayError(UINT uErrID);
    HRESULT _TransAccelerator(LPMSG lpmsg, WORD wID);
    VOID    _GetDoVerbRect(LPRECT prc);


    CEventMap                m_EvtMap;      // events for control.
    BORDERWIDTHS             m_rcToolSpace; // for WebBrowser OC.
    COleClientSite           m_CS;          // clientsite
    CAdviseSink              m_AS;          // advise sink
    CInPlaceFrame            m_IPF;         // inplace frame
    CInPlaceSite             m_IPS;         // inplace site object
    CServiceProvider         m_SP;          // IServiceProvider;
    COleContainer            m_OCtr;        // IOleContainer
    CCommandTarget           m_OCT;         // IOleCommandTarget
    HWND                     m_hWndBrowser; // hWnd of main browser
    HWND                     m_hWndFrame;   // hWnd that contains OC Site
    HWND                     m_hWndEdit;    // URL edit ctrl.
    LPUNKNOWN                m_pUnk;        // the object itself.
    IWebBrowser   *          m_pWB;         // pointer to IWebBrowser for OC
    LPVIEWOBJECT             m_pVO;         // pointer to IViewObject
    LPOLEOBJECT              m_pOO;         // pointer to IOleObject
    LPOLEINPLACEOBJECT       m_pIPO;        // pointer to InPlaceActiveObject
    LPDISPATCH               m_pDisp;       // IDispatch to WebBrowserOC
    LPOLEINPLACEACTIVEOBJECT m_pActiveObj;  // current active object
    LPOLECONTROL             m_pOC;         // IOleControl interface for OC
    ULONG                    m_Ref;         // refcount
    INT                      m_iZoomMin;    // min fontzoom range for curr. doc.
    INT                      m_iZoomMost;   // most fontzoom range etc.
    INT                      m_iZoom;       // current zoom setting for etc.
    OLE_SERVER_STATE         m_state;       // current OLE state of OC
    DWORD                    m_dwMiscStatus;// misc status bits for OC
    BOOL                     m_fModelessEnabled; // OC is putting up modal dlg?
    HPALETTE                 m_hPal;
};

typedef CMSJOCCtr FAR * LPMSJOCCtr;

extern LPMSJOCCtr g_pCtr;

#endif

