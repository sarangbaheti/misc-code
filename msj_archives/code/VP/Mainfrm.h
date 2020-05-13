// MSJ Visual Developer Column
//
// This source code is a small sub-set of one of 50 classes
// found in Stingray's Objective Toolkit product
// For more information: http://www.stingsoft.com

//  Author:		Scot Wingo and George Shepherd.
//  Description:	Declarations for MSJSuperView
//  Created:		9/1/97
//

class CZoomBar : public CToolBar
{
public:
    CComboBox   m_comboBox;
    CFont       m_font;
};

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void MyUpdatePane();
        void MyChangePane(int,LPCTSTR);
public:
	CStatusBar  m_wndStatusBar;
	CZoomBar    m_wndToolBar;
	int m_nUpdates;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
    afx_msg void OnUpdatePercent(CCmdUI *);
    afx_msg void OnUpdateLevel(CCmdUI *);
    afx_msg void OnUpdateLocation(CCmdUI *);
    afx_msg void OnUpdatePoint(CCmdUI *);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
