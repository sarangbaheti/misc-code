#include "stdafx.h"
#include "multree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMultiTreeCtrl, CTreeCtrl)
   //{{AFX_MSG_MAP(CMultiTreeCtrl)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMultiTreeCtrl::CMultiTreeCtrl()
{
   m_bControlKeyDown = FALSE;
}

CMultiTreeCtrl::~CMultiTreeCtrl()
{
}

//////////////////
// Helper to select or deselect all items.
//
void CMultiTreeCtrl::SelectAll(HTREEITEM hItem, UINT uSelState)
{
   while (hItem) {
      SelectAll(GetChildItem(hItem), uSelState);
      SetItemState(hItem, uSelState, TVIS_SELECTED);
      hItem = GetNextSiblingItem(hItem);
   }
}

//////////////////
// Handle button-down event
//
void CMultiTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
   UINT dummy;

   if (GetKeyState(VK_CONTROL) < 0) {
      // Control key is down:
      //
      m_bControlKeyDown = TRUE;     // note it
      SetFocus();                   // to show focus item

      // Bypass default handler for multiple selection
      return;

   } else {
      // Normal (no control key):
      //
      if (HitTest(point, &dummy))   // if mouse is over an item:
         SelectAll(0);              // deselect all items
   }

   // Make sure to pass to default handler for normal selection
   CTreeCtrl::OnLButtonDown(nFlags, point);
}

//////////////////
// Handle button-up event
// 
void CMultiTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
   if (m_bControlKeyDown) {

      // Control key was down when mouse clicked:
      
      // Get item under mouse
      UINT dummy;
      HTREEITEM hItemNew = HitTest(point, &dummy);

      if (hItemNew) {
         // Figure out new selection state (= toggle current state)
         //
         UINT uNewSelState = 
            GetItemState(hItemNew, TVIS_SELECTED) & TVIS_SELECTED ? 
               0 : TVIS_SELECTED;
            
         // Get old selected item and state
         HTREEITEM hItemOld = GetSelectedItem();
         UINT uOldSelState  = hItemOld ? 
            GetItemState(hItemOld, TVIS_SELECTED) : 0;
            
         // Select new item (to get focus)
         SelectItem(hItemNew);   

         // Set proper selection (highlight) state for new item
         SetItemState(hItemNew, uNewSelState,  TVIS_SELECTED);

         // Restore state of old selected item, which
         // Windows could have changed as result of SelectItem()
         // --But don't do it if new == old
         //
         if (hItemOld && hItemOld != hItemNew)
            SetItemState(hItemOld, uOldSelState, TVIS_SELECTED);
      }
   }
   m_bControlKeyDown = FALSE; // clear

   CTreeCtrl::OnLButtonUp(nFlags, point);
}
