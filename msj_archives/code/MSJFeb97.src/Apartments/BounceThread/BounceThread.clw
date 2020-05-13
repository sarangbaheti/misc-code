; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBounceThreadCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BounceThread.h"
CDK=Y

ClassCount=2
Class1=CBounceThreadCtrl
Class2=CBounceThreadPropPage

ResourceCount=3
Resource1=IDD_ABOUTBOX_BOUNCETHREAD
LastPage=0
Resource2=IDD_PROPPAGE_BOUNCETHREAD
Resource3=IDR_MENU1

[CLS:CBounceThreadCtrl]
Type=0
HeaderFile=BounceThreadCtl.h
ImplementationFile=BounceThreadCtl.cpp
Filter=W
LastObject=CBounceThreadCtrl
BaseClass=COleControl
VirtualFilter=wWC

[CLS:CBounceThreadPropPage]
Type=0
HeaderFile=BounceThreadPpg.h
ImplementationFile=BounceThreadPpg.cpp
Filter=D

[DLG:IDD_ABOUTBOX_BOUNCETHREAD]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_BOUNCETHREAD]
Type=1
Class=CBounceThreadPropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[MNU:IDR_MENU1]
Type=1
Command1=ID_POPUP_BEEPEVERYSECOND
Command2=ID_POPUP_PRIORITY_TIMECRITICAL
Command3=ID_POPUP_PRIORITY_HIGHEST
Command4=ID_POPUP_PRIORITY_ABOVE
Command5=ID_POPUP_PRIORITY_NORMAL
Command6=ID_POPUP_PRIORITY_BELOW
Command7=ID_POPUP_PRIORITY_LOWEST
Command8=ID_POPUP_PRIORITY_IDLE
CommandCount=8

