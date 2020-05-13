// Demo42Ppg.cpp : Implementation of the CDemo42PropPage property page class.

#include "stdafx.h"
#include "demo42.h"
#include "Demo42Ppg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDemo42PropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDemo42PropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CDemo42PropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDemo42PropPage, "DEMO42.Demo42PropPage.1",
	0xb18d5924, 0x3101, 0x11d0, 0x90, 0x6f, 0, 0x60, 0x8c, 0x86, 0xb8, 0x9c)


/////////////////////////////////////////////////////////////////////////////
// CDemo42PropPage::CDemo42PropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CDemo42PropPage

BOOL CDemo42PropPage::CDemo42PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DEMO42_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42PropPage::CDemo42PropPage - Constructor

CDemo42PropPage::CDemo42PropPage() :
	COlePropertyPage(IDD, IDS_DEMO42_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CDemo42PropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42PropPage::DoDataExchange - Moves data between page and properties

void CDemo42PropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CDemo42PropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CDemo42PropPage message handlers
