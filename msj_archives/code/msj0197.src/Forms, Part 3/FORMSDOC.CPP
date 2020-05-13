// formsDoc.cpp : implementation of the CFormsDoc class
//

#include "stdafx.h"
#include "formapp.h"

#include "formsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormsDoc

IMPLEMENT_DYNCREATE(CFormsDoc, CDocument)

BEGIN_MESSAGE_MAP(CFormsDoc, CDocument)
	//{{AFX_MSG_MAP(CFormsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormsDoc construction/destruction

CFormsDoc::CFormsDoc()
{
	// TODO: add one-time construction code here

}

CFormsDoc::~CFormsDoc()
{
}

BOOL CFormsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFormsDoc serialization

void CFormsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFormsDoc diagnostics

#ifdef _DEBUG
void CFormsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFormsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormsDoc commands
