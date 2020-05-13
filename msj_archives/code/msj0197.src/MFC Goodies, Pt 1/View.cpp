////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#include "StdAfx.h"
#include "DibView.h"
#include "Doc.h"
#include "View.h"
#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDIBView, CScrollView)

BEGIN_MESSAGE_MAP(CDIBView, CScrollView)
	ON_COMMAND(ID_VIEW_DITHER, OnDither)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DITHER, OnUpdateDither)
	ON_WM_SETFOCUS()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
END_MESSAGE_MAP()

CDIBView::CDIBView()
{
	m_bDither = TRUE;
}

CDIBView::~CDIBView()
{
}

//////////////////
// Get the DIB. Duh.
//
CDib* CDIBView::GetDIB()
{
	CDIBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDib* pDIB = pDoc->GetDIB();
	ASSERT_VALID(pDIB);
	return pDIB->m_hObject ? pDIB : NULL;
}

//////////////////
// Initial update: set scroll sizes.
//
void CDIBView::OnInitialUpdate()
{
	TRACE("CDIBView::OnInitialUpdate\n");
	CScrollView::OnInitialUpdate();
	CDib* pDIB = GetDIB();
	SetScrollSizes(MM_TEXT, pDIB ? pDIB->GetSize() : CSize(100,100));
	DoRealizePalette(TRUE);
}

//////////////////
// Draw the bitmap. Be careful to specify foreground/background.
//
void CDIBView::OnDraw(CDC* pDC)
{
	CDib* pDIB = GetDIB();
	if (pDIB)
		pDIB->Draw(*pDC, NULL, NULL, m_bDither);
}

//////////////////
// Dithering command
//
void CDIBView::OnDither()
{
	m_bDither = ! m_bDither;
	Invalidate();
}

void CDIBView::OnUpdateDither(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bDither);
}

//////////////////
// Palette changed: 
// If not because of me, realize the palette in background.
//
void CDIBView::OnPaletteChanged(CWnd* pFocusWnd)
{
	TRACEFN("%s::OnPaletteChanged(from %s)\n",
		DbgName(this), DbgName(pFocusWnd));

	if (pFocusWnd!=this) {
		DoRealizePalette(FALSE);
	} else {
		TRACE0("[It's me, don't realize palette]\n");
	}
}

////////////////
// Realize my palette.
//
int CDIBView::DoRealizePalette(BOOL bForeground)
{
	TRACEFN("%s::DoRealizePalette(%s)\n", DbgName(this),
		bForeground ? "foreground" : "background");

	CDib* pDIB = GetDIB();
	if (!pDIB)
		return 0;

	// Selet palette into client DC and realize it
	CClientDC dc = this;
	CPalette* pPal = pDIB->GetPalette();
	CPalette* pOldPal = dc.SelectPalette(pPal, !bForeground);
	UINT nColorsChanged = dc.RealizePalette();
	if (nColorsChanged > 0)
		Invalidate(FALSE);	// tell Windows to repaint
	if (pOldPal)
		dc.SelectPalette(pOldPal, TRUE);
	TRACE("%d colors changed\n", nColorsChanged);
	return nColorsChanged;
}

////////////////
// Got WM_QUEYNEWPALETTE from parent frame: realize my palette.
// Normally, this message is only sent to top-level windows.
// Return num colors changed.
//
BOOL CDIBView::OnQueryNewPalette() 
{
	TRACEFN("%s::OnQueryNewPalette\n", DbgName(this));
	return DoRealizePalette(TRUE);
}

//////////////////
// View was activated: realize foreground palette.
//
void CDIBView::OnSetFocus(CWnd* pOldWnd)
{
	TRACE("CDIBView::OnSetFocus\n");
	CView::OnSetFocus(pOldWnd);
	DoRealizePalette(TRUE);
}
