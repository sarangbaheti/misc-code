// DTDemoView.cpp : implementation of the CDTDemoView class
//

#include "stdafx.h"
#include "DTDemo.h"

#include "DTDemoDoc.h"
#include "DTDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDTDemoView


IMPLEMENT_DYNCREATE(CDTDemoView, CView)

BEGIN_MESSAGE_MAP(CDTDemoView, CView)
	//{{AFX_MSG_MAP(CDTDemoView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTDemoView construction/destruction

CDTDemoView::CDTDemoView()
{
	m_pCircleHit = NULL;
}

CDTDemoView::~CDTDemoView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDTDemoView HitTest

const CCircle* CDTDemoView::HitTest(const CPoint& Point)
{
	CDTDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Check in reverse order to deal with clipping.
	const CCircle *pCircleHit = NULL;
	for (int n = pDoc->GetCircleCount() - 1; n >= 0 && pCircleHit == NULL; n--)
	{
		if (pDoc->GetCircle(n).HitTest(Point))
		{
			pCircleHit = &(pDoc->GetCircle(n));
		}
	}
	return pCircleHit;
}

/////////////////////////////////////////////////////////////////////////////
// CDTDemoView drawing

void CDTDemoView::OnDraw(CDC* pDC)
{
	CDTDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (int n = 0; n < pDoc->GetCircleCount(); n++)
	{
		pDoc->GetCircle(n).Draw(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDTDemoView diagnostics

#ifdef _DEBUG
void CDTDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDTDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDTDemoDoc* CDTDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDTDemoDoc)));
	return (CDTDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDTDemoView message handlers

void CDTDemoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CRect ClientRect(0, 0, 1000, 1000);
	if (m_ToolTip.Create(this, TTS_ALWAYSTIP) && m_ToolTip.AddTool(this))
	{
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, SHRT_MAX);
		m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_AUTOPOP, SHRT_MAX);
		m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_INITIAL, 200);
		m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_RESHOW, 200);
	}
	else
	{
		TRACE("Error in creating ToolTip");
	}
}

BOOL CDTDemoView::OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	BOOL bHandledNotify = FALSE;

	CPoint CursorPos;
	VERIFY(::GetCursorPos(&CursorPos));
	ScreenToClient(&CursorPos);

	CRect ClientRect;
	GetClientRect(ClientRect);

	// Make certain that the cursor is in the client rect, because the
	// mainframe also wants these messages to provide tooltips for the
	// toolbar.
	if (ClientRect.PtInRect(CursorPos))
	{
		TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
		m_pCircleHit = HitTest(CursorPos);

		if (m_pCircleHit)
		{
			// Adjust the text by filling in TOOLTIPTEXT
			CString strTip;
			const CPoint& Center = m_pCircleHit->GetCenter();
			COLORREF Color = m_pCircleHit->GetColor();
			strTip.Format("Center:  (%d, %d)\nRadius:  %d\nColor:  (%d, %d, %d)", 
				Center.x, Center.y, m_pCircleHit->GetRadius(), 
				(int)GetRValue(Color), (int)GetGValue(Color), (int)GetBValue(Color));
			ASSERT(strTip.GetLength() < sizeof(pTTT->szText));
			::strcpy(pTTT->szText, strTip);

			// Set the text color to same color as circle
			m_ToolTip.SendMessage(TTM_SETTIPTEXTCOLOR, Color, 0L);
		}
		else
		{
			pTTT->szText[0] = 0;
		}
		bHandledNotify = TRUE;
	}
	return bHandledNotify;
}

BOOL CDTDemoView::PreTranslateMessage(MSG* pMsg) 
{
	if (::IsWindow(m_ToolTip.m_hWnd) && pMsg->hwnd == m_hWnd)
	{
		switch(pMsg->message)
		{
		case WM_LBUTTONDOWN:	
		case WM_MOUSEMOVE:
		case WM_LBUTTONUP:	
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:	
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			m_ToolTip.RelayEvent(pMsg);
			break;
		}
	}
	return CView::PreTranslateMessage(pMsg);
}

void CDTDemoView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (::IsWindow(m_ToolTip.m_hWnd))
	{
		const CCircle* pCircleHit = HitTest(point);

		if (!pCircleHit || pCircleHit != m_pCircleHit)
		{
			// Use Activate() to hide the tooltip.
			m_ToolTip.Activate(FALSE);		
		}

		if (pCircleHit)
		{
			m_ToolTip.Activate(TRUE);
			m_pCircleHit = pCircleHit;
		}
	}
	CView::OnMouseMove(nFlags, point);
}
