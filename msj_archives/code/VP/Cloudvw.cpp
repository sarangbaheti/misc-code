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
#include "cloud.h"

#include "clouddoc.h"
#include "cloudvw.h"
#include "mainfrm.h" //For status bars.

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCloudView

//IMPLEMENT_DYNCREATE(CCloudView, CScrollView)
IMPLEMENT_DYNCREATE(CCloudView, MSJSuperView)

//BEGIN_MESSAGE_MAP(CCloudView, CScrollView)
    BEGIN_MESSAGE_MAP(CCloudView, MSJSuperView)
    //{{AFX_MSG_MAP(CCloudView)
    ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
    ON_WM_SETCURSOR()
    ON_COMMAND(ID_EDIT_AUTOCLOUD, OnAutoCloud)
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)

END_MESSAGE_MAP()
    
/////////////////////////////////////////////////////////////////////////////
// CCloudView construction/destruction

CCloudView::CCloudView()
{
    SetScrollSizes(MM_TEXT, CSize(0, 0));
    //Turn on zooming, default is zooming off.

}

CCloudView::~CCloudView()
{

}

//	
//	OnDraw
//	
//	Much like scribble, just blast a list of clouds to
//	the display.
//	
void CCloudView::OnDraw(CDC* pDC)
{
    CCloudDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    
    // Get the invalidated rectangle of the view, or in the case
    // of printing, the clipping region of the printer dc.
    CRect rectClip;
    CRect rectCloud;
    pDC->GetClipBox(&rectClip);
    pDC->LPtoDP(&rectClip);
    rectClip.InflateRect(1, 1); // avoid rounding to nothing
    
    // Note: CScrollView::OnPaint() will have already adjusted the
    // viewport origin before calling OnDraw(), to reflect the
    // currently scrolled position.

    CTypedPtrList<CObList,CCloud*>& cloudList = pDoc->m_cloudList;
    POSITION pos = cloudList.GetHeadPosition();
    while (pos != NULL)	{
	CCloud* pCloud = cloudList.GetNext(pos);
	rectCloud = pCloud->GetBoundingRect();
	pDC->LPtoDP(&rectCloud);
	rectCloud.InflateRect(1, 1); // avoid rounding to nothing
	if (!rectCloud.IntersectRect(&rectCloud, &rectClip))
	    continue;
	pCloud->DrawCloud(pDC);
    }

}

void CCloudView::OnInitialUpdate()
{
	SetScrollInfo();
	CScrollView::OnInitialUpdate();
}

//	OnUpdate
//	
//	Sometimes a cloud comes in as hint.
//

void CCloudView::OnUpdate(CView* /* pSender */, LPARAM /* lHint */, 
	CObject* pHint) 
{
    // The document has informed this view that some data has changed.
    if (pHint != NULL){
	if (pHint->IsKindOf(RUNTIME_CLASS(CCloud))){
	    // The hint is that a stroke as been added (or changed).
	    // So, invalidate its rectangle.
	    CCloud* pCloud = (CCloud*)pHint;
	    CClientDC dc(this);
	    OnPrepareDC(&dc);
	    CRect rectInvalid = pCloud->GetBoundingRect();
	    dc.LPtoDP(&rectInvalid);
	    InvalidateRect(&rectInvalid);
	    return;
	}
    }
    // We can't interpret the hint, so assume that anything might
    // have been updated.
    Invalidate(TRUE);
    return;
}

//	
//	SetScrollInfo
//	
//	Have to call OnPrepareDC to make sure our log coords
//	are cool.
//	
void CCloudView::SetScrollInfo()
{
    CSize     sizeDoc = GetDocument()->GetDocSize();
    SetScrollSizes(MM_TEXT, sizeDoc);    
}

/////////////////////////////////////////////////////////////////////////////
// CCloudView printing

BOOL CCloudView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CCloudView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCloudView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCloudView diagnostics

#ifdef _DEBUG
void CCloudView::AssertValid() const
{
//	CScrollView::AssertValid();
	MSJSuperView::AssertValid();
}

void CCloudView::Dump(CDumpContext& dc) const
{
//	CScrollView::Dump(dc);
	MSJSuperView::Dump(dc);
}

CCloudDoc* CCloudView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCloudDoc)));
	return (CCloudDoc*)m_pDocument;
}
#endif //_DEBUG

void CCloudView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	nFlags; //UNUSED
	    CCloudDoc * pDoc = GetDocument();	    
	    CClientDC dc(this);
	    OnPrepareDC(&dc);  // set up mapping mode and viewport origin
	    dc.DPtoLP(&point);
		CCloud * pNewCloud = pDoc->NewCloud(point);
		pNewCloud->DrawCloud(&dc);
		pDoc->UpdateAllViews(this, 0L, pNewCloud);
}

//Draw some stuff on the status bar to help see what's going on.
void CCloudView::OnMouseMove(UINT nFlags, CPoint point)
{
    TCHAR buf[256];
    CPoint logPoint = point;
    nFlags; //UNUSED
    
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&logPoint);

	_stprintf(buf,_T("Log: (%d,%d) Dev: (%d,%d)"),
	    logPoint.x,logPoint.y,point.x,point.y);
    MyChangeStatusBar(1,buf);
  

}

void CCloudView::MyChangeStatusBar(int nPane,LPCTSTR text)
{
    CWinApp* pApp = AfxGetApp() ;
    CMainFrame* pFrame = (CMainFrame*)pApp->m_pMainWnd ;
    ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CMainFrame))) ;
    pFrame->MyChangePane(nPane,text);  
}        
 
void CCloudView::ZoomLevelChanged(void) //MSJSuperView overriden virtual
{
    TCHAR buffer[56];
    
    _stprintf(buffer,_T("Scale: %.3f"),GetZoomLevel()); //MSJSuperView
    MyChangeStatusBar(3,buffer);
    _stprintf(buffer,_T("Percent: %.3f"),GetZoomLevel() * 100.0f);
    MyChangeStatusBar(2,buffer);
    _stprintf(buffer,_T("%.0f"),GetZoomLevel() * 100.0f);
    MSJSuperView::ZoomLevelChanged(); //MSJSuperView
}


//	OnAutoCloud
//	Propogate the view with clouds every 200
//	logical units.
//	
//	Why?
//	
//	I'm getting tired of placing clouds ;->
//
void CCloudView::OnAutoCloud() 
{
    CCloudDoc * pDoc = GetDocument();
    CSize sizeDoc = pDoc->GetDocSize();
    CPoint tmpPoint(0,0);
    CCloud * pNewCloud;
    for (int i = 200; i < sizeDoc.cx;i +=200){
	for (int j = 200;j < sizeDoc.cy;j +=200){
	    tmpPoint.x = j;
	    tmpPoint.y = i;	    
	    pNewCloud = pDoc->NewCloud(tmpPoint);	    
	}
    }
    pDoc->UpdateAllViews(this, 0L, NULL);
    Invalidate(TRUE);
    return;
}

//	OnSetCursor
//	Cursor handler, that sets the cursor based on current 
//	zoom interface 'mode'. UI handlers call this guy to
//	force a change in cursor.
//
BOOL CCloudView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	message; //UNUSED
	nHitTest; //UNUSED
	pWnd; //UNUSED

	::SetCursor(::LoadCursor(NULL,IDC_ARROW));
	return TRUE;

}

