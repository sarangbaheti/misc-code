// formsView.cpp : implementation of the CFormsView class
//

#include "stdafx.h"
#include "formapp.h"
#include "text.h"

#include "formsDoc.h"
#include "formview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormsView

IMPLEMENT_DYNCREATE(CFormsView, CView)

BEGIN_MESSAGE_MAP(CFormsView, CView)
	//{{AFX_MSG_MAP(CFormsView)
	ON_COMMAND(ID_TEST, OnTest)
	ON_COMMAND(ID_REPORT, OnReport)
	ON_COMMAND(ID_MODIFY_STRING, OnModifyString)
	ON_COMMAND(ID_MODIFY_CTRL, OnModifyCtrl)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormsView construction/destruction

CFormsView::CFormsView()
{
	// TODO: add construction code here

}

CFormsView::~CFormsView()
{
}

BOOL CFormsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFormsView drawing

void CFormsView::OnDraw(CDC* pDC)
{
	CFormsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFormsView printing

BOOL CFormsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFormsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFormsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFormsView diagnostics

#ifdef _DEBUG
void CFormsView::AssertValid() const
{
	CView::AssertValid();
}

void CFormsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFormsDoc* CFormsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFormsDoc)));
	return (CFormsDoc*)m_pDocument;
}
#endif //_DEBUG

