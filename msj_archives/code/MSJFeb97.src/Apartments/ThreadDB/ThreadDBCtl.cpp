// ThreadDBCtl.cpp : Implementation of the CThreadDBCtrl OLE control class.

#include "stdafx.h"
#include "ThreadDB.h"
#include "ThreadDBCtl.h"
#include "ThreadDBPpg.h"
#include "searchthread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CThreadDBCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CThreadDBCtrl, COleControl)
	//{{AFX_MSG_MAP(CThreadDBCtrl)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CThreadDBCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CThreadDBCtrl)
	DISP_FUNCTION(CThreadDBCtrl, "StartSearch", StartSearch, VT_BOOL, VTS_I4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CThreadDBCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CThreadDBCtrl, COleControl)
	//{{AFX_EVENT_MAP(CThreadDBCtrl)
	EVENT_CUSTOM("SearchFinished", FireSearchFinished, VTS_DISPATCH)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CThreadDBCtrl, 1)
	PROPPAGEID(CThreadDBPropPage::guid)
END_PROPPAGEIDS(CThreadDBCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CThreadDBCtrl, "THREADDB.ThreadDBCtrl.1",
	0x7bf3c963, 0x21d6, 0x11d0, 0xa7, 0x7f, 0, 0, 0, 0, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CThreadDBCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DThreadDB =
		{ 0x7bf3c961, 0x21d6, 0x11d0, { 0xa7, 0x7f, 0, 0, 0, 0, 0, 0 } };
const IID BASED_CODE IID_DThreadDBEvents =
		{ 0x7bf3c962, 0x21d6, 0x11d0, { 0xa7, 0x7f, 0, 0, 0, 0, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwThreadDBOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CThreadDBCtrl, IDS_THREADDB, _dwThreadDBOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl::CThreadDBCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CThreadDBCtrl

BOOL CThreadDBCtrl::CThreadDBCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_THREADDB,
			IDB_THREADDB,
			afxRegApartmentThreading,
			_dwThreadDBOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl::CThreadDBCtrl - Constructor

CThreadDBCtrl::CThreadDBCtrl()
{
	InitializeIIDs(&IID_DThreadDB, &IID_DThreadDBEvents);

	m_pSearchThread = NULL ;
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl::~CThreadDBCtrl - Destructor

CThreadDBCtrl::~CThreadDBCtrl()
{
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl::OnDraw - Drawing function

void CThreadDBCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
	pdc->DrawText ("Thread DB", -1, (LPRECT) &rcBounds, DT_CENTER | DT_VCENTER | DT_SINGLELINE) ;
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl::DoPropExchange - Persistence support

void CThreadDBCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl::OnResetState - Reset control to default state

void CThreadDBCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl::AboutBox - Display an "About" box to the user

void CThreadDBCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_THREADDB);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBCtrl message handlers

BOOL CThreadDBCtrl::StartSearch(long SocialSecurityNumber) 
{
/*
Create thread object in suspended state. Set member variables.
*/
	m_pSearchThread = (CSearchThread *) AfxBeginThread (
		RUNTIME_CLASS (CSearchThread),
		THREAD_PRIORITY_NORMAL, 0, 
		CREATE_SUSPENDED) ;

	m_pSearchThread->m_pCtrl = this ;
	m_pSearchThread->m_ssn = SocialSecurityNumber ;

/*
Find all the event IDispatch interface pointers and marshal them to the thread.
*/

	IDispatch * pDispatch; 	IStream *	pStream ; 	HRESULT hr ;
	POSITION pos = m_xEventConnPt.GetStartPosition();

	while (pos != NULL)
	{
/*
Get next IDispatch in connection point's list.
*/
		pDispatch = (LPDISPATCH)m_xEventConnPt.GetNextConnection(pos);
		
/*
Create stream for marshaling IDispatch to search thread.
*/
		hr = CoMarshalInterThreadInterfaceInStream(
			IID_IDispatch,	// interface ID to marshal
			pDispatch,		// ptr to interface to marshal
			&pStream) ;		// output variable

		if (hr != S_OK)
		{
			AfxMessageBox ("Couldn't marshal ptr to thread") ;
		}
/*
Place stream in member variable where search thread will look for it.
*/
		m_pSearchThread->m_StreamArray.Add (pStream) ;
	}

/*
Allow thread to resume running now that we have initialized
all of its member variables. 
*/

	m_pSearchThread->ResumeThread ( ) ;
	return TRUE;
}

