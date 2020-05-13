
//***********************************************************************
//
//  MainFrame.h
//
//***********************************************************************

class CMainFrame : public CFrameWnd
{
    DECLARE_DYNCREATE (CMainFrame)

protected:
    virtual BOOL PreCreateWindow (CREATESTRUCT&);

    afx_msg int OnCreate (LPCREATESTRUCT);
    afx_msg void OnRefreshDrive (UINT);

    DECLARE_MESSAGE_MAP ()
};



