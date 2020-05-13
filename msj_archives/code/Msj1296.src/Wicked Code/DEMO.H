//***************************************************************************
//
//  Demo.h
//
//***************************************************************************

#define ID_LISTVIEW 100

class CMyListCtrl : public CSortListCtrl
{
protected:
    virtual int OnCompareItems (void*, void*, int);
    virtual CString OnNeedText (void*, int);
    virtual void OnDeleteItem (void*);
};

class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
};

class CMainWindow : public CFrameWnd
{
protected:
    CMyListCtrl m_wndListView;

public:
    CMainWindow ();

protected:
    void InitListCtrl ();
    BOOL AddItemToListView (WIN32_FIND_DATA&);

    afx_msg int OnCreate (LPCREATESTRUCT);
    afx_msg void OnSize (UINT, int, int);

    DECLARE_MESSAGE_MAP ()
};

typedef struct tagITEMINFO {
    CString strFileName;
    DWORD dwFileSize;
    FILETIME ftCreated;
} ITEMINFO, *PITEMINFO;
