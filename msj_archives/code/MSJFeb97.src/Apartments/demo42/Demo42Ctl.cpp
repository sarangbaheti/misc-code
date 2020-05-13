// Demo42Ctl.cpp : Implementation of the CDemo42Ctrl OLE control class.

#include "stdafx.h"
#include "demo42.h"
#include "Demo42Ctl.h"
#include "Demo42Ppg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDemo42Ctrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDemo42Ctrl, COleControl)
	//{{AFX_MSG_MAP(CDemo42Ctrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CDemo42Ctrl, COleControl)
	//{{AFX_DISPATCH_MAP(CDemo42Ctrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CDemo42Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CDemo42Ctrl, COleControl)
	//{{AFX_EVENT_MAP(CDemo42Ctrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CDemo42Ctrl, 1)
	PROPPAGEID(CDemo42PropPage::guid)
END_PROPPAGEIDS(CDemo42Ctrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDemo42Ctrl, "DEMO42.Demo42Ctrl.1",
	0xb18d5923, 0x3101, 0x11d0, 0x90, 0x6f, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CDemo42Ctrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DDemo42 =
		{ 0xb18d5921, 0x3101, 0x11d0, { 0x90, 0x6f, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c } };
const IID BASED_CODE IID_DDemo42Events =
		{ 0xb18d5922, 0x3101, 0x11d0, { 0x90, 0x6f, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwDemo42OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CDemo42Ctrl, IDS_DEMO42, _dwDemo42OleMisc)


/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl::CDemo42CtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CDemo42Ctrl

BOOL CDemo42Ctrl::CDemo42CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_DEMO42,
			IDB_DEMO42,
			afxRegApartmentThreading,
			_dwDemo42OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl::CDemo42Ctrl - Constructor

CDemo42Ctrl::CDemo42Ctrl()
{
	InitializeIIDs(&IID_DDemo42, &IID_DDemo42Events);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl::~CDemo42Ctrl - Destructor

CDemo42Ctrl::~CDemo42Ctrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl::OnDraw - Drawing function

void CDemo42Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	char out [256] ;
	wsprintf (out, "MFC V4.2\nThread ID == 0x%x", GetCurrentThreadId( )) ;
	pdc->DrawText (out, -1, (LPRECT) &rcBounds, DT_CENTER) ;
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl::DoPropExchange - Persistence support

void CDemo42Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl::OnResetState - Reset control to default state

void CDemo42Ctrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl::AboutBox - Display an "About" box to the user

void CDemo42Ctrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_DEMO42);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42Ctrl message handlers
