////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.1 on Windows 95
// See Virgil.cpp
// 
#include "StdAfx.h"
#include "Virgil.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_WHO, OnIndicatorWho)
	ON_NOTIFY( TTN_NEEDTEXT, 0, OnGetTooltipText)
	ON_COMMAND(ID_VIEW_MASK, OnViewMaskOrImage)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MASK, OnUpdateViewMaskOrImage)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR,        // status line indicator
	ID_INDICATOR_WHO		// "who" indicator
};

CMainFrame::CMainFrame()
{
	m_bViewMask = FALSE;
}

CMainFrame::~CMainFrame()
{
}

/////////////////
// Create main window. In addition to the usual stuff:
//
// - load image and mask bitmaps
// - set window size to be exactly same as bitmap
// - install palette message handler
// - enable tooltips
//
// Note: in order to make drawing simpler, so I don't have to calculate the
// client area each time, I created this window with no toolbar. There are
// no commands to put there anyway.
//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) {
		return -1;
	} 
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))) {
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Load image bitmap
	if (!m_dibImage.Load(AfxGetResourceHandle(), IDB_BITMAP)) {
		TRACE("*** Failed to load bitmap\n");
		return -1;
	}
	// Load mask bitmap
	if (!m_dibMask.Load(AfxGetResourceHandle(), IDB_BITMAPMASK)) {
		TRACE("*** Failed to load mask\n");
		return -1;
	}
	ASSERT(m_dibMask.GetSize() == m_dibImage.GetSize());

	// Readjust initial size
	MINMAXINFO mmi;
	OnGetMinMaxInfo(&mmi);
	SetWindowPos(NULL, 0, 0, mmi.ptMaxSize.x, mmi.ptMaxSize.y,
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);

	// Install palette message handler
	m_palMsgHandler.Install(this, m_dibImage.GetPalette());

	EnableToolTips();

	return 0;
}

//////////////////
// Paint function uses CDib to draw either image or mask
//
void CMainFrame::OnPaint() 
{
	CPaintDC dc(this);
	CDib* pDIB = m_bViewMask ? &m_dibMask : &m_dibImage;
	pDIB->Draw(dc);
}

////////////////
// Update "who" indicator. 
//
void CMainFrame::OnIndicatorWho(CCmdUI* pCmdUI) 
{
	CPoint pt;
	GetCursorPos(&pt);					// current mouse pos
	ScreenToClient(&pt);					// in client coords
	pCmdUI->SetText(GetWhoItIs(pt));	// find who and set text
}

//////////////////
// Figure out what "tool"--i.e. person--the mouse is over, if any.
//
int CMainFrame::OnToolHitTest(CPoint pt, TOOLINFO* pTI) const
{
	int nHit = -1;	// assume none
	if (pTI && !(GetWhoItIs(pt).IsEmpty()) ) {
		// Need to return a unique value from last time:
		// so just return the point as an integer
		//
		nHit = MAKELONG(pt.x, pt.y);
		// setup TOOLINFO structure
		pTI->hwnd = m_hWnd;
		pTI->uId  = nHit;
		pTI->rect = CRect(CPoint(pt.x-1,pt.y-1),CSize(2,2));
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		pTI->uFlags |= TTF_NOTBUTTON; // OR with TTF_ALWAYSTIP to show
												// tip even when window not active
	}
	return nHit;
}

//////////////////
// Get tooltip text. idFrom is whatever I returned above as uID:
// namely, the mouse point coded as integer.
//
void CMainFrame::OnGetTooltipText(NMHDR* pNMHDR, LRESULT* plRes)
{
	TOOLTIPTEXT& ttt = *((TOOLTIPTEXT*)pNMHDR);
	strncpy(ttt.szText,
		GetWhoItIs(CPoint (pNMHDR->idFrom)),
		sizeof(ttt.szText));
}

//////////////////
// Main helper to figure out who it is under a given point in the image.
//
CString CMainFrame::GetWhoItIs(CPoint pt) const
{
	static struct {
		COLORREF color;
		LPCTSTR  name;
	} data [] = {
		// The entries in this table must match colors in the mask.
		// Each color identifies a person/object in the painting.
		//
		{ RGB(255,  0,  0), "Virgil" },
		{ RGB(  0,255,  0), "Octavia" },
		{ RGB(  0,  0,255), "Octavia's Maiden" },
		{ RGB(  0, 66, 66), "Unknown Character" },
		{ RGB(255,255,  0), "Book 6 of the Aeneid" },
		{ RGB(132,  0,132), "Unknown Character" },
		{ RGB(  0,  0,132), "Ionic Column" },
		{ RGB(  0,132,255), "Unknown Character" },
		{ RGB(132, 66,  0), "Pretorian Guard" },
		{ RGB(  0,132,  0), "Caesar Augustus" },
		{ RGB(  0,132,132), "Drapes" },
		{ 0, NULL }
	};

	// Create memory DC, select mask bitmap into it and call CDC::GetPixel
	// to get the color of the corresponding pixel in the mask
	//
	CDC dc;
	dc.CreateCompatibleDC(NULL);
	CBitmap * pOldBm = dc.SelectObject((CDib*)&m_dibMask);
	COLORREF color = dc.GetPixel(pt);	// mask pixel
	dc.SelectObject(pOldBm);				// restore 
	
	// Computee text. If I'm viewing the mask, generate
	// "RGB(x,y) = (R,G,B)" before name of character.
	//
	CString s;
	if (m_bViewMask) {
		s.Format("RGB(%d,%d)=(%d,%d,%d) ", pt.x, pt.y, 
			GetRValue(color), GetGValue(color), GetBValue(color));
	}

	if (color != RGB(255,255,255)) {	// white = nothing
		// Do linear search through table
		for (int i=0; data[i].name; i++) {
			if (data[i].color==color)
				s += data[i].name;
		}
	}
	return s;
}

//////////////////
// View Mask/View Image command: toggle flag
//
void CMainFrame::OnViewMaskOrImage() 
{
	m_bViewMask = !m_bViewMask;
	Invalidate();
}
void CMainFrame::OnUpdateViewMaskOrImage(CCmdUI* pCmdUI) 
{
	pCmdUI->SetText(m_bViewMask ? "&Image" : "&Mask");
}

//////////////////
// Force window same size as image
//
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	if (m_dibImage.m_hObject) {
		CSize sz = m_dibImage.GetSize(); // size of bitmap
		CRect rcWin, rcClient;
		GetWindowRect(&rcWin);
		GetClientRect(&rcClient);
		lpMMI->ptMaxSize = lpMMI->ptMinTrackSize = lpMMI->ptMaxTrackSize = 
			CPoint(sz.cx + rcWin.Width() - rcClient.Width(),
					 sz.cy + rcWin.Height()- rcClient.Height());
	}	
}
	