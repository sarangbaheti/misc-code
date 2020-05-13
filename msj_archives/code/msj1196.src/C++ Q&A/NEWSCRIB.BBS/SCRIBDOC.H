////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation.
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See SCRIBBLE.CPP for Description of program.
//

// Forward declaration of data structure class
class CStroke;

class CScribbleDoc : public CDocument {
protected:
   CScribbleDoc();
   DECLARE_DYNCREATE(CScribbleDoc)
   BOOL            m_bInitialized; // ***PD: whether doc is initialized
public:
   CTypedPtrList<CObList,CStroke*>     m_strokeList;   

   CPen*    GetCurrentPen() { return &m_penCur; }
   void     InitDocument();
   CStroke* NewStroke();
   virtual  ~CScribbleDoc();

   // ***PD new functions
   BOOL     Initialize();
   BOOL     IsInitialized() { return m_bInitialized; }

   //{{AFX_VIRTUAL(CScribbleDoc)
   public:
   virtual BOOL OnNewDocument();
   virtual void Serialize(CArchive& ar);
   virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
   virtual void DeleteContents();
   //}}AFX_VIRTUAL

protected:
   // The document keeps track of the current pen width on
   // behalf of all views. We'd like the user interface of
   // Scribble to be such that if the user chooses the Draw
   // Thick Line command, it will apply to all views, not just
   // the view that currently has the focus.

   UINT            m_nPenWidth;        // current user-selected pen width
   BOOL            m_bThickPen;        // TRUE if current pen is thick
   UINT            m_nThinWidth;
   UINT            m_nThickWidth;
   CPen            m_penCur;           // pen created according to
                                       // user-selected pen style (width)
   void ReplacePen();

   //{{AFX_MSG(CScribbleDoc)
   afx_msg void OnEditClearAll();
   afx_msg void OnPenThickOrThin();
   afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
   afx_msg void OnUpdatePenThickOrThin(CCmdUI* pCmdUI);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// class CStroke
//
// A stroke is a series of connected points in the scribble drawing.
// A scribble document may have multiple strokes.

class CStroke : public CObject {
public:
   CStroke(UINT nPenWidth);

protected:
   CStroke();
   DECLARE_SERIAL(CStroke)
   UINT  m_nPenWidth;    // one pen width applies to entire stroke

public:
   CArray<CPoint,CPoint>  m_pointArray;   // series of connected points
   BOOL DrawStroke(CDC* pDC);
   virtual void Serialize(CArchive& ar);
};
