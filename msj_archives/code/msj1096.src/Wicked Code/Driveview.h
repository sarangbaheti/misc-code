//***********************************************************************
//
//  DriveView.h
//
//***********************************************************************

class CDriveView : public CTreeView
{
    DECLARE_DYNCREATE (CDriveView)

public:
    CDriveView ();
    void RefreshDrive (UINT);
    CString GetPathFromItem (HTREEITEM);
    BOOL ExpandPath (LPCTSTR, BOOL = TRUE);

protected:
    CEvent m_event;
    CImageList m_imglDrives;
    DWORD m_dwMediaID[26];
    HANDLE m_hThreads[26];
    UINT m_nThreadCount;

    UINT InitTree ();
    BOOL AddDriveNode (CString&);
    UINT AddDirectoryNodes (HTREEITEM, CString&);
    void CreateMonitoringThread (CString&);
    void SetButtonState (HTREEITEM, CString&);
    void UpdateButtonState (HTREEITEM, CString&);
    UINT DeleteChildren (HTREEITEM);
    void AddDummyNode (HTREEITEM);
    BOOL IsDriveNode (HTREEITEM);
    BOOL HasSubdirectory (CString&);
    void RefreshDirectory (HTREEITEM);
    HTREEITEM FindItem (HTREEITEM, CString&);
    HTREEITEM GetDriveNode (HTREEITEM);
    DWORD GetSerialNumber (CString&);
    BOOL IsMediaValid (CString&);
    BOOL IsPathValid (CString&);

    static UINT ThreadFunc (LPVOID);

    virtual BOOL PreCreateWindow (CREATESTRUCT&);
    virtual void OnInitialUpdate ();
    virtual void OnSelectionChanged (CString&);
  
    afx_msg void OnDestroy ();
    afx_msg void OnItemExpanding (NMHDR*, LRESULT*);
    afx_msg void OnSelChanged (NMHDR*, LRESULT*);
    afx_msg LONG OnDriveContentsChanged (UINT, LONG);

    DECLARE_MESSAGE_MAP ();
};

typedef struct tagTHREADINFO
{
    UINT    nDrive;     // Drive number (0=A, 1=B, and so on)
    HANDLE  hEvent;     // Event handle
    HWND    hWnd;       // Handle of window to receive event notification
} THREADINFO, *PTHREADINFO;

