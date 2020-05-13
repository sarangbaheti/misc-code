////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.1 on Windows 95
// See ShadeCap.cpp
// 
#include "StdAfx.h"
#include "ShadeCap.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_SYSCOLORCHANGE()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_SETTINGCHANGE, OnSettingChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] = {
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
	m_bActive = -1; // invalid
}

CMainFrame::~CMainFrame()
{
}

//////////////////
// Standard MFC create stuff
//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))	{
		return -1;      // fail to create
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))) {
		return -1;      // fail to create
	}
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	return 0;
}

// Private MFC function only sets the title if it's different
//
extern void AFXAPI AfxSetWindowText(HWND, LPCTSTR);

//////////////////
// Override to change title--app name first, then doc name
//
void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	AfxSetWindowText(m_hWnd, m_strTitle + " " + GetDocTitle());
}

//////////////////
// Get doc title: I use full path name or "untitled"
//
CString CMainFrame::GetDocTitle()
{
	CString s = GetActiveDocument()->GetPathName();
	return s.IsEmpty() ?  "Untitled" : s;
}

////////////////
// Mini-class to get the caption rectangle of a window in window coords.
// This is the area of the title bar inside the window frame,
// including the icon but not the min/max/close buttons.
// 
class CCaptionRect : public CRect {
public:
	CCaptionRect(const CWnd& wnd); // use reference to deny NULL ptr
};

/////////////////
// Paint non-client area: First let Windows paint, then I'll paint over it.
//
// I use the relatively obscure and poorly documented update region feature
// to prevent Windows from painting the title text. This is to get totally
// flicker-free painting when the user sizes the window. Note that Windows
// sometimes uses WPARAM=1.
//
void CMainFrame::OnNcPaint()
{
	MSG& msg = AfxGetThreadState()->m_lastSentMsg;
	HRGN hRgn = (HRGN)msg.wParam;

	CCaptionRect rc(*this);		// caption rectangle in window coords
	CRect rcWin;					// window rect
	GetWindowRect(&rcWin);		// .. get window rect
	rc += rcWin.TopLeft();		// convert caption rect to screen coords

	// Don't bother painting if the caption doesn't lie within the region.
	//
	if (msg.wParam > 1 && !::RectInRegion((HRGN)msg.wParam, &rc)) {
		CFrameWnd::OnNcPaint(); // just do default thing
		return;						// and quit
	}

	// Exclude caption from update region
	//
	HRGN hRgnCaption = ::CreateRectRgnIndirect(&rc);
	HRGN hRgnNew     = ::CreateRectRgnIndirect(&rc);
	if (msg.wParam > 1) {
		// wParam is a valid region: subtract caption from it
		::CombineRgn(hRgnNew, hRgn, hRgnCaption, RGN_DIFF);
	} else {
		// wParam is not a valid region: create one that's the whole
		// window minus the caption bar
		HRGN hRgnAll = ::CreateRectRgnIndirect(&rcWin);
		CombineRgn(hRgnNew, hRgnAll, hRgnCaption, RGN_DIFF);
		DeleteObject(hRgnAll);
	}

	// Call Windows to do WM_NCPAINT with altered update region
	//
	WPARAM savewp = msg.wParam;	// save original wParam
	msg.wParam = (WPARAM)hRgnNew;	// set new region for DefWindowProc
	CFrameWnd::OnNcPaint();			// call it
	DeleteObject(hRgnCaption);		// clean up
	DeleteObject(hRgnNew);			// ...
	msg.wParam = savewp;				// restore original wParam

	PaintCaption();					// Now paint my special caption
}

//////////////////
// Non-client area (de)activated: paint it
//
BOOL CMainFrame::OnNcActivate(BOOL bActive)
{
	// Mimic MFC kludge to stay active if WF_STAYACTIVE bit is on
	//
	if (m_nFlags & WF_STAYACTIVE)
		bActive = TRUE;
	if (!IsWindowEnabled())			// but not if disabled
		bActive = FALSE;

	if (bActive==m_bActive)
		return TRUE;					// nothing to do

	// Turn WS_VISIBLE off before callinf DefWindowProc,
	// so DefWindowProc won't paint and thereby cause flicker.
	//
	DWORD dwStyle = GetStyle();
	if (dwStyle & WS_VISIBLE)
		SetWindowLong(m_hWnd, GWL_STYLE, (dwStyle & ~ WS_VISIBLE));
	// do not call the base class because it will call Default()
	// and we may have changed bActive.
	DefWindowProc(WM_NCACTIVATE, bActive, 0L);
	if (dwStyle & WS_VISIBLE)
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	// At this point, nothing has happened (since WS_VISIBLE was off).
	// Now it's time to paint.
	//
	m_bActive = bActive;			// update state
	SendMessage(WM_NCPAINT);	// paint non-client area (frame too)
	return TRUE;					// done OK
}

//////////////////
// Someone called SetWindowText: paint new text.
//
LRESULT CMainFrame::OnSetText(WPARAM wParam, LPARAM lParam)
{
	// Turn WS_VISIBLE style off before calling Windows to
	// set the text, then turn it back on again after.
	//
	DWORD dwStyle = GetStyle();
	if (dwStyle & WS_VISIBLE)
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle & ~ WS_VISIBLE);
	LRESULT lRet = DefWindowProc(WM_SETTEXT, wParam, lParam); 
	if (dwStyle & WS_VISIBLE)
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	m_rcCaption.SetRectEmpty();			 // invalidate caption
	SendMessage(WM_NCPAINT);	// paint non-client area (frame too)
	PaintCaption();							 // ..and paint it
	return lRet;
}

//////////////////
// User changed system settings (possibly font) or colors.
// Invalidate everything to generate anew.
// 
LRESULT CMainFrame::OnSettingChange(WPARAM, LPARAM)
{
	OnSysColorChange();
	return 0;
}
void CMainFrame::OnSysColorChange()
{
	m_fontCaption.DeleteObject();	// generate new fonts
	m_fontAcme.DeleteObject();		// ...
	m_rcCaption.SetRectEmpty();	// will force new bitmap to be created
}

//////////////////
// Paint custom caption. Flag tells whether active or not.
// Just blast the bitmap to the title bar, but not iif minimized (iconic).
//
void CMainFrame::PaintCaption(BOOL bActive)
{
	if (!IsIconic()) {
		CWindowDC dcWin(this);
		CDC dc;
		dc.CreateCompatibleDC(&dcWin);
		CBitmap* pOldBitmap = dc.SelectObject(GetCaptionBitmap(bActive));
		const CRect& rc = m_rcCaption;
		dcWin.BitBlt(rc.left,rc.top,rc.Width(),rc.Height(),&dc,0,0,SRCCOPY);
	}
}

//////////////////
// Helper function to compute the luminosity for an RGB color.
// Measures how bright the color is. I use this so I can draw the caption
// text using the user's chosen color, unless it's too dark. See MSDN for
// definition of luminosity and how to compute it.
//
static int GetLuminosity(COLORREF color)
{
#define HLSMAX 240	// This is what Display Properties uses
#define RGBMAX 255	// max r/g/b value is 255
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	int rgbMax = max( max(r,g), b);
	int rgbMin = min( min(r,g), b);
	return (((rgbMax+rgbMin) * HLSMAX) + RGBMAX ) / (2*RGBMAX);
}

#define COLOR_WHITE RGB(255,255,255)
#define COLOR_BLACK RGB(0,0,0)
#define NCOLORSHADES 64		// this many shades in gradient

//////////////////
// Helper to paint rectangle with a color.
//
static void PaintRect(CDC& dc, int x, int y, int w, int h, COLORREF color)
{
	CBrush brush(color);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.PatBlt(x, y, w, h, PATCOPY);
	dc.SelectObject(pOldBrush);
}

//////////////////
// Get the appropriate bitmap whether active/inactive. If the size of
// the caption rect has changed since the last time it was generated,
// generate it again.
// 
// This is the function that actually does the shading. It creates a
// bitmap that's used to paint the caption. It looks horrible, but it's
// just a lot of bit-twiddling GDI stuff.
//
CBitmap* CMainFrame::GetCaptionBitmap(BOOL bActive)
{
	CBitmap& bm = m_bmCaption[bActive!=0]; // one of two bitmaps
	CCaptionRect rcCap(*this);					// caption rectangle in win coords
	if (rcCap != m_rcCaption) {				// if changed since last time:
		m_bmCaption[0].DeleteObject();		// delete both bitmaps,
		m_bmCaption[1].DeleteObject();		// ..they are bad
		m_rcCaption = rcCap;						// note for next time
	}
	if (bm.m_hObject)
		return &bm;								   // already have bitmap; return it.
	
	// Either the size changed or the bitmap was never created. Create it.
	// 
	rcCap -= rcCap.TopLeft(); // convert caption rectangle origin to (0,0)
	int w = rcCap.Width();
	int h = rcCap.Height();
	int cxIcon = GetSystemMetrics(SM_CXSIZE);
	int cyIcon = GetSystemMetrics(SM_CYSIZE);

	// Create bitmap same size as caption area and select into memory DC
	//
	CWindowDC dcWin(this);
	CDC dc;
	dc.CreateCompatibleDC(&dcWin);
	bm.DeleteObject();
	bm.CreateCompatibleBitmap(&dcWin, w, h);
	CBitmap* pOldBitmap = dc.SelectObject(&bm);

	// Paint shaded background. Note all painting is into memory DC,
	// not window, so there's no flicker.
	//
	if (!bActive) {
		// Inactive caption: don't do shading, just fill w/bg color
		PaintRect(dc, 0, 0, w, h, GetSysColor(COLOR_INACTIVECAPTION));

	} else {
		// Active caption: do shading
		//
		COLORREF clrBG = GetSysColor(COLOR_ACTIVECAPTION); // background color
		int r = GetRValue(clrBG);				// red..
		int g = GetGValue(clrBG);				// ..green
		int b = GetBValue(clrBG);				// ..blue color vals
		int x = 5*rcCap.right/6;				// start 5/6 of the way right
		int w = x - rcCap.left;					// width of area to shade
		int xDelta= max(w/NCOLORSHADES,1);	// width of one shade band

		// Paint far right 1/6 of caption the background color
		PaintRect(dc, x, 0, rcCap.right-x, h, clrBG);

		// Compute new color brush for each band from x to x + xDelta.
		// Excel uses a linear algorithm from black to normal, i.e.
		//
		//		color = CaptionColor * r
		//
		// where r is the ratio x/w, which ranges from 0 (x=0, left)
		// to 1 (x=w, right). This results in a mostly black title bar,
		// since we humans don't distinguish dark colors as well as light
		// ones. So instead, I use the formula
		//
		//		color = CaptionColor * [1-(1-r)^2]
		//
		// which still equals black when r=0 and CaptionColor when r=1,
		// but spends more time near CaptionColor. For example, when r=.5,
		// the multiplier is [1-(1-.5)^2] = .75, closer to 1 than .5.
		// I leave the algebra to the reader to verify that the above formula
		// is equivalent to
		//
		//		color = CaptionColor - (CaptionColor*(w-x)*(w-x))/(w*w)
		//
		// The computation looks horrendous, but it's only done once each
		// time the caption changes size; thereafter BitBlt'ed to the screen.
		//
		while (x > xDelta) {						// paint bands right to left
			x -= xDelta;							// next band
			int wmx2 = (w-x)*(w-x);				// w minus x squared
			int w2  = w*w;							// w squared
			PaintRect(dc, x, 0, xDelta, h,	
				RGB(r-(r*wmx2)/w2, g-(g*wmx2)/w2, b-(b*wmx2)/w2));
		}

		PaintRect(dc,0,0,x,h,COLOR_BLACK);  // whatever's left ==> black
	}

	// Draw icon and caption buttons.
	// These are all drawn inside a rectangle of dimensions SM_C[XY]SIZE.
	//
	CRect rcButn(0,0,cxIcon,cyIcon);

	// Within the basic button rectangle, Windows 95 uses a 1 or 2 pixel border
	// Icon has 2 pixel border on left, 1 pixel on top/bottom, 0 right
	rcButn.DeflateRect(0,1);
	rcButn.left += 2;
	DrawIconEx(dc.m_hDC, rcButn.left, rcButn.top,
		(HICON)GetClassLong(m_hWnd, GCL_HICONSM),
		rcButn.Width(), rcButn.Height(), 0, NULL, DI_NORMAL);

	// Close box has a 2 pixel border on all sides but left, which is zero
	rcButn.DeflateRect(0,1);				// shrink top/bottom 1 more
	rcButn += CPoint(w-cxIcon-2,0);		// move right
	dc.DrawFrameControl(&rcButn, DFC_CAPTION, DFCS_CAPTIONCLOSE);

	DWORD dwStyle = GetStyle();

	// Max/restore button is like close box; just shift rectangle left
	//
	if (dwStyle & WS_MAXIMIZEBOX) {
		rcButn -= CPoint(cxIcon,0);
		dc.DrawFrameControl(&rcButn, DFC_CAPTION,
			IsZoomed() ? DFCS_CAPTIONRESTORE : DFCS_CAPTIONMAX);
	}

	// Minimize button has 2 pixel border on all sides but right.
	//
	if (dwStyle & WS_MINIMIZEBOX) {
		rcButn -= CPoint(cxIcon-2,0);
		dc.DrawFrameControl(&rcButn, DFC_CAPTION, DFCS_CAPTIONMIN);
	}

	// Now draw text. First Create fonts if needed
	//
	if (!m_fontCaption.m_hObject)
		CreateFonts();

	// Paint "ACME TEXT" using ACME font, always white
	//
	CString s = m_strTitle + " ";			 // app title
	CRect rcText = rcCap;					 // caption rectangle
	rcText.left += cxIcon+2;				 // start after icon
	rcText.right = rcButn.left-2;			 // don't draw past buttons
	dc.SetBkMode(TRANSPARENT);				 // draw on top of our shading
	dc.SetTextColor(COLOR_WHITE);			 // always white
	CFont* pOldFont = dc.SelectObject(&m_fontAcme);
	dc.DrawText(s, &rcText, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	// Now paint window title (caption)
	//
	rcText.left += dc.GetTextExtent(s).cx; // move past "ACME EDIT "
	if (rcText.right > rcText.left) {		// if still room:
		COLORREF clrText;							// text color
		if (bActive) {
			// Excel always uses white for title color, but I use the user's
			// selected color--unless it's too dark, then I use white.
			//
			clrText = GetSysColor(COLOR_CAPTIONTEXT);
			if (GetLuminosity(clrText) < 90) // good from trial & error
				clrText = COLOR_WHITE;
		} else
			clrText = GetSysColor(COLOR_INACTIVECAPTIONTEXT);

		// Paint the text. Use DT_END_ELLIPSIS to draw ellipsis if text
		// won't fit. Win32 sure is friendly!
		//
		dc.SetTextColor(clrText);
		dc.SelectObject(&m_fontCaption);
		dc.DrawText(GetDocTitle(), &rcText,
			DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	} 

	// Restore DC
	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldBitmap);

	return &bm; // return bitmap to caller--whew!
}

//////////////////
// Helper function to build the fonts I need.
//
void CMainFrame::CreateFonts()
{
	// Get current system caption font, just to get its size
	//
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(ncm);
	VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0));
	m_fontCaption.CreateFontIndirect(&ncm.lfCaptionFont);

	// Create "ACME" font same size as caption font, but use Book Antiqua
	//
	m_fontAcme.CreatePointFont(120, "Book Antiqua"); // 12 pt for now
	LOGFONT lf;
	m_fontAcme.GetLogFont(&lf);					// get font info
	m_fontAcme.DeleteObject();						// I don't really want 12 pt
	lf.lfWeight|=FW_BOLD;							// make bold
	lf.lfHeight = ncm.lfCaptionFont.lfHeight; // same height as caption font
	m_fontAcme.CreateFontIndirect(&lf);			// create font
}

//////////////////
// CCaptionRect: Constructor conputes caption rectangle in window coords.
//
CCaptionRect::CCaptionRect(const CWnd& wnd)
{
	// Get size of frame around window
	DWORD dwStyle = wnd.GetStyle();
	CSize szFrame = (dwStyle & WS_THICKFRAME) ?
		CSize(GetSystemMetrics(SM_CXSIZEFRAME),
			   GetSystemMetrics(SM_CYSIZEFRAME)) :
		CSize(GetSystemMetrics(SM_CXFIXEDFRAME),
				GetSystemMetrics(SM_CYFIXEDFRAME));

	int cxIcon = GetSystemMetrics(SM_CXSIZE); // width of caption icon/button

	// Compute rectangle
	wnd.GetWindowRect(this);		// window rect in screen coords
	*this -= CPoint(left, top);	// shift origin to (0,0)
	left  += szFrame.cx;				// frame
	right -= szFrame.cx;				// frame
	top   += szFrame.cy;				// top = end of frame
	bottom = top + GetSystemMetrics(SM_CYCAPTION)  // height of caption
		- GetSystemMetrics(SM_CYBORDER);				  // minus gray shadow border
}
