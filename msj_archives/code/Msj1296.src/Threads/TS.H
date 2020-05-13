#ifndef _TSW
#define _TSW

#include <afxmt.h>

class CThreadSafeWnd
{
public:
	CThreadSafeWnd() {}
	~CThreadSafeWnd() {}

	void SetWindow(CWnd* pwnd) {m_pCWnd = pwnd;}
	void PaintCircle(COLORREF color, CRect& rc);

private:
	CWnd* m_pCWnd;
	CCriticalSection m_CSect;
};

#endif