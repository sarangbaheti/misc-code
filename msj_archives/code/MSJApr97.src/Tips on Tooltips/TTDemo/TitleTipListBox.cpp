// TitleTipListBox.cpp : implementation file
//

#include "stdafx.h"
#include "TitleTipListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleTipListBox

CTitleTipListBox::CTitleTipListBox()
: m_LastMouseMovePoint(0, 0), m_nNoIndex(-1)
{
	m_bMouseCaptured = FALSE;
}

CTitleTipListBox::~CTitleTipListBox()
{
	ASSERT(!m_bMouseCaptured);
}

int CTitleTipListBox::GetIdealItemRect(int nIndex, LPRECT lpRect)
{
	// Calculate the ideal rect for an item. The ideal rect is dependent
	// on the length of the string. This only works for regular 
	// (non owner-draw)listboxes.
	ASSERT(lpRect);
	ASSERT(nIndex >= 0);
	DWORD dwStyle = GetStyle();
	int	nStatus = GetItemRect(nIndex, lpRect);	
	if (nStatus != LB_ERR && !(dwStyle & LBS_OWNERDRAWFIXED) && !(dwStyle & LBS_OWNERDRAWVARIABLE))
	{
		CString strItem;
		GetText(nIndex, strItem);
		if (!strItem.IsEmpty())
		{
			// Calulate the ideal text length.
			CClientDC DC(this);
			CFont* pOldFont = DC.SelectObject(GetFont());
			CSize ItemSize = DC.GetTextExtent(strItem);
			DC.SelectObject(pOldFont);

			// Take the maximum of regular width and ideal width.
			const int cxEdgeSpace = 2;
			lpRect->right = max(lpRect->right, 
				lpRect->left + ItemSize.cx + (cxEdgeSpace * 2));
		}
	}
	else
	{
		TRACE("Owner-draw listbox detected - override CTitleTipListBox::GetIdeaItemRect()\n");
	}
	return nStatus;
}

void CTitleTipListBox::AdjustTitleTip(int nNewIndex)
{
	if (!::IsWindow(m_TitleTip.m_hWnd))
	{
		VERIFY(m_TitleTip.Create(this));
	}

	if (nNewIndex == m_nNoIndex)
	{
		m_TitleTip.Hide();
	}
	else
	{
		CRect IdealItemRect;
		GetIdealItemRect(nNewIndex, IdealItemRect);
		CRect ItemRect;
		GetItemRect(nNewIndex, ItemRect);
		if (ItemRect == IdealItemRect)
		{
			m_TitleTip.Hide();
		}
		else
		{
			// Adjust the rect for being near the edge of screen.
			ClientToScreen(IdealItemRect);
			int nScreenWidth = ::GetSystemMetrics(SM_CXFULLSCREEN);
			if (IdealItemRect.right > nScreenWidth)
			{
				IdealItemRect.OffsetRect(nScreenWidth - IdealItemRect.right, 0);
			}
			if (IdealItemRect.left < 0)
			{
				IdealItemRect.OffsetRect(-IdealItemRect.left, 0);
			}

			m_TitleTip.Show(IdealItemRect, nNewIndex);  
		}
	}

	if (m_TitleTip.IsWindowVisible())
	{
		// Make sure we capture mouse so we can detect when to turn off 
		// title tip.
		if (!m_bMouseCaptured && GetCapture() != this)
		{
			CaptureMouse();
		}
	}
	else
	{
		// The tip is invisible so release the mouse.
		if (m_bMouseCaptured)
		{
			VERIFY(ReleaseCapture());
			m_bMouseCaptured = FALSE;
		}
	}
}

void CTitleTipListBox::CaptureMouse()
{
	ASSERT(!m_bMouseCaptured);
	CPoint Point;
	VERIFY(GetCursorPos(&Point));
	ScreenToClient(&Point);
	m_LastMouseMovePoint = Point;
	SetCapture();
	m_bMouseCaptured = TRUE;
}


BOOL CTitleTipListBox::IsAppActive()
{
	BOOL bAppActive = FALSE;
	CWnd* pTopParent = GetTopLevelParent();
	CWnd* pActiveWnd = GetActiveWindow();
	if (pActiveWnd == pTopParent || pTopParent->IsChild(pActiveWnd))
	{
		bAppActive = TRUE;
	}
	return bAppActive;
}


BEGIN_MESSAGE_MAP(CTitleTipListBox, CListBox)
	//{{AFX_MSG_MAP(CTitleTipListBox)
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
	ON_WM_KILLFOCUS()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(LB_ADDSTRING, OnContentChanged)
	ON_MESSAGE(LB_INSERTSTRING, OnContentChanged)
	ON_MESSAGE(LB_DELETESTRING, OnContentChanged)
	ON_MESSAGE(LB_ADDFILE, OnContentChanged)
	ON_MESSAGE(LB_DIR, OnContentChanged)
	ON_MESSAGE(LB_RESETCONTENT, OnContentChanged)
	ON_MESSAGE(LB_SETCARETINDEX, OnContentChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitleTipListBox message handlers


LONG CTitleTipListBox::OnContentChanged(UINT, LONG)
{
	// Turn off title tip.
	AdjustTitleTip(m_nNoIndex);
	return Default();
}


void CTitleTipListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (point != m_LastMouseMovePoint && IsAppActive())
	{
		m_LastMouseMovePoint = point;

		int nIndexHit = m_nNoIndex;

		CRect ClientRect;
		GetClientRect(ClientRect);
		if (ClientRect.PtInRect(point))
		{
			// Hit test.
			for (int n = 0; nIndexHit == m_nNoIndex && n < GetCount(); n++)
			{
				CRect ItemRect;
				GetItemRect(n, ItemRect);
				if (ItemRect.PtInRect(point))
				{
					nIndexHit = n;	
				}
			}
		}
		AdjustTitleTip(nIndexHit);
	}
	CListBox::OnMouseMove(nFlags, point);
}


void CTitleTipListBox::OnSelchange() 
{
	int nSelIndex;
	if (GetStyle() & LBS_MULTIPLESEL)
	{
		nSelIndex = GetCaretIndex();	
	}
	else
	{
		nSelIndex = GetCurSel();
	}
	AdjustTitleTip(nSelIndex);
	m_TitleTip.InvalidateRect(NULL);
	m_TitleTip.UpdateWindow();
}

void CTitleTipListBox::OnKillFocus(CWnd* pNewWnd) 
{
	CListBox::OnKillFocus(pNewWnd);
	if (pNewWnd != &m_TitleTip)
	{
		AdjustTitleTip(m_nNoIndex);
	}
}

void CTitleTipListBox::OnDestroy() 
{
	AdjustTitleTip(m_nNoIndex);
	m_TitleTip.DestroyWindow();
	CListBox::OnDestroy();
}

void CTitleTipListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Temporarily disable mouse capturing because the base class may 
	// capture the mouse.

	if (m_bMouseCaptured)
	{
		ReleaseCapture();
		m_bMouseCaptured = FALSE;
	}

	CListBox::OnLButtonDown(nFlags, point);

	if (m_TitleTip.IsWindowVisible())
	{
		m_TitleTip.InvalidateRect(NULL);
		if (this != GetCapture())
		{
			CaptureMouse();
		}
	}
}

void CTitleTipListBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CListBox::OnLButtonUp(nFlags, point);

	if (this != GetCapture() && m_TitleTip.IsWindowVisible())
	{
		CaptureMouse();
	}
}


BOOL CTitleTipListBox::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
	{
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
			// Make the active view because that is the default
			// behaviour caused by WM_MOUSEACTIVATE when NO TitleTip
			// is over this window.
			AdjustTitleTip(m_nNoIndex);
			CFrameWnd* pFrameWnd = GetParentFrame();
			if (pFrameWnd)
			{
				BOOL bDone = FALSE;
				CWnd* pWnd = this;
				while (!bDone)
				{
					pWnd = pWnd->GetParent();
					if (!pWnd || pWnd == pFrameWnd)
					{
						bDone = TRUE;
					}
					else if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))
					{
						pFrameWnd->SetActiveView((CView*)pWnd);
						bDone = TRUE;
					}
				}
			}
			break;
	}
	
	return CListBox::PreTranslateMessage(pMsg);
}

