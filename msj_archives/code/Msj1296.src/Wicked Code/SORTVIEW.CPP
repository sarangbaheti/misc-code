//***************************************************************************
//
//  SortView.cpp
//
//***************************************************************************

#include <afxwin.h>
#include <afxcmn.h>
#include "SortView.h"

BEGIN_MESSAGE_MAP (CSortListCtrl, CListCtrl)
    ON_WM_DESTROY ()
    ON_MESSAGE (LVM_DELETEITEM, OnDeleteItemMsg)
    ON_MESSAGE (LVM_DELETEALLITEMS, OnDeleteAllItemsMsg)
    ON_NOTIFY_REFLECT (LVN_COLUMNCLICK, OnColumnClick)
    ON_NOTIFY_REFLECT (LVN_GETDISPINFO, OnGetDispInfo)
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
// Initializers

CSortListCtrl::CSortListCtrl ()
{
    m_bAutoDelete = TRUE;
}

BOOL CSortListCtrl::PreCreateWindow (CREATESTRUCT& cs)
{
    if (!CListCtrl::PreCreateWindow (cs))
        return FALSE;

    //
    // Make sure the control has headers with clickable buttons. Also make
    // sure that neither the LVS_SORTASCENDING nor the LVS_SORTDESCENDING
    // flag is set.
    //
    cs.style &= ~(LVS_NOCOLUMNHEADER | LVS_NOSORTHEADER |
        LVS_SORTASCENDING | LVS_SORTDESCENDING);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Message handlers

void CSortListCtrl::OnDestroy ()
{
    //
    // If m_bAutoDelete is nonzero, delete the objects that the items'
    // lParams point to.
    //
    int nCount;
    if (m_bAutoDelete && (nCount = GetItemCount ())) {
        for (int i=0; i<nCount; i++) {
            DWORD dwItem = GetItemData (i);
            OnDeleteItem ((void*) dwItem);
        }
    }
    CListCtrl::OnDestroy ();
}

LONG CSortListCtrl::OnDeleteItemMsg (UINT wParam, LONG lParam)
{
    //
    // If m_bAutoDelete is nonzero, delete the object that the item's
    // lParam points to. Allow the default window procedure to delete the
    // item itself.
    //
    if (m_bAutoDelete) {
        DWORD dwItem = GetItemData ((int) wParam);
        LRESULT lResult = Default (); // Must come BEFORE OnDeleteItem!
        OnDeleteItem ((void*) dwItem);
        return lResult;
    }
    return Default ();
}

LONG CSortListCtrl::OnDeleteAllItemsMsg (UINT wParam, LONG lParam)
{
    //
    // If m_bAutoDelete is nonzero, delete the objects that the items'
    // lParams point to. Allow the default window procedure to delete the
    // items themselves.
    //
    int nCount;
    if (m_bAutoDelete && (nCount = GetItemCount ())) {
        for (int i=0; i<nCount; i++) {
            DWORD dwItem = GetItemData (i);
            OnDeleteItem ((void*) dwItem);
        }
    }
    return Default ();
}

void CSortListCtrl::OnColumnClick (NMHDR* pnmh, LRESULT* pResult) 
{
    //
    // When a header button is clicked, call the control's SortItems
    // function to sort the data in the column. The column number in the
    // second parameter is the lParamSort parameter that's passed to the
    // comparison function.
    //
    NM_LISTVIEW* pnmlv = (NM_LISTVIEW*) pnmh;

    SORTINFO si;
    si.pThis = this;
    si.nColumn = pnmlv->iSubItem;

    SortItems (CompareFunc, (DWORD) &si);
}

void CSortListCtrl::OnGetDispInfo (NMHDR* pnmh, LRESULT* pResult)
{
    //
    // Call the derived class's virtual OnNeedText function to get the
    // display text for the requested item/subitem.
    //
    LV_DISPINFO* plvdi = (LV_DISPINFO*) pnmh;

    if (plvdi->item.mask & LVIF_TEXT) {
        void* pItem = (void*) plvdi->item.lParam;
        CString string = OnNeedText (pItem, plvdi->item.iSubItem);
        ::lstrcpy (plvdi->item.pszText, string);
    }
}

/////////////////////////////////////////////////////////////////////////////
// Overridables

void CSortListCtrl::OnDeleteItem (void* pItem)
{
    //
    // If this function gets called, m_bAutoDelete better be FALSE.
    // Otherwise, somebody forgot to override it in the derived class.
    //
    ASSERT (!m_bAutoDelete);
}

/////////////////////////////////////////////////////////////////////////////
// Public interface functions

int CSortListCtrl::InsertItem (void* pItem, int nItem)
{
    //
    // Insert an item into the control. The key here is that the item's
    // lParam is actually a pointer to the object that holds the item's
    // data. pszText is set to LPSTR_TEXTCALLBACK so our OnGetDispInfo
    // function will be called to get the text of an item or subitem.
    //
    LV_ITEM item;
    item.mask = LVIF_TEXT | LVIF_PARAM;
    item.pszText = LPSTR_TEXTCALLBACK;
    item.iItem = (nItem == -1) ? GetItemCount () : nItem;
    item.iSubItem = 0;
    item.lParam = (LPARAM) pItem;

    return CListCtrl::InsertItem (&item);
}

/////////////////////////////////////////////////////////////////////////////
// Comparison function

int CALLBACK CSortListCtrl::CompareFunc (LPARAM lParam1, LPARAM lParam2,
    LPARAM lParamSort)
{
    //
    // Call the derived class's virtual OnCompareItems function to
    // compare the items or subitems referenced by lParam1 and lParam2.
    //
    PSORTINFO psi = (PSORTINFO) lParamSort;
    CSortListCtrl* pThis = psi->pThis;
    int nColumn = psi->nColumn;

    return pThis->OnCompareItems ((void*) lParam1, (void*) lParam2, nColumn);
}
