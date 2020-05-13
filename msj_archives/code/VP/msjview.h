// MSJ Visual Developer Column
//
// This source code is a small sub-set of one of 50 classes
// found in Stingray's Objective Toolkit product
// For more information: http://www.stingsoft.com

//  Author:		Scot Wingo and George Shepherd.
//  Description:	Declarations for MSJSuperView
//  Created:		9/1/97
//

#ifndef __MSJSUPERVIEW_H__
#define __MSJSUPERVIEW_H__

//Enumerations for intellimouse support.
enum MSJDirectionType {
	MSJ_UP               = 1,
	MSJ_LEFT             = 2,
	MSJ_DOWN             = 3,
	MSJ_RIGHT            = 4,
	MSJ_PGDOWN           = 5,
	MSJ_PGUP             = 6,
	MSJ_TOP              = 7,
	MSJ_BOTTOM           = 8,
	MSJ_MOSTLEFT         = 9,
	MSJ_MOSTRIGHT        = 10,
	MSJ_TOPLEFT          = 11,
	MSJ_BOTTOMRIGHT      = 12,

};

class MSJSuperView : public CScrollView
{
    DECLARE_DYNAMIC(MSJSuperView);
public:
// Construction    
protected:
    MSJSuperView();         // protected constructor used by dynamic creation
    
// Operations
public:
    // Overridden CScrollView member functions
    // sizeDefault lives in scrollview?
    void   SetScrollSizes(int nMapMode,
			  SIZE sizeTotal, const SIZE& sizePage = sizeDefault,
			  const SIZE& sizeLine = sizeDefault);

	CPoint GetLogicalCenterPoint(void);
   void   CenterOnLogicalPoint(CPoint ptCenter);
    
    // Zooming functions
    float GetZoomLevel() {return m_fZoomScale;};
    void     ZoomIn    (CPoint *point = NULL, float delta = 1.25);
    void     ZoomOut   (CPoint *point = NULL, float delta = 1.25);
    
    //Arguments slightly different, so people can just enter percent
    //and have point as default instead of having to specify null point.
    //void     ZoomPercent(int nPercent = 25,CPoint *point = NULL);
    
    // Zooming utility functions
    void      ViewDPtoLP (LPPOINT lpPoints, int nCount = 1);
    void      ViewLPtoDP (LPPOINT lpPoints, int nCount = 1);
    void      ClientToDevice(CPoint &point);

	//Panning member functions.
	BOOL DoScroll(int nDirection, int nSize);
	void MySetCursor(int nCursor);

#ifdef _DEBUG
    void AssertValid() const;
#endif //_DEBUG

// Overrideables
protected:
    // Override this to get zoom scale change notifications.
    virtual void ZoomLevelChanged(void) {};
    virtual void SetZoomLevel(float);

// Implementation
protected:
    virtual ~MSJSuperView();

    virtual void OnDraw(CDC* pDC) = 0; // Pass on Pure Virtual from CScrollView
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    // Printing support
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

    
protected:
    void      PersistRatio(const CSize &orig, CSize &dest, CPoint &remainder);
    void      ReCalcBars(void);
    void      UpdateViewport(CPoint * ptNewCenter);
    
    // Private member variables
    CSize     m_szOrigTotalDev;  // Origional total size in device units
    CSize     m_szOrigPageDev;   // Origional page scroll size in device units
    CSize     m_szOrigLineDev;   // Origional line scroll size in device units
    float     m_fZoomScale;      // Current ratio between device/logical units

	// Mouse Wheel members
	BOOL m_bMouseWheelDrag;
	int m_nMouseWheelTimer;
	CPoint m_ptMouseWheelOrg;
	MSJMouseWheelOriginWnd * m_pWndDrag;
    
public:
    // Generated message map functions
    //{{AFX_MSG(SECZoomView)
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint );
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP();
};

#endif // __MSJSUPERVIEW_H__
