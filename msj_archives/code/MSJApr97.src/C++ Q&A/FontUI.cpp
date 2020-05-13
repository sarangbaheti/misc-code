////////////////////////////////////////////////////////////////
// FontUI Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// CFontUI handles the user interface for changing font sizes, as well
// as saving/restoring font info in the application profile
//
#include "StdAfx.h"
#include "FontUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFontUI::CFontUI()
{
	m_nFontSizeMin = 4;
	m_nFontSizeMax = 120;
}

CFontUI::~CFontUI()
{
}

//////////////////
// Main UI function.
//		op = 0  ==>	run common font dialog
//    op < 0  ==>	font size smaller
//    op < 0  ==>	font size bigger
//
// Returns BOOL, whether changed or not, and CFont has new font.
//
BOOL CFontUI::OnChangeFont(CFont& font, int op, CWnd* pWnd, DWORD dwFlags)
{
	// Get logical font structure
	ASSERT(font.m_hObject);
	LOGFONT logfont;
	font.GetLogFont(&logfont);
	
	if (op==0) {
		// Run common font dialog
		CFontDialog dlg(&logfont, dwFlags, NULL, pWnd);
		dlg.m_cf.nSizeMin = m_nFontSizeMin;
		dlg.m_cf.nSizeMax = m_nFontSizeMax;
		if (dlg.DoModal() != IDOK)
			return FALSE;
	} else {
		// Compute point size and increment/decrement
		CWindowDC dc(NULL);
		int ppi = dc.GetDeviceCaps(LOGPIXELSY);
		int ptSize = MulDiv(-logfont.lfHeight, 72, ppi); // convert to points
		ptSize = GrowFontSize(ptSize, op);					 // grow (or shrink)
		if (ptSize < m_nFontSizeMin  || ptSize > m_nFontSizeMax)
			return FALSE;
		logfont.lfHeight = MulDiv(-ptSize, ppi, 72);		 // convert to logical
	}

	// Change the font
	font.DeleteObject();
	return font.CreateFontIndirect(&logfont);
}

//////////////////
// Increment or decrement font point size based on current size.
// Algorithm:
// If point size is
//			<= 12		incr = 1 pts
//			10..32	incr = 2 pts
//			32..48   incr = 4 pts
//			>= 48    incr = 8 pts
// Derived classes can override this virtual function to change this.
// Return zero to disallow changing size.
//
int CFontUI::GrowFontSize(int ptSize, int dir)
{
	int incr = ptSize <= 12 ? 1 : ptSize < 32 ? 2 : ptSize < 48 ? 4 : 8;
	ptSize += dir>0 ? incr : -incr;;
	return ptSize;
}

//////////////////
// Create font from info in application profile. Reads info in the form
// facename,ptsize,weight,italic
//
BOOL CFontUI::GetProfileFont(LPCTSTR lpszKey, LPCTSTR lpszVal, CFont& font,
	CDC* pDC)
{
	CWinApp *pApp = AfxGetApp();
	ASSERT_VALID(pApp);
	CString s = pApp->GetProfileString(lpszKey, lpszVal);
	if (s.IsEmpty())
		return FALSE;

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfCharSet = DEFAULT_CHARSET;
	int bItalic;
	int iPtSize;

	// scanf is overkill, but I'm lazy
	if (sscanf((LPCTSTR)s, "%[a-zA-Z ],%d,%d,%d",
		lf.lfFaceName, &iPtSize, &lf.lfWeight, &bItalic) != 4)
		return FALSE;
	lf.lfHeight = MulDiv(-iPtSize, 	// convert ptsize to logical units
		::GetDeviceCaps(pDC ? pDC->m_hDC : ::GetDC(NULL), LOGPIXELSY), 72);
	lf.lfItalic = bItalic;	// because lf.lfItalic is a BYTE
	font.DeleteObject();		// bye 
	return font.CreateFontIndirect(&lf);
}

//////////////////
// Write font to app profile in the form "facename,ptsize,weight,italic"
//
BOOL CFontUI::WriteProfileFont(LPCTSTR lpszKey, LPCTSTR lpszVal, CFont& font,
	CDC* pDC)
{
	CWinApp *pApp = AfxGetApp();
	ASSERT_VALID(pApp);
	LOGFONT lf;
	font.GetLogFont(&lf);
	int iPtSize = MulDiv(-lf.lfHeight, 72,
		::GetDeviceCaps(pDC ? pDC->m_hDC : ::GetDC(NULL), LOGPIXELSY));
	CString s;
	s.Format("%s,%d,%d,%d", lf.lfFaceName, iPtSize, lf.lfWeight, lf.lfItalic);
	return pApp->WriteProfileString(lpszKey, lpszVal, s);
}
