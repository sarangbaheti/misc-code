// datapane.h : header file

#ifndef DATAPANE_H
#define DATAPANE_H

class CDataPane : public CWnd
{								// class CDataPane
$$IF(multipane)
	DECLARE_DYNCREATE(CDataPane)
protected:
	CDataPane();
$$ELSE
public:
	CDataPane(CWnd* parent);
$$ENDIF

	CListCtrl	m_ctlList;

	//{{AFX_VIRTUAL(CDataPane)
$$IF(multipane)
	protected:
	virtual void PostNcDestroy();
$$ENDIF
	//}}AFX_VIRTUAL

public:
	virtual ~CDataPane();

protected:
	//{{AFX_MSG(CDataPane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
