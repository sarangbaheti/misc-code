// stdpane.h : header file

#ifndef STDPANE_H
#define STDPANE_H

class CStdPane : public CWnd
{								// class CStdPane
$$IF(multipane)
	DECLARE_DYNCREATE(CStdPane)
protected:
	CStdPane();
$$ELSE // not multipane
public:
	CStdPane(CWnd* parent);
$$ENDIF // not multipane	

	//{{AFX_VIRTUAL(CStdPane)
$$IF(multipane)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
$$ENDIF
	//}}AFX_VIRTUAL

public:
	virtual ~CStdPane();

protected:
	//{{AFX_MSG(CStdPane)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
