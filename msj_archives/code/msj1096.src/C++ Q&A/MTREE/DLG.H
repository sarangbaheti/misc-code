#include "multree.h"

/////////////////
// Dialog to test multiple-selection tree control.
// Lets user add/insert items.
//
class CMyDialog : public CDialog {
public:
   CMyDialog(CWnd* pParent = NULL);   // standard constructor

   //{{AFX_DATA(CMyDialog)
   enum { IDD = IDD_DIALOG1 };
   CMultiTreeCtrl m_wndTree;  // Tree control
   CEdit          m_wndEdit;  // Edit control for item to add/insert
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CMyDialog)
   protected:
   virtual BOOL OnInitDialog();
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   void AppendItemNames(CString&s, HTREEITEM hItem);
   HTREEITEM AddItem(const TCHAR* lpText, HTREEITEM hParentItem);

protected:
   //{{AFX_MSG(CMyDialog)
   afx_msg void OnSelectAll();
   afx_msg void OnDeselectAll();
   afx_msg void OnAddItem();
   afx_msg void OnInsertItem();
   afx_msg void OnDeleteItem();
   afx_msg void OnShowSelected();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
