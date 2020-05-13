// BounceThreadPpg.cpp : Implementation of the CBounceThreadPropPage property page class.

#include "stdafx.h"
#include "BounceThread.h"
#include "BounceThreadPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CBounceThreadPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CBounceThreadPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CBounceThreadPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CBounceThreadPropPage, "BOUNCETHREAD.BounceThreadPropPage.1",
	0x7255dc24, 0x51d2, 0x11d0, 0x90, 0x8d, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c)


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadPropPage::CBounceThreadPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CBounceThreadPropPage

BOOL CBounceThreadPropPage::CBounceThreadPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_BOUNCETHREAD_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadPropPage::CBounceThreadPropPage - Constructor

CBounceThreadPropPage::CBounceThreadPropPage() :
	COlePropertyPage(IDD, IDS_BOUNCETHREAD_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CBounceThreadPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadPropPage::DoDataExchange - Moves data between page and properties

void CBounceThreadPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CBounceThreadPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CBounceThreadPropPage message handlers
