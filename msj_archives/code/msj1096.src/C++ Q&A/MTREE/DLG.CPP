#include "stdafx.h"
#include "mtree.h"
#include "dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
   //{{AFX_MSG_MAP(CMyDialog)
   ON_BN_CLICKED(IDC_SELECTALL,   OnSelectAll)
   ON_BN_CLICKED(IDC_DESELECTALL, OnDeselectAll)
   ON_BN_CLICKED(IDC_ADD,         OnAddItem)
   ON_BN_CLICKED(IDC_INSERT,      OnInsertItem)
   ON_BN_CLICKED(IDC_DELETE,      OnDeleteItem)
   ON_BN_CLICKED(IDC_SHOWSEL,     OnShowSelected)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/) 
   : CDialog(CMyDialog::IDD, pParent)
{
   //{{AFX_DATA_INIT(CMyDialog)
   //}}AFX_DATA_INIT
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CMyDialog)
   //}}AFX_DATA_MAP
}

// Some initial items to play with
//
TCHAR* MyItems[] = {
   _T("Root"),
   _T("MIND"),
   _T("Time"),
   NULL
};

/////////////////
// Initialize dialog: add some items to tree control.
//
BOOL CMyDialog::OnInitDialog()
{
   VERIFY(m_wndEdit.SubclassDlgItem(IDC_EDIT1,   this));
   VERIFY(m_wndTree.SubclassDlgItem(IDC_TREECTL, this));

   for (int i=0; MyItems[i]; i++)
      AddItem(MyItems[i], NULL);

   return CDialog::OnInitDialog();
}

/////////////////////////////////////////////////////////////////////////////
// CMyDialog message handlers

void CMyDialog::OnSelectAll() 
{
   m_wndTree.SelectAll(TVIS_SELECTED);
}

//////////////////
// When deselecting all items manually, you must also call 
//
//   m_wndTree.SelectItem(NULL); 
//
// so Windows doesn't think there's still an item selected.
//
void CMyDialog::OnDeselectAll() 
{
   m_wndTree.SelectAll(0);
   m_wndTree.SetFocus(); // so you can see the focus item
}

////////////////
// Add edit item to current level
//
void CMyDialog::OnAddItem() 
{
   CString sText;
   m_wndEdit.GetWindowText(sText);
   if (sText.GetLength() > 0)
      AddItem(sText, m_wndTree.GetParentItem(m_wndTree.GetSelectedItem()));
}

////////////////
// Insert edit item into selected level.
//
void CMyDialog::OnInsertItem() 
{
   CString sText;
   m_wndEdit.GetWindowText(sText);
   AddItem(sText, m_wndTree.GetSelectedItem());
}

////////////////
// Delete selected item. Note: Only deletes SINGLY selected
// item, not all multiply-selected items.
//
void CMyDialog::OnDeleteItem() 
{
   m_wndTree.DeleteItem(m_wndTree.GetSelectedItem());
}

////////////////
// Show selected items in message box
//
void CMyDialog::OnShowSelected() 
{
   CString s = "Selected items:\n";
   AppendItemNames(s, m_wndTree.GetRootItem());
   MessageBox(s);
}

////////////////
// Helper to append items names of all the items within an item.
// Calls itself recursively to get child names.
//
void CMyDialog::AppendItemNames(CString&s, HTREEITEM hItem) 
{
   while (hItem) {
      if (m_wndTree.GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED) {
         s += m_wndTree.GetItemText(hItem);
         s += '\n';
      }
      AppendItemNames(s, m_wndTree.GetChildItem(hItem));
      hItem = m_wndTree.GetNextSiblingItem(hItem);
   }
}

/////////////////
// Helper function to add or insert an item in the tree.
//
HTREEITEM CMyDialog::AddItem(const TCHAR* lpText, HTREEITEM hParentItem)
{
   TV_INSERTSTRUCT tvis;
   tvis.hParent = hParentItem;
   tvis.item.pszText = (TCHAR*)lpText;
   tvis.item.mask = TVIF_TEXT;
   return m_wndTree.InsertItem(&tvis);
}
