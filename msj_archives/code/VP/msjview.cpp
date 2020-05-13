// MSJ Visual Developer Column
//
// This source code is a small sub-set of one of 50 classes
// found in Stingray's Objective Toolkit product
// For more information: http://www.stingsoft.com

//  Author:		Scot Wingo and George Shepherd.
//  Description:	Declarations for MSJSuperView
//  Created:		9/1/97
//


#include "stdafx.h"
#include "resource.h"

#ifndef __MSJSUPERVIEW_H__
#include "msjview.h"
#endif


#define new DEBUG_NEW


BEGIN_MESSAGE_MAP(MSJSuperView, CScrollView)
    //{{AFX_MSG_MAP(SECPanWnd)
    ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL MSJSuperView::OnMouseWheel(UINT nFlags, short zDelta, CPoint ptMouse)
{
	TRACE("OnMouseWheel\n");
	//Special logic for CONTROL and mousewheel which is zooming.
	if (nFlags == MK_CONTROL)
	{
		//int zoom = GetZoom();
		float fCurrentZoom = m_fZoomScale;
		if (zDelta > 0)
			ZoomIn(&ptMouse,.10f );
		else 
			ZoomOut(&ptMouse,.10f);
	}
	else if (nFlags == MK_SHIFT)
	{
		//Here you would implement your data traversal routines.
		//Unfortunately this sample doesn't have any, so let's
		//just display a nice debug output message instead.

		TRACE("Got a shift key!\n");
	}
	else
		return CScrollView::OnMouseWheel(nFlags,zDelta,ptMouse);

	return TRUE;
	
}


void MSJSuperView::OnMButtonDown(UINT nFlags, CPoint point) 
{
TRACE("MBUTTONDOWN\n");
	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;

	if (!bCtl && nFlags == MK_MBUTTON)
	{
		GetCursorPos(&point);
		point -= CPoint(15,15);
		SetCursorPos(point.x, point.y);
		ScreenToClient(&point);
		
		m_bMouseWheelDrag = TRUE;
		m_ptMouseWheelOrg = point;
		SetCapture();
		m_nMouseWheelTimer = SetTimer(999, 10, NULL);

		m_pWndDrag = new MSJMouseWheelOriginWnd(MSJ_IDB_ORIGIN_ALL);
		m_pWndDrag->CreateWnd(this);
		m_pWndDrag->MoveWindow(CRect(m_ptMouseWheelOrg.x, m_ptMouseWheelOrg.y, m_ptMouseWheelOrg.x+30, m_ptMouseWheelOrg.y+30));
		m_pWndDrag->ShowWindow(SW_SHOW);

	}
	else
		CScrollView::OnMButtonDown(nFlags, point);
}

void MSJSuperView::OnMButtonUp(UINT nFlags, CPoint point) 
{
	TRACE("MBUTTONUP\n");
	if (m_bMouseWheelDrag)
	{
		delete m_pWndDrag;
		m_bMouseWheelDrag = FALSE;
		ReleaseCapture();
		KillTimer(m_nMouseWheelTimer);
		SetCursor(NULL);

		GetCursorPos(&point);
		point += CPoint(15,15);
		SetCursorPos(point.x, point.y);
		ScreenToClient(&point);
	}
	CScrollView::OnMButtonUp(nFlags, point);
}

void MSJSuperView::OnMouseMove(UINT nFlags, CPoint point) 
{
	TRACE("OnMouseMove\n");
	CScrollView::OnMouseMove(nFlags, point);
}

void MSJSuperView::OnTimer(UINT nIDEvent) 
{
	TRACE("ONTIMER\n");
	if (nIDEvent == 999 && m_bMouseWheelDrag)
	{
		CPoint ptCur;
		GetCursorPos(&ptCur);
		ScreenToClient(&ptCur);

		CPoint pt = ptCur - m_ptMouseWheelOrg;

		int direction;
		int nScroll;

		if (abs(pt.x) > abs(pt.y))
		{
			direction = pt.x > 0 ? MSJ_RIGHT : MSJ_LEFT;
			nScroll = abs(pt.x) /8;
		}
		else
		{
			direction = pt.y > 0 ? MSJ_DOWN : MSJ_UP;
			nScroll = abs(pt.y) /8;
		}

		if (nScroll > 0)
		{
			m_pWndDrag->ShowWindow(SW_HIDE);
			DoScroll(direction, nScroll);
			m_pWndDrag->MoveWindow(CRect(m_ptMouseWheelOrg.x, m_ptMouseWheelOrg.y, m_ptMouseWheelOrg.x+30, m_ptMouseWheelOrg.y+30));
			m_pWndDrag->ShowWindow(SW_SHOW);
			m_pWndDrag->UpdateWindow();
		}

		if (nScroll == 0 && abs(pt.x) < 5 && abs(pt.y) < 5)
			direction = -1;
		
		int nCursor;
		switch (direction)
		{
		case MSJ_RIGHT: nCursor = MSJ_IDC_IMR; break;
		case MSJ_LEFT: nCursor = MSJ_IDC_IML; break;
		case MSJ_UP: nCursor = MSJ_IDC_IMU; break;
		case MSJ_DOWN: nCursor = MSJ_IDC_IMD; break;
		default: nCursor = MSJ_IDC_IMA; break;
		}
	
	MySetCursor(nCursor);

	}
	else
		CScrollView::OnTimer(nIDEvent);
}



BOOL MSJSuperView::DoScroll(int nDirection, int nSize)
{
    int xOrig, x, xMax;
    int yOrig, y, yMax;

    CScrollBar* pBar;
    DWORD dwStyle = GetStyle();
    //If no scroll bars, don't do anything
    // e.g. the user has a small scale in a zoom, or a large
    //     window and there are no scroll bars.  Everything is
    //     in view, so no panning needed.
    
    pBar = GetScrollBarCtrl(SB_VERT);
    if ((pBar != NULL && !pBar->IsWindowEnabled()) ||
	(pBar == NULL && !(dwStyle & WS_VSCROLL)))
	nSize = 0;
    
    pBar = GetScrollBarCtrl(SB_HORZ);
    if ((pBar != NULL && !pBar->IsWindowEnabled()) ||
	(pBar == NULL && !(dwStyle & WS_HSCROLL)))
	nSize = 0;
    
    // Adjust current x position based on scroll bar constraints.
    xOrig = x = GetScrollPos(SB_HORZ);
    
    // CWnd scrolling is very different in Win32/Win16, call
    // GetScrollRange on Win16 and GetScrollLimit on Win32 to
    // make sure the correct adjusted max is retrieved not something
    // bogus.  We do this for both x and y here.
    
    xMax = GetScrollLimit(SB_HORZ);
	if (nDirection == MSJ_LEFT || nDirection == MSJ_RIGHT)
	{
		if (nDirection == MSJ_LEFT)
			x -= nSize;
		else 
			x += nSize;

		//Sanity checks.
    if (x < 0)
		x = 0;
    else if (x > xMax)
		x = xMax;
	}
    
    // Adjust current y position based on scroll bar constraints.
    yOrig = y = GetScrollPos(SB_VERT);
    yMax = GetScrollLimit(SB_VERT);
   
	if (nDirection == MSJ_UP ||nDirection == MSJ_DOWN)
	{
		if (nDirection == MSJ_UP)
			y -= nSize;
		else
			y += nSize;	

		//Sanity checks.
		if (y < 0)
			y = 0;
	    else if (y > yMax)
			y = yMax;
    }

    // If nothing changed, just return, no work to do.
    if (x == xOrig && y == yOrig)
		return FALSE;
    

	// This order and combination of calls generates the smoothest
	// scrolling.
	// UpdateWindow slows down things, but without it items are
	// 'stretched' around the scrollbar zomes because of multiple
	// ScrollWindow calls - this is especially noticable in realtime
	// panning.
	
	if (x != xOrig)
	    SetScrollPos(SB_HORZ, x);
	if (y != yOrig)
	    SetScrollPos(SB_VERT, y);
	ScrollWindow(-(x-xOrig), -(y-yOrig));
	
	UpdateWindow();
    return TRUE;
}

//	
//	MSJSuperView
//	
//	Default to no zoom scale, and zooming is offf
//
MSJSuperView::MSJSuperView() : CScrollView()
{
    m_fZoomScale  = 1.0f;
    ZoomLevelChanged();
} 

//	
//	~MSJSuperView
//	
//	
MSJSuperView::~MSJSuperView()
{
    
}

// SetZoomLevel
// Makes sure the new scale is within bounds.
//
// SetZoomLevel can be overriden for different behavior
//

void MSJSuperView::SetZoomLevel(float fNewScale)
{
	m_fZoomScale = fNewScale;
 
}
//
// MSJSuperView printing
//

BOOL MSJSuperView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

//
// MSJSuperView overridden CScrollView members
//

//	
//	SetScrollSizes
//	
//	Store the original values in member data for later, so
//	we always know what our original setup was.
//
//      Most code borrowed from CScrollView, we're just in ANISOTROPIC mode.
//

void MSJSuperView::SetScrollSizes (int nMapMode,
				  SIZE sizeTotal,
				  const SIZE& sizePage /* = sizeDefault */, // in logical units
				  const SIZE& sizeLine /* = sizeDefault */) // in logical units
{
    ASSERT_VALID(this);
    
    nMapMode; //UNUSED
    // Set up the defaults
    if (sizeTotal.cx == 0 && sizeTotal.cy == 0){
	sizeTotal.cx = 1;
	sizeTotal.cy = 1;
    }
    //SetWindowExt doesn't like 0,0 will bomb out.
    ASSERT(sizeTotal.cx > 0 && sizeTotal.cy > 0);
    
    m_nMapMode    = MM_ANISOTROPIC; // Need for arbitrary scaling
    m_totalLog    = sizeTotal;
    
    // Setup default Viewport extent to be conversion of Window extent
    // into device units.
    
    //BLOCK for DC
    {
	CWindowDC dc(NULL);
	dc.SetMapMode(m_nMapMode);
	
	// total size
	m_totalDev = m_totalLog;
	dc.LPtoDP((LPPOINT)&m_totalDev);
    } // Release DC here
    
    m_szOrigTotalDev = m_totalDev;
    m_szOrigPageDev  = sizePage;
    m_szOrigLineDev  = sizeLine;
    ReCalcBars();
    
    ZoomLevelChanged(); //Notify app that there's a new zoom level 1.0f.   
}

//	
//	OnPrepareDC
//	
//	Does all the work for MSJSuperView.
//	
//	
void MSJSuperView::OnPrepareDC (
    CDC* pDC, 
    CPrintInfo* pInfo)
{
    
    ASSERT_VALID(pDC);
    ASSERT(m_totalLog.cx >= 0 && m_totalLog.cy >= 0);
    ASSERT(m_totalDev.cx >= 0 && m_totalDev.cx >= 0);
    
    // Set the Mapping mode, and the window and viewport extents
    // Note: This will always be ANISOTROPIC for MSJSuperView
    pDC->SetMapMode(m_nMapMode);
    pDC->SetWindowExt(m_totalLog);  //Set up the logical window

    //Now figure out the origin for the viewport, depends on
    //This code is from CSCrollView
    CPoint ptVpOrg;
    pDC->SetViewportExt(m_totalDev); // in device coordinates
    
    // by default shift viewport origin in negative direction of scroll
    ASSERT(pDC->GetWindowOrg() == CPoint(0,0));
    ptVpOrg = -GetDeviceScrollPosition();
    
    // Set the new viewport origin, call CView for printing behavior
    pDC->SetViewportOrg(ptVpOrg);
    CView::OnPrepareDC(pDC, pInfo);
} 

//	MSJSuperView::ReCalcBars
//	
//	
//	Since we're changing the viewport around, we'll need to
//	modify the scrollbars where CScrollView just sets them
//	up at start of day and scrolls.
//	
//      This code originally lived in CScrollView::SetScrollSizes, but
//      I had to move it here to facilitate updating the scroll bars.
//
void MSJSuperView::ReCalcBars (void)
{
    ASSERT_VALID(this);
    {  // BLOCK for DC
      CWindowDC dc(NULL);
      dc.SetMapMode(m_nMapMode);

      // Calculate new device units for scrollbar
      // Start with origional logical units from SetScrollPos
      m_pageDev = m_szOrigPageDev;
      dc.LPtoDP((LPPOINT)&m_pageDev);
      m_lineDev = m_szOrigLineDev;
      dc.LPtoDP((LPPOINT)&m_lineDev);
   } // Free DC

   // Make sure of the range
   if (m_pageDev.cy < 0)  m_pageDev.cy = -m_pageDev.cy;
   if (m_lineDev.cy < 0)  m_lineDev.cy = -m_lineDev.cy;

   // If none specified - use one tenth, Just like CScrollView
   
   //ASSERT(m_totalDev.cx >= 0 && m_totalDev.cy >= 0);
   if (m_totalDev.cx < 0 || m_totalDev.cy < 0){
       TRACE0("MSJSuperView: Zoom level too low, divide by zero possible\n");
       ASSERT(FALSE);
	   return; //bail out! danger! warning Will Robinson!!!
   }
   
   if (m_pageDev.cx == 0) m_pageDev.cx = m_totalDev.cx / 10;
   if (m_pageDev.cy == 0) m_pageDev.cy = m_totalDev.cy / 10;
   if (m_lineDev.cx == 0) m_lineDev.cx = m_pageDev.cx  / 10;
   if (m_lineDev.cy == 0) m_lineDev.cy = m_pageDev.cy  / 10;

   // Now update the scrollbars
   if (m_hWnd != NULL) {
      UpdateBars();
      Invalidate(TRUE); // Zoom scale changed, redraw all
   }
}


//
// MSJSuperView custom members to implement zooming functionality
//

//	
//	ZoomIn
//	
//	
void MSJSuperView::ZoomIn (
    CPoint *point,   // point in logical coordinates
    float  delta)    // scale factor
{
    ASSERT_VALID(this);
    ASSERT(m_nMapMode == MM_ANISOTROPIC);
    SetZoomLevel(m_fZoomScale + delta);
    UpdateViewport(point);
    return;
} 

//	
//	ZoomOut
//	
void MSJSuperView::ZoomOut (
    CPoint *point,   // point in logical coordinates
    float  delta)    // scale factor
{
    ASSERT_VALID(this);
    ASSERT(m_nMapMode == MM_ANISOTROPIC);
    // Decrease the zoom scale.
    SetZoomLevel(m_fZoomScale - delta);
    
    UpdateViewport(point);
    
    return;
} 

//	
//	CenterOnLogicalPoint
//	
//	Same as CScrollView::CenterOnPoint, but for log point.
//	
//	

void MSJSuperView::CenterOnLogicalPoint(CPoint pt)
{
    // Convert the point to device coordinates
    ViewLPtoDP(&pt);
    // Account for scroll bar position
    ClientToDevice(pt);
    // Use CScrollView's function for device coordinates
    CScrollView::CenterOnPoint(pt);
} 

//	
//	GetLogicalCenterPoint
//	
CPoint MSJSuperView::GetLogicalCenterPoint (void)  
{
    CPoint pt;
    CRect rect;
    // Get the center of screen
    GetClientRect(&rect);
    pt.x = (rect.Width()  / 2);
    pt.y = (rect.Height() / 2);
    
    // Convert the point to logical coordinates
    ViewDPtoLP(&pt);
    return pt;
} 


//	
//	ViewDPtoLP
//	
//	Same as DPtoLP, but uses Client DC.
void MSJSuperView::ViewDPtoLP (
    LPPOINT lpPoints,
    int     nCount)
{
    // Convert to logical units
    // Called from View when no DC is available
    ASSERT(m_nMapMode > 0); // must be set
    CWindowDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(lpPoints, nCount);
} 

//	
//	Same as LPtoDP, but uses Client DC
//	
void MSJSuperView::ViewLPtoDP (
    LPPOINT lpPoints,
    int     nCount)
{
    // Convert to logical units
    // Called from View when no DC is available
    ASSERT(m_nMapMode > 0); // must be set
    CWindowDC dc(this);
    OnPrepareDC(&dc);
    dc.LPtoDP(lpPoints, nCount);
} 

void MSJSuperView::ClientToDevice (
    CPoint &point)
{
    // Need to account for scrollbar position
    CPoint scrollPt = GetDeviceScrollPosition();
    point.x += scrollPt.x;
    point.y += scrollPt.y;
} 

//	
//	PersistRatio
//	
//	Since we're not ISOTROPIC, make sure we maintain
//	the same x/y ratios.
//	
void MSJSuperView::PersistRatio (
    const CSize &orig,
    CSize       &dest,
    CPoint      &remainder)
{
    float ratio1 = (float) orig.cx / orig.cy;
    float ratio2 = (float) dest.cx / dest.cy;
    int   newSize;
    
    // Do nothing if they are the same
    if (ratio1 > ratio2) {
	// Shrink hieght
	newSize = (int)(dest.cx / ratio1);
	remainder.x = 0;
	remainder.y = dest.cy - newSize;
	dest.cy = newSize;
    } else if (ratio2 > ratio1) {
	// Shrink width
	newSize = (int)(dest.cy * ratio1);
	remainder.x = dest.cx - newSize;
	remainder.y = 0;
	dest.cx = newSize;
    }
} 

//	UpdateViewport
//	
//      Called after the scale factor has
//	changed, calculates center if needed,
//	then updates the viewport, updates the
//	scroll bars and finally notifies our decendents
//      that the zoom factor has changed fia ZoomLevelChanged.
//	
void MSJSuperView::UpdateViewport(CPoint * ptNewCenter)
{
    //Ok for ptNewCenter = NULL
    ASSERT_VALID(this);
    CPoint ptCenter;

    if (!ptNewCenter)
		ptCenter = GetLogicalCenterPoint();
    else 
		ptCenter = *ptNewCenter;
    
    // Modify the Viewport extent
    m_totalDev.cx = (int) ((float) m_szOrigTotalDev.cx * m_fZoomScale);
    m_totalDev.cy = (int) ((float) m_szOrigTotalDev.cy * m_fZoomScale);
    ReCalcBars();
    
    // Set the current center point.
    CenterOnLogicalPoint(ptCenter);
    
    // Notify the class that a new zoom scale was done
    ZoomLevelChanged();
    return;
}


#ifdef _DEBUG
void MSJSuperView::AssertValid() const
{
#ifdef LATER
    //Verify min/max condition if set
    if (m_fZoomMin != -1 && m_fZoomMax !=-1) {
	   ASSERT (m_fZoomMin <= m_fZoomScale);
	   ASSERT (m_fZoomScale <= m_fZoomMax);
	   }
#endif //LATER
    
    CView::AssertValid();
} 

#endif //_DEBUG


void MSJSuperView::MySetCursor(int nCursor)
{
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nCursor),RT_GROUP_CURSOR);
	HICON hCursor = ::LoadCursor(hInst,MAKEINTRESOURCE(nCursor));
	SetCursor(hCursor);
}



IMPLEMENT_DYNAMIC(MSJSuperView, CScrollView)

