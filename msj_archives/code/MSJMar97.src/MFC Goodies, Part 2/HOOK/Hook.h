////////////////////////////////////////////////////////////////
// HOOK Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See HOOK.CPP.
// 
#include "resource.h"

class CApp : public CWinApp {
public:
	CApp();
	virtual BOOL InitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};
