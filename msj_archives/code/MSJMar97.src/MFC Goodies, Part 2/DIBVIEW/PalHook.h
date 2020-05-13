////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#ifndef _PALMSGHOOK_H
#define _PALMSGHOOK_H

#include "MsgHook.h"

//////////////////
// Generic palette message handler makes handling palette messages easy.
// To use:
//
// * Instaniate a CPalMsgHandler in your main frame and
//   every CWnd class that needs to realize palettes (e.g., your view).
// * Call Install to install.
// * Call DoRealizePalette(TRUE) from your view's OnInitialUpdate fn.
//
class CPalMsgHandler : public CMsgHook {
protected:
	CPalette* m_pPalette; // ptr to palette

	DECLARE_DYNAMIC(CPalMsgHandler);

	// These are similar to, but NOT the same as the equivalent CWnd fns.
	// Rarely, if ever need to override.
	//
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);	
	virtual void OnPaletteChanged(CWnd* pFocusWnd);
	virtual BOOL OnQueryNewPalette();
	virtual void OnSetFocus(CWnd* pOldWnd);

	// Override this if you realize your palette some other way
	// (not by having a ptr to a CPalette).
	//
	virtual int  DoRealizePalette(BOOL bForeground);

public:
	CPalMsgHandler();
	~CPalMsgHandler();

	// Get/Set palette obj
	CPalette* GetPalette()				{ return m_pPalette; }
	void SetPalette(CPalette* pPal)	{ m_pPalette = pPal; }

	// Call this to install the palette handler
	BOOL Install(CWnd* pWnd, CPalette* pPal) {
		m_pPalette = pPal;
		return HookWindow(pWnd);
	}
};

#endif
