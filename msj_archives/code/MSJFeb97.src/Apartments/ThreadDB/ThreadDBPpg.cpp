// ThreadDBPpg.cpp : Implementation of the CThreadDBPropPage property page class.

#include "stdafx.h"
#include "ThreadDB.h"
#include "ThreadDBPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CThreadDBPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CThreadDBPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CThreadDBPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CThreadDBPropPage, "THREADDB.ThreadDBPropPage.1",
	0x7bf3c964, 0x21d6, 0x11d0, 0xa7, 0x7f, 0, 0, 0, 0, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CThreadDBPropPage::CThreadDBPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CThreadDBPropPage

BOOL CThreadDBPropPage::CThreadDBPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_THREADDB_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBPropPage::CThreadDBPropPage - Constructor

CThreadDBPropPage::CThreadDBPropPage() :
	COlePropertyPage(IDD, IDS_THREADDB_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CThreadDBPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBPropPage::DoDataExchange - Moves data between page and properties

void CThreadDBPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CThreadDBPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CThreadDBPropPage message handlers
