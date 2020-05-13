////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.2 on Windows 95
//
// PFORM illustrates how to paint forms with bitmap backgrounds.
// 
#include "stdafx.h"
#include "pform.h"
#include "doc.h"
#include "view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyFormView, CFormView)

BEGIN_MESSAGE_MAP(CMyFormView, CFormView)
	//{{AFX_MSG_MAP(CMyFormView)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DRAWITEM()
	ON_COMMAND(ID_VIEW_EDIT_TOO,						OnViewEditToo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EDIT_TOO,			OnUpdateViewEditToo)
	ON_COMMAND_EX(ID_VIEW_PLAIN,						OnViewWhich)
	ON_COMMAND_EX(ID_VIEW_DENTS,						OnViewWhich)
	ON_COMMAND_EX(ID_VIEW_MARBLE,						OnViewWhich)
	ON_COMMAND_EX(ID_VIEW_MARBLE_HOLLOW,			OnViewWhich)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PLAIN,				OnUpdateViewWhich)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DENTS,				OnUpdateViewWhich)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MARBLE,			OnUpdateViewWhich)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MARBLE_HOLLOW,	OnUpdateViewWhich)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////
// Create View: create bitmaps and brushes.
//
CMyFormView::CMyFormView()	: CFormView(IDD_MYFORM)
{
	VERIFY(m_bmDents.LoadBitmap(IDB_DENTS));					// dents bitmap
	VERIFY(m_bmMarble.LoadBitmap(IDB_MARBLE));				// marble bitmap

	VERIFY(m_brDents.CreatePatternBrush(&m_bmDents));		// bitmap brush
	VERIFY(m_brCyan.CreateSolidBrush(RGB(0,255,255)));		// solid cyan brush
	VERIFY(m_brHollow.CreateStockObject(NULL_BRUSH));		// transparent brush

	// Get size of marble bitmap for tiling
	BITMAP bm;
	VERIFY(m_bmMarble.GetBitmap(&bm));
	m_szMarble = CSize(bm.bmWidth, bm.bmHeight); // size of marble bitmap
	m_nWhich = ID_VIEW_DENTS;							// start w/dents
	m_bEditToo = FALSE;									// don't paint edit controls
}

CMyFormView::~CMyFormView()
{
}

//////////////////
// Got WM_CTLCOLOR: return handle of background brush to use.
//
HBRUSH CMyFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (m_nWhich==ID_VIEW_PLAIN || (nCtlColor==CTLCOLOR_EDIT && !m_bEditToo))
		// normal processing: don't do anything
		return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// Set background mode transparent so controls will not paint over their
	// backgrounds--I am doing it with brush or WM_ERASEBKGND.
	//
	pDC->SetBkMode(TRANSPARENT);
	return m_nWhich == ID_VIEW_DENTS ? m_brDents :
		m_nWhich == ID_VIEW_MARBLE ? m_brCyan : m_brHollow;
}

//////////////////
// Erase background: If using marble bitmap, tile background with it
//
BOOL CMyFormView::OnEraseBkgnd(CDC* pDC) 
{
	if (m_nWhich>=ID_VIEW_MARBLE) { // marble or hollow marble
		CDC memdc;
		memdc.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = memdc.SelectObject(&m_bmMarble);
		CRect rc;
		GetClientRect(&rc);
		const CSize& sz = m_szMarble;
		for (int y=0; y < rc.Height(); y += sz.cy) { // for each row:
			for (int x=0; x < rc.Width(); x += sz.cx) { // for each column:
				pDC->BitBlt(x, y, sz.cx, sz.cy, &memdc, 0, 0, SRCCOPY); // copy
			}
		}
		memdc.SelectObject(pOldBitmap);
		return TRUE;
	}
	return CFormView::OnEraseBkgnd(pDC);
}

//////////////////
// Switch from dents to marble or vice versa.
// For marble backgrounds, use owner-draw buttons
//
BOOL CMyFormView::OnViewWhich(UINT nID)
{
	m_nWhich = nID;
	for (UINT id=IDOK; id<=IDCANCEL; id++) {
		CWnd* pButton = GetDlgItem(id);
		ASSERT(pButton);
		pButton->ModifyStyle(nID>=ID_VIEW_MARBLE ? 0 : BS_OWNERDRAW,
			nID>=ID_VIEW_MARBLE ? BS_OWNERDRAW : 0);
	}

	// Change static icon to owner draw if using hollow brush
	CWnd* pStatic = GetDlgItem(IDC_MYICON);
	DWORD dwStyle = pStatic->GetStyle();
	dwStyle &= ~ 0x0F;
	dwStyle |= nID>=ID_VIEW_MARBLE_HOLLOW ? SS_OWNERDRAW : SS_ICON;
	::SetWindowLong(pStatic->m_hWnd, GWL_STYLE, dwStyle);

	Invalidate(TRUE);	// repaint
	return TRUE;
}

void CMyFormView::OnUpdateViewWhich(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(pCmdUI->m_nID == m_nWhich);
}

void CMyFormView::OnViewEditToo() 
{
	m_bEditToo = !m_bEditToo;
	Invalidate(TRUE); // repaint
}

void CMyFormView::OnUpdateViewEditToo(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bEditToo);
	pCmdUI->Enable(m_nWhich!=ID_VIEW_PLAIN);
}

/////////////////
// OnSize handler eliminates jerky repaints during sizing.
// Can't use WS_CLIPCHILDREN with hollow brush beacause hollow controls
// assume parent background was painted, so I only turn WS_CLIPCHILDREN
// on if the current barckground style is not the marble w/hollow brush.
//
void CMyFormView::OnSize(UINT nType, int cx, int cy) 
{
	if (m_nWhich != ID_VIEW_MARBLE_HOLLOW)
		ModifyStyle(0, WS_CLIPCHILDREN); // turn on WS_CLIPCHILDREN

	CFormView::OnSize(nType, cx, cy);	// default

	if (m_nWhich != ID_VIEW_MARBLE_HOLLOW) {
		UpdateWindow();
		ModifyStyle(WS_CLIPCHILDREN, 0); // turn off WS_CLIPCHILDREN
	}
}

/////////////////
// Draw owner-draw buttons
//
void CMyFormView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpdis) 
{
	const UINT& nAction = lpdis->itemAction;
	if (m_nWhich>=ID_VIEW_MARBLE &&
			(nAction==ODA_DRAWENTIRE || nAction==ODA_SELECT)) {
		// Full redraw or selected (up/down) state changed
		CWnd* pCtl = CWnd::FromHandle(lpdis->hwndItem);
		CString sText;
		pCtl->GetWindowText(sText);				// button text
		CRect rc;
		pCtl->GetWindowRect(&rc);					// window rectangle..
		pCtl->ScreenToClient(&rc);					// ..client rectangle
		if (lpdis->itemState & ODS_SELECTED)	// button is down:
			rc += CPoint(1,1);						// shift southeast

		CDC* pDC = CDC::FromHandle(lpdis->hDC);

		if (m_nWhich == ID_VIEW_MARBLE) {
			// paint cyan background
			CBrush* pOldBrush = pDC->SelectObject(&m_brCyan);
			pDC->PatBlt(0, 0, rc.Width(), rc.Height(), PATCOPY);
			pOldBrush = pDC->SelectObject(pOldBrush);

		} else {
			// paint marble background
			CDC memdc;
			memdc.CreateCompatibleDC(pDC);
			CBitmap* pOldBitmap = memdc.SelectObject(&m_bmMarble);
			pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &memdc, 0, 0, SRCCOPY);
			memdc.SelectObject(pOldBitmap);
		}

		if (lpdis->CtlType==ODT_BUTTON) {
			// Draw button border using COLOR_BTNTEXT
			CBrush* pOldBrush = pDC->SelectObject(&m_brHollow);
			CPen pen(PS_SOLID, 2, GetSysColor(COLOR_BTNTEXT));
			CPen* pOldPen = pDC->SelectObject(&pen);
			pDC->Rectangle(&rc);					 // Draw rectangle

			// Draw button text
			pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));
			pDC->DrawText(sText,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			pDC->SelectObject(pOldBrush);
			pDC->SelectObject(pOldPen);
		} else {
			// Note: assumes static icon!
			pDC->DrawIcon(0, 0, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
		}

	} else
		CFormView::OnDrawItem(nIDCtl, lpdis); // default 
}
