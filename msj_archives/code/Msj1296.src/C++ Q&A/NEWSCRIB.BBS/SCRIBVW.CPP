////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation.
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See SCRIBBLE.CPP for Description of program.
//
#include "stdafx.h"
#include "Scribble.h"
#include "ScribDoc.h"
#include "ScribVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleView

IMPLEMENT_DYNCREATE(CScribbleView, CView)

BEGIN_MESSAGE_MAP(CScribbleView, CView)
   //{{AFX_MSG_MAP(CScribbleView)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   //}}AFX_MSG_MAP
   // Standard printing commands
   ON_COMMAND(ID_FILE_PRINT,         CView::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT,  CView::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleView construction/destruction

CScribbleView::CScribbleView()
{
}

CScribbleView::~CScribbleView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView drawing

void CScribbleView::OnDraw(CDC* pDC)
{
   CScribbleDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   if (pDoc->IsInitialized()) {
      // The view delegates the drawing of individual strokes to
      // CStroke::DrawStroke().
      CTypedPtrList<CObList,CStroke*>& strokeList = pDoc->m_strokeList;
      POSITION pos = strokeList.GetHeadPosition();
      while (pos != NULL) {
         CStroke* pStroke = strokeList.GetNext(pos);
         pStroke->DrawStroke(pDC);
      }
   } else {
      // Draw "empty" background.
      // Easier to use HBRUSH than create CBrush here.
      // Note: be sure to use COLOR_3DFACE to get the
      // right logical color, in case user has customized it.
      //
      CRect rc;
      GetClientRect(&rc);
      HGDIOBJ hOldBrush = pDC->SelectObject(GetSysColorBrush(COLOR_3DSHADOW));
      pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
      pDC->SelectObject(hOldBrush);
   }
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView printing

BOOL CScribbleView::OnPreparePrinting(CPrintInfo* pInfo)
{
   return DoPreparePrinting(pInfo);
}

void CScribbleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CScribbleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView message handlers

//////////////////
// **NEW: Change so drawing is allowed only if doc is initialized.
//
void CScribbleView::OnLButtonDown(UINT, CPoint point) 
{
   CScribbleDoc* pDoc = GetDocument();
   if (pDoc->IsInitialized()) {
      m_pStrokeCur = pDoc->NewStroke();
      // Add first point to the new stroke
      m_pStrokeCur->m_pointArray.Add(point);

      SetCapture();       // Capture the mouse until button up.
      m_ptPrev = point;   // Serves as the MoveTo() anchor point for the
                          // LineTo() the next point, as the user drags the
                          // mouse.
   }
   return;
}

void CScribbleView::OnLButtonUp(UINT, CPoint point) 
{
   // Mouse button up is interesting in the Scribble application
   // only if the user is currently drawing a new stroke by dragging
   // the captured mouse.

   if (GetCapture() != this)
      return; // If this window (view) didn't capture the mouse,
              // then the user isn't drawing in this window.

   CScribbleDoc* pDoc = GetDocument();

   CClientDC dc(this);

   CPen* pOldPen = dc.SelectObject(pDoc->GetCurrentPen());
   dc.MoveTo(m_ptPrev);
   dc.LineTo(point);
   dc.SelectObject(pOldPen);
   m_pStrokeCur->m_pointArray.Add(point);

   ReleaseCapture();   // Release the mouse capture established at
                       // the beginning of the mouse drag.
   return;
}

void CScribbleView::OnMouseMove(UINT, CPoint point) 
{
   // Mouse movement is interesting in the Scribble application
   // only if the user is currently drawing a new stroke by dragging
   // the captured mouse.

   if (GetCapture() != this)
      return; // If this window (view) didn't capture the mouse,
              // then the user isn't drawing in this window.

   CClientDC dc(this);
   m_pStrokeCur->m_pointArray.Add(point);

   // Draw a line from the previous detected point in the mouse
   // drag to the current point.
   CPen* pOldPen = dc.SelectObject(GetDocument()->GetCurrentPen());
   dc.MoveTo(m_ptPrev);
   dc.LineTo(point);
   dc.SelectObject(pOldPen);
   m_ptPrev = point;
   return;
}

BOOL CScribbleView::OnCmdMsg(UINT nID, int nCode, void* pExtra,
   AFX_CMDHANDLERINFO* pHandlerInfo)
{
   CScribbleDoc *pDoc = GetDocument();
   return pDoc->IsInitialized() ?
      CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) : FALSE;
}

