// DTDemoDoc.cpp : implementation of the CDTDemoDoc class
//

#include "stdafx.h"
#include "DTDemo.h"

#include "DTDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDTDemoDoc

IMPLEMENT_DYNCREATE(CDTDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDTDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDTDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTDemoDoc construction/destruction

CDTDemoDoc::CDTDemoDoc()
{
	// Initialize all the circles in the array.
	::srand((unsigned)time(NULL));
	int n = 0;
	const int nWidth = 600;
	const int nHeight = 400;
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 10, RGB(128, 0, 0));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 20, RGB(0, 128, 0));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 30, RGB(0, 0, 128));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 40, RGB(192, 192, 192));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 50, RGB(255, 0, 255));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 60, RGB(0, 255, 255));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 70, RGB(255, 255, 0));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 80, RGB(255, 0, 0));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 90, RGB(0, 255, 0));
	m_CircleArray[n++].Initialize(
		CPoint(rand() % nWidth, rand() % nHeight), 100, RGB(0, 0, 255));
	ASSERT(n == CIRCLECOUNT);
}

CDTDemoDoc::~CDTDemoDoc()
{
}

BOOL CDTDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDTDemoDoc serialization

void CDTDemoDoc::Serialize(CArchive& ar)
{
	ASSERT(0);
}

/////////////////////////////////////////////////////////////////////////////
// CDTDemoDoc diagnostics

#ifdef _DEBUG
void CDTDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDTDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDTDemoDoc commands
