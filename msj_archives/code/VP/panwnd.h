// MSJ Visual Developer Column
//
// This source code is a small sub-set of one of 50 classes
// found in Stingray's Objective Toolkit product
// For more information: http://www.stingsoft.com

//  Author:		Scot Wingo and George Shepherd.
//  Description:	Declarations for MSJSuperView
//  Created:		9/1/97
//


#ifndef __PANWND_H__
#define __PANWND_H__

//Predeclaration for global helper function.
void MSJDrawTransparentBitmap(CDC* pDC, CBitmap* pBitmap, int xStart,
	int yStart, COLORREF cTransparentColor);

//Window class to help us with drawing of cursor.
class MSJMouseWheelOriginWnd: public CWnd
{
public:
	MSJMouseWheelOriginWnd(int nID);
	BOOL CreateWnd(CWnd* pParent);
	CBitmap m_bmOrigin;
	CSize m_size;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXDragLineWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //__PANWND_H__
