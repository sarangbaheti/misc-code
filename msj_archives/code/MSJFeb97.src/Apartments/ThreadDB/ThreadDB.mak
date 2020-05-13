# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=ThreadDB - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ThreadDB - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ThreadDB - Win32 Release" && "$(CFG)" !=\
 "ThreadDB - Win32 Debug" && "$(CFG)" != "ThreadDB - Win32 Unicode Debug" &&\
 "$(CFG)" != "ThreadDB - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ThreadDB.mak" CFG="ThreadDB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ThreadDB - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ThreadDB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ThreadDB - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ThreadDB - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "ThreadDB - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "ThreadDB - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ThreadDB.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Customer.obj"
	-@erase "$(INTDIR)\SearchThread.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ThreadDB.obj"
	-@erase "$(INTDIR)\ThreadDB.pch"
	-@erase "$(INTDIR)\ThreadDB.res"
	-@erase "$(INTDIR)\ThreadDB.tlb"
	-@erase "$(INTDIR)\ThreadDBCtl.obj"
	-@erase "$(INTDIR)\ThreadDBPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\ThreadDB.exp"
	-@erase "$(OUTDIR)\ThreadDB.lib"
	-@erase "$(OUTDIR)\ThreadDB.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_MBCS" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)/ThreadDB.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ThreadDB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ThreadDB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ThreadDB.pdb" /machine:I386 /def:".\ThreadDB.def"\
 /out:"$(OUTDIR)/ThreadDB.ocx" /implib:"$(OUTDIR)/ThreadDB.lib" 
DEF_FILE= \
	".\ThreadDB.def"
LINK32_OBJS= \
	"$(INTDIR)\Customer.obj" \
	"$(INTDIR)\SearchThread.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ThreadDB.obj" \
	"$(INTDIR)\ThreadDB.res" \
	"$(INTDIR)\ThreadDBCtl.obj" \
	"$(INTDIR)\ThreadDBPpg.obj"

"$(OUTDIR)\ThreadDB.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\ThreadDB.ocx
InputPath=.\Release\ThreadDB.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ThreadDB.ocx" "$(OUTDIR)\ThreadDB.bsc"\
 "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Customer.obj"
	-@erase "$(INTDIR)\Customer.sbr"
	-@erase "$(INTDIR)\SearchThread.obj"
	-@erase "$(INTDIR)\SearchThread.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\ThreadDB.obj"
	-@erase "$(INTDIR)\ThreadDB.pch"
	-@erase "$(INTDIR)\ThreadDB.res"
	-@erase "$(INTDIR)\ThreadDB.sbr"
	-@erase "$(INTDIR)\ThreadDB.tlb"
	-@erase "$(INTDIR)\ThreadDBCtl.obj"
	-@erase "$(INTDIR)\ThreadDBCtl.sbr"
	-@erase "$(INTDIR)\ThreadDBPpg.obj"
	-@erase "$(INTDIR)\ThreadDBPpg.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\ThreadDB.bsc"
	-@erase "$(OUTDIR)\ThreadDB.exp"
	-@erase "$(OUTDIR)\ThreadDB.ilk"
	-@erase "$(OUTDIR)\ThreadDB.lib"
	-@erase "$(OUTDIR)\ThreadDB.ocx"
	-@erase "$(OUTDIR)\ThreadDB.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/ThreadDB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ThreadDB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ThreadDB.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Customer.sbr" \
	"$(INTDIR)\SearchThread.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\ThreadDB.sbr" \
	"$(INTDIR)\ThreadDBCtl.sbr" \
	"$(INTDIR)\ThreadDBPpg.sbr"

"$(OUTDIR)\ThreadDB.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ThreadDB.pdb" /debug /machine:I386 /def:".\ThreadDB.def"\
 /out:"$(OUTDIR)/ThreadDB.ocx" /implib:"$(OUTDIR)/ThreadDB.lib" 
DEF_FILE= \
	".\ThreadDB.def"
LINK32_OBJS= \
	"$(INTDIR)\Customer.obj" \
	"$(INTDIR)\SearchThread.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ThreadDB.obj" \
	"$(INTDIR)\ThreadDB.res" \
	"$(INTDIR)\ThreadDBCtl.obj" \
	"$(INTDIR)\ThreadDBPpg.obj"

"$(OUTDIR)\ThreadDB.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\ThreadDB.ocx
InputPath=.\Debug\ThreadDB.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ThreadDB.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Customer.obj"
	-@erase "$(INTDIR)\SearchThread.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ThreadDB.obj"
	-@erase "$(INTDIR)\ThreadDB.pch"
	-@erase "$(INTDIR)\ThreadDB.res"
	-@erase "$(INTDIR)\ThreadDB.tlb"
	-@erase "$(INTDIR)\ThreadDBCtl.obj"
	-@erase "$(INTDIR)\ThreadDBPpg.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\ThreadDB.exp"
	-@erase "$(OUTDIR)\ThreadDB.ilk"
	-@erase "$(OUTDIR)\ThreadDB.lib"
	-@erase "$(OUTDIR)\ThreadDB.ocx"
	-@erase "$(OUTDIR)\ThreadDB.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32"\
 /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL"\
 /Fp"$(INTDIR)/ThreadDB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ThreadDB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ThreadDB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ThreadDB.pdb" /debug /machine:I386 /def:".\ThreadDB.def"\
 /out:"$(OUTDIR)/ThreadDB.ocx" /implib:"$(OUTDIR)/ThreadDB.lib" 
DEF_FILE= \
	".\ThreadDB.def"
LINK32_OBJS= \
	"$(INTDIR)\Customer.obj" \
	"$(INTDIR)\SearchThread.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ThreadDB.obj" \
	"$(INTDIR)\ThreadDB.res" \
	"$(INTDIR)\ThreadDBCtl.obj" \
	"$(INTDIR)\ThreadDBPpg.obj"

"$(OUTDIR)\ThreadDB.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\ThreadDB.ocx
InputPath=.\DebugU\ThreadDB.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\ThreadDB.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Customer.obj"
	-@erase "$(INTDIR)\SearchThread.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ThreadDB.obj"
	-@erase "$(INTDIR)\ThreadDB.pch"
	-@erase "$(INTDIR)\ThreadDB.res"
	-@erase "$(INTDIR)\ThreadDB.tlb"
	-@erase "$(INTDIR)\ThreadDBCtl.obj"
	-@erase "$(INTDIR)\ThreadDBPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\ThreadDB.exp"
	-@erase "$(OUTDIR)\ThreadDB.lib"
	-@erase "$(OUTDIR)\ThreadDB.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)/ThreadDB.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ThreadDB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ThreadDB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ThreadDB.pdb" /machine:I386 /def:".\ThreadDB.def"\
 /out:"$(OUTDIR)/ThreadDB.ocx" /implib:"$(OUTDIR)/ThreadDB.lib" 
DEF_FILE= \
	".\ThreadDB.def"
LINK32_OBJS= \
	"$(INTDIR)\Customer.obj" \
	"$(INTDIR)\SearchThread.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ThreadDB.obj" \
	"$(INTDIR)\ThreadDB.res" \
	"$(INTDIR)\ThreadDBCtl.obj" \
	"$(INTDIR)\ThreadDBPpg.obj"

"$(OUTDIR)\ThreadDB.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\ThreadDB.ocx
InputPath=.\ReleaseU\ThreadDB.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

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

# Name "ThreadDB - Win32 Release"
# Name "ThreadDB - Win32 Debug"
# Name "ThreadDB - Win32 Unicode Debug"
# Name "ThreadDB - Win32 Unicode Release"

!IF  "$(CFG)" == "ThreadDB - Win32 Release"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "ThreadDB - Win32 Release"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ThreadDB - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)/ThreadDB.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ThreadDB.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/ThreadDB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ThreadDB.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32"\
 /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL"\
 /Fp"$(INTDIR)/ThreadDB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ThreadDB.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)/ThreadDB.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ThreadDB.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ThreadDB.cpp
DEP_CPP_THREA=\
	".\StdAfx.h"\
	".\ThreadDB.h"\
	

!IF  "$(CFG)" == "ThreadDB - Win32 Release"


"$(INTDIR)\ThreadDB.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"


"$(INTDIR)\ThreadDB.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"

"$(INTDIR)\ThreadDB.sbr" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"


"$(INTDIR)\ThreadDB.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"


"$(INTDIR)\ThreadDB.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ThreadDB.def

!IF  "$(CFG)" == "ThreadDB - Win32 Release"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ThreadDB.rc

!IF  "$(CFG)" == "ThreadDB - Win32 Release"

DEP_RSC_THREAD=\
	".\ThreadDB.ico"\
	".\ThreadDBCtl.bmp"\
	
NODEP_RSC_THREAD=\
	".\Release\ThreadDB.tlb"\
	

"$(INTDIR)\ThreadDB.res" : $(SOURCE) $(DEP_RSC_THREAD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/ThreadDB.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"

DEP_RSC_THREAD=\
	".\ThreadDB.ico"\
	".\ThreadDBCtl.bmp"\
	
NODEP_RSC_THREAD=\
	".\Debug\ThreadDB.tlb"\
	

"$(INTDIR)\ThreadDB.res" : $(SOURCE) $(DEP_RSC_THREAD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/ThreadDB.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"

DEP_RSC_THREAD=\
	".\ThreadDB.ico"\
	".\ThreadDBCtl.bmp"\
	
NODEP_RSC_THREAD=\
	".\DebugU\ThreadDB.tlb"\
	

"$(INTDIR)\ThreadDB.res" : $(SOURCE) $(DEP_RSC_THREAD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/ThreadDB.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"

DEP_RSC_THREAD=\
	".\ThreadDB.ico"\
	".\ThreadDBCtl.bmp"\
	
NODEP_RSC_THREAD=\
	".\ReleaseU\ThreadDB.tlb"\
	

"$(INTDIR)\ThreadDB.res" : $(SOURCE) $(DEP_RSC_THREAD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/ThreadDB.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ThreadDB.odl

!IF  "$(CFG)" == "ThreadDB - Win32 Release"


"$(OUTDIR)\ThreadDB.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/ThreadDB.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"


"$(OUTDIR)\ThreadDB.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/ThreadDB.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"


"$(OUTDIR)\ThreadDB.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/ThreadDB.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"


"$(OUTDIR)\ThreadDB.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/ThreadDB.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ThreadDBCtl.cpp
DEP_CPP_THREADD=\
	".\SearchThread.h"\
	".\StdAfx.h"\
	".\ThreadDB.h"\
	".\ThreadDBCtl.h"\
	".\ThreadDBPpg.h"\
	

!IF  "$(CFG)" == "ThreadDB - Win32 Release"


"$(INTDIR)\ThreadDBCtl.obj" : $(SOURCE) $(DEP_CPP_THREADD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"


"$(INTDIR)\ThreadDBCtl.obj" : $(SOURCE) $(DEP_CPP_THREADD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"

"$(INTDIR)\ThreadDBCtl.sbr" : $(SOURCE) $(DEP_CPP_THREADD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"


"$(INTDIR)\ThreadDBCtl.obj" : $(SOURCE) $(DEP_CPP_THREADD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"


"$(INTDIR)\ThreadDBCtl.obj" : $(SOURCE) $(DEP_CPP_THREADD) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ThreadDBPpg.cpp
DEP_CPP_THREADDB=\
	".\StdAfx.h"\
	".\ThreadDB.h"\
	".\ThreadDBPpg.h"\
	

!IF  "$(CFG)" == "ThreadDB - Win32 Release"


"$(INTDIR)\ThreadDBPpg.obj" : $(SOURCE) $(DEP_CPP_THREADDB) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"


"$(INTDIR)\ThreadDBPpg.obj" : $(SOURCE) $(DEP_CPP_THREADDB) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"

"$(INTDIR)\ThreadDBPpg.sbr" : $(SOURCE) $(DEP_CPP_THREADDB) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"


"$(INTDIR)\ThreadDBPpg.obj" : $(SOURCE) $(DEP_CPP_THREADDB) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"


"$(INTDIR)\ThreadDBPpg.obj" : $(SOURCE) $(DEP_CPP_THREADDB) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SearchThread.cpp
DEP_CPP_SEARC=\
	".\Customer.h"\
	".\SearchThread.h"\
	".\StdAfx.h"\
	".\ThreadDB.h"\
	".\ThreadDBCtl.h"\
	

!IF  "$(CFG)" == "ThreadDB - Win32 Release"


"$(INTDIR)\SearchThread.obj" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"


"$(INTDIR)\SearchThread.obj" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"

"$(INTDIR)\SearchThread.sbr" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"


"$(INTDIR)\SearchThread.obj" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"


"$(INTDIR)\SearchThread.obj" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Customer.cpp
DEP_CPP_CUSTO=\
	".\Customer.h"\
	".\StdAfx.h"\
	".\ThreadDB.h"\
	

!IF  "$(CFG)" == "ThreadDB - Win32 Release"


"$(INTDIR)\Customer.obj" : $(SOURCE) $(DEP_CPP_CUSTO) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Debug"


"$(INTDIR)\Customer.obj" : $(SOURCE) $(DEP_CPP_CUSTO) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"

"$(INTDIR)\Customer.sbr" : $(SOURCE) $(DEP_CPP_CUSTO) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Debug"


"$(INTDIR)\Customer.obj" : $(SOURCE) $(DEP_CPP_CUSTO) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ELSEIF  "$(CFG)" == "ThreadDB - Win32 Unicode Release"


"$(INTDIR)\Customer.obj" : $(SOURCE) $(DEP_CPP_CUSTO) "$(INTDIR)"\
 "$(INTDIR)\ThreadDB.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
