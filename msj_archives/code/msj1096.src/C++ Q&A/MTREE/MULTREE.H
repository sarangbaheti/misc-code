/////////////////
// Modified tree control class handles multiple selection.
//
class CMultiTreeCtrl : public CTreeCtrl {
private:
   BOOL        m_bControlKeyDown;

public:
   CMultiTreeCtrl();
   virtual ~CMultiTreeCtrl();

   // Functions to select or deselect all items within an item
   void SelectAll(HTREEITEM hItem, UINT uSelState);
   void SelectAll(UINT uSelState) {
      SelectAll(GetRootItem(), uSelState);
   }

protected:
   //{{AFX_MSG(CMultiTreeCtrl)
   afx_msg void OnSelChanged (LPNMHDR pnmhdr, LRESULT *pLResult);
   afx_msg void OnSelChanging(LPNMHDR pnmhdr, LRESULT *pLResult);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
};

