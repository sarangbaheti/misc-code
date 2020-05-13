////////////////////////////////////////////////////////////////
// CFORM Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See CFORM.CPP for Description of program.
// 
#include "resource.h"       // main symbols

class CMyApp : public CWinApp {
public:
   CMyApp();

   //{{AFX_VIRTUAL(CMyApp)
   public:
   virtual BOOL InitInstance();
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CMyApp)
   afx_msg void OnAppAbout();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
