; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutBox
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "$$root$$.h"
LastPage=0

ResourceCount=2
Resource1=IDD_ABOUT
Resource2=IDR_MAINMENU

ClassCount=$$numclasses$$ // 3 + # window panes
Class1=CMainWindow
Class2=CAboutBox
Class3=C$$Safe_root$$App
$$paneclass$$

[CLS:CMainWindow]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainwnd.h
ImplementationFile=mainwnd.cpp
LastObject=CMainWindow
Filter=T
VirtualFilter=fWC

[DLG:IDD_ABOUT]
Type=1
Class=CAboutBox
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308353

[CLS:CAboutBox]
Type=0
HeaderFile=$$root$$.h
ImplementationFile=$$root$$.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutBox

[CLS:C$$Safe_root$$App]
Type=0
HeaderFile=$$root$$.h
ImplementationFile=$$root$$.cpp
BaseClass=CWinApp
LastObject=C$$Safe_root$$App
Filter=N
VirtualFilter=AC

[MNU:IDR_MAINMENU]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2
$$/////////////////////////////////////////////////////////
$$IF(toolbar)

[TB:IDR_MAINMENU]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8
$$ENDIF // toolbar
$$/////////////////////////////////////////////////////////
$$IF(treepane)

[CLS:CTreePane]
Type=0
HeaderFile=treepane.h
ImplementationFile=treepane.cpp
BaseClass=CWnd
Filter=W
LastObject=CTreePane
VirtualFilter=WC
$$ENDIF // treepane
$$/////////////////////////////////////////////////////////
$$IF(datapane)

[CLS:CDataPane]
Type=0
HeaderFile=datapane.h
ImplementationFile=datapane.cpp
BaseClass=CWnd
Filter=W
LastObject=CDataPane
VirtualFilter=WC
$$ENDIF // datapane
$$/////////////////////////////////////////////////////////
$$IF(stdpane)

[CLS:CStdPane]
Type=0
HeaderFile=stdpane.h
ImplementationFile=stdpane.cpp
BaseClass=CWnd
LastObject=CStdPane
$$ENDIF // stdpane
