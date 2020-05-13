#include "stdafx.h"
#include "cform.h"
#include "doc.h"
#include "view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyFormView, CFormView)


BEGIN_MESSAGE_MAP(CMyFormView, CView)
   //{{AFX_MSG_MAP(CMyFormView)
   ON_WM_CREATE()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyFormView::CMyFormView()
   : CFormView(CMyFormView::IDD)
{
   //{{AFX_DATA_INIT(CMyFormView)
      // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

CMyFormView::~CMyFormView()
{
}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
   CFormView::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CMyFormView)
   //}}AFX_DATA_MAP
}

int CMyFormView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if (CView::OnCreate(lpCreateStruct) == -1)
      return -1;
   
   return 0;
}

void CMyFormView::OnInitialUpdate() 
{
   CFormView::OnInitialUpdate();
   ModifyStyle(WS_BORDER, 0);
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
}
