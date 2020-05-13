// TitleTip.cpp : implementation file
//

#include "stdafx.h"
#include "TitleTip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleTip

LPCSTR CTitleTip::m_pszWndClass = NULL;

CTitleTip::CTitleTip()
:m_nNoIndex(-1) 
{
	// Register the window class if it has not already been registered by
	// previous instantiation of CTitleTip.
	if (m_pszWndClass == NULL)
	{
		m_pszWndClass = AfxRegisterWndClass(
			CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW);
	}
	m_nItemIndex = m_nNoIndex;
	m_pListBox = NULL;
}

CTitleTip::~CTitleTip()
{
}

BOOL CTitleTip::Create(CListBox* pParentWnd)
{
	ASSERT_VALID(pParentWnd);
	m_pListBox = pParentWnd;

	// Don't add border to regular (non owner-draw) listboxes because
	// owner-draw item automatically adds border.
	DWORD dwStyle = WS_POPUP;
	if (!IsListBoxOwnerDraw())
	{
		dwStyle |= WS_BORDER;
	}

	return CreateEx(0, m_pszWndClass, NULL, 
		dwStyle, 0, 0, 0, 0,
		pParentWnd->GetSafeHwnd(), NULL, NULL);
}

BOOL CTitleTip::IsListBoxOwnerDraw()
{
	ASSERT_VALID(m_pListBox);
	DWORD dwStyle = m_pListBox->GetStyle();
	return (dwStyle & LBS_OWNERDRAWFIXED) || (dwStyle & LBS_OWNERDRAWVARIABLE);
}

void CTitleTip::Show(CRect DisplayRect, int nItemIndex)
{
	ASSERT_VALID(m_pListBox);
	ASSERT(nItemIndex < m_pListBox->GetCount()); 
	ASSERT(nItemIndex >= 0);
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(!DisplayRect.IsRectEmpty());

	// Invalidate if new item.
	if (m_nItemIndex != nItemIndex)
	{
		m_nItemIndex = nItemIndex;
		InvalidateRect(NULL);
	}

	// Adjust window position and visibility.
	CRect WindowRect;
	GetWindowRect(WindowRect);
	int nSWPFlags = SWP_SHOWWINDOW | SWP_NOACTIVATE;
	if (WindowRect == DisplayRect)
	{
		nSWPFlags |= SWP_NOMOVE | SWP_NOSIZE;
	}
	VERIFY(SetWindowPos(&wndTopMost, 
		DisplayRect.left, DisplayRect.top, DisplayRect.Width(), DisplayRect.Height(), 
		nSWPFlags));
}

void CTitleTip::Hide()
{
	ASSERT(::IsWindow(m_hWnd));
	ShowWindow(SW_HIDE);
}


BEGIN_MESSAGE_MAP(CTitleTip, CWnd)
	//{{AFX_MSG_MAP(CTitleTip)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTitleTip message handlers

void CTitleTip::OnPaint() 
{
	ASSERT(m_nItemIndex != m_nNoIndex);

	CPaintDC DC(this);

	int nSavedDC = DC.SaveDC();

	CRect ClientRect;
	GetClientRect(ClientRect);

	if (IsListBoxOwnerDraw())
	{
		// Let the listbox do the real drawing.
		DRAWITEMSTRUCT DrawItemStruct;

		DrawItemStruct.CtlType = ODT_LISTBOX;
		DrawItemStruct.CtlID = m_pListBox->GetDlgCtrlID();
		DrawItemStruct.itemID = m_nItemIndex;
		DrawItemStruct.itemAction = ODA_DRAWENTIRE;
		DrawItemStruct.hwndItem = m_pListBox->GetSafeHwnd();
		DrawItemStruct.hDC = DC.GetSafeHdc();
		DrawItemStruct.rcItem = ClientRect;
		DrawItemStruct.itemData = m_pListBox->GetItemData(m_nItemIndex);
		DrawItemStruct.itemState = (m_pListBox->GetSel(m_nItemIndex) > 0 ? ODS_SELECTED : 0);
		if (m_pListBox->GetStyle() & LBS_MULTIPLESEL)
		{
			if (m_pListBox->GetCaretIndex() == m_nItemIndex)
			{
				DrawItemStruct.itemState |= ODS_FOCUS;
			}
		}
		else
		{
			DrawItemStruct.itemState |= ODS_FOCUS;
		}

		m_pListBox->DrawItem(&DrawItemStruct);
	}
	else
	{
		// Do all of the drawing ourselves
		CFont* pFont = m_pListBox->GetFont();
		ASSERT_VALID(pFont);
		DC.SelectObject(pFont);

		COLORREF clrBackground = RGB(255, 255, 255);
		if (m_pListBox->GetSel(m_nItemIndex) > 0)
		{
			DC.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
			clrBackground = ::GetSysColor(COLOR_HIGHLIGHT);
		}

		// Draw background
		DC.FillSolidRect(ClientRect, clrBackground);

		// Draw text of item
		CString strItem;
		m_pListBox->GetText(m_nItemIndex, strItem);
		ASSERT(!strItem.IsEmpty());
		DC.SetBkMode(TRANSPARENT);
		DC.TextOut(1, -1, strItem);
	}

	DC.RestoreDC(nSavedDC);

	// Do not call CWnd::OnPaint() for painting messages
}

