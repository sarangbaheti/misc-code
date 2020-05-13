// treepane.h : header file

#ifndef TREEPANE_H
#define TREEPANE_H

class CTreePane : public CWnd
{								// class CTreePane
$$IF(multipane)
	DECLARE_DYNCREATE(CTreePane)
protected:
	CTreePane();
$$ELSE
public:
	CTreePane(CWnd* parent);
$$ENDIF

	CTreeCtrl	m_ctlTree;
	HTREEITEM	m_root;

	//{{AFX_VIRTUAL(CTreePane)
$$IF(treepane)
protected:
	virtual void PostNcDestroy();
$$ENDIF
	//}}AFX_VIRTUAL

public:
	virtual ~CTreePane();

protected:
	//{{AFX_MSG(CTreePane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
