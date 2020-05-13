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
#include "FontUI.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const TCHAR SETTINGS[] = _T("Settings");

IMPLEMENT_DYNCREATE(CDIBView, CScrollView)

BEGIN_MESSAGE_MAP(CDIBView, CScrollView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_COMMAND(ID_FILE_PRINT,			OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_VIEW_DITHER,			OnDither)
	ON_COMMAND(ID_VIEW_SIZE_TO_FIT,  OnSizeToFit)
	ON_COMMAND_RANGE(ID_VIEW_FONT,	ID_VIEW_FONT_BIGGER, OnFontChange)
	ON_COMMAND_RANGE(ID_ZOOM_4TH,		ID_ZOOM_4X,				OnZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DITHER,						OnUpdateDither)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ZOOM_4TH, ID_ZOOM_4X,	OnUpdateZoom)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT,							OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_DIRECT,				OnUpdatePrint)
END_MESSAGE_MAP()

CFont CDIBView::g_font;

CDIBView::CDIBView()
{
	if (!g_font.m_hObject) {
		// Restore font from profile
		if (!CFontUI().GetProfileFont(SETTINGS, "Font", g_font)) {
			// Use 8pt Courier (monospace) default
			g_font.CreatePointFont(100,"Courier");
		}
	}
	m_iZoom=0;
	m_bSized=FALSE;
	m_bUseDrawDib = AfxGetApp()->GetProfileInt(SETTINGS, "Dither", 1);
}

CDIBView::~CDIBView()
{
	CFontUI().WriteProfileFont(SETTINGS, "Font", g_font);
	AfxGetApp()->WriteProfileInt(SETTINGS, "Dither", m_bUseDrawDib);
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
	TRACEFN("CDIBView::OnInitialUpdate\n");
	CScrollView::OnInitialUpdate();

	// Compute size/position of text rectangle
	UpdateScrollSizes();

	CDib* pDIB = GetDIB();
	if (pDIB) {
		if (!m_palMsgHandler.IsHooked())
			m_palMsgHandler.Install(this, pDIB->GetPalette());

		// The following line is required because MFC does not send
		// WM_INITIALUPDATE through normal channels. Only realize in
		// foreground if I have the focus (could be updating all views
		// from OnFontChange)
		//
		m_palMsgHandler.DoRealizePalette(m_hWnd==::GetFocus());
		
		if (!m_bSized) {
			// size window perfectly around frame
			GetParentFrame()->RecalcLayout();
			OnSizeToFit();
			m_bSized=TRUE;
		}
	}
}

//////////////////
// Compute scroll sizes based on new font/image
//
void CDIBView::UpdateScrollSizes()
{
	m_rcDIB.SetRectEmpty();
	m_rcText.SetRectEmpty();

	CDib* pDIB = GetDIB();
	if (!pDIB) {
		SetScrollSizes(MM_TEXT, CSize(100,100));
		return;
	}

	// Adjust DIB rectangle by current zoom factor
	m_rcDIB = CRect(CPoint(0,0), pDIB->GetSize());
	if (m_iZoom>0) {
		m_rcDIB.right  <<= m_iZoom;
		m_rcDIB.bottom <<= m_iZoom;
	} else if (m_iZoom<0) {
		m_rcDIB.right  >>= -m_iZoom;
		m_rcDIB.bottom >>= -m_iZoom;		
	}

	// Compute text rectangle
	CClientDC dc(this);
	int w = m_rcDIB.Width();
	int h = m_rcDIB.Height();
	m_rcText.SetRect(0, h, w, h);
	DrawBITMAPHEADER(dc, pDIB, m_rcText, DT_CALCRECT);

	// Total width is max of bitmap, text
	if (w > m_rcText.right)
		m_rcText.right = w;

	SetScrollSizes(MM_TEXT, CSize(m_rcText.right, m_rcText.bottom));
}

//////////////////
// Draw the bitmap. Be careful to specify foreground/background.
// Following bitmap, display fields in BITMAPINFOHEADER
//
void CDIBView::OnDraw(CDC* pDC)
{
	CDib* pDIB = GetDIB();
	if (pDIB) {
		pDIB->Draw(*pDC, &m_rcDIB, NULL, m_bUseDrawDib);
		DrawBITMAPHEADER(*pDC, pDIB, m_rcText);
	}
}

//////////////////
// Helper fn to draw the formatted BITMAPINFOHEADER text.
// Because Windows is so brain damaged, this requires manually
// outputting each line with TabbedTextOut. DrawText is what I would ideally
// use here, but Windows doesn't let you use DT_CALCRECT and DT_TABSTOP at
// the same time. I need both, because I'm setting a custom tab stop to make
// my text align, but also need to calculate the size of the text in advance
// so I can set my scroll ranges.
//
void CDIBView::DrawBITMAPHEADER(CDC& dc, CDib* pDIB,
	CRect& rc, UINT nFormat)
{
	DIBSECTION ds;
	VERIFY(pDIB->GetObject(sizeof(ds), &ds)==sizeof(ds));
	const BITMAPINFOHEADER& bmi = ds.dsBmih;

	// Format BITMAPINFOHEADER into a string
	CString sCompression="none";
	if (bmi.biCompression)
		sCompression.Format("0x%04x",bmi.biCompression);
	CString buf, text = "BITMAPINFOHEADER:\n";
	buf.Format(" biSize\t= %ld\n",			bmi.biSize);			text += buf;
	buf.Format(" biWidth\t= %ld\n",			bmi.biWidth);			text += buf;
	buf.Format(" biHeight\t= %ld\n",			bmi.biHeight);			text += buf;
	buf.Format(" biPlanes\t= %d\n",			bmi.biPlanes);			text += buf;
	buf.Format(" biBitCount\t= %d\n",		bmi.biBitCount);		text += buf;
	buf.Format(" biCompression\t= %s\n",	sCompression);			text += buf;
	buf.Format(" biSizeImage\t= %ld\n",		bmi.biSizeImage);		text += buf;
	buf.Format(" biXPelsPerMeter\t= %ld\n",bmi.biXPelsPerMeter);text += buf;
	buf.Format(" biYPelsPerMeter\t= %ld\n",bmi.biYPelsPerMeter);text += buf;
	buf.Format(" biClrUsed\t= %ld\n",		bmi.biClrUsed);		text += buf;
	buf.Format(" biClrImportant\t= %ld",	bmi.biClrImportant);	text += buf;

	// Now draw it using current font
	CFont *pOldFont = dc.SelectObject(&g_font);	// select my font
	DRAWTEXTPARAMS dtp;
	memset(&dtp,0,sizeof(dtp));
	dtp.cbSize = sizeof(dtp); // size of struct
	dtp.iTabLength = 20;		  // avg 20 chars per tab
	DrawTextEx(dc, (TCHAR*)(LPCTSTR)text, -1, &rc,
		nFormat|DT_EXPANDTABS|DT_TABSTOP, &dtp);
	dc.SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// Standard printing stuff
//
BOOL CDIBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	PRINTDLG& pd = pInfo->m_pPD->m_pd;
	pd.Flags |= PD_NOPAGENUMS;
	if (!DoPreparePrinting(pInfo))
		return FALSE;
	if (!GetDeviceCaps(pd.hDC, RASTERCAPS) & RC_BITBLT) {
		MessageBox("Sorry, this printer does not support bitmaps.",
			"DIBVIEW",MB_OK);
		return FALSE;
	}
	return TRUE;
}

//////////////////
// Print the bitmap. This would be the same as drawing it, but must scale
// the size to be true WYSIWYG
//
void CDIBView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CDib* pDIB = GetDIB();
	if (!pDIB)
		return;

	// save stuff
	CRect rcDIB  = m_rcDIB;
	CRect rcText = m_rcText;

	// Convert display resolution to printer resolution
	CClientDC dcScreen(this);
	CDC& dcPrinter = *pDC;
	CSize sz = pDIB->GetSize();
	int w = MulDiv(sz.cx, dcPrinter.GetDeviceCaps(LOGPIXELSX),
		dcScreen.GetDeviceCaps(LOGPIXELSX));
	int h = MulDiv(sz.cy, dcPrinter.GetDeviceCaps(LOGPIXELSY),
		dcScreen.GetDeviceCaps(LOGPIXELSY));

	// Compute new image, text rectangles
	m_rcDIB.SetRect(0,0,w,h);				 // use new rectangle
	m_rcText.SetRect(0, h, w, h);			 // approx

	// Convert font to printer device units
	CFontUI fui;
	int pts = fui.GetFontPointSize(g_font, dcScreen);
	fui.SetFontPointSize(g_font, dcPrinter, pts);
	DrawBITMAPHEADER(dcPrinter, pDIB, m_rcText, DT_CALCRECT);

	// Draw with new rects and font
	OnDraw(pDC);

	// Restore everthing to original
	fui.SetFontPointSize(g_font, dcScreen, pts);
	m_rcDIB  = rcDIB;
	m_rcText = rcText;
}

void CDIBView::OnUpdatePrint(CCmdUI* pCmdUI)
{
	// Only enable printing if I have a DIB (for SDI app)
	pCmdUI->Enable(GetDIB()!=NULL);
}

//////////////////
// Dithering command
//
void CDIBView::OnDither()
{
	m_bUseDrawDib = ! m_bUseDrawDib;
	Invalidate();
}

void CDIBView::OnUpdateDither(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bUseDrawDib);
}

//////////////////
// Double-clicking zooms the image: left button=bigger; right=smaller.
// Double-clicking in the text area invokes Font dialog.
//
void CDIBView::OnLButtonDblClk(UINT nFlags, CPoint pt)
{
	pt += GetScrollPosition();
	if (m_rcDIB.PtInRect(pt))
		SetZoom(m_iZoom + 1);
	else if (m_rcText.PtInRect(pt))
		OnFontChange(ID_VIEW_FONT);
}

void CDIBView::OnRButtonDblClk(UINT nFlags, CPoint pt)
{
	pt += GetScrollPosition();
	if (m_rcDIB.PtInRect(pt))
		SetZoom(m_iZoom - 1);
	else if (m_rcText.PtInRect(pt))
		OnFontChange(ID_VIEW_FONT);
}

//////////////////
// Zoom (magnify) command
//
void CDIBView::OnZoom(UINT nID)
{
	SetZoom(m_iZoom = nID-ID_ZOOM_NORMAL);
}

void CDIBView::OnUpdateZoom(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(((int)pCmdUI->m_nID)==ID_ZOOM_NORMAL+m_iZoom);
}

void CDIBView::SetZoom(int iZoom)
{
	if (-2<=iZoom && iZoom<=2) {
		m_iZoom = iZoom;
		UpdateScrollSizes();
		Invalidate();
	}
}

//////////////////
// Szie To Fit command
//
void CDIBView::OnSizeToFit()
{
	ResizeParentToFit(FALSE);

	// MFC might have grown the window off the screen--I'll fix it
	CRect rc, rcMax;
	CFrameWnd* pFrame = GetParentFrame();
	ASSERT_VALID(pFrame);
	pFrame->GetWindowRect(&rc);
	CWnd* pGrandParent = pFrame->GetParent();
	if (pGrandParent) {
		// use top level window as maximum rectangle
		pGrandParent->ScreenToClient(&rc);
		pGrandParent->GetClientRect(&rcMax);
	} else {
		// use whole screen as maximum rectangle
		rcMax.SetRect(0,0,GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN));
	}
	BOOL bTooBig = FALSE;
	if (rc.bottom > rcMax.bottom) {
		rc.bottom = rcMax.bottom;
		rc.right += GetSystemMetrics(SM_CXVSCROLL) +
			GetSystemMetrics(SM_CXBORDER);
		bTooBig = TRUE;
	}
	if (rc.right > rcMax.right) {
		rc.right = rcMax.right;
		bTooBig = TRUE;
	}
	if (bTooBig) {
		pFrame->SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height(),
			SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
	}
}

////////////////////////////////////////////////////////////////
// Handle font change (bigger/smaller/dialog)
//
void CDIBView::OnFontChange(UINT nID)
{
	CFontUI fui;
	if (fui.OnChangeFont(g_font,
		nID==ID_VIEW_FONT_BIGGER ? 1 : nID==ID_VIEW_FONT_SMALLER ? -1 : 0,
		this,
		CF_SCREENFONTS|CF_FORCEFONTEXIST)) {

		// For all views to recompute scroll sizes and repaint
		GetTopLevelFrame()->SendMessageToDescendants(WM_INITIALUPDATE);
	}
}
