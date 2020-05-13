# Microsoft Developer Studio Generated NMAKE File, Format Version 42001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=wavctrl - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to wavctrl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "wavctrl - Win32 Release" && "$(CFG)" !=\
 "wavctrl - Win32 Debug" && "$(CFG)" != "wavctrl - Win32 Unicode Debug" &&\
 "$(CFG)" != "wavctrl - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "wavctrl.mak" CFG="wavctrl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wavctrl - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wavctrl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wavctrl - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wavctrl - Win32 Unicode Release" (based on\
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
# PROP Target_Last_Scanned "wavctrl - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "wavctrl - Win32 Release"

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

ALL : "$(OUTDIR)\wavctrl.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\wavctrl.obj"
	-@erase "$(INTDIR)\wavctrl.pch"
	-@erase "$(INTDIR)\wavctrl.res"
	-@erase "$(INTDIR)\wavctrl.tlb"
	-@erase "$(INTDIR)\WavctrlCtl.obj"
	-@erase "$(INTDIR)\WavctrlPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\wavctrl.exp"
	-@erase "$(OUTDIR)\wavctrl.lib"
	-@erase "$(OUTDIR)\wavctrl.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/wavctrl.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/wavctrl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wavctrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/wavctrl.pdb" /machine:I386 /def:".\wavctrl.def"\
 /out:"$(OUTDIR)/wavctrl.ocx" /implib:"$(OUTDIR)/wavctrl.lib" 
DEF_FILE= \
	".\wavctrl.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\wavctrl.obj" \
	"$(INTDIR)\wavctrl.res" \
	"$(INTDIR)\WavctrlCtl.obj" \
	"$(INTDIR)\WavctrlPpg.obj" \
	"..\..\Msdev\lib\Winmm.lib"

"$(OUTDIR)\wavctrl.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\wavctrl.ocx
InputPath=.\Release\wavctrl.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"

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

ALL : "$(OUTDIR)\wavctrl.ocx" "$(OUTDIR)\regsvr32.trg" "$(OUTDIR)\wavctrl.bsc"

CLEAN : 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\wavctrl.obj"
	-@erase "$(INTDIR)\wavctrl.pch"
	-@erase "$(INTDIR)\wavctrl.res"
	-@erase "$(INTDIR)\wavctrl.sbr"
	-@erase "$(INTDIR)\wavctrl.tlb"
	-@erase "$(INTDIR)\WavctrlCtl.obj"
	-@erase "$(INTDIR)\WavctrlCtl.sbr"
	-@erase "$(INTDIR)\WavctrlPpg.obj"
	-@erase "$(INTDIR)\WavctrlPpg.sbr"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\wavctrl.bsc"
	-@erase "$(OUTDIR)\wavctrl.exp"
	-@erase "$(OUTDIR)\wavctrl.ilk"
	-@erase "$(OUTDIR)\wavctrl.lib"
	-@erase "$(OUTDIR)\wavctrl.ocx"
	-@erase "$(OUTDIR)\wavctrl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/wavctrl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/wavctrl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wavctrl.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\wavctrl.sbr" \
	"$(INTDIR)\WavctrlCtl.sbr" \
	"$(INTDIR)\WavctrlPpg.sbr"

"$(OUTDIR)\wavctrl.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/wavctrl.pdb" /debug /machine:I386 /def:".\wavctrl.def"\
 /out:"$(OUTDIR)/wavctrl.ocx" /implib:"$(OUTDIR)/wavctrl.lib" 
DEF_FILE= \
	".\wavctrl.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\wavctrl.obj" \
	"$(INTDIR)\wavctrl.res" \
	"$(INTDIR)\WavctrlCtl.obj" \
	"$(INTDIR)\WavctrlPpg.obj" \
	"..\..\Msdev\lib\Winmm.lib"

"$(OUTDIR)\wavctrl.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\wavctrl.ocx
InputPath=.\Debug\wavctrl.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\wavctrl.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\wavctrl.obj"
	-@erase "$(INTDIR)\wavctrl.pch"
	-@erase "$(INTDIR)\wavctrl.res"
	-@erase "$(INTDIR)\wavctrl.tlb"
	-@erase "$(INTDIR)\WavctrlCtl.obj"
	-@erase "$(INTDIR)\WavctrlPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\wavctrl.exp"
	-@erase "$(OUTDIR)\wavctrl.ilk"
	-@erase "$(OUTDIR)\wavctrl.lib"
	-@erase "$(OUTDIR)\wavctrl.ocx"
	-@erase "$(OUTDIR)\wavctrl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/wavctrl.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/wavctrl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wavctrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/wavctrl.pdb" /debug /machine:I386 /def:".\wavctrl.def"\
 /out:"$(OUTDIR)/wavctrl.ocx" /implib:"$(OUTDIR)/wavctrl.lib" 
DEF_FILE= \
	".\wavctrl.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\wavctrl.obj" \
	"$(INTDIR)\wavctrl.res" \
	"$(INTDIR)\WavctrlCtl.obj" \
	"$(INTDIR)\WavctrlPpg.obj" \
	"..\..\Msdev\lib\Winmm.lib"

"$(OUTDIR)\wavctrl.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\wavctrl.ocx
InputPath=.\DebugU\wavctrl.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\wavctrl.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\wavctrl.obj"
	-@erase "$(INTDIR)\wavctrl.pch"
	-@erase "$(INTDIR)\wavctrl.res"
	-@erase "$(INTDIR)\wavctrl.tlb"
	-@erase "$(INTDIR)\WavctrlCtl.obj"
	-@erase "$(INTDIR)\WavctrlPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\wavctrl.exp"
	-@erase "$(OUTDIR)\wavctrl.lib"
	-@erase "$(OUTDIR)\wavctrl.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/wavctrl.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/wavctrl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wavctrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/wavctrl.pdb" /machine:I386 /def:".\wavctrl.def"\
 /out:"$(OUTDIR)/wavctrl.ocx" /implib:"$(OUTDIR)/wavctrl.lib" 
DEF_FILE= \
	".\wavctrl.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\wavctrl.obj" \
	"$(INTDIR)\wavctrl.res" \
	"$(INTDIR)\WavctrlCtl.obj" \
	"$(INTDIR)\WavctrlPpg.obj" \
	"..\..\Msdev\lib\Winmm.lib"

"$(OUTDIR)\wavctrl.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\wavctrl.ocx
InputPath=.\ReleaseU\wavctrl.ocx
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

# Name "wavctrl - Win32 Release"
# Name "wavctrl - Win32 Debug"
# Name "wavctrl - Win32 Unicode Debug"
# Name "wavctrl - Win32 Unicode Release"

!IF  "$(CFG)" == "wavctrl - Win32 Release"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "wavctrl - Win32 Release"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "wavctrl - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/wavctrl.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\wavctrl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/wavctrl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\wavctrl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/wavctrl.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\wavctrl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/wavctrl.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\wavctrl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wavctrl.cpp
DEP_CPP_WAVCT=\
	".\StdAfx.h"\
	".\wavctrl.h"\
	

!IF  "$(CFG)" == "wavctrl - Win32 Release"


"$(INTDIR)\wavctrl.obj" : $(SOURCE) $(DEP_CPP_WAVCT) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"


"$(INTDIR)\wavctrl.obj" : $(SOURCE) $(DEP_CPP_WAVCT) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"

"$(INTDIR)\wavctrl.sbr" : $(SOURCE) $(DEP_CPP_WAVCT) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"


"$(INTDIR)\wavctrl.obj" : $(SOURCE) $(DEP_CPP_WAVCT) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"


"$(INTDIR)\wavctrl.obj" : $(SOURCE) $(DEP_CPP_WAVCT) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wavctrl.def

!IF  "$(CFG)" == "wavctrl - Win32 Release"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wavctrl.rc

!IF  "$(CFG)" == "wavctrl - Win32 Release"

DEP_RSC_WAVCTR=\
	".\wavctrl.ico"\
	".\WavctrlCtl.bmp"\
	
NODEP_RSC_WAVCTR=\
	".\Release\wavctrl.tlb"\
	

"$(INTDIR)\wavctrl.res" : $(SOURCE) $(DEP_RSC_WAVCTR) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/wavctrl.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"

DEP_RSC_WAVCTR=\
	".\wavctrl.ico"\
	".\WavctrlCtl.bmp"\
	
NODEP_RSC_WAVCTR=\
	".\Debug\wavctrl.tlb"\
	

"$(INTDIR)\wavctrl.res" : $(SOURCE) $(DEP_RSC_WAVCTR) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/wavctrl.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"

DEP_RSC_WAVCTR=\
	".\wavctrl.ico"\
	".\WavctrlCtl.bmp"\
	
NODEP_RSC_WAVCTR=\
	".\DebugU\wavctrl.tlb"\
	

"$(INTDIR)\wavctrl.res" : $(SOURCE) $(DEP_RSC_WAVCTR) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/wavctrl.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"

DEP_RSC_WAVCTR=\
	".\wavctrl.ico"\
	".\WavctrlCtl.bmp"\
	
NODEP_RSC_WAVCTR=\
	".\ReleaseU\wavctrl.tlb"\
	

"$(INTDIR)\wavctrl.res" : $(SOURCE) $(DEP_RSC_WAVCTR) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/wavctrl.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wavctrl.odl

!IF  "$(CFG)" == "wavctrl - Win32 Release"


"$(OUTDIR)\wavctrl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/wavctrl.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"


"$(OUTDIR)\wavctrl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/wavctrl.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"


"$(OUTDIR)\wavctrl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/wavctrl.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"


"$(OUTDIR)\wavctrl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/wavctrl.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WavctrlCtl.cpp
DEP_CPP_WAVCTRL=\
	".\StdAfx.h"\
	".\wavctrl.h"\
	".\WavctrlCtl.h"\
	".\WavctrlPpg.h"\
	

!IF  "$(CFG)" == "wavctrl - Win32 Release"


"$(INTDIR)\WavctrlCtl.obj" : $(SOURCE) $(DEP_CPP_WAVCTRL) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"


"$(INTDIR)\WavctrlCtl.obj" : $(SOURCE) $(DEP_CPP_WAVCTRL) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"

"$(INTDIR)\WavctrlCtl.sbr" : $(SOURCE) $(DEP_CPP_WAVCTRL) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"


"$(INTDIR)\WavctrlCtl.obj" : $(SOURCE) $(DEP_CPP_WAVCTRL) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"


"$(INTDIR)\WavctrlCtl.obj" : $(SOURCE) $(DEP_CPP_WAVCTRL) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WavctrlPpg.cpp
DEP_CPP_WAVCTRLP=\
	".\StdAfx.h"\
	".\wavctrl.h"\
	".\WavctrlPpg.h"\
	

!IF  "$(CFG)" == "wavctrl - Win32 Release"


"$(INTDIR)\WavctrlPpg.obj" : $(SOURCE) $(DEP_CPP_WAVCTRLP) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"


"$(INTDIR)\WavctrlPpg.obj" : $(SOURCE) $(DEP_CPP_WAVCTRLP) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"

"$(INTDIR)\WavctrlPpg.sbr" : $(SOURCE) $(DEP_CPP_WAVCTRLP) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"


"$(INTDIR)\WavctrlPpg.obj" : $(SOURCE) $(DEP_CPP_WAVCTRLP) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"


"$(INTDIR)\WavctrlPpg.obj" : $(SOURCE) $(DEP_CPP_WAVCTRLP) "$(INTDIR)"\
 "$(INTDIR)\wavctrl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Msdev\lib\Winmm.lib

!IF  "$(CFG)" == "wavctrl - Win32 Release"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Debug"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "wavctrl - Win32 Unicode Release"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
