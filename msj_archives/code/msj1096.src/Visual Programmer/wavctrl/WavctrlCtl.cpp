// WavctrlCtl.cpp : Implementation of the CWavctrlCtrl OLE control class.

#include "stdafx.h"
#include <mmsystem.h>
#include "wavctrl.h"
#include "WavctrlCtl.h"
#include "WavctrlPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWavctrlCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWavctrlCtrl, COleControl)
	//{{AFX_MSG_MAP(CWavctrlCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CWavctrlCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CWavctrlCtrl)
	DISP_FUNCTION(CWavctrlCtrl, "Play", Play, VT_EMPTY, VTS_BSTR)
	DISP_STOCKPROP_READYSTATE()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CWavctrlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CWavctrlCtrl, COleControl)
	//{{AFX_EVENT_MAP(CWavctrlCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	EVENT_STOCK_READYSTATECHANGE()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CWavctrlCtrl, 1)
	PROPPAGEID(CWavctrlPropPage::guid)
END_PROPPAGEIDS(CWavctrlCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWavctrlCtrl, "WAVCTRL.WavctrlCtrl.1",
	0x5bb5c4e3, 0xd723, 0x11cf, 0xa5, 0x21, 0, 0xa0, 0x24, 0xa6, 0x52, 0xfa)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CWavctrlCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DWavctrl =
		{ 0x5bb5c4e1, 0xd723, 0x11cf, { 0xa5, 0x21, 0, 0xa0, 0x24, 0xa6, 0x52, 0xfa } };
const IID BASED_CODE IID_DWavctrlEvents =
		{ 0x5bb5c4e2, 0xd723, 0x11cf, { 0xa5, 0x21, 0, 0xa0, 0x24, 0xa6, 0x52, 0xfa } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwWavctrlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CWavctrlCtrl, IDS_WAVCTRL, _dwWavctrlOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl::CWavctrlCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CWavctrlCtrl

BOOL CWavctrlCtrl::CWavctrlCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_WAVCTRL,
			IDB_WAVCTRL,
			afxRegApartmentThreading,
			_dwWavctrlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl::CWavctrlCtrl - Constructor

CWavctrlCtrl::CWavctrlCtrl()
{
	InitializeIIDs(&IID_DWavctrl, &IID_DWavctrlEvents);

	m_lReadyState = READYSTATE_LOADING;
	// TODO: Call InternalSetReadyState when the readystate changes.

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl::~CWavctrlCtrl - Destructor

CWavctrlCtrl::~CWavctrlCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl::OnDraw - Drawing function

void CWavctrlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_hWnd)
		ShowWindow(FALSE);
	

	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);

	if (!IsOptimizedDraw())
	{
		// The container does not support optimized drawing.

		// TODO: if you selected any GDI objects into the device context *pdc,
		//		restore the previously-selected objects here.
		//		For more information, please see MFC technical note #nnn,
		//		"Optimizing an ActiveX Control".
	}
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl::DoPropExchange - Persistence support

void CWavctrlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
// For information on using these flags, please see MFC technical note
// #nnn, "Optimizing an ActiveX Control".
DWORD CWavctrlCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control can activate without creating a window.
	// TODO: when writing the control's message handlers, avoid using
	//		the m_hWnd member variable without first checking that its
	//		value is non-NULL.
	dwFlags |= windowlessActivate;

	// The control can optimize its OnDraw method, by not restoring
	// the original GDI objects in the device context.
	dwFlags |= canOptimizeDraw;
	return dwFlags;
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl::OnResetState - Reset control to default state

void CWavctrlCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl::AboutBox - Display an "About" box to the user

void CWavctrlCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_WAVCTRL);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlCtrl message handlers

void CWavctrlCtrl::Play(LPCTSTR lpWAV) 
{
	::PlaySound(lpWAV, NULL, SND_FILENAME | SND_SYNC);
}
