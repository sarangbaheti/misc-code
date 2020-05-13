#include "stdafx.h"
#include "ts.h"

void CThreadSafeWnd::PaintCircle(COLORREF color, CRect& rc)
{
	CSingleLock csl(&m_CSect);
	if (csl.Lock());
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState( ));	// not necessary so far

		CDC* pdc = m_pCWnd->GetDC();
		CBrush brush(color);
		CBrush* oldbrush = pdc->SelectObject(&brush);
		pdc->Ellipse(rc);
		pdc->SelectObject(oldbrush);
		GdiFlush();						// don't wait to update the display
	}
}  
