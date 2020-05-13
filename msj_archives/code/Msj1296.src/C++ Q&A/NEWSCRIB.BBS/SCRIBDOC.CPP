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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
   //{{AFX_MSG_MAP(CScribbleDoc)
   ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
   ON_COMMAND(ID_PEN_THICK_OR_THIN, OnPenThickOrThin)
   ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
   ON_UPDATE_COMMAND_UI(ID_PEN_THICK_OR_THIN, OnUpdatePenThickOrThin)
   //}}AFX_MSG_MAP

END_MESSAGE_MAP()

CScribbleDoc::CScribbleDoc()
{
}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
   if (!CDocument::OnNewDocument())
      return FALSE;
   InitDocument();
   m_bInitialized = FALSE; // Not initialized yet
   return TRUE;
}

void CScribbleDoc::Serialize(CArchive& ar)
{
   if (ar.IsStoring()) {
   } else {
   }
   m_strokeList.Serialize(ar);
}

BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
   if (!CDocument::OnOpenDocument(lpszPathName))
      return FALSE;
   InitDocument();
   return m_bInitialized = TRUE; // an open doc is initialized
}

void CScribbleDoc::DeleteContents() 
{
   while (!m_strokeList.IsEmpty()) {
      delete m_strokeList.RemoveHead();
   }
   CDocument::DeleteContents();
}

//////////////////
// NOTE: This is the old function from the tutorial code. It's called
// InitDocument but it's only the raw initialization, not the
// "real" initialization, which requires setting m_bInitialized to TRUE.
//
void CScribbleDoc::InitDocument()
{
   m_bThickPen = FALSE;
   m_nThinWidth = 2;   // default thin pen is 2 pixels wide
   m_nThickWidth = 5;  // default thick pen is 5 pixels wide
   ReplacePen();       // initialize pen according to current width
}

CStroke* CScribbleDoc::NewStroke()
{
   CStroke* pStrokeItem = new CStroke(m_nPenWidth);
   m_strokeList.AddTail(pStrokeItem);
   SetModifiedFlag();  // Mark the document as having been modified, for
                  // purposes of confirming File Close.
   return pStrokeItem;
}

//////////////////
// This function REALLY initializes a new document, as opposed to
// OnNewDocument. That is, it performs the initialization required
// to use the document. It's called when the user invokes the File New
// command from the menu. This implementation doesn't actually do anything,
// it just sleeps to simulate some long operation a real app might do.
//
BOOL CScribbleDoc::Initialize()
{
   // This implementation doesn't actually do anything
   // except sleep for three seconds to simulate a lengthy operation
   //
   CWaitCursor wait;   // display wait cursor
   Sleep(3000);
	UpdateAllViews(NULL);
   return m_bInitialized = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStroke

IMPLEMENT_SERIAL(CStroke, CObject, 1)
CStroke::CStroke()
{
   // This empty constructor should be used by serialization only
}

CStroke::CStroke(UINT nPenWidth)
{
   m_nPenWidth = nPenWidth;
}

void CStroke::Serialize(CArchive& ar)
{
   if (ar.IsStoring()) {
      ar << (WORD)m_nPenWidth;
      m_pointArray.Serialize(ar);
   } else {
      WORD w;
      ar >> w;
      m_nPenWidth = w;
      m_pointArray.Serialize(ar);
   }
}

BOOL CStroke::DrawStroke(CDC* pDC)
{
   CPen penStroke;
   if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
      return FALSE;
   CPen* pOldPen = pDC->SelectObject(&penStroke);
   pDC->MoveTo(m_pointArray[0]);
   for (int i=1; i < m_pointArray.GetSize(); i++) {
      pDC->LineTo(m_pointArray[i]);
   }

   pDC->SelectObject(pOldPen);
   return TRUE;
}

void CScribbleDoc::OnEditClearAll() 
{
   DeleteContents();
   SetModifiedFlag();  // Mark the document as having been modified, for
                       // purposes of confirming File Close.
   UpdateAllViews(NULL);
}

void CScribbleDoc::OnPenThickOrThin() 
{
   // Toggle the state of the pen between thin or thick.
   m_bThickPen = !m_bThickPen;

   // Change the current pen to reflect the new user-specified width.
   ReplacePen();
}

void CScribbleDoc::ReplacePen()
{
   m_nPenWidth = m_bThickPen? m_nThickWidth : m_nThinWidth;

   // Change the current pen to reflect the new user-specified width.
   m_penCur.DeleteObject();
   m_penCur.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)); // solid black
}

void CScribbleDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(!m_strokeList.IsEmpty());
}

void CScribbleDoc::OnUpdatePenThickOrThin(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_bThickPen);
}
