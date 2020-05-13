// WebButtonPpg.cpp : Implementation of the CWebButtonPropPage property page class.

#include "stdafx.h"
#include "WebButton.h"
#include "WebButtonPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWebButtonPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWebButtonPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CWebButtonPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWebButtonPropPage, "WEBBUTTON.WebButtonPropPage.1",
	0x381c5024, 0x2fda, 0x11d0, 0x8b, 0xc1, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CWebButtonPropPage::CWebButtonPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CWebButtonPropPage

BOOL CWebButtonPropPage::CWebButtonPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_WEBBUTTON_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonPropPage::CWebButtonPropPage - Constructor

CWebButtonPropPage::CWebButtonPropPage() :
	COlePropertyPage(IDD, IDS_WEBBUTTON_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CWebButtonPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonPropPage::DoDataExchange - Moves data between page and properties

void CWebButtonPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CWebButtonPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonPropPage message handlers
