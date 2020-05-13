// MSJ Visual Developer Column
//
// This source code is a small sub-set of one of 50 classes
// found in Stingray's Objective Toolkit product
// For more information: http://www.stingsoft.com

//  Author:		Scot Wingo and George Shepherd.
//  Description:	Declarations for MSJSuperView
//  Created:		9/1/97
//


#ifndef __CLOUDVW_H__
#define __CLOUDVW_H__


typedef enum {NORMAL,ZOOMINPOINT,ZOOMOUTPOINT,ZOOMRECT} CloudViewMode;

#include "msjview.h"

class CCloudView : public MSJSuperView  //MSJSuperView
{
    
protected: // create from serialization only
	CCloudView();
	DECLARE_DYNCREATE(CCloudView)

// Attributes
public:
	CCloudDoc* GetDocument();

// Operations
public:
    
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCloudView)
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void ZoomLevelChanged(void);
    
protected:
    virtual void OnInitialUpdate(); // called first time after construct
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);    
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CCloudView();
    void SetScrollInfo();
    void MyChangeStatusBar(int,LPCTSTR);
    
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCloudView)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnAutoCloud();

	//}}AFX_MSG
    DECLARE_MESSAGE_MAP();
};

#ifndef _DEBUG  // debug version in cloudvw.cpp
inline CCloudDoc* CCloudView::GetDocument()
   { return (CCloudDoc*)m_pDocument; }
#endif

#endif //__CLOUDVW_H__

