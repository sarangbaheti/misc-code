// Circle.cpp : implementation of the CCircle class
//

#include "stdafx.h"
#include "circle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCircle

CCircle::CCircle()
{
	m_CenterPoint = CPoint(0, 0);
	m_nRadius = 0;
	m_Color = 0;
}


void CCircle::Initialize(const CPoint& CenterPoint, int nRadius, COLORREF Color)
{
	m_CenterPoint = CenterPoint;
	m_nRadius = nRadius;
	m_Color = Color;
}

/////////////////////////////////////////////////////////////////////////////
// CCircle drawing

void CCircle::Draw(CDC* pDC) const
{
	ASSERT_VALID(pDC);

	CRect Rect;
	Rect.top = m_CenterPoint.y - m_nRadius;
	Rect.bottom = m_CenterPoint.y + m_nRadius;
	Rect.left = m_CenterPoint.x - m_nRadius;
	Rect.right = m_CenterPoint.x + m_nRadius;

	CBrush Brush;
	Brush.CreateSolidBrush(m_Color);
	CBrush* pOldBrush = pDC->SelectObject(&Brush);

	VERIFY(pDC->Ellipse(Rect));

	pDC->SelectObject(pOldBrush);
}

/////////////////////////////////////////////////////////////////////////////
// CCircle hittesting

inline double Square(int n) { return (double(n) * double(n)); }

BOOL CCircle::HitTest(const CPoint& Point) const
{
	CPoint Diff = m_CenterPoint - Point;
	return ((Square(Diff.x) + Square(Diff.y)) <= Square(m_nRadius));
}


