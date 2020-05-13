// Demo40Ctl.cpp : Implementation of the CDemo40Ctrl OLE control class.

#include "stdafx.h"
#include "demo40.h"
#include "Demo40Ctl.h"
#include "Demo40Ppg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDemo40Ctrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDemo40Ctrl, COleControl)
	//{{AFX_MSG_MAP(CDemo40Ctrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CDemo40Ctrl, COleControl)
	//{{AFX_DISPATCH_MAP(CDemo40Ctrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CDemo40Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CDemo40Ctrl, COleControl)
	//{{AFX_EVENT_MAP(CDemo40Ctrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CDemo40Ctrl, 1)
	PROPPAGEID(CDemo40PropPage::guid)
END_PROPPAGEIDS(CDemo40Ctrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDemo40Ctrl, "DEMO40.Demo40Ctrl.1",
	0x3f4a8894, 0x30dd, 0x11d0, 0x90, 0x6d, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CDemo40Ctrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DDemo40 =
		{ 0x3f4a8892, 0x30dd, 0x11d0, { 0x90, 0x6d, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c } };
const IID BASED_CODE IID_DDemo40Events =
		{ 0x3f4a8893, 0x30dd, 0x11d0, { 0x90, 0x6d, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwDemo40OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CDemo40Ctrl, IDS_DEMO40, _dwDemo40OleMisc)


/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl::CDemo40CtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CDemo40Ctrl

BOOL CDemo40Ctrl::CDemo40CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_DEMO40,
			IDB_DEMO40,
			FALSE,                      //  Not insertable
			_dwDemo40OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl::CDemo40Ctrl - Constructor

CDemo40Ctrl::CDemo40Ctrl()
{
	InitializeIIDs(&IID_DDemo40, &IID_DDemo40Events);
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl::~CDemo40Ctrl - Destructor

CDemo40Ctrl::~CDemo40Ctrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl::OnDraw - Drawing function

void CDemo40Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));

	char out [256] ;
	wsprintf (out, "MFC V4.0\nThread ID == 0x%x", GetCurrentThreadId( )) ;
	pdc->DrawText (out, -1, (LPRECT) &rcBounds, DT_CENTER) ;
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl::DoPropExchange - Persistence support

void CDemo40Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl::OnResetState - Reset control to default state

void CDemo40Ctrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl::AboutBox - Display an "About" box to the user

void CDemo40Ctrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_DEMO40);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40Ctrl message handlers
