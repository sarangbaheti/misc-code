/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.75 */
/* at Sat Feb 22 21:15:31 1997
 */
/* Compiler settings for CPP_component.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY

#include "rpcproxy.h"
#include "CPP_component.h"

#define TYPE_FORMAT_STRING_SIZE   49                                
#define PROC_FORMAT_STRING_SIZE   133                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IStock, ver. 0.0,
   GUID={0xC8D363E5,0xFC5C,0x11CF,{0xA2,0x88,0x00,0xA0,0xC9,0x05,0xA4,0x57}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IStock_ServerInfo;

#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x301004b, /* MIDL Version 3.1.75 */
    0,
    UserMarshalRoutines,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short IStock_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    42,
    84,
    108
    };

static const MIDL_SERVER_INFO IStock_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IStock_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IStock_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IStock_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(11) _IStockProxyVtbl = 
{
    &IStock_ProxyInfo,
    &IID_IStock,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IStock::Buy */ ,
    (void *)-1 /* IStock::Sell */ ,
    (void *)-1 /* IStock::put_Commission */ ,
    (void *)-1 /* IStock::get_Commission */
};


static const PRPC_STUB_FUNCTION IStock_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IStockStubVtbl =
{
    &IID_IStock,
    &IStock_ServerInfo,
    11,
    &IStock_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, float, double or hyper in -Oif or -Oicf.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Buy */

			0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/*  2 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0x1c ),	/* x86, MIPS, PPC Stack size/offset = 28 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/*  6 */	NdrFcShort( 0x20 ),	/* 32 */
/*  8 */	NdrFcShort( 0x8 ),	/* 8 */
/* 10 */	0x6,		/* 6 */
			0x5,		/* 5 */

	/* Parameter lAccount */

/* 12 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 14 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 16 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrStock */

/* 18 */	NdrFcShort( 0x8b ),	/* 139 */
#ifndef _ALPHA_
/* 20 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 22 */	NdrFcShort( 0x18 ),	/* Type Offset=24 */

	/* Parameter lShares */

/* 24 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 26 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter dblPrice */

/* 30 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 32 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 34 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 36 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 38 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 40 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Sell */

/* 42 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 44 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 46 */	NdrFcShort( 0x1c ),	/* x86, MIPS, PPC Stack size/offset = 28 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 48 */	NdrFcShort( 0x20 ),	/* 32 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	0x6,		/* 6 */
			0x5,		/* 5 */

	/* Parameter lAccount */

/* 54 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 56 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 58 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrStock */

/* 60 */	NdrFcShort( 0x8b ),	/* 139 */
#ifndef _ALPHA_
/* 62 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 64 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter lShares */

/* 66 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 68 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter dblPrice */

/* 72 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 74 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 76 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 80 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Commission */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 86 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 88 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
#else
			NdrFcShort( 0x14 ),	/* MIPS & PPC Stack size/offset = 20 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 90 */	NdrFcShort( 0x10 ),	/* 16 */
/* 92 */	NdrFcShort( 0x8 ),	/* 8 */
/* 94 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter dblCommission */

/* 96 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 98 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* MIPS & PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 100 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 104 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
#else
			NdrFcShort( 0x10 ),	/* MIPS & PPC Stack size/offset = 16 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Commission */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 110 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 112 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 116 */	NdrFcShort( 0x18 ),	/* 24 */
/* 118 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter retval */

/* 120 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 122 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 124 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 126 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 128 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x12, 0x0,	/* FC_UP */
/*  2 */	NdrFcShort( 0xc ),	/* Offset= 12 (14) */
/*  4 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  6 */	NdrFcShort( 0x2 ),	/* 2 */
/*  8 */	0x9,		/* 9 */
			0x0,		/*  */
/* 10 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 12 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 14 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 16 */	NdrFcShort( 0x8 ),	/* 8 */
/* 18 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (4) */
/* 20 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 22 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 24 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */
/* 28 */	NdrFcShort( 0x4 ),	/* 4 */
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (0) */
/* 34 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0x4 ),	/* 4 */
/* 40 */	NdrFcShort( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0xffffffd6 ),	/* Offset= -42 (0) */
/* 44 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 46 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

const CInterfaceProxyVtbl * _CPP_component_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IStockProxyVtbl,
    0
};

const CInterfaceStubVtbl * _CPP_component_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IStockStubVtbl,
    0
};

PCInterfaceName const _CPP_component_InterfaceNamesList[] = 
{
    "IStock",
    0
};

const IID *  _CPP_component_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _CPP_component_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CPP_component, pIID, n)

int __stdcall _CPP_component_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_CPP_component_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo CPP_component_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CPP_component_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CPP_component_StubVtblList,
    (const PCInterfaceName * ) & _CPP_component_InterfaceNamesList,
    (const IID ** ) & _CPP_component_BaseIIDList,
    & _CPP_component_IID_Lookup, 
    1,
    2
};
