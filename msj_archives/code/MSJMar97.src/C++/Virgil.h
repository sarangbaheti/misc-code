////////////////////////////////////////////////////////////////
// VIRGIL Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See Virgil.cpp
// 
#include "resource.h"

class CMyApp : public CWinApp {
public:
	CMyApp();
	virtual BOOL InitInstance();
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnAppAbout();
};
