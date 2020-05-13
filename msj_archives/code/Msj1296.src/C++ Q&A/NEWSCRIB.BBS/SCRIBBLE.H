////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation.
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See SCRIBBLE.CPP for Description of program.
//
#ifndef __AFXWIN_H__
   #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CScribbleApp : public CWinApp {
private:
	BOOL	m_bRemoveProfile;			  // delete profile on exit?
	BOOL	MaybeRegisterFileTypes(); // helper

public:
   CScribbleApp();
   ~CScribbleApp();
   virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Note: non-virtual override
	BOOL ProcessShellCommand(CCommandLineInfo& rCmdInfo);

   virtual LRESULT ProcessWndProcException(CException* e, const MSG* pMsg);

   //{{AFX_MSG(CScribbleApp)
   afx_msg void OnAppAbout();
   afx_msg void OnMyFileNew();
   afx_msg void OnExUser();
   afx_msg void OnExMemory();
   afx_msg void OnExResource();
   afx_msg void OnInstall();
   afx_msg void OnRemove();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

