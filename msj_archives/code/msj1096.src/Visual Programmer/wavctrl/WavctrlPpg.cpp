// WavctrlPpg.cpp : Implementation of the CWavctrlPropPage property page class.

#include "stdafx.h"
#include "wavctrl.h"
#include "WavctrlPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWavctrlPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWavctrlPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CWavctrlPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWavctrlPropPage, "WAVCTRL.WavctrlPropPage.1",
	0x5bb5c4e4, 0xd723, 0x11cf, 0xa5, 0x21, 0, 0xa0, 0x24, 0xa6, 0x52, 0xfa)


/////////////////////////////////////////////////////////////////////////////
// CWavctrlPropPage::CWavctrlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CWavctrlPropPage

BOOL CWavctrlPropPage::CWavctrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_WAVCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlPropPage::CWavctrlPropPage - Constructor

CWavctrlPropPage::CWavctrlPropPage() :
	COlePropertyPage(IDD, IDS_WAVCTRL_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CWavctrlPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlPropPage::DoDataExchange - Moves data between page and properties

void CWavctrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CWavctrlPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CWavctrlPropPage message handlers
