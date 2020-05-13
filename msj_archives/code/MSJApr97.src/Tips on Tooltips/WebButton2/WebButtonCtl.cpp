// WebButtonCtl.cpp : Implementation of the CWebButtonCtrl OLE control class.

#include "stdafx.h"
#include "WebButton.h"
#include "WebButtonCtl.h"
#include "WebButtonPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWebButtonCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWebButtonCtrl, COleControl)
	//{{AFX_MSG_MAP(CWebButtonCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_MESSAGE(OCM_DRAWITEM, OnOcmDrawItem)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolNeedText)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CWebButtonCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CWebButtonCtrl)
	DISP_PROPERTY_NOTIFY(CWebButtonCtrl, "ToolTipEnabled", m_bToolTipEnabled, OnToolTipEnabledChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CWebButtonCtrl, "ToolTipText", m_strToolTipText, OnToolTipTextChanged, VT_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CWebButtonCtrl, COleControl)
	//{{AFX_EVENT_MAP(CWebButtonCtrl)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CWebButtonCtrl, 1)
	PROPPAGEID(CWebButtonPropPage::guid)
END_PROPPAGEIDS(CWebButtonCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWebButtonCtrl, "WEBBUTTON.WebButtonCtrl.1",
	0x381c5023, 0x2fda, 0x11d0, 0x8b, 0xc1, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CWebButtonCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DWebButton =
	{ 0x381c5021, 0x2fda, 0x11d0, 
        { 0x8b, 0xc1, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DWebButtonEvents =
	{ 0x381c5022, 0x2fda, 0x11d0, 
        { 0x8b, 0xc1, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwWebButtonOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_ACTSLIKEBUTTON;

IMPLEMENT_OLECTLTYPE(CWebButtonCtrl, IDS_WEBBUTTON, _dwWebButtonOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::CWebButtonCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CWebButtonCtrl

BOOL CWebButtonCtrl::CWebButtonCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_WEBBUTTON,
			IDB_WEBBUTTON,
			afxRegApartmentThreading,
			_dwWebButtonOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::CWebButtonCtrl - Constructor

CWebButtonCtrl::CWebButtonCtrl()
{
	InitializeIIDs(&IID_DWebButton, &IID_DWebButtonEvents);
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::~CWebButtonCtrl - Destructor

CWebButtonCtrl::~CWebButtonCtrl()
{
	if (m_Bitmap.m_hObject)
	{
		m_Bitmap.DeleteObject();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::OnDraw - Drawing function

void CWebButtonCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DoSuperclassPaint(pdc, rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::DoPropExchange - Persistence support

void CWebButtonCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	VERIFY(PX_Bool(pPX, "ToolTipEnabled", m_bToolTipEnabled, 1));
	VERIFY(PX_String(pPX, "ToolTipText", m_strToolTipText, 
        "WebButton ToolTip"));
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::OnResetState - Reset control to default state

void CWebButtonCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CWebButtonCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("BUTTON");
	cs.style |= BS_PUSHBUTTON | BS_OWNERDRAW;
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::IsSubclassedControl - This is a subclassed control

BOOL CWebButtonCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::OnOcmCommand - Handle command messages

LRESULT CWebButtonCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif
	if (wNotifyCode == BN_CLICKED)
	{
		FireClick();
	}
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::OnOcmDrawItem - Handle owner drawing

LRESULT CWebButtonCtrl::OnOcmDrawItem(WPARAM wParam, LPARAM lParam)
{
	DRAWITEMSTRUCT* pDIS = (DRAWITEMSTRUCT*)lParam;
	ASSERT(pDIS);

	enum BORDER { INNER, OUTER };

	COLORREF clrTopLeft[2];
	COLORREF clrBottomRight[2];
	CPoint BitmapOffset(0, 0);

	if (pDIS->itemState & ODS_SELECTED) // Down position
	{
		clrTopLeft[OUTER] =	::GetSysColor(COLOR_3DDKSHADOW);
		clrTopLeft[INNER] = ::GetSysColor(COLOR_3DSHADOW);
		clrBottomRight[OUTER] =	::GetSysColor(COLOR_3DHILIGHT);
		clrBottomRight[INNER] =	::GetSysColor(COLOR_3DLIGHT);
		BitmapOffset.Offset(1, 1);
	}
	else // up position
	{
		clrTopLeft[OUTER] =	::GetSysColor(COLOR_3DHILIGHT);
		clrTopLeft[INNER] = ::GetSysColor(COLOR_3DLIGHT);
		clrBottomRight[OUTER] =	::GetSysColor(COLOR_3DDKSHADOW);
		clrBottomRight[INNER] =	::GetSysColor(COLOR_3DSHADOW);
	}

	CDC* pDC = CDC::FromHandle(pDIS->hDC);

	CRect CurrentRect(&pDIS->rcItem);

	// Draw button 3-d border and face
	pDC->Draw3dRect(CurrentRect, clrTopLeft[OUTER], clrBottomRight[OUTER]);
	CurrentRect.InflateRect(-1, -1);
	pDC->Draw3dRect(CurrentRect, clrTopLeft[INNER], clrBottomRight[INNER]);
	CurrentRect.InflateRect(-1, -1);
	pDC->FillSolidRect(CurrentRect, ::GetSysColor(COLOR_BTNFACE));
	CurrentRect.InflateRect(-2, -2);
	
	// Draw bitmap image on button face. Center the image and shrink if
	// necessary
	HBITMAP hBitmap = ::LoadBitmap(AfxGetResourceHandle(), 
		MAKEINTRESOURCE(IDB_WEBBUTTON));
	if (hBitmap)
	{
		CBitmap* pBitmap = CBitmap::FromHandle(hBitmap);

		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);
		MemDC.SelectObject(*pBitmap);

		CSize BitmapSize;
		BITMAP BM;
		pBitmap->GetObject(sizeof(BITMAP), &BM);
		BitmapSize.cx = BM.bmWidth;
		BitmapSize.cy = BM.bmHeight;

		if (BitmapSize.cx < CurrentRect.Width())
		{
			CurrentRect.left += (CurrentRect.Width() - BitmapSize.cx) / 2;
			CurrentRect.right = CurrentRect.left + BitmapSize.cx;
		}
		if (BitmapSize.cy < CurrentRect.Height())
		{
			CurrentRect.top += (CurrentRect.Height() - BitmapSize.cy) / 2;
			CurrentRect.bottom = CurrentRect.top + BitmapSize.cx;
		}
		CurrentRect += BitmapOffset;
		pDC->StretchBlt(CurrentRect.left, CurrentRect.top, 
			CurrentRect.Width(), CurrentRect.Height(),
			&MemDC, 0, 0, BitmapSize.cx, BitmapSize.cy,
			SRCCOPY);
	}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl::RelayToolTipEvent - Pass mouse messages to ToolTip

void CWebButtonCtrl::RelayToolTipEvent(const MSG* pMsg)
{
	MSG MsgCopy;
	::memcpy(&MsgCopy, pMsg, sizeof(MSG));
	FilterToolTipMessage(&MsgCopy);
}


int CWebButtonCtrl::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	if (m_bToolTipEnabled && pTI != NULL && pTI->cbSize >= sizeof(TOOLINFO))
	{
		// setup the TOOLINFO structure
		pTI->hwnd = m_hWnd;
		pTI->uId = 0;
		pTI->uFlags = 0;
		GetClientRect(&(pTI->rect));
		pTI->lpszText = LPSTR_TEXTCALLBACK;
	}

	return (m_bToolTipEnabled ? 1 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CWebButtonCtrl message handlers

int CWebButtonCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	if (m_Bitmap.LoadBitmap(IDB_WEBBUTTON))
	{
		SendMessage(BM_SETIMAGE, IMAGE_BITMAP, 
            (LPARAM)m_Bitmap.GetSafeHandle());
	}
	else
	{
		TRACE("Unable to load bitmap for button.");
	}

	EnableToolTips(TRUE);
	return 0;
}

void CWebButtonCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	RelayToolTipEvent(GetCurrentMessage());
	COleControl::OnMouseMove(nFlags, point);
}

void CWebButtonCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	RelayToolTipEvent(GetCurrentMessage());
	COleControl::OnLButtonDown(nFlags, point);
}

void CWebButtonCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	RelayToolTipEvent(GetCurrentMessage());
	COleControl::OnLButtonUp(nFlags, point);
}

BOOL CWebButtonCtrl::OnToolNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	::strcpy(pTTT->szText, m_strToolTipText);
	return TRUE;
}


 
/////////////////////////////////////////////////////////////////////////////
// Property changed handlers

void CWebButtonCtrl::OnToolTipEnabledChanged() 
{
	SetModifiedFlag();
}

void CWebButtonCtrl::OnToolTipTextChanged() 
{
	SetModifiedFlag();
}


