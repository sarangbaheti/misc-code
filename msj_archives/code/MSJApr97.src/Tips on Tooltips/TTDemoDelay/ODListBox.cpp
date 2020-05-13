// ODListBox.cpp : implementation file
//

#include "stdafx.h"
#include "TTDemo.h"
#include "ODListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODListBox

CODListBox::CODListBox()
: m_nEdgeSpace(4), m_nFontHeight(20) 
{
	VERIFY(m_Font.CreateFont(m_nFontHeight, 0, 0, 0, FW_BOLD, 
		0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial"));
}

CODListBox::~CODListBox()
{
}

int CODListBox::GetIdealItemRect(int nIndex, LPRECT lpRect)
{
	ASSERT(nIndex >= 0);

	int nResult = GetItemRect(nIndex, lpRect);

	if (nResult != LB_ERR)
	{
		CClientDC DC(this);
		CFont* pOldFont = DC.SelectObject(&m_Font);

		// Calculate the text length.
		CString strItem;
		GetText(nIndex, strItem);
		CSize TextSize = DC.GetTextExtent(strItem);

		// Take the maximum of the regular or ideal.
		lpRect->right = max(lpRect->right, 
			lpRect->left + TextSize.cx + (m_nEdgeSpace * 2));

		DC.SelectObject(pOldFont);
	}
	return nResult;
}

BEGIN_MESSAGE_MAP(CODListBox, CTitleTipListBox)
	//{{AFX_MSG_MAP(CODListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODListBox message handlers

void CODListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	ASSERT_VALID(pDC);
	int nSavedDC = pDC->SaveDC();

	CString strItem;
	if (lpDrawItemStruct->itemID != -1)
	{
		GetText(lpDrawItemStruct->itemID, strItem);
	}

	COLORREF TextColor;
	COLORREF BackColor;
	UINT nItemState = lpDrawItemStruct->itemState; 
	if (nItemState & ODS_SELECTED)
	{
		TextColor = RGB(255, 255, 255); // White
		BackColor = RGB(255, 0, 0); // Red
	}
	else
	{
		TextColor = RGB(255, 0, 0);  // Red
		BackColor = RGB(255, 255, 255); // White
	}
	
	CRect ItemRect(lpDrawItemStruct->rcItem);

	// Draw background
	pDC->FillSolidRect(ItemRect, BackColor);

	// Draw text
	pDC->SetTextColor(TextColor);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&m_Font);
	ItemRect.left += m_nEdgeSpace;
	pDC->DrawText(strItem, ItemRect, 
		DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	ItemRect.left -= m_nEdgeSpace;

	// Draw focus rect if necessary
	if (nItemState & ODS_FOCUS)
	{
		pDC->DrawFocusRect(ItemRect);
	}

	pDC->RestoreDC(nSavedDC);
}

void CODListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = m_nFontHeight + (m_nEdgeSpace * 2);	
}
