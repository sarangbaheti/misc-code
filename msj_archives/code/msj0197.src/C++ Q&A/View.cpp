////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See ShadeCap.cpp
// 
#include "StdAfx.h"
#include "ShadeCap.h"
#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyView, CEditView)

BEGIN_MESSAGE_MAP(CMyView, CEditView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyView::CMyView()
{
}

CMyView::~CMyView()
{
}

int CMyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct)==-1)
		return -1;
	m_font.CreatePointFont(110, "Arial"); // 11 pt
	GetEditCtrl().SetFont(&m_font);
	return 0;
}
