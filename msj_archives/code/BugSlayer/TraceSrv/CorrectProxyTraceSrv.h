/*----------------------------------------------------------------------
John Robbins
Microsoft Systems Journal, December 1997 - Bugslayer Column!
----------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////
// BIG NOTE!!!!!
////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------------------
    While this might look like the ATL proxy generated file, it is
really a massaged version.  Unfortunately, the proxy generator does not
generate the best code in the world.  IDispatch::Invoke returns an error
code that is pretty useful but the generated code does not check it.
This makes it very difficult to see if something failed because all of
these functions just appear to work.  From a proactive debugging
standpoint, this is not good at all!
    I went through and put ASSERTS macros in strategic places inside
this code.  If you extend the TraceSrv interface, you will need to
generate a new file, fix it, then rename it to CorrectProxyTraceSrv.h.
    In addition, I also consolidated the code for the property value
change notifications so there is not so much duplication.
----------------------------------------------------------------------*/

template <class T>
class CProxyDITraceEvent :
    public IConnectionPointImpl<T ,
                                &DIID_DITraceEvent ,
                                CComDynamicUnkArray>
{
private :
    // This function actually does the work for the property change
    //  notifications.  Why duplicate reams of code?
    void Fire_PropertyChange ( DISPID dID , VARIANT_BOOL bNewVal )
    {
        VARIANTARG* pvars = new VARIANTARG[1];
        for (int i = 0; i < 1; i++)
            VariantInit(&pvars[i]);
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[0].vt = VT_BOOL;
                pvars[0].boolVal= bNewVal;
                DISPPARAMS disp = { pvars, NULL, 1, 0 };
                IDispatch* pDispatch =reinterpret_cast<IDispatch*>(*pp);
                // Here is where you need to handle the return.
                HRESULT hr ;
                hr = pDispatch->Invoke(dID ,
                                       IID_NULL,
                                       LOCALE_USER_DEFAULT,
                                       DISPATCH_METHOD,
                                       &disp,
                                       NULL,
                                       NULL,
                                       NULL);
                ASSERT ( SUCCEEDED ( hr ) ) ;
            }
            pp++;
        }
        pT->Unlock();
        delete[] pvars;
    }


public  :
    // The actual trace event itself.
    void Fire_TraceEvent( BSTR bstrText )
    {
        VARIANTARG* pvars = new VARIANTARG[1];
        for (int i = 0; i < 1; i++)
        {
            VariantInit(&pvars[i]);
        }
        T* pT = (T*)this;
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            if (*pp != NULL)
            {
                pvars[0].vt = VT_BSTR;
                pvars[0].bstrVal= bstrText;
                DISPPARAMS disp = { pvars, NULL, 1, 0 };
                IDispatch* pDispatch =
                                     reinterpret_cast<IDispatch*>(*pp);
                // Here is where you need to handle the return.
                HRESULT hr ;
                hr = pDispatch->Invoke(0x1,
                                       IID_NULL,
                                       LOCALE_USER_DEFAULT,
                                       DISPATCH_METHOD,
                                       &disp,
                                       NULL,
                                       NULL,
                                       NULL);
                ASSERT ( SUCCEEDED ( hr ) ) ;
            }
            pp++;
        }
        pT->Unlock();
        delete[] pvars;
    }

    void Fire_ChangeShowTimeStamps ( VARIANT_BOOL bNewVal )
    {
        Fire_PropertyChange ( 0x2 , bNewVal ) ;
    }
    void Fire_ChangeShowTraceAsODS ( VARIANT_BOOL bNewVal )
    {
        Fire_PropertyChange ( 0x3 , bNewVal ) ;
    }
    void Fire_ChangeShowItemNumber ( VARIANT_BOOL bNewVal )
    {
        Fire_PropertyChange ( 0x4 , bNewVal ) ;
    }
    void Fire_ChangeShowPID ( VARIANT_BOOL bNewVal )
    {
        Fire_PropertyChange ( 0x5 , bNewVal ) ;
    }
    void Fire_ChangeAddCRLF ( VARIANT_BOOL bNewVal )
    {
        Fire_PropertyChange ( 0x6 , bNewVal ) ;
    }
};

