// Circle.h : interface of the CCircle class
//
/////////////////////////////////////////////////////////////////////////////

class CCircle
{
public:
	CCircle();
	virtual ~CCircle() {}

	void Initialize(const CPoint& CenterPoint, int nRadius, COLORREF Color);

	void Draw(CDC* pDC) const;
	BOOL HitTest(const CPoint& Point) const;

	COLORREF GetColor() const { return m_Color; }
	const CPoint& GetCenter() const { return m_CenterPoint; }
	int GetRadius() const { return m_nRadius; }

// Implementation
protected:
	CPoint m_CenterPoint;
	int m_nRadius;
	COLORREF m_Color;
};


/////////////////////////////////////////////////////////////////////////////
