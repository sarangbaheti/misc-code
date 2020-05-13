////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 5.0 on Windows 95
// 
#include "stdafx.h"
#include "doc.h"
#include "view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyView, CEditView)

BEGIN_MESSAGE_MAP(CMyView, CEditView)
END_MESSAGE_MAP()

CMyView::CMyView()
{
}

CMyView::~CMyView()
{
}

void CMyView::OnDraw(CDC* pDC)
{
}
