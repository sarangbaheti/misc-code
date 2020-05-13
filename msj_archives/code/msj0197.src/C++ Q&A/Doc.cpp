////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See ShadeCap.cpp
// 
#include "StdAfx.h"
#include "ShadeCap.h"
#include "Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

CMyDoc::CMyDoc()
{
}

CMyDoc::~CMyDoc()
{
}

//////////////////
// Serialize text:: pass to edit view
//
void CMyDoc::Serialize(CArchive& ar)
{
	CEditView* pView = (CEditView*)m_viewList.GetHead();
	ASSERT_KINDOF(CEditView, pView);
	pView->SerializeRaw(ar);
}

//////////////////
// New document: clear edit view
//
BOOL CMyDoc::OnNewDocument()
{
	if (CDocument::OnNewDocument()) {
		CEditView* pView = (CEditView*)m_viewList.GetHead();
		ASSERT_KINDOF(CEditView, pView);
		pView->SetWindowText(NULL);
		return TRUE;
	}
	return FALSE;
}
