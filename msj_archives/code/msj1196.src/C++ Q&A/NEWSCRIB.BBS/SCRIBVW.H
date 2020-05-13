////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation.
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See SCRIBBLE.CPP for Description of program.
//
class CScribbleView : public CView {
public:
   virtual ~CScribbleView();
   CScribbleDoc* GetDocument() { return (CScribbleDoc*)m_pDocument; }
protected:
   CScribbleView();
   DECLARE_DYNCREATE(CScribbleView)
   CStroke*    m_pStrokeCur;   // the stroke in progress
   CPoint      m_ptPrev;       // the last mouse pt in the stroke in progress

   // ***PD new override
   BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
      AFX_CMDHANDLERINFO* pHandlerInfo);

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CScribbleView)
   public:
   virtual void OnDraw(CDC* pDC); // ***PD override
   protected:
   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
   virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CScribbleView)
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point); // ***PD override
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
