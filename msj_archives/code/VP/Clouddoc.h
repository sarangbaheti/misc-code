// MSJ Visual Developer Column
//
// This source code is a small sub-set of one of 50 classes
// found in Stingray's Objective Toolkit product
// For more information: http://www.stingsoft.com

//  Author:		Scot Wingo and George Shepherd.
//  Description:	Declarations for MSJSuperView
//  Created:		9/1/97
//

#ifdef WIN32
#include <afxtempl.h>
#endif //WIN32

/////////////////////////////////////////////////////////////////////////////
// class CCloud
//
// A cloud is a drawing of a cloud.  All we need is it's center.

class CCloud : public CObject
{
public:
    CCloud(CPoint ptNew,int nNewNumber);

protected:
    CCloud();
    DECLARE_SERIAL(CCloud);
	
// Attributes
    CPoint m_ptCenter;
    int    m_nCloudNumber;
    CRect  m_rectBounding;

// Operations
public:
    BOOL DrawCloud(CDC* pDC);
    CRect& GetBoundingRect();
    
public:
    virtual void Serialize(CArchive& ar);
};

class CCloudDoc : public CDocument
{
protected: // create from serialization only
    CCloudDoc();
    DECLARE_DYNCREATE(CCloudDoc);
	
// Attributes
public:
    

    CTypedPtrList<CObList,CCloud*>     m_cloudList;
   
    
// Operations
public:
    CCloud * NewCloud(CPoint);
    CSize    GetDocSize() {return m_sizeDoc;}
protected:
    CSize    m_sizeDoc;
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCloudDoc)
public:
    virtual BOOL OnNewDocument();
#ifdef ORIG_CODE //Will this work on win32?
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
#else
    virtual BOOL OnOpenDocument(const TCHAR * pszPathName);
#endif
    virtual void DeleteContents();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CCloudDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    
protected:
    void            InitDocument();
// Generated message map functions
protected:
    //{{AFX_MSG(CCloudDoc)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP();
};

/////////////////////////////////////////////////////////////////////////////
