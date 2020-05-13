# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=BounceThread - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to BounceThread - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "BounceThread - Win32 Release" && "$(CFG)" !=\
 "BounceThread - Win32 Debug" && "$(CFG)" !=\
 "BounceThread - Win32 Unicode Debug" && "$(CFG)" !=\
 "BounceThread - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "BounceThread.mak" CFG="BounceThread - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BounceThread - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BounceThread - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BounceThread - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BounceThread - Win32 Unicode Release" (based on\
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
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "BounceThread - Win32 Release"

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

ALL : "$(OUTDIR)\BounceThread.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\bounceth.obj"
	-@erase "$(INTDIR)\BounceThread.obj"
	-@erase "$(INTDIR)\BounceThread.pch"
	-@erase "$(INTDIR)\BounceThread.res"
	-@erase "$(INTDIR)\BounceThread.tlb"
	-@erase "$(INTDIR)\BounceThreadCtl.obj"
	-@erase "$(INTDIR)\BounceThreadPpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\BounceThread.exp"
	-@erase "$(OUTDIR)\BounceThread.lib"
	-@erase "$(OUTDIR)\BounceThread.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/BounceThread.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/BounceThread.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BounceThread.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/BounceThread.pdb" /machine:I386 /def:".\BounceThread.def"\
 /out:"$(OUTDIR)/BounceThread.ocx" /implib:"$(OUTDIR)/BounceThread.lib" 
DEF_FILE= \
	".\BounceThread.def"
LINK32_OBJS= \
	"$(INTDIR)\bounceth.obj" \
	"$(INTDIR)\BounceThread.obj" \
	"$(INTDIR)\BounceThread.res" \
	"$(INTDIR)\BounceThreadCtl.obj" \
	"$(INTDIR)\BounceThreadPpg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\BounceThread.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\BounceThread.ocx
InputPath=.\Release\BounceThread.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"

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

ALL : "$(OUTDIR)\BounceThread.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\bounceth.obj"
	-@erase "$(INTDIR)\BounceThread.obj"
	-@erase "$(INTDIR)\BounceThread.pch"
	-@erase "$(INTDIR)\BounceThread.res"
	-@erase "$(INTDIR)\BounceThread.tlb"
	-@erase "$(INTDIR)\BounceThreadCtl.obj"
	-@erase "$(INTDIR)\BounceThreadPpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\BounceThread.exp"
	-@erase "$(OUTDIR)\BounceThread.ilk"
	-@erase "$(OUTDIR)\BounceThread.lib"
	-@erase "$(OUTDIR)\BounceThread.ocx"
	-@erase "$(OUTDIR)\BounceThread.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL"\
 /Fp"$(INTDIR)/BounceThread.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/BounceThread.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BounceThread.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/BounceThread.pdb" /debug /machine:I386\
 /def:".\BounceThread.def" /out:"$(OUTDIR)/BounceThread.ocx"\
 /implib:"$(OUTDIR)/BounceThread.lib" 
DEF_FILE= \
	".\BounceThread.def"
LINK32_OBJS= \
	"$(INTDIR)\bounceth.obj" \
	"$(INTDIR)\BounceThread.obj" \
	"$(INTDIR)\BounceThread.res" \
	"$(INTDIR)\BounceThreadCtl.obj" \
	"$(INTDIR)\BounceThreadPpg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\BounceThread.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\BounceThread.ocx
InputPath=.\Debug\BounceThread.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\BounceThread.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\bounceth.obj"
	-@erase "$(INTDIR)\BounceThread.obj"
	-@erase "$(INTDIR)\BounceThread.pch"
	-@erase "$(INTDIR)\BounceThread.res"
	-@erase "$(INTDIR)\BounceThread.tlb"
	-@erase "$(INTDIR)\BounceThreadCtl.obj"
	-@erase "$(INTDIR)\BounceThreadPpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\BounceThread.exp"
	-@erase "$(OUTDIR)\BounceThread.ilk"
	-@erase "$(OUTDIR)\BounceThread.lib"
	-@erase "$(OUTDIR)\BounceThread.ocx"
	-@erase "$(OUTDIR)\BounceThread.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/BounceThread.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/BounceThread.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BounceThread.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/BounceThread.pdb" /debug /machine:I386\
 /def:".\BounceThread.def" /out:"$(OUTDIR)/BounceThread.ocx"\
 /implib:"$(OUTDIR)/BounceThread.lib" 
DEF_FILE= \
	".\BounceThread.def"
LINK32_OBJS= \
	"$(INTDIR)\bounceth.obj" \
	"$(INTDIR)\BounceThread.obj" \
	"$(INTDIR)\BounceThread.res" \
	"$(INTDIR)\BounceThreadCtl.obj" \
	"$(INTDIR)\BounceThreadPpg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\BounceThread.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\BounceThread.ocx
InputPath=.\DebugU\BounceThread.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\BounceThread.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\bounceth.obj"
	-@erase "$(INTDIR)\BounceThread.obj"
	-@erase "$(INTDIR)\BounceThread.pch"
	-@erase "$(INTDIR)\BounceThread.res"
	-@erase "$(INTDIR)\BounceThread.tlb"
	-@erase "$(INTDIR)\BounceThreadCtl.obj"
	-@erase "$(INTDIR)\BounceThreadPpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\BounceThread.exp"
	-@erase "$(OUTDIR)\BounceThread.lib"
	-@erase "$(OUTDIR)\BounceThread.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/BounceThread.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/BounceThread.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BounceThread.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/BounceThread.pdb" /machine:I386 /def:".\BounceThread.def"\
 /out:"$(OUTDIR)/BounceThread.ocx" /implib:"$(OUTDIR)/BounceThread.lib" 
DEF_FILE= \
	".\BounceThread.def"
LINK32_OBJS= \
	"$(INTDIR)\bounceth.obj" \
	"$(INTDIR)\BounceThread.obj" \
	"$(INTDIR)\BounceThread.res" \
	"$(INTDIR)\BounceThreadCtl.obj" \
	"$(INTDIR)\BounceThreadPpg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\BounceThread.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\BounceThread.ocx
InputPath=.\ReleaseU\BounceThread.ocx
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

# Name "BounceThread - Win32 Release"
# Name "BounceThread - Win32 Debug"
# Name "BounceThread - Win32 Unicode Debug"
# Name "BounceThread - Win32 Unicode Release"

!IF  "$(CFG)" == "BounceThread - Win32 Release"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "BounceThread - Win32 Release"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "BounceThread - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/BounceThread.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BounceThread.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL"\
 /Fp"$(INTDIR)/BounceThread.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BounceThread.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/BounceThread.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BounceThread.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/BounceThread.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BounceThread.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BounceThread.cpp
DEP_CPP_BOUNC=\
	".\BounceThread.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "BounceThread - Win32 Release"


"$(INTDIR)\BounceThread.obj" : $(SOURCE) $(DEP_CPP_BOUNC) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"


"$(INTDIR)\BounceThread.obj" : $(SOURCE) $(DEP_CPP_BOUNC) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"


"$(INTDIR)\BounceThread.obj" : $(SOURCE) $(DEP_CPP_BOUNC) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"


"$(INTDIR)\BounceThread.obj" : $(SOURCE) $(DEP_CPP_BOUNC) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BounceThread.def

!IF  "$(CFG)" == "BounceThread - Win32 Release"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BounceThread.rc

!IF  "$(CFG)" == "BounceThread - Win32 Release"

DEP_RSC_BOUNCE=\
	".\BounceThread.ico"\
	".\BounceThreadCtl.bmp"\
	
NODEP_RSC_BOUNCE=\
	".\Release\BounceThread.tlb"\
	

"$(INTDIR)\BounceThread.res" : $(SOURCE) $(DEP_RSC_BOUNCE) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/BounceThread.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"

DEP_RSC_BOUNCE=\
	".\BounceThread.ico"\
	".\BounceThreadCtl.bmp"\
	".\Debug\BounceThread.tlb"\
	

"$(INTDIR)\BounceThread.res" : $(SOURCE) $(DEP_RSC_BOUNCE) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/BounceThread.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"

DEP_RSC_BOUNCE=\
	".\BounceThread.ico"\
	".\BounceThreadCtl.bmp"\
	
NODEP_RSC_BOUNCE=\
	".\DebugU\BounceThread.tlb"\
	

"$(INTDIR)\BounceThread.res" : $(SOURCE) $(DEP_RSC_BOUNCE) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/BounceThread.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"

DEP_RSC_BOUNCE=\
	".\BounceThread.ico"\
	".\BounceThreadCtl.bmp"\
	
NODEP_RSC_BOUNCE=\
	".\ReleaseU\BounceThread.tlb"\
	

"$(INTDIR)\BounceThread.res" : $(SOURCE) $(DEP_RSC_BOUNCE) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/BounceThread.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BounceThread.odl

!IF  "$(CFG)" == "BounceThread - Win32 Release"


"$(OUTDIR)\BounceThread.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/BounceThread.tlb" /win32\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"


"$(OUTDIR)\BounceThread.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/BounceThread.tlb" /win32\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"


"$(OUTDIR)\BounceThread.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/BounceThread.tlb" /win32\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"


"$(OUTDIR)\BounceThread.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/BounceThread.tlb" /win32\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BounceThreadCtl.cpp
DEP_CPP_BOUNCET=\
	".\bounceth.h"\
	".\BounceThread.h"\
	".\BounceThreadCtl.h"\
	".\BounceThreadPpg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "BounceThread - Win32 Release"


"$(INTDIR)\BounceThreadCtl.obj" : $(SOURCE) $(DEP_CPP_BOUNCET) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"


"$(INTDIR)\BounceThreadCtl.obj" : $(SOURCE) $(DEP_CPP_BOUNCET) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"


"$(INTDIR)\BounceThreadCtl.obj" : $(SOURCE) $(DEP_CPP_BOUNCET) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"


"$(INTDIR)\BounceThreadCtl.obj" : $(SOURCE) $(DEP_CPP_BOUNCET) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BounceThreadPpg.cpp
DEP_CPP_BOUNCETH=\
	".\BounceThread.h"\
	".\BounceThreadPpg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "BounceThread - Win32 Release"


"$(INTDIR)\BounceThreadPpg.obj" : $(SOURCE) $(DEP_CPP_BOUNCETH) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"


"$(INTDIR)\BounceThreadPpg.obj" : $(SOURCE) $(DEP_CPP_BOUNCETH) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"


"$(INTDIR)\BounceThreadPpg.obj" : $(SOURCE) $(DEP_CPP_BOUNCETH) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"


"$(INTDIR)\BounceThreadPpg.obj" : $(SOURCE) $(DEP_CPP_BOUNCETH) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bounceth.cpp
DEP_CPP_BOUNCETH_=\
	".\bounceth.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "BounceThread - Win32 Release"


"$(INTDIR)\bounceth.obj" : $(SOURCE) $(DEP_CPP_BOUNCETH_) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Debug"


"$(INTDIR)\bounceth.obj" : $(SOURCE) $(DEP_CPP_BOUNCETH_) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Debug"


"$(INTDIR)\bounceth.obj" : $(SOURCE) $(DEP_CPP_BOUNCETH_) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ELSEIF  "$(CFG)" == "BounceThread - Win32 Unicode Release"


"$(INTDIR)\bounceth.obj" : $(SOURCE) $(DEP_CPP_BOUNCETH_) "$(INTDIR)"\
 "$(INTDIR)\BounceThread.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
