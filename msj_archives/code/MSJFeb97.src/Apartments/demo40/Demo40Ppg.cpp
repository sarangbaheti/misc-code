// Demo40Ppg.cpp : Implementation of the CDemo40PropPage property page class.

#include "stdafx.h"
#include "demo40.h"
#include "Demo40Ppg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDemo40PropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDemo40PropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CDemo40PropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDemo40PropPage, "DEMO40.Demo40PropPage.1",
	0x3f4a8895, 0x30dd, 0x11d0, 0x90, 0x6d, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c)


/////////////////////////////////////////////////////////////////////////////
// CDemo40PropPage::CDemo40PropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CDemo40PropPage

BOOL CDemo40PropPage::CDemo40PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DEMO40_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40PropPage::CDemo40PropPage - Constructor

CDemo40PropPage::CDemo40PropPage() :
	COlePropertyPage(IDD, IDS_DEMO40_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CDemo40PropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40PropPage::DoDataExchange - Moves data between page and properties

void CDemo40PropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CDemo40PropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CDemo40PropPage message handlers
