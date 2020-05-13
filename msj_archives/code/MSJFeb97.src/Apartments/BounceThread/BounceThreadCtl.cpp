// BounceThreadCtl.cpp : Implementation of the CBounceThreadCtrl OLE control class.

#include "stdafx.h"
#include "bounceth.h"
#include "BounceThread.h"
#include "BounceThreadCtl.h"
#include "BounceThreadPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL g_Beep = FALSE ;
DWORD NextBeepTime ;

IMPLEMENT_DYNCREATE(CBounceThreadCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CBounceThreadCtrl, COleControl)
	//{{AFX_MSG_MAP(CBounceThreadCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_BEEPEVERYSECOND, OnPopupBeepeverysecond)
	ON_UPDATE_COMMAND_UI(ID_POPUP_BEEPEVERYSECOND, OnUpdatePopupBeepeverysecond)
	ON_COMMAND(ID_POPUP_PRIORITY_ABOVE, OnPopupPriorityAbove)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PRIORITY_ABOVE, OnUpdatePopupPriorityAbove)
	ON_COMMAND(ID_POPUP_PRIORITY_BELOW, OnPopupPriorityBelow)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PRIORITY_BELOW, OnUpdatePopupPriorityBelow)
	ON_COMMAND(ID_POPUP_PRIORITY_HIGHEST, OnPopupPriorityHighest)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PRIORITY_HIGHEST, OnUpdatePopupPriorityHighest)
	ON_COMMAND(ID_POPUP_PRIORITY_IDLE, OnPopupPriorityIdle)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PRIORITY_IDLE, OnUpdatePopupPriorityIdle)
	ON_COMMAND(ID_POPUP_PRIORITY_LOWEST, OnPopupPriorityLowest)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PRIORITY_LOWEST, OnUpdatePopupPriorityLowest)
	ON_COMMAND(ID_POPUP_PRIORITY_NORMAL, OnPopupPriorityNormal)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PRIORITY_NORMAL, OnUpdatePopupPriorityNormal)
	ON_COMMAND(ID_POPUP_PRIORITY_TIMECRITICAL, OnPopupPriorityTimecritical)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PRIORITY_TIMECRITICAL, OnUpdatePopupPriorityTimecritical)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CBounceThreadCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CBounceThreadCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CBounceThreadCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CBounceThreadCtrl, COleControl)
	//{{AFX_EVENT_MAP(CBounceThreadCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CBounceThreadCtrl, 1)
	PROPPAGEID(CBounceThreadPropPage::guid)
END_PROPPAGEIDS(CBounceThreadCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CBounceThreadCtrl, "BOUNCETHREAD.BounceThreadCtrl.1",
	0x7255dc23, 0x51d2, 0x11d0, 0x90, 0x8d, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CBounceThreadCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DBounceThread =
		{ 0x7255dc21, 0x51d2, 0x11d0, { 0x90, 0x8d, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c } };
const IID BASED_CODE IID_DBounceThreadEvents =
		{ 0x7255dc22, 0x51d2, 0x11d0, { 0x90, 0x8d, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwBounceThreadOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CBounceThreadCtrl, IDS_BOUNCETHREAD, _dwBounceThreadOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl::CBounceThreadCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CBounceThreadCtrl

BOOL CBounceThreadCtrl::CBounceThreadCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_BOUNCETHREAD,
			IDB_BOUNCETHREAD,
			afxRegApartmentThreading,
			_dwBounceThreadOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl::CBounceThreadCtrl - Constructor

CBounceThreadCtrl::CBounceThreadCtrl()
{
	InitializeIIDs(&IID_DBounceThread, &IID_DBounceThreadEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl::~CBounceThreadCtrl - Destructor

CBounceThreadCtrl::~CBounceThreadCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl::OnDraw - Drawing function

void CBounceThreadCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl::DoPropExchange - Persistence support

void CBounceThreadCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl::OnResetState - Reset control to default state

void CBounceThreadCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl::AboutBox - Display an "About" box to the user

void CBounceThreadCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_BOUNCETHREAD);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadCtrl message handlers

int CBounceThreadCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	m_pThread = (CBounceThread *)AfxBeginThread (
		RUNTIME_CLASS(CBounceThread), 
		THREAD_PRIORITY_LOWEST, 
		0, 
		CREATE_SUSPENDED) ;

	m_pThread->m_pControl = this ;

/*
Resume the thread, allowing it to run
*/
  	m_pThread->ResumeThread( ) ;	
	return 0;
}

void CBounceThreadCtrl::OnDestroy() 
{
	COleControl::OnDestroy();
	
	m_pThread->PostThreadMessage(WM_QUIT, 0, 0) ;
	m_pThread->SetThreadPriority(THREAD_PRIORITY_TIME_CRITICAL) ;

	WaitForSingleObject (m_pThread->m_hThread, INFINITE) ;
// CloseHandle done in destructor
	
}

void CBounceThreadCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
		CMenu menu ;
	menu.LoadMenu (IDR_MENU1) ;

	CMenu *pPopup = menu.GetSubMenu (0) ;
	pPopup->TrackPopupMenu (
		TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_LEFTBUTTON,
		point.x, point.y, this, NULL) ;

	
}

void CBounceThreadCtrl::OnPopupBeepeverysecond( ) 
{
	g_Beep = !g_Beep ;	

	if (g_Beep == TRUE)
	{
		NextBeepTime = GetTickCount( ) + 1000 ;
	}
}

void CBounceThreadCtrl::OnUpdatePopupBeepeverysecond(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (g_Beep) ;	
}

void CBounceThreadCtrl::OnPopupPriorityTimecritical() 
{
	m_pThread->SetThreadPriority (THREAD_PRIORITY_TIME_CRITICAL) ;
}

void CBounceThreadCtrl::OnUpdatePopupPriorityTimecritical(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (m_pThread->GetThreadPriority( ) == THREAD_PRIORITY_TIME_CRITICAL) ;
}

void CBounceThreadCtrl::OnPopupPriorityHighest() 
{
	m_pThread->SetThreadPriority (THREAD_PRIORITY_HIGHEST) ;
}

void CBounceThreadCtrl::OnUpdatePopupPriorityHighest(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (m_pThread->GetThreadPriority( ) == THREAD_PRIORITY_HIGHEST) ;
}

void CBounceThreadCtrl::OnPopupPriorityAbove() 
{
	m_pThread->SetThreadPriority (THREAD_PRIORITY_ABOVE_NORMAL) ;
}

void CBounceThreadCtrl::OnUpdatePopupPriorityAbove(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (m_pThread->GetThreadPriority( ) == THREAD_PRIORITY_ABOVE_NORMAL) ;
}

void CBounceThreadCtrl::OnPopupPriorityNormal() 
{
	m_pThread->SetThreadPriority (THREAD_PRIORITY_NORMAL) ;
}

void CBounceThreadCtrl::OnUpdatePopupPriorityNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (m_pThread->GetThreadPriority( ) == THREAD_PRIORITY_NORMAL) ;
}

void CBounceThreadCtrl::OnPopupPriorityBelow() 
{
	m_pThread->SetThreadPriority (THREAD_PRIORITY_BELOW_NORMAL) ;
}

void CBounceThreadCtrl::OnUpdatePopupPriorityBelow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (m_pThread->GetThreadPriority( ) == THREAD_PRIORITY_BELOW_NORMAL) ;
}

void CBounceThreadCtrl::OnPopupPriorityLowest() 
{
	m_pThread->SetThreadPriority (THREAD_PRIORITY_LOWEST) ;
}

void CBounceThreadCtrl::OnUpdatePopupPriorityLowest(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (m_pThread->GetThreadPriority( ) == THREAD_PRIORITY_LOWEST) ;
}

void CBounceThreadCtrl::OnPopupPriorityIdle() 
{
	m_pThread->SetThreadPriority (THREAD_PRIORITY_IDLE) ;
}

void CBounceThreadCtrl::OnUpdatePopupPriorityIdle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (m_pThread->GetThreadPriority( ) == THREAD_PRIORITY_IDLE) ;
}
