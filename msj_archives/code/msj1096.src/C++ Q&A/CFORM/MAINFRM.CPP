#include "stdafx.h"
#include "cform.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
   //{{AFX_MSG_MAP(CMainFrame)
   ON_WM_CREATE()
   ON_WM_PAINT()
   ON_COMMAND(ID_FIX_PAINT, OnFixPaint)
   ON_UPDATE_COMMAND_UI(ID_FIX_PAINT, OnUpdateFixPaint)
   ON_COMMAND(ID_CENTER_FORM, OnCenterForm)
   ON_UPDATE_COMMAND_UI(ID_CENTER_FORM, OnUpdateCenterForm)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = {
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
   // By default, draw form centered and fix the paint error.
   m_bCenterForm = m_bFixPaint = TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
      return -1;
   
   if (!m_wndToolBar.Create(this) ||
      !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators,
        sizeof(indicators)/sizeof(UINT))) {
      TRACE0("Failed to create status bar\n");
      return -1;      // fail to create
   }

   m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

   return 0;
}

////////////////
// Recalculate the layout of the view.
// Move the view to the center of the window.
//
void CMainFrame::RecalcLayout(BOOL bNotify)
{
   // First, let MFC recalculate the layout as per the 
   // normal thing. MFC will figure out where to place 
   // the view, taking into account which status bars 
   // are displayed, etc.
   //
   CFrameWnd::RecalcLayout(bNotify);   

   CScrollView* pView = (CScrollView*)GetActiveView();
   if (pView && m_bCenterForm) {
      // Move form view to center of main 
      // window if it's smaller.
      //
      pView->GetWindowRect(&m_rcNormalView);
      ScreenToClient(&m_rcNormalView);    // view rect MFC would use
      CSize sz = pView->GetTotalSize();   // length, width
      CRect rc = m_rcNormalView;
      if (rc.Width() > sz.cx)                   // if window > form:
         rc.left += (rc.Width() -sz.cx) >> 1;   // move over half the extra
      if (rc.Height() > sz.cy)                  // ditto for height
         rc.top  += (rc.Height()-sz.cy) >> 1;   // ...

      // This actually moves the view window
      pView->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(),
         SWP_NOACTIVATE|SWP_NOZORDER);
   }
}

//////////////////
// Moving the view/form to the center of the main
// frame window will leave extra white space in upper 
// left corner. To fix this, need to paint two rectangles.
//
void CMainFrame::OnPaint() 
{
   CView* pView = GetActiveView();
   if (pView && m_bCenterForm && m_bFixPaint) {
      CPaintDC dc(this);

      // Easier to use HBRUSH than create CBrush here.
      // Note: be sure to use COLOR_3DFACE to get the
      // right logical color, in case user has customized it.
      //
      HBRUSH hOldBrush = (HBRUSH)::SelectObject(dc.m_hDC, 
         GetSysColorBrush(COLOR_3DFACE));

      CRect rc = m_rcNormalView;       // "Normal" (MFC) view pos
      CRect rcView;                    // actual view pos (we moved it)
      pView->GetWindowRect(&rcView);   // ...
      ScreenToClient(&rcView);         // ...

      // paint horz rectangle along top edge
      rc.bottom = rcView.top;
      dc.PatBlt(rc.left,rc.top,rc.Width(),rc.Height(),PATCOPY);

      // paint vert rectangle along left side
      rc.bottom = rcView.bottom;
      rc.right  = rcView.left;
      dc.PatBlt(rc.left,rc.top,rc.Width(),rc.Height(),PATCOPY);

      ::SelectObject(dc.m_hDC, hOldBrush);
   }
   CFrameWnd::OnPaint();
}

////////////////
// Below is straightforward UI stuff to manage the commands
// View Center Form and View Fix Paint
//

void CMainFrame::OnFixPaint() 
{
   m_bFixPaint = !m_bFixPaint;
   RecalcLayout();
}

void CMainFrame::OnUpdateFixPaint(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_bFixPaint);
}

void CMainFrame::OnCenterForm() 
{
   m_bCenterForm = !m_bCenterForm;
   RecalcLayout();
}

void CMainFrame::OnUpdateCenterForm(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_bCenterForm);
}
