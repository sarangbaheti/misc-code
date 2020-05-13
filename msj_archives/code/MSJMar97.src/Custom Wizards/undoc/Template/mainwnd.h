// mainwnd.h - interface to CMainWindow class

#ifndef MAINWND_H
#define MAINWND_H

///////////////////////////////////////////////////////////////////////////////

$$IF(treepane)
class CTreePane;
$$ENDIF
$$IF(datapane)
class CDataPane;
$$ENDIF
$$IF(stdpane)
class CStdPane;
$$ENDIF

class CMainWindow : public CFrameWnd
{								// class CMainWindow
public:
	CMainWindow();
	virtual ~CMainWindow();

$$IF(multipane)
	CSplitterWnd	m_splitter;	// frame for view panes
$$ENDIF // multipane
$$IF(treepane)
	CTreePane*		m_treepane;
$$ENDIF
$$IF(datapane)
	CDataPane*		m_datapane;
$$ENDIF
$$IF(stdpane)
	CStdPane*		m_stdpane;
$$ENDIF

	//{{AFX_VIRTUAL(CMainWindow)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

protected:
$$IF(statusbar)
	CStatusBar	m_wndStatusBar;
$$ENDIF
$$IF(toolbar)
	CToolBar	m_wndToolBar;
$$ENDIF
	//{{AFX_MSG(CMainWindow)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};								// class CMainWindow

#endif
