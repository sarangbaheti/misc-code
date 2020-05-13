////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See DIBVIEW.CPP for Description of program.
// 
#include "resource.h"

#ifdef _MDI
#define IDR_MAINFRAME IDR_MAINFRAMEMDI
#else
#define IDR_MAINFRAME IDR_MAINFRAMESDI
#endif

//////////////////
// Application class
//
class CApp : public CWinApp {
public:
	CApp();
	virtual BOOL InitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};
