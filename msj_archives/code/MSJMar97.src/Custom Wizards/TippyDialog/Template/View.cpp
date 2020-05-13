// $$root$$View.cpp : implementation of the C$$Safe_root$$View class
//

#include "stdafx.h"
#include "$$root$$.h"

#include "$$root$$Doc.h"
#include "$$root$$View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View

IMPLEMENT_DYNCREATE(C$$Safe_root$$View, CView)

BEGIN_MESSAGE_MAP(C$$Safe_root$$View, CView)
	//{{AFX_MSG_MAP(C$$Safe_root$$View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View construction/destruction

C$$Safe_root$$View::C$$Safe_root$$View()
{
	// TODO: add construction code here

}

C$$Safe_root$$View::~C$$Safe_root$$View()
{
}

BOOL C$$Safe_root$$View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View drawing

void C$$Safe_root$$View::OnDraw(CDC* pDC)
{
	C$$Safe_root$$Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View printing

BOOL C$$Safe_root$$View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void C$$Safe_root$$View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void C$$Safe_root$$View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View diagnostics

#ifdef _DEBUG
void C$$Safe_root$$View::AssertValid() const
{
	CView::AssertValid();
}

void C$$Safe_root$$View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C$$Safe_root$$Doc* C$$Safe_root$$View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C$$Safe_root$$Doc)));
	return (C$$Safe_root$$Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View message handlers
