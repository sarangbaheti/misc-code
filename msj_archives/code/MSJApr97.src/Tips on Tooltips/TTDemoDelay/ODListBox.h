// ODListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CODListBox window

#include "TitleTipListBox.h"

class CODListBox : public CTitleTipListBox
{
// Construction
public:
	CODListBox();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CODListBox();

protected:
	const int m_nEdgeSpace; // Extra space surrounding text
	const int m_nFontHeight; // Height of font
	CFont m_Font; // Font used for displaying item

	virtual int GetIdealItemRect(int nIndex, LPRECT lpRect);

	// Generated message map functions
protected:
	//{{AFX_MSG(CODListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
