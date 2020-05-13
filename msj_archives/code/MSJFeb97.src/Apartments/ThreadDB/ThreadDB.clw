; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CThreadDBCtrl
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ThreadDB.h"
CDK=Y

ClassCount=4
Class1=CThreadDBCtrl
Class2=CThreadDBPropPage

ResourceCount=1
Resource1=IDD_ABOUTBOX_THREADDB
LastPage=0
Class3=CCustomer
Class4=CSearchThread

[CLS:CThreadDBCtrl]
Type=0
HeaderFile=ThreadDBCtl.h
ImplementationFile=ThreadDBCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CThreadDBCtrl

[CLS:CThreadDBPropPage]
Type=0
HeaderFile=ThreadDBPpg.h
ImplementationFile=ThreadDBPpg.cpp
Filter=D

[DLG:IDD_ABOUTBOX_THREADDB]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=?

[DLG:IDD_PROPPAGE_THREADDB]
Type=1
ControlCount=0
Class=CThreadDBPropPage

[CLS:CSearchThread]
Type=0
HeaderFile=SearchThread.h
ImplementationFile=SearchThread.cpp
BaseClass=CWinThread
Filter=N
LastObject=CSearchThread

[CLS:CCustomer]
Type=0
HeaderFile=Customer.h
ImplementationFile=Customer.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CCustomer
VirtualFilter=C

