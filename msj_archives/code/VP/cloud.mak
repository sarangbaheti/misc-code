# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=CLOUD - Win32 Unicode SEC DLL Debug
!MESSAGE No configuration specified.  Defaulting to CLOUD - Win32 Unicode SEC\
 DLL Debug.
!ENDIF 

!IF "$(CFG)" != "CLOUD - Win32 SEC static AFXDLL Release" && "$(CFG)" !=\
 "CLOUD - Win32 SEC static AFXDLL Debug" && "$(CFG)" !=\
 "CLOUD - Win32 SEC DLL Debug" && "$(CFG)" != "CLOUD - Win32 SEC DLL Release" &&\
 "$(CFG)" != "CLOUD - Win32 Unicode SEC static AFXDLL Debug" && "$(CFG)" !=\
 "CLOUD - Win32 Unicode SEC static AFXDLL Release" && "$(CFG)" !=\
 "CLOUD - Win32 Unicode SEC DLL Release" && "$(CFG)" !=\
 "CLOUD - Win32 Unicode SEC DLL Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "cloud.mak" CFG="CLOUD - Win32 Unicode SEC DLL Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CLOUD - Win32 SEC static AFXDLL Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "CLOUD - Win32 SEC static AFXDLL Debug" (based on\
 "Win32 (x86) Application")
!MESSAGE "CLOUD - Win32 SEC DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "CLOUD - Win32 SEC DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "CLOUD - Win32 Unicode SEC static AFXDLL Debug" (based on\
 "Win32 (x86) Application")
!MESSAGE "CLOUD - Win32 Unicode SEC static AFXDLL Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "CLOUD - Win32 Unicode SEC DLL Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "CLOUD - Win32 Unicode SEC DLL Debug" (based on\
 "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "CLOUD - Win32 Unicode SEC DLL Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WIN40REL"
# PROP Intermediate_Dir "WIN40REL"
OUTDIR=.\WIN40REL
INTDIR=.\WIN40REL

ALL : "$(OUTDIR)\cloud.exe"

CLEAN : 
	-@erase ".\WIN40REL\cloud.exe"
	-@erase ".\WIN40REL\Stdafx.obj"
	-@erase ".\WIN40REL\Cloudvw.obj"
	-@erase ".\WIN40REL\cloud.pch"
	-@erase ".\WIN40REL\Clouddoc.obj"
	-@erase ".\WIN40REL\Mainfrm.obj"
	-@erase ".\WIN40REL\Cloud.obj"
	-@erase ".\WIN40REL\CLOUD.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cloud.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WIN40REL/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CLOUD.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cloud.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/cloud.pdb" /machine:I386 /out:"$(OUTDIR)/cloud.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Cloudvw.obj" \
	"$(INTDIR)/Clouddoc.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Cloud.obj" \
	"$(INTDIR)/CLOUD.res"

"$(OUTDIR)\cloud.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WIN40DEB"
# PROP Intermediate_Dir "WIN40DEB"
OUTDIR=.\WIN40DEB
INTDIR=.\WIN40DEB

ALL : "$(OUTDIR)\cloud.exe"

CLEAN : 
	-@erase ".\WIN40DEB\vc40.pdb"
	-@erase ".\WIN40DEB\cloud.pch"
	-@erase ".\WIN40DEB\vc40.idb"
	-@erase ".\WIN40DEB\cloud.exe"
	-@erase ".\WIN40DEB\Clouddoc.obj"
	-@erase ".\WIN40DEB\Cloudvw.obj"
	-@erase ".\WIN40DEB\Mainfrm.obj"
	-@erase ".\WIN40DEB\Cloud.obj"
	-@erase ".\WIN40DEB\Stdafx.obj"
	-@erase ".\WIN40DEB\CLOUD.res"
	-@erase ".\WIN40DEB\cloud.ilk"
	-@erase ".\WIN40DEB\cloud.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cloud.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WIN40DEB/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CLOUD.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cloud.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/cloud.pdb" /debug /machine:I386 /out:"$(OUTDIR)/cloud.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Clouddoc.obj" \
	"$(INTDIR)/Cloudvw.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Cloud.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/CLOUD.res"

"$(OUTDIR)\cloud.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_SE"
# PROP BASE Intermediate_Dir "Win32_SE"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DLL40DEB"
# PROP Intermediate_Dir "DLL40DEB"
OUTDIR=.\DLL40DEB
INTDIR=.\DLL40DEB

ALL : "$(OUTDIR)\cloud.exe"

CLEAN : 
	-@erase ".\DLL40DEB\vc40.pdb"
	-@erase ".\DLL40DEB\cloud.pch"
	-@erase ".\DLL40DEB\vc40.idb"
	-@erase ".\DLL40DEB\cloud.exe"
	-@erase ".\DLL40DEB\Cloudvw.obj"
	-@erase ".\DLL40DEB\Clouddoc.obj"
	-@erase ".\DLL40DEB\Mainfrm.obj"
	-@erase ".\DLL40DEB\Stdafx.obj"
	-@erase ".\DLL40DEB\Cloud.obj"
	-@erase ".\DLL40DEB\CLOUD.res"
	-@erase ".\DLL40DEB\cloud.ilk"
	-@erase ".\DLL40DEB\cloud.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_SECDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_SECDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cloud.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DLL40DEB/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CLOUD.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cloud.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/cloud.pdb" /debug /machine:I386 /out:"$(OUTDIR)/cloud.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Cloudvw.obj" \
	"$(INTDIR)/Clouddoc.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Cloud.obj" \
	"$(INTDIR)/CLOUD.res"

"$(OUTDIR)\cloud.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32_S0"
# PROP BASE Intermediate_Dir "Win32_S0"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "DLL40REL"
# PROP Intermediate_Dir "DLL40REL"
OUTDIR=.\DLL40REL
INTDIR=.\DLL40REL

ALL : "$(OUTDIR)\cloud.exe"

CLEAN : 
	-@erase ".\DLL40REL\cloud.exe"
	-@erase ".\DLL40REL\Cloudvw.obj"
	-@erase ".\DLL40REL\cloud.pch"
	-@erase ".\DLL40REL\Mainfrm.obj"
	-@erase ".\DLL40REL\Stdafx.obj"
	-@erase ".\DLL40REL\Clouddoc.obj"
	-@erase ".\DLL40REL\Cloud.obj"
	-@erase ".\DLL40REL\CLOUD.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_SECDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_SECDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cloud.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\DLL40REL/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CLOUD.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cloud.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/cloud.pdb" /machine:I386 /out:"$(OUTDIR)/cloud.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Cloudvw.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Clouddoc.obj" \
	"$(INTDIR)/Cloud.obj" \
	"$(INTDIR)/CLOUD.res"

"$(OUTDIR)\cloud.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CLOUD___"
# PROP BASE Intermediate_Dir "CLOUD___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CLOUD___"
# PROP Intermediate_Dir "CLOUD___"
# PROP Target_Dir ""
OUTDIR=.\CLOUD___
INTDIR=.\CLOUD___

ALL : "$(OUTDIR)\cloud.exe"

CLEAN : 
	-@erase ".\CLOUD___\vc40.pdb"
	-@erase ".\CLOUD___\cloud.pch"
	-@erase ".\CLOUD___\vc40.idb"
	-@erase ".\CLOUD___\cloud.exe"
	-@erase ".\CLOUD___\Stdafx.obj"
	-@erase ".\CLOUD___\Cloud.obj"
	-@erase ".\CLOUD___\Cloudvw.obj"
	-@erase ".\CLOUD___\Mainfrm.obj"
	-@erase ".\CLOUD___\Clouddoc.obj"
	-@erase ".\CLOUD___\CLOUD.res"
	-@erase ".\CLOUD___\cloud.ilk"
	-@erase ".\CLOUD___\cloud.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)/cloud.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\CLOUD___/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CLOUD.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cloud.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/cloud.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/cloud.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Cloud.obj" \
	"$(INTDIR)/Cloudvw.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Clouddoc.obj" \
	"$(INTDIR)/CLOUD.res"

"$(OUTDIR)\cloud.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CLOUD__0"
# PROP BASE Intermediate_Dir "CLOUD__0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CLOUD__0"
# PROP Intermediate_Dir "CLOUD__0"
# PROP Target_Dir ""
OUTDIR=.\CLOUD__0
INTDIR=.\CLOUD__0

ALL : "$(OUTDIR)\cloud.exe"

CLEAN : 
	-@erase ".\CLOUD__0\cloud.exe"
	-@erase ".\CLOUD__0\Stdafx.obj"
	-@erase ".\CLOUD__0\Mainfrm.obj"
	-@erase ".\CLOUD__0\cloud.pch"
	-@erase ".\CLOUD__0\Cloud.obj"
	-@erase ".\CLOUD__0\Cloudvw.obj"
	-@erase ".\CLOUD__0\Clouddoc.obj"
	-@erase ".\CLOUD__0\CLOUD.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)/cloud.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\CLOUD__0/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CLOUD.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cloud.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/cloud.pdb" /machine:I386\
 /out:"$(OUTDIR)/cloud.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Cloud.obj" \
	"$(INTDIR)/Cloudvw.obj" \
	"$(INTDIR)/Clouddoc.obj" \
	"$(INTDIR)/CLOUD.res"

"$(OUTDIR)\cloud.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CLOUD__2"
# PROP BASE Intermediate_Dir "CLOUD__2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CLOUD__2"
# PROP Intermediate_Dir "CLOUD__2"
# PROP Target_Dir ""
OUTDIR=.\CLOUD__2
INTDIR=.\CLOUD__2

ALL : "$(OUTDIR)\cloud.exe"

CLEAN : 
	-@erase ".\CLOUD__2\cloud.exe"
	-@erase ".\CLOUD__2\Cloud.obj"
	-@erase ".\CLOUD__2\cloud.pch"
	-@erase ".\CLOUD__2\Clouddoc.obj"
	-@erase ".\CLOUD__2\Stdafx.obj"
	-@erase ".\CLOUD__2\Cloudvw.obj"
	-@erase ".\CLOUD__2\Mainfrm.obj"
	-@erase ".\CLOUD__2\CLOUD.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_SECDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_SECDLL" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_SECDLL" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)/cloud.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\CLOUD__2/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CLOUD.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cloud.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/cloud.pdb" /machine:I386\
 /out:"$(OUTDIR)/cloud.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Cloud.obj" \
	"$(INTDIR)/Clouddoc.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Cloudvw.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/CLOUD.res"

"$(OUTDIR)\cloud.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CLOUD__3"
# PROP BASE Intermediate_Dir "CLOUD__3"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CLOUD__3"
# PROP Intermediate_Dir "CLOUD__3"
# PROP Target_Dir ""
OUTDIR=.\CLOUD__3
INTDIR=.\CLOUD__3

ALL : "$(OUTDIR)\cloud.exe"

CLEAN : 
	-@erase ".\CLOUD__3\vc40.pdb"
	-@erase ".\CLOUD__3\cloud.pch"
	-@erase ".\CLOUD__3\vc40.idb"
	-@erase ".\CLOUD__3\cloud.exe"
	-@erase ".\CLOUD__3\Mainfrm.obj"
	-@erase ".\CLOUD__3\Stdafx.obj"
	-@erase ".\CLOUD__3\Cloudvw.obj"
	-@erase ".\CLOUD__3\Cloud.obj"
	-@erase ".\CLOUD__3\Clouddoc.obj"
	-@erase ".\CLOUD__3\CLOUD.res"
	-@erase ".\CLOUD__3\cloud.ilk"
	-@erase ".\CLOUD__3\cloud.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_SECDLL" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_SECDLL" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_SECDLL" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)/cloud.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\CLOUD__3/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CLOUD.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cloud.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/cloud.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/cloud.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Cloudvw.obj" \
	"$(INTDIR)/Cloud.obj" \
	"$(INTDIR)/Clouddoc.obj" \
	"$(INTDIR)/CLOUD.res"

"$(OUTDIR)\cloud.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "CLOUD - Win32 SEC static AFXDLL Release"
# Name "CLOUD - Win32 SEC static AFXDLL Debug"
# Name "CLOUD - Win32 SEC DLL Debug"
# Name "CLOUD - Win32 SEC DLL Release"
# Name "CLOUD - Win32 Unicode SEC static AFXDLL Debug"
# Name "CLOUD - Win32 Unicode SEC static AFXDLL Release"
# Name "CLOUD - Win32 Unicode SEC DLL Release"
# Name "CLOUD - Win32 Unicode SEC DLL Debug"

!IF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Release"

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Debug"

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Debug"

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Release"

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Debug"

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Release"

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Release"

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp

!IF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Release"

DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\SECALL.H"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cloud.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cloud.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Debug"

DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cloud.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cloud.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Debug"

DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_SECDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cloud.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cloud.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Release"

DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_SECDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cloud.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cloud.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Debug"

DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)/cloud.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cloud.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Release"

DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)/cloud.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cloud.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Release"

DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_SECDLL" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)/cloud.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cloud.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Debug"

DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_SECDLL" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)/cloud.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cloud.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CLOUD.rc
DEP_RSC_CLOUD=\
	".\Res\Cloud.ico"\
	".\Res\Clouddoc.ico"\
	".\Res\Idr_pan.ico"\
	".\Res\Idr_zoom.ico"\
	".\Res\pan_hand.cur"\
	".\Res\Toolbar.bmp"\
	".\Res\zoomdrag.cur"\
	".\Res\zoomin.cur"\
	".\Res\zoomout.cur"\
	".\Res\zoomrect.cur"\
	

!IF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Release"


"$(INTDIR)\CLOUD.res" : $(SOURCE) $(DEP_RSC_CLOUD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Debug"


"$(INTDIR)\CLOUD.res" : $(SOURCE) $(DEP_RSC_CLOUD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Debug"


"$(INTDIR)\CLOUD.res" : $(SOURCE) $(DEP_RSC_CLOUD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Release"


"$(INTDIR)\CLOUD.res" : $(SOURCE) $(DEP_RSC_CLOUD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Debug"


"$(INTDIR)\CLOUD.res" : $(SOURCE) $(DEP_RSC_CLOUD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Release"


"$(INTDIR)\CLOUD.res" : $(SOURCE) $(DEP_RSC_CLOUD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Release"


"$(INTDIR)\CLOUD.res" : $(SOURCE) $(DEP_RSC_CLOUD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Debug"


"$(INTDIR)\CLOUD.res" : $(SOURCE) $(DEP_RSC_CLOUD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Clouddoc.cpp

!IF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Release"

DEP_CPP_CLOUDD=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	{$(INCLUDE)}"\SECALL.H"\
	

"$(INTDIR)\Clouddoc.obj" : $(SOURCE) $(DEP_CPP_CLOUDD) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Debug"

DEP_CPP_CLOUDD=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Clouddoc.obj" : $(SOURCE) $(DEP_CPP_CLOUDD) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Debug"

DEP_CPP_CLOUDD=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Clouddoc.obj" : $(SOURCE) $(DEP_CPP_CLOUDD) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Release"

DEP_CPP_CLOUDD=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Clouddoc.obj" : $(SOURCE) $(DEP_CPP_CLOUDD) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Debug"

DEP_CPP_CLOUDD=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Clouddoc.obj" : $(SOURCE) $(DEP_CPP_CLOUDD) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Release"

DEP_CPP_CLOUDD=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Clouddoc.obj" : $(SOURCE) $(DEP_CPP_CLOUDD) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Release"

DEP_CPP_CLOUDD=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Clouddoc.obj" : $(SOURCE) $(DEP_CPP_CLOUDD) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Debug"

DEP_CPP_CLOUDD=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Clouddoc.obj" : $(SOURCE) $(DEP_CPP_CLOUDD) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mainfrm.cpp

!IF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Release"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Debug"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Debug"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Release"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Debug"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Release"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Release"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Debug"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cloud.cpp

!IF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Release"

DEP_CPP_CLOUD_=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	{$(INCLUDE)}"\SECALL.H"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloud.obj" : $(SOURCE) $(DEP_CPP_CLOUD_) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Debug"

DEP_CPP_CLOUD_=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloud.obj" : $(SOURCE) $(DEP_CPP_CLOUD_) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Debug"

DEP_CPP_CLOUD_=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloud.obj" : $(SOURCE) $(DEP_CPP_CLOUD_) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Release"

DEP_CPP_CLOUD_=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloud.obj" : $(SOURCE) $(DEP_CPP_CLOUD_) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Debug"

DEP_CPP_CLOUD_=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloud.obj" : $(SOURCE) $(DEP_CPP_CLOUD_) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Release"

DEP_CPP_CLOUD_=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloud.obj" : $(SOURCE) $(DEP_CPP_CLOUD_) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Release"

DEP_CPP_CLOUD_=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloud.obj" : $(SOURCE) $(DEP_CPP_CLOUD_) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Debug"

DEP_CPP_CLOUD_=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Mainfrm.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloud.obj" : $(SOURCE) $(DEP_CPP_CLOUD_) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cloudvw.cpp

!IF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Release"

DEP_CPP_CLOUDV=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloudvw.obj" : $(SOURCE) $(DEP_CPP_CLOUDV) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC static AFXDLL Debug"

DEP_CPP_CLOUDV=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloudvw.obj" : $(SOURCE) $(DEP_CPP_CLOUDV) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Debug"

DEP_CPP_CLOUDV=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloudvw.obj" : $(SOURCE) $(DEP_CPP_CLOUDV) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 SEC DLL Release"

DEP_CPP_CLOUDV=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloudvw.obj" : $(SOURCE) $(DEP_CPP_CLOUDV) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Debug"

DEP_CPP_CLOUDV=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloudvw.obj" : $(SOURCE) $(DEP_CPP_CLOUDV) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC static AFXDLL Release"

DEP_CPP_CLOUDV=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloudvw.obj" : $(SOURCE) $(DEP_CPP_CLOUDV) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Release"

DEP_CPP_CLOUDV=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloudvw.obj" : $(SOURCE) $(DEP_CPP_CLOUDV) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ELSEIF  "$(CFG)" == "CLOUD - Win32 Unicode SEC DLL Debug"

DEP_CPP_CLOUDV=\
	".\Stdafx.h"\
	".\Cloud.h"\
	".\Clouddoc.h"\
	".\Cloudvw.h"\
	".\Mainfrm.h"\
	{$(INCLUDE)}"\SECALL.H"\
	".\..\..\Include\slocale.h"\
	{$(INCLUDE)}"\SECPANVW.H"\
	

"$(INTDIR)\Cloudvw.obj" : $(SOURCE) $(DEP_CPP_CLOUDV) "$(INTDIR)"\
 "$(INTDIR)\cloud.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
