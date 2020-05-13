// MSJ Visual Developer Column
//
// This source code is a small sub-set of one of 50 classes
// found in Stingray's Objective Toolkit product
// For more information: http://www.stingsoft.com

//  Author:		Scot Wingo and George Shepherd.
//  Description:	Declarations for MSJSuperView
//  Created:		9/1/97
//

#include "stdafx.h"
#include "panwnd.h"

/////////////////////////////////////////////////////////////////////////////
// MSJMouseWheelOriginWnd

MSJMouseWheelOriginWnd::MSJMouseWheelOriginWnd(int nID)
{

	m_bmOrigin.LoadBitmap(nID);
}

BOOL MSJMouseWheelOriginWnd::CreateWnd(CWnd* pParent)
{
	if (!CreateEx(
			0, AfxRegisterWndClass(CS_SAVEBITS), NULL, WS_CLIPSIBLINGS|WS_CHILD,
			0, 0, 1, 1,
			pParent->GetSafeHwnd(), NULL))
	{
		TRACE0("Failed to create window in CreateWnd\n");
		ASSERT(0);
		return FALSE;
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(MSJMouseWheelOriginWnd, CWnd)
	//{{AFX_MSG_MAP(MSJMouseWheelOriginWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MSJMouseWheelOriginWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(rect);

	// choose bitmap for the header
	CBitmap* pBitmap = &m_bmOrigin;
	CDC* pDC = &dc;

	if (pBitmap)
	{
		// Bitmap size
		BITMAP     bm;
		pBitmap->GetObject(sizeof(BITMAP), (LPSTR)&bm);

		CPoint     ptSize;
		ptSize.x = bm.bmWidth;            // Get width of bitmap
		ptSize.y = bm.bmHeight;           // Get height of bitmap
		pDC->DPtoLP(&ptSize, 1);      // Convert from device to logical points

		// Draw bitmap
		if (rect.Width() >= ptSize.x && rect.Height() >= ptSize.x)
		{
			// must have at least the first bitmap loaded before calling DrawItem
			ASSERT(pBitmap->m_hObject != NULL);     // required

			int x = rect.left + max(1, (rect.Width()-ptSize.x)/2);
			int y = rect.top + max(1, (rect.Height()-ptSize.y)/2);

			MSJDrawTransparentBitmap(pDC, // The destination DC.
				pBitmap, // The bitmap to be drawn.
				x,        // X coordinate.
				y,        // Y coordinate.
				RGB(255,0,0)); // The color for transparent
								   // pixels (white grey).

		}
	}
}

// MSJDrawTransparentBitmap
//
// This function lets you draw transparent bitmaps. The parameter
// cTransparentColor specifies the color for transparent pixels.
// All pixels in the bitmap which should be transparent should be
// marked with this color.
//
// The function was copied and adapated from knowledge base article Q79212
// Title: Drawing Transparent Bitmaps

void MSJDrawTransparentBitmap(CDC* pDC, CBitmap* pBitmap, int xStart,
	int yStart, COLORREF cTransparentColor)
{
   CBitmap    bmAndBack, bmAndObject, bmAndMem, bmSave;
   CDC        dcMem, dcBack, dcObject, dcTemp, dcSave;

   dcTemp.CreateCompatibleDC(pDC);
   dcTemp.SelectObject(pBitmap);   // Select the bitmap


   BITMAP     bm;
   pBitmap->GetObject(sizeof(BITMAP), (LPSTR)&bm);

   CPoint     ptSize;
   ptSize.x = bm.bmWidth;            // Get width of bitmap
   ptSize.y = bm.bmHeight;           // Get height of bitmap
   dcTemp.DPtoLP(&ptSize, 1);      // Convert from device
									 // to logical points

   // Create some DCs to hold temporary data.
   dcBack.CreateCompatibleDC(pDC);
   dcObject.CreateCompatibleDC(pDC);
   dcMem.CreateCompatibleDC(pDC);
   dcSave.CreateCompatibleDC(pDC);

   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.

   // Monochrome DC
   bmAndBack.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   // Monochrome DC
   bmAndObject.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);
   bmSave.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);

   // Each DC must select a bitmap object to store pixel data.
   CBitmap* pbmBackOld   = dcBack.SelectObject(&bmAndBack);
   CBitmap* pbmObjectOld = dcObject.SelectObject(&bmAndObject);
   CBitmap* pbmMemOld    = dcMem.SelectObject(&bmAndMem);
   CBitmap* pbmSaveOld   = dcSave.SelectObject(&bmSave);

   // Set proper mapping mode.
   dcTemp.SetMapMode(pDC->GetMapMode());

   // Save the bitmap sent here, because it will be overwritten.
   dcSave.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCCOPY);

   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   COLORREF cColor = dcTemp.SetBkColor(cTransparentColor);

   // Create the object mask for the bitmap by performing a BitBlt
   // from the source bitmap to a monochrome bitmap.
   dcObject.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0,
		  SRCCOPY);

   // Set the background color of the source DC back to the original
   // color.
   dcTemp.SetBkColor(cColor);

   // Create the inverse of the object mask.
   dcBack.BitBlt(0, 0, ptSize.x, ptSize.y, &dcObject, 0, 0,
		  NOTSRCCOPY);

   // Copy the background of the main DC to the destination.
   dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, pDC, xStart, yStart,
		  SRCCOPY);

   // Mask out the places where the bitmap will be placed.
   dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, &dcObject, 0, 0, SRCAND);

   // Mask out the transparent colored pixels on the bitmap.
   dcTemp.BitBlt(0, 0, ptSize.x, ptSize.y, &dcBack, 0, 0, SRCAND);

   // XOR the bitmap with the background on the destination DC.
   dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCPAINT);

   // Copy the destination to the screen.
   pDC->BitBlt(xStart, yStart, ptSize.x, ptSize.y, &dcMem, 0, 0,
		  SRCCOPY);

   // Place the original bitmap back into the bitmap sent here.
   dcTemp.BitBlt(0, 0, ptSize.x, ptSize.y, &dcSave, 0, 0, SRCCOPY);

   // Reset the memory bitmaps.
   dcBack.SelectObject(pbmBackOld);
   dcObject.SelectObject(pbmObjectOld);
   dcMem.SelectObject(pbmMemOld);
   dcSave.SelectObject(pbmSaveOld);

   // Memory DCs and Bitmap objects will be deleted automatically
}


