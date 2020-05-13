////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#include "StdAfx.h"
#include "DibView.h"
#include "Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDIBDoc, CDocument)

BEGIN_MESSAGE_MAP(CDIBDoc, CDocument)
END_MESSAGE_MAP()

CDIBDoc::CDIBDoc()
{
}

CDIBDoc::~CDIBDoc()
{
}

//////////////////
// Override to load bitmap directly instead of doing serialization stuff.
//
BOOL CDIBDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	DeleteContents();
	return m_dib.Load(lpszPathName);
}

//////////////////
// Delete contents of doc: delete the DIB
//
void CDIBDoc::DeleteContents()
{
	m_dib.DeleteObject();
}
