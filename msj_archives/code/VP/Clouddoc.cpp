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

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define CLOUD_SIZE 50
/////////////////////////////////////////////////////////////////////////////
// CCloudDoc

IMPLEMENT_DYNCREATE(CCloudDoc, CDocument)

BEGIN_MESSAGE_MAP(CCloudDoc, CDocument)
	//{{AFX_MSG_MAP(CCloudDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloudDoc construction/destruction

CCloudDoc::CCloudDoc()
{
	// TODO: add one-time construction code here

}

CCloudDoc::~CCloudDoc()
{
}

void CCloudDoc::InitDocument()
{
    //Let's create a big document so we have scrollbars always.
    
    m_sizeDoc = CSize(3000,3000);
}

BOOL CCloudDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	    return FALSE;
	InitDocument();
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCloudDoc serialization

void CCloudDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()){
	ar << m_sizeDoc;
    }
    else{
	ar >> m_sizeDoc;
    }
    m_cloudList.Serialize(ar);
    return;
}

CCloud* CCloudDoc::NewCloud(CPoint ptNew)
{
    CCloud* pCloudNew = new CCloud(ptNew,m_cloudList.GetCount() + 1);
    m_cloudList.AddTail(pCloudNew);
    SetModifiedFlag();  // Mark the document as having been modified, for
    // purposes of confirming File Close.
    return pCloudNew;
}


/////////////////////////////////////////////////////////////////////////////
// CCloudDoc diagnostics

#ifdef _DEBUG
void CCloudDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCloudDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


#ifdef ORIG_CODE //Win16 barfs on LPCTSTR
BOOL CCloudDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    if (!CDocument::OnOpenDocument(lpszPathName))
	return FALSE;
    
    InitDocument();    
    return TRUE;
}
#else
BOOL CCloudDoc::OnOpenDocument(const TCHAR *pszPathName)
{
    if (!CDocument::OnOpenDocument(pszPathName))
	return FALSE;
    
    InitDocument();    
    return TRUE;
}

#endif


void CCloudDoc::DeleteContents()
{
    while (!m_cloudList.IsEmpty()) {
	delete m_cloudList.RemoveHead();
    }
    CDocument::DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
// CCloud

IMPLEMENT_SERIAL(CCloud, CObject, 1)
CCloud::CCloud()
{
	// This empty constructor should be used by serialization only
}

CCloud::CCloud(CPoint ptNew, int nNewNumber)
{
    m_ptCenter            = ptNew;
    m_nCloudNumber        = nNewNumber;
    
}

void CCloud::Serialize(CArchive& ar)
{
    if (ar.IsStoring()){
	ar <<m_ptCenter;
	ar <<(WORD)m_nCloudNumber;
    }
    else{
	ar >>m_ptCenter;
	WORD w;
	ar >> w;
	m_nCloudNumber = w;
	
    }
    return;
}

BOOL CCloud::DrawCloud(CDC* pDC)
{
    CPen penCloud;
    TCHAR buffer[256];
    
    if (!penCloud.CreatePen(PS_SOLID, 4, RGB(0,0,0)))
	return FALSE;
    CPen* pOldPen = pDC->SelectObject(&penCloud);
    CRect rectCloud(m_ptCenter.x - CLOUD_SIZE,m_ptCenter.y - CLOUD_SIZE,
		    m_ptCenter.x + CLOUD_SIZE,m_ptCenter.y + CLOUD_SIZE);
    //Later this will be arc calls for cloud drawing.
    pDC->Ellipse(&rectCloud);
    
    _stprintf(buffer,_T("Circle %d"),m_nCloudNumber);

    CFont textFont;
    textFont.CreateFont(-19,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));

    CRect recTextSize(0,0,0,0);
    CFont * pOldFont = pDC->SelectObject(&textFont);
    pDC->DrawText(buffer,_tcsclen(buffer),&recTextSize,DT_CALCRECT);

    
    CRect recText(m_ptCenter.x - recTextSize.Width()/2,
		  m_ptCenter.y - recTextSize.Height()/2,
		  m_ptCenter.x + recTextSize.Width(),
		  m_ptCenter.y + recTextSize.Height());
    
    pDC->DrawText(buffer,_tcsclen(buffer),&recText,DT_LEFT);
    
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldFont);
    return TRUE;
}

CRect& CCloud::GetBoundingRect()
{
    m_rectBounding.left   = m_ptCenter.x -CLOUD_SIZE - 5;
    m_rectBounding.right  = m_ptCenter.x +CLOUD_SIZE + 5;
    m_rectBounding.top    = m_ptCenter.y -CLOUD_SIZE - 5;
    m_rectBounding.bottom = m_ptCenter.y +CLOUD_SIZE + 5;
    
    return m_rectBounding;
}

