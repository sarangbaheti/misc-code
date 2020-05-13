# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=demo42 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to demo42 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "demo42 - Win32 Release" && "$(CFG)" != "demo42 - Win32 Debug"\
 && "$(CFG)" != "demo42 - Win32 Unicode Debug" && "$(CFG)" !=\
 "demo42 - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "demo42.mak" CFG="demo42 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "demo42 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "demo42 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "demo42 - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "demo42 - Win32 Unicode Release" (based on\
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
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "demo42 - Win32 Release"

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

ALL : "$(OUTDIR)\demo42.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\demo42.obj"
	-@erase "$(INTDIR)\demo42.pch"
	-@erase "$(INTDIR)\demo42.res"
	-@erase "$(INTDIR)\demo42.tlb"
	-@erase "$(INTDIR)\Demo42Ctl.obj"
	-@erase "$(INTDIR)\Demo42Ppg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\demo42.exp"
	-@erase "$(OUTDIR)\demo42.lib"
	-@erase "$(OUTDIR)\demo42.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/demo42.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/demo42.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/demo42.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/demo42.pdb" /machine:I386 /def:".\demo42.def"\
 /out:"$(OUTDIR)/demo42.ocx" /implib:"$(OUTDIR)/demo42.lib" 
DEF_FILE= \
	".\demo42.def"
LINK32_OBJS= \
	"$(INTDIR)\demo42.obj" \
	"$(INTDIR)\demo42.res" \
	"$(INTDIR)\Demo42Ctl.obj" \
	"$(INTDIR)\Demo42Ppg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\demo42.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\demo42.ocx
InputPath=.\Release\demo42.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"

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

ALL : "$(OUTDIR)\demo42.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\demo42.obj"
	-@erase "$(INTDIR)\demo42.pch"
	-@erase "$(INTDIR)\demo42.res"
	-@erase "$(INTDIR)\demo42.tlb"
	-@erase "$(INTDIR)\Demo42Ctl.obj"
	-@erase "$(INTDIR)\Demo42Ppg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\demo42.exp"
	-@erase "$(OUTDIR)\demo42.ilk"
	-@erase "$(OUTDIR)\demo42.lib"
	-@erase "$(OUTDIR)\demo42.ocx"
	-@erase "$(OUTDIR)\demo42.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/demo42.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/demo42.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/demo42.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/demo42.pdb" /debug /machine:I386 /def:".\demo42.def"\
 /out:"$(OUTDIR)/demo42.ocx" /implib:"$(OUTDIR)/demo42.lib" 
DEF_FILE= \
	".\demo42.def"
LINK32_OBJS= \
	"$(INTDIR)\demo42.obj" \
	"$(INTDIR)\demo42.res" \
	"$(INTDIR)\Demo42Ctl.obj" \
	"$(INTDIR)\Demo42Ppg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\demo42.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\demo42.ocx
InputPath=.\Debug\demo42.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\demo42.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\demo42.obj"
	-@erase "$(INTDIR)\demo42.pch"
	-@erase "$(INTDIR)\demo42.res"
	-@erase "$(INTDIR)\demo42.tlb"
	-@erase "$(INTDIR)\Demo42Ctl.obj"
	-@erase "$(INTDIR)\Demo42Ppg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\demo42.exp"
	-@erase "$(OUTDIR)\demo42.ilk"
	-@erase "$(OUTDIR)\demo42.lib"
	-@erase "$(OUTDIR)\demo42.ocx"
	-@erase "$(OUTDIR)\demo42.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/demo42.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/demo42.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/demo42.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/demo42.pdb" /debug /machine:I386 /def:".\demo42.def"\
 /out:"$(OUTDIR)/demo42.ocx" /implib:"$(OUTDIR)/demo42.lib" 
DEF_FILE= \
	".\demo42.def"
LINK32_OBJS= \
	"$(INTDIR)\demo42.obj" \
	"$(INTDIR)\demo42.res" \
	"$(INTDIR)\Demo42Ctl.obj" \
	"$(INTDIR)\Demo42Ppg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\demo42.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\demo42.ocx
InputPath=.\DebugU\demo42.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\demo42.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\demo42.obj"
	-@erase "$(INTDIR)\demo42.pch"
	-@erase "$(INTDIR)\demo42.res"
	-@erase "$(INTDIR)\demo42.tlb"
	-@erase "$(INTDIR)\Demo42Ctl.obj"
	-@erase "$(INTDIR)\Demo42Ppg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\demo42.exp"
	-@erase "$(OUTDIR)\demo42.lib"
	-@erase "$(OUTDIR)\demo42.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/demo42.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/demo42.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/demo42.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/demo42.pdb" /machine:I386 /def:".\demo42.def"\
 /out:"$(OUTDIR)/demo42.ocx" /implib:"$(OUTDIR)/demo42.lib" 
DEF_FILE= \
	".\demo42.def"
LINK32_OBJS= \
	"$(INTDIR)\demo42.obj" \
	"$(INTDIR)\demo42.res" \
	"$(INTDIR)\Demo42Ctl.obj" \
	"$(INTDIR)\Demo42Ppg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\demo42.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\demo42.ocx
InputPath=.\ReleaseU\demo42.ocx
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

# Name "demo42 - Win32 Release"
# Name "demo42 - Win32 Debug"
# Name "demo42 - Win32 Unicode Debug"
# Name "demo42 - Win32 Unicode Release"

!IF  "$(CFG)" == "demo42 - Win32 Release"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "demo42 - Win32 Release"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "demo42 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/demo42.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\demo42.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/demo42.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\demo42.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/demo42.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\demo42.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/demo42.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\demo42.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\demo42.cpp
DEP_CPP_DEMO4=\
	".\demo42.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "demo42 - Win32 Release"


"$(INTDIR)\demo42.obj" : $(SOURCE) $(DEP_CPP_DEMO4) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"


"$(INTDIR)\demo42.obj" : $(SOURCE) $(DEP_CPP_DEMO4) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"


"$(INTDIR)\demo42.obj" : $(SOURCE) $(DEP_CPP_DEMO4) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"


"$(INTDIR)\demo42.obj" : $(SOURCE) $(DEP_CPP_DEMO4) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\demo42.def

!IF  "$(CFG)" == "demo42 - Win32 Release"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\demo42.rc

!IF  "$(CFG)" == "demo42 - Win32 Release"

DEP_RSC_DEMO42=\
	".\demo42.ico"\
	".\Demo42Ctl.bmp"\
	
NODEP_RSC_DEMO42=\
	".\Release\demo42.tlb"\
	

"$(INTDIR)\demo42.res" : $(SOURCE) $(DEP_RSC_DEMO42) "$(INTDIR)"\
 "$(INTDIR)\demo42.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/demo42.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"

DEP_RSC_DEMO42=\
	".\demo42.ico"\
	".\Demo42Ctl.bmp"\
	
NODEP_RSC_DEMO42=\
	".\Debug\demo42.tlb"\
	

"$(INTDIR)\demo42.res" : $(SOURCE) $(DEP_RSC_DEMO42) "$(INTDIR)"\
 "$(INTDIR)\demo42.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/demo42.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"

DEP_RSC_DEMO42=\
	".\demo42.ico"\
	".\Demo42Ctl.bmp"\
	
NODEP_RSC_DEMO42=\
	".\DebugU\demo42.tlb"\
	

"$(INTDIR)\demo42.res" : $(SOURCE) $(DEP_RSC_DEMO42) "$(INTDIR)"\
 "$(INTDIR)\demo42.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/demo42.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"

DEP_RSC_DEMO42=\
	".\demo42.ico"\
	".\Demo42Ctl.bmp"\
	
NODEP_RSC_DEMO42=\
	".\ReleaseU\demo42.tlb"\
	

"$(INTDIR)\demo42.res" : $(SOURCE) $(DEP_RSC_DEMO42) "$(INTDIR)"\
 "$(INTDIR)\demo42.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/demo42.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\demo42.odl

!IF  "$(CFG)" == "demo42 - Win32 Release"


"$(OUTDIR)\demo42.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/demo42.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"


"$(OUTDIR)\demo42.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/demo42.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"


"$(OUTDIR)\demo42.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/demo42.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"


"$(OUTDIR)\demo42.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/demo42.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Demo42Ctl.cpp
DEP_CPP_DEMO42C=\
	".\demo42.h"\
	".\Demo42Ctl.h"\
	".\Demo42Ppg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "demo42 - Win32 Release"


"$(INTDIR)\Demo42Ctl.obj" : $(SOURCE) $(DEP_CPP_DEMO42C) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"


"$(INTDIR)\Demo42Ctl.obj" : $(SOURCE) $(DEP_CPP_DEMO42C) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"


"$(INTDIR)\Demo42Ctl.obj" : $(SOURCE) $(DEP_CPP_DEMO42C) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"


"$(INTDIR)\Demo42Ctl.obj" : $(SOURCE) $(DEP_CPP_DEMO42C) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Demo42Ppg.cpp
DEP_CPP_DEMO42P=\
	".\demo42.h"\
	".\Demo42Ppg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "demo42 - Win32 Release"


"$(INTDIR)\Demo42Ppg.obj" : $(SOURCE) $(DEP_CPP_DEMO42P) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Debug"


"$(INTDIR)\Demo42Ppg.obj" : $(SOURCE) $(DEP_CPP_DEMO42P) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Debug"


"$(INTDIR)\Demo42Ppg.obj" : $(SOURCE) $(DEP_CPP_DEMO42P) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ELSEIF  "$(CFG)" == "demo42 - Win32 Unicode Release"


"$(INTDIR)\Demo42Ppg.obj" : $(SOURCE) $(DEP_CPP_DEMO42P) "$(INTDIR)"\
 "$(INTDIR)\demo42.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
