//***********************************************************************
//
//  DVDemo.cpp
//
//***********************************************************************

#include <afxwin.h>
#include <afxcview.h>
#include <afxmt.h>
#include "Resource.h"
#include "DVDemo.h"
#include "MainFrame.h"
#include "DriveView.h"
#include "DemoDoc.h"

CMyApp myApp;

BOOL CMyApp::InitInstance ()
{
    SetRegistryKey ("Microsoft Systems Journal");
    LoadStdProfileSettings ();

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate (
        IDR_MAINFRAME,
        RUNTIME_CLASS (CDemoDoc),
        RUNTIME_CLASS (CMainFrame),
        RUNTIME_CLASS (CDriveView)
    );

    AddDocTemplate (pDocTemplate);

    CCommandLineInfo cmdInfo;
    ParseCommandLine (cmdInfo);

    if (!ProcessShellCommand (cmdInfo))
        return FALSE;

    return TRUE;
}


