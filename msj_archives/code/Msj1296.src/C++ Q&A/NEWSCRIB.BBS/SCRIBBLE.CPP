////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// This program is based on the SCRIBBLE program that comes with
// Microsoft Visual C++, as part of the MFC tutorial.
//
// This modified SCRIBBLE shows
//
// -how to write an SDI app that starts with an empty frame instead
//  of a new document;
//
// -how to setup the systemp registry to call your app with a special
//  switch when the user does "File New" from the Windows 95 shell;
//
// -how to parse the switch in your InitInstance function;
//
// -how to write an exception handler to handle any uncaught exception
//  that occurs while the app is running.
// 
#include "stdafx.h"
#include "Scribble.h"
#include "MainFrm.h"
#include "ScribDoc.h"
#include "ScribVw.h"
#include <eh.h>         // set_terminate
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleApp

BEGIN_MESSAGE_MAP(CScribbleApp, CWinApp)
   //{{AFX_MSG_MAP(CScribbleApp)
   ON_COMMAND(ID_APP_ABOUT,    OnAppAbout)
   ON_COMMAND(ID_EX_USER,      OnExUser)
   ON_COMMAND(ID_EX_MEMORY,    OnExMemory)
   ON_COMMAND(ID_EX_RESOURCE,  OnExResource)
   ON_COMMAND(ID_INSTALL,		 OnInstall)
   ON_COMMAND(ID_REMOVE,		 OnRemove)
   //}}AFX_MSG_MAP
   ON_COMMAND(ID_FILE_NEW,     OnMyFileNew)
   ON_COMMAND(ID_FILE_OPEN,    CWinApp::OnFileOpen)
   ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CScribbleApp theApp;

typedef void (*TERMINATE_FN)();
TERMINATE_FN old_terminate = NULL;

////////////////
// Custom terminate handler just displays message
//
void my_terminate()
{
   MessageBox(NULL, "Help me, I'm dying.", "Terminate", MB_OK);
   if (old_terminate)
      old_terminate();
}

//////////////////
// Custom class to parse command line switches.
// To parse your own switches, just override CCommandLineInfo::ParseParam.
//
class CMyCmdLineInfo : public CCommandLineInfo {
public:
	virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast);
	enum { ShellNew=100 };
};

//////////////////
// Custom override to parse my own switches.
// Recognizes /ShellNew
//
void CMyCmdLineInfo::ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast)
{
	TRACE("CMyCmdLineInfo::ParseParam(%s)\n",pszParam);
	if (bFlag && stricmp(pszParam, "ShellNew")==0)
		(UINT&)m_nShellCommand = ShellNew;
	else 
		CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}

CScribbleApp::CScribbleApp()
{
   MfxTraceInit();         // initialize TRACEWIN tracing
   old_terminate = set_terminate(my_terminate);
	m_bRemoveProfile = FALSE;
}

CScribbleApp::~CScribbleApp()
{
   set_terminate(old_terminate);
}

//////////////////
// Initialize app
//
BOOL CScribbleApp::InitInstance()
{
	SetRegistryKey("MSJ");		// Use HKEY_CURRENT_USER\Software\MSJ for INI
	LoadStdProfileSettings();	// Load INI file options (including MRU file)

	// create doc template
   CDocTemplate* pDocTemplate;
   pDocTemplate = new CSingleDocTemplate(
      IDR_MAINFRAME,
      RUNTIME_CLASS(CScribbleDoc),
      RUNTIME_CLASS(CMainFrame),
      RUNTIME_CLASS(CScribbleView));
   AddDocTemplate(pDocTemplate);

	if (!MaybeRegisterFileTypes())	// Maybe register shell stuff
		return FALSE;

   // Parse command line. Use my own custom class.
   CMyCmdLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);
	if (!ProcessShellCommand(cmdInfo)) // dispatch command
      return FALSE;
      
   return TRUE;
}

//////////////////
// Quit SCRIBBLE. If the user chose to remove the installation,
// delete the profile settings. This must happen now since other
// functions update the profile as the app is shutting down, recreating
// the profile entry if it's gone. This will remove it for good
//
int CScribbleApp::ExitInstance()
{
	int nRet = CWinApp::ExitInstance();
	if (m_bRemoveProfile)
		RegDeleteKey(HKEY_CURRENT_USER,"Software\\MSJ\\Scribble");
	return nRet;
}

//////////////////
// Override to handle /ShellNew option
//
BOOL CScribbleApp::ProcessShellCommand(CCommandLineInfo& cmdInfo)
{
	TRACE("CScribbleApp::ProcessShellCommand(%d)\n",cmdInfo.m_nShellCommand);
	if (cmdInfo.m_nShellCommand==CMyCmdLineInfo::ShellNew) {
		OnMyFileNew();
		return TRUE;
	}
	return CWinApp::ProcessShellCommand(cmdInfo);  // let MFC do it
}

//////////////////
// REALLY create new document: that is, initialize the empty doc object.
//
void CScribbleApp::OnMyFileNew()
{
   OnFileNew(); // do normal thing to create new doc
                // (in case this is an open doc, reuse it)

   CFrameWnd* pFrame = (CFrameWnd*)m_pMainWnd;
   ASSERT_KINDOF(CFrameWnd, pFrame);
   CScribbleView* pView = (CScribbleView*)pFrame->GetActiveView();
   ASSERT_KINDOF(CScribbleView, pView);
   pView->GetDocument()->Initialize(); // initialize new doc
}

void CScribbleApp::OnAppAbout()
{
   CDialog(IDD_ABOUTBOX).DoModal();
}

//////////////////
// Commands to throw various kinds of exceptions.
//
void CScribbleApp::OnExUser()		 { AfxThrowUserException();	  }
void CScribbleApp::OnExMemory()	 { AfxThrowMemoryException();   }
void CScribbleApp::OnExResource() { AfxThrowResourceException(); }

//////////////////
// Exception handler of last resort displays message box describing
// exception, then tries to save all files.
//
LRESULT CScribbleApp::ProcessWndProcException(CException* e, const MSG* pMsg)
{
   CString s = "An unhandled error occurred in your program.\n\n";
   CString m;
   m.Format("type\t%s\n", e->GetRuntimeClass()->m_lpszClassName);
   s += m;
   m.Format("HWND\t0x%04x\nmsg\t0x%04x\nwParam\t0x%08x\nlParam\t0x%08x",
      pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
   s += m;
   s += "\n\nSelect:\nAbort \tto terminate the program;\n";
   s += "Retry \tto let MFC handle the error; or\n";
   s += "Ignore \tto do nothing.\n\n";
   s += "After this dialog, you'll have a chance to save modified documents.";
   int nRes = MessageBox(m_pMainWnd->GetSafeHwnd(), s, "Error!", 
      MB_ABORTRETRYIGNORE);

   // Save any modified docs
   SaveAllModified();

   if (nRes==IDABORT)
      THROW_LAST();			// will call terminate()
   else if (nRes==IDRETRY)
      return CWinApp::ProcessWndProcException(e, pMsg); // do MFC Thing

   return 0; // IDIGNORE
}

//////////////////
// Dialog asks user whether to register scribble file types
//
class CRegisterConfirmDialog : public CDialog {
public:
	CRegisterConfirmDialog() : CDialog (IDD_REGISTER) { }
	DECLARE_MESSAGE_MAP()
   afx_msg BOOL OnButton(UINT id) { EndDialog(id); return TRUE; }
};

BEGIN_MESSAGE_MAP(CRegisterConfirmDialog, CDialog)
	ON_COMMAND_EX(IDYES, OnButton)
	ON_COMMAND_EX(IDNO,  OnButton)
END_MESSAGE_MAP()

//////////////////
// Check for proper registration, and maybe prompt user to register.
// Better to do it this way than blithely clobber the registry.
//
BOOL CScribbleApp::MaybeRegisterFileTypes()
{
   HKEY hkey;
	if (RegOpenKey(HKEY_CLASSES_ROOT, ".SCB\\ShellNew", &hkey)==ERROR_SUCCESS)
		// if ShellNew key exists, assume already registered.
		// Theoretically, should check for proper values of all keys
		return TRUE;

	switch (CRegisterConfirmDialog().DoModal()) {
	case IDCANCEL:
		return FALSE; // abort
	case IDNO:
		return TRUE;  // continue, but don't register
	}
	
	// User selected OK, so do the installation
	OnInstall();

	return TRUE;
}

//////////////////
// "Install" scribble (register file types)
//
void CScribbleApp::OnInstall()
{
// EnableShellOpen();				// Only use to support File Manager
	RegisterShellFileTypes(TRUE); // TRUE for Win 95

	// MFC has set HKEY_CLASSES_ROOT\.SCB\ShellNew\NullFile = ""
	// So we must remove and replace with Command =
	//
	HKEY hkey;
	if (RegOpenKey(HKEY_CLASSES_ROOT,".SCB\\ShellNew",&hkey)==ERROR_SUCCESS) {
		RegDeleteValue(hkey, "NullFile");
		CString s = "SCRIBBLE.EXE /ShellNew";
		DWORD len = s.GetLength() + 1;
		RegSetValueEx(hkey, "Command", 0, REG_SZ, (BYTE*)(LPCSTR)s, len);
		RegCloseKey(hkey);
	} else {
		ASSERT(FALSE);
	}
}

//////////////////
// De-install SCRIBBLE app
// Remove registry keys. Profile must be deferred since shutdown code
// will write stuff like MRU files to the profile, recreating it.
//
void CScribbleApp::OnRemove()
{
   RegDeleteKey(HKEY_CLASSES_ROOT,".SCB");
   RegDeleteKey(HKEY_CLASSES_ROOT,"Scribble.Document");
	m_bRemoveProfile = TRUE;
}
