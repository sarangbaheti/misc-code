////////////////////////////////////////////////////////////////
// Copyright 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.1 on Windows 95
// See StatusPane.cpp
// 
#include "resource.h"

class CApp : public CWinApp {
public:
	CApp();
	virtual BOOL InitInstance();

	//{{AFX_MSG(CApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
