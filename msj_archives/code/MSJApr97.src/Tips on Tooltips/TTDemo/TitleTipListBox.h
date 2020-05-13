// TitleTipListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTitleTipListBox window

#ifndef __TITLETIPLISTBOX_H__
#define __TITLETIPLISTBOX_H__

#include "TitleTip.h"

class CTitleTipListBox : public CListBox
{
// Construction
public:
	CTitleTipListBox();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitleTipListBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTitleTipListBox();

protected:
	const int m_nNoIndex; // Not a valid index
	CPoint m_LastMouseMovePoint; // Last position of mouse cursor
	BOOL m_bMouseCaptured; // Is mouse captured?
	CTitleTip m_TitleTip; // TitleTip that gets displayed when necessary

	// This method should be overridden by an owner-draw listbox.
	virtual int GetIdealItemRect(int nIndex, LPRECT lpRect);

	void AdjustTitleTip(int nNewIndex);
	void CaptureMouse();
	BOOL IsAppActive();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTitleTipListBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSelchange();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LONG OnContentChanged(UINT, LONG);

	DECLARE_MESSAGE_MAP()
};

#endif // __TITLETIPLISTBOX_H__

/////////////////////////////////////////////////////////////////////////////
