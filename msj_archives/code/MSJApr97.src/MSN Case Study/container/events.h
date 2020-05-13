#ifndef __EVENTS_H__
#define __EVENTS_H__

class CMSJOCCtr;

class CEventMap : public IDispatch
{
public:
        // IUnknown methods
        STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj)
        {
            *ppvObj = 0;

            if (::IsEqualIID(riid, IID_IDispatch) ||
                ::IsEqualIID(riid, IID_IUnknown) ||
                ::IsEqualIID(riid, DIID_DWebBrowserEvents))
            {
                *ppvObj = this;
            }
            else return E_NOINTERFACE;

            AddRef();
            return S_OK;
        }

        STDMETHOD_(ULONG,AddRef)(THIS) {return ++m_cRefs;}
        STDMETHOD_(ULONG,Release)(THIS)
        {
            _ASSERTE(m_cRefs);
            m_cRefs--;
            ULONG ulRC = m_cRefs;
            if (!m_cRefs)
                delete this;

            return ulRC;
        }

        // IDispatch methods
        STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetTypeInfo)(
                THIS_
                UINT itinfo,
                LCID lcid,
                ITypeInfo FAR* FAR* pptinfo)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetIDsOfNames)(
                        THIS_
                        REFIID         riid,
                        LPOLESTR FAR * rgszNames,
                        UINT           cNames,
                        LCID           lcid,
                        DISPID FAR   * rgdispid)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(Invoke)(
                        THIS_
                        DISPID           dispidMember,
                        REFIID           riid,
                        LCID             lcid,
                        WORD             wFlags,
                        DISPPARAMS FAR * pdispparams,
                        VARIANT    FAR * pvarResult,
                        EXCEPINFO  FAR * pexcepinfo,
                        UINT       FAR * puArgErr);

    CEventMap(CMSJOCCtr * pCtr) :
        m_pCtr(pCtr),
        m_cEvents(0),
        m_pConnPt(0),
        m_cRefs(1)
    {}

   ~CEventMap(VOID);

    HRESULT GetEventsFromCtrl(LPOLECONTROL pOleCtl);
    VOID    UnhookEvents(VOID);

protected:
    HRESULT           _OnBeginNavigate(DISPPARAMS * pDP, PUINT puArgErr);
    HRESULT           _OnNavigate(DISPPARAMS * pDP, PUINT puArgErr);
    HRESULT           _OnCommandStateChange(DISPPARAMS * pDP, PUINT puArgErr);
    HRESULT           _OnStatusTextChange(DISPPARAMS * pDP, PUINT puArgErr);
    HRESULT           _OnProgress(DISPPARAMS * pDP, PUINT puArgErr);
    CMSJOCCtr       * m_pCtr;
    LPCONNECTIONPOINT m_pConnPt;
    UINT              m_cEvents;
    ULONG             m_cRefs;
    DWORD             m_dwCookie;
};


#endif
