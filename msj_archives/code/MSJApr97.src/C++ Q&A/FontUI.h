////////////////////////////////////////////////////////////////
// FontUI Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See FontUI.cpp
//
class CFontUI {
protected:
	int		m_nFontSizeMin;	// min..
	int		m_nFontSizeMax;	// ..and max font size in points
	virtual  int GrowFontSize(int ptSize, int dir);
public:
	CFontUI();
	virtual ~CFontUI();
	BOOL OnChangeFont(CFont& font, int op, CWnd* pWnd=NULL, DWORD dwFlags=0);
	void SetMinMaxFontSize(int nMin, int nMax)
		{ m_nFontSizeMin = nMin; m_nFontSizeMax = nMax; }

	BOOL WriteProfileFont(LPCTSTR lpszKey, LPCTSTR lpszVal, CFont& font,
		CDC* pDC=NULL);
	BOOL GetProfileFont(LPCTSTR lpszKey, LPCTSTR lpszVal, CFont& font,
		CDC* pDC=NULL);
};
