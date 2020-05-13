////////////////////////////////////////////////////////////////
// ShareEdit 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#include "resource.h"       // main symbols

#ifdef _MDIAPP
#define IDR_MAINFRAME IDR_MAINFRAMEMDI
#else
#define IDR_MAINFRAME IDR_MAINFRAMESDI
#endif

class CMyApp : public CWinApp {
public:
	CMyApp();
	virtual BOOL InitInstance();
protected:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};
