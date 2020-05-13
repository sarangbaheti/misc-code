////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.2 on Windows 95
// See pform.cpp
// 
#include "stdafx.h"
#include "pform.h"
#include "doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
	//{{AFX_MSG_MAP(CMyDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyDoc::CMyDoc()
{
}

CMyDoc::~CMyDoc()
{
}

void CMyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
	} else {
	}
}
