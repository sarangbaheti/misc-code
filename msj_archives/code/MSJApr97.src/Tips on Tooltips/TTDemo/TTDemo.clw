; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTitleTipListBox
LastTemplate=CListBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TTDemo.h"

ClassCount=7
Class1=CTTDemoApp
Class2=CTTDemoDlg

ResourceCount=2
Class3=CLongItemWnd
Class4=CLongItemListBox
Resource1=IDR_MAINFRAME
Class5=CODListBox
Class6=COwnerDrawListBox
Class7=CTitleTipListBox
Resource2=IDD_TTDEMO_DIALOG

[CLS:CTTDemoApp]
Type=0
HeaderFile=TTDemo.h
ImplementationFile=TTDemo.cpp
Filter=N

[CLS:CTTDemoDlg]
Type=0
HeaderFile=TTDemoDlg.h
ImplementationFile=TTDemoDlg.cpp
Filter=D
LastObject=IDC_REGLISTBOX


[DLG:IDD_TTDEMO_DIALOG]
Type=1
Class=CTTDemoDlg
ControlCount=5
Control1=IDC_REGLISTBOX,listbox,1352728835
Control2=IDC_ODLISTBOX,listbox,1352728915
Control3=IDOK,button,1342242817
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CLongItemWnd]
Type=0
HeaderFile=longitemwnd.h
ImplementationFile=longitemwnd.cpp
BaseClass=CWnd
LastObject=CLongItemWnd

[CLS:CLongItemListBox]
Type=0
HeaderFile=longitemlistbox.h
ImplementationFile=longitemlistbox.cpp
BaseClass=CListBox
LastObject=CLongItemListBox

[CLS:CODListBox]
Type=0
HeaderFile=ODListBox.h
ImplementationFile=ODListBox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC
LastObject=CODListBox

[CLS:COwnerDrawListBox]
Type=0
HeaderFile=OwnList.h
ImplementationFile=OwnList.cpp
BaseClass=CListBox

[CLS:CTitleTipListBox]
Type=0
HeaderFile=titletiplistbox.h
ImplementationFile=titletiplistbox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC
LastObject=CTitleTipListBox

