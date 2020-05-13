//***********************************************************************
//
//  Demo.h
//
//***********************************************************************

class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
};

class CMainWindow : public CFrameWnd
{
public:
    CMainWindow ();

protected:
    void DrawRandomEllipse (CDC*, CRect&);

    afx_msg void OnLButtonDown (UINT, CPoint);
    DECLARE_MESSAGE_MAP ()
};
