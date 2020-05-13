//***************************************************************************
//
//  SortView.h
//
//***************************************************************************

class CSortListCtrl : public CListCtrl
{
public:
    BOOL m_bAutoDelete;

protected:
    virtual PreCreateWindow (CREATESTRUCT&);
    virtual int OnCompareItems (void*, void*, int) = 0; // Must override
    virtual CString OnNeedText (void*, int) = 0;        // Must override
    virtual void OnDeleteItem (void*);

public:
    CSortListCtrl ();
    int InsertItem (void*, int = -1);

    static int CALLBACK CompareFunc (LPARAM, LPARAM, LPARAM);

protected:
    afx_msg void OnDestroy ();
    afx_msg LONG OnDeleteItemMsg (UINT, LONG);
    afx_msg LONG OnDeleteAllItemsMsg (UINT, LONG);
    afx_msg void OnColumnClick (NMHDR*, LRESULT*);
    afx_msg void OnGetDispInfo (NMHDR*, LRESULT*);

    DECLARE_MESSAGE_MAP ()
};

typedef struct tagSORTINFO {
    CSortListCtrl* pThis;
    int nColumn;
} SORTINFO, *PSORTINFO;
