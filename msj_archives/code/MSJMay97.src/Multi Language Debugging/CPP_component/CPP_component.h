/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Sat Feb 22 21:15:31 1997
 */
/* Compiler settings for CPP_component.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CPP_component_h__
#define __CPP_component_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IStock_FWD_DEFINED__
#define __IStock_FWD_DEFINED__
typedef interface IStock IStock;
#endif 	/* __IStock_FWD_DEFINED__ */


#ifndef __CStock_FWD_DEFINED__
#define __CStock_FWD_DEFINED__

#ifdef __cplusplus
typedef class CStock CStock;
#else
typedef struct CStock CStock;
#endif /* __cplusplus */

#endif 	/* __CStock_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IStock_INTERFACE_DEFINED__
#define __IStock_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStock
 * at Sat Feb 22 21:15:31 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IStock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C8D363E5-FC5C-11CF-A288-00A0C905A457")
    IStock : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Buy( 
            /* [in] */ long lAccount,
            /* [in] */ BSTR bstrStock,
            /* [in] */ long lShares,
            /* [in] */ double dblPrice) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Sell( 
            /* [in] */ long lAccount,
            /* [in] */ BSTR bstrStock,
            /* [in] */ long lShares,
            /* [in] */ double dblPrice) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Commission( 
            /* [in] */ double dblCommission) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Commission( 
            /* [retval][out] */ double __RPC_FAR *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStock __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStock __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStock __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStock __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStock __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStock __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStock __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Buy )( 
            IStock __RPC_FAR * This,
            /* [in] */ long lAccount,
            /* [in] */ BSTR bstrStock,
            /* [in] */ long lShares,
            /* [in] */ double dblPrice);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sell )( 
            IStock __RPC_FAR * This,
            /* [in] */ long lAccount,
            /* [in] */ BSTR bstrStock,
            /* [in] */ long lShares,
            /* [in] */ double dblPrice);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Commission )( 
            IStock __RPC_FAR * This,
            /* [in] */ double dblCommission);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Commission )( 
            IStock __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *retval);
        
        END_INTERFACE
    } IStockVtbl;

    interface IStock
    {
        CONST_VTBL struct IStockVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStock_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStock_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStock_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStock_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStock_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStock_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStock_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IStock_Buy(This,lAccount,bstrStock,lShares,dblPrice)	\
    (This)->lpVtbl -> Buy(This,lAccount,bstrStock,lShares,dblPrice)

#define IStock_Sell(This,lAccount,bstrStock,lShares,dblPrice)	\
    (This)->lpVtbl -> Sell(This,lAccount,bstrStock,lShares,dblPrice)

#define IStock_put_Commission(This,dblCommission)	\
    (This)->lpVtbl -> put_Commission(This,dblCommission)

#define IStock_get_Commission(This,retval)	\
    (This)->lpVtbl -> get_Commission(This,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStock_Buy_Proxy( 
    IStock __RPC_FAR * This,
    /* [in] */ long lAccount,
    /* [in] */ BSTR bstrStock,
    /* [in] */ long lShares,
    /* [in] */ double dblPrice);


void __RPC_STUB IStock_Buy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStock_Sell_Proxy( 
    IStock __RPC_FAR * This,
    /* [in] */ long lAccount,
    /* [in] */ BSTR bstrStock,
    /* [in] */ long lShares,
    /* [in] */ double dblPrice);


void __RPC_STUB IStock_Sell_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IStock_put_Commission_Proxy( 
    IStock __RPC_FAR * This,
    /* [in] */ double dblCommission);


void __RPC_STUB IStock_put_Commission_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IStock_get_Commission_Proxy( 
    IStock __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *retval);


void __RPC_STUB IStock_get_Commission_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStock_INTERFACE_DEFINED__ */



#ifndef __CPP_COMPONENTLib_LIBRARY_DEFINED__
#define __CPP_COMPONENTLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CPP_COMPONENTLib
 * at Sat Feb 22 21:15:31 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CPP_COMPONENTLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CStock;

class DECLSPEC_UUID("C8D363E9-FC5C-11CF-A288-00A0C905A457")
CStock;
#endif
#endif /* __CPP_COMPONENTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
