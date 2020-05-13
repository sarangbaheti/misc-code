# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=demo40 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to demo40 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "demo40 - Win32 Release" && "$(CFG)" != "demo40 - Win32 Debug"\
 && "$(CFG)" != "demo40 - Win32 Unicode Debug" && "$(CFG)" !=\
 "demo40 - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "demo40.mak" CFG="demo40 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "demo40 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "demo40 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "demo40 - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "demo40 - Win32 Unicode Release" (based on\
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
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "demo40 - Win32 Release"

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

ALL : "$(OUTDIR)\demo40.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Release\demo40.lib"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\demo40.obj"
	-@erase ".\Release\demo40.pch"
	-@erase ".\Release\demo40.res"
	-@erase ".\Release\demo40.tlb"
	-@erase ".\Release\Demo40Ctl.obj"
	-@erase ".\Release\Demo40Ppg.obj"
	-@erase ".\Release\demo40.exp"
	-@erase ".\Release\regsvr32.trg"
	-@erase ".\Release\demo40.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/demo40.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/demo40.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/demo40.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/demo40.pdb" /machine:I386 /def:".\demo40.def"\
 /out:"$(OUTDIR)/demo40.ocx" /implib:"$(OUTDIR)/demo40.lib" 
DEF_FILE= \
	".\demo40.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/demo40.obj" \
	"$(INTDIR)/Demo40Ctl.obj" \
	"$(INTDIR)/Demo40Ppg.obj" \
	"$(INTDIR)/demo40.res"

"$(OUTDIR)\demo40.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\demo40.ocx
InputPath=.\Release\demo40.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"

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

ALL : "$(OUTDIR)\demo40.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Debug\demo40.ilk"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\demo40.obj"
	-@erase ".\Debug\demo40.pch"
	-@erase ".\Debug\demo40.res"
	-@erase ".\Debug\demo40.tlb"
	-@erase ".\Debug\Demo40Ctl.obj"
	-@erase ".\Debug\Demo40Ppg.obj"
	-@erase ".\Debug\demo40.lib"
	-@erase ".\Debug\demo40.exp"
	-@erase ".\Debug\demo40.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\regsvr32.trg"
	-@erase ".\Debug\demo40.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/demo40.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/demo40.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/demo40.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/demo40.pdb" /debug /machine:I386 /def:".\demo40.def"\
 /out:"$(OUTDIR)/demo40.ocx" /implib:"$(OUTDIR)/demo40.lib" 
DEF_FILE= \
	".\demo40.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/demo40.obj" \
	"$(INTDIR)/Demo40Ctl.obj" \
	"$(INTDIR)/Demo40Ppg.obj" \
	"$(INTDIR)/demo40.res"

"$(OUTDIR)\demo40.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\demo40.ocx
InputPath=.\Debug\demo40.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\demo40.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\DebugU\demo40.ilk"
	-@erase ".\DebugU\StdAfx.obj"
	-@erase ".\DebugU\demo40.obj"
	-@erase ".\DebugU\demo40.pch"
	-@erase ".\DebugU\demo40.res"
	-@erase ".\DebugU\demo40.tlb"
	-@erase ".\DebugU\Demo40Ctl.obj"
	-@erase ".\DebugU\Demo40Ppg.obj"
	-@erase ".\DebugU\demo40.lib"
	-@erase ".\DebugU\demo40.exp"
	-@erase ".\DebugU\demo40.pdb"
	-@erase ".\DebugU\vc40.pdb"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\DebugU\demo40.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/demo40.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/demo40.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/demo40.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/demo40.pdb" /debug /machine:I386 /def:".\demo40.def"\
 /out:"$(OUTDIR)/demo40.ocx" /implib:"$(OUTDIR)/demo40.lib" 
DEF_FILE= \
	".\demo40.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/demo40.obj" \
	"$(INTDIR)/Demo40Ctl.obj" \
	"$(INTDIR)/Demo40Ppg.obj" \
	"$(INTDIR)/demo40.res"

"$(OUTDIR)\demo40.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\demo40.ocx
InputPath=.\DebugU\demo40.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\demo40.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\ReleaseU\demo40.lib"
	-@erase ".\ReleaseU\StdAfx.obj"
	-@erase ".\ReleaseU\demo40.obj"
	-@erase ".\ReleaseU\demo40.pch"
	-@erase ".\ReleaseU\demo40.res"
	-@erase ".\ReleaseU\demo40.tlb"
	-@erase ".\ReleaseU\Demo40Ctl.obj"
	-@erase ".\ReleaseU\Demo40Ppg.obj"
	-@erase ".\ReleaseU\demo40.exp"
	-@erase ".\ReleaseU\regsvr32.trg"
	-@erase ".\ReleaseU\demo40.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/demo40.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/demo40.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/demo40.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/demo40.pdb" /machine:I386 /def:".\demo40.def"\
 /out:"$(OUTDIR)/demo40.ocx" /implib:"$(OUTDIR)/demo40.lib" 
DEF_FILE= \
	".\demo40.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/demo40.obj" \
	"$(INTDIR)/Demo40Ctl.obj" \
	"$(INTDIR)/Demo40Ppg.obj" \
	"$(INTDIR)/demo40.res"

"$(OUTDIR)\demo40.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\demo40.ocx
InputPath=.\ReleaseU\demo40.ocx
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

# Name "demo40 - Win32 Release"
# Name "demo40 - Win32 Debug"
# Name "demo40 - Win32 Unicode Debug"
# Name "demo40 - Win32 Unicode Release"

!IF  "$(CFG)" == "demo40 - Win32 Release"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "demo40 - Win32 Release"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "demo40 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/demo40.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\demo40.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/demo40.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\demo40.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/demo40.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\demo40.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/demo40.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\demo40.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\demo40.cpp
DEP_CPP_DEMO4=\
	".\StdAfx.h"\
	".\demo40.h"\
	

!IF  "$(CFG)" == "demo40 - Win32 Release"


"$(INTDIR)\demo40.obj" : $(SOURCE) $(DEP_CPP_DEMO4) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"


"$(INTDIR)\demo40.obj" : $(SOURCE) $(DEP_CPP_DEMO4) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"


"$(INTDIR)\demo40.obj" : $(SOURCE) $(DEP_CPP_DEMO4) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"


"$(INTDIR)\demo40.obj" : $(SOURCE) $(DEP_CPP_DEMO4) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\demo40.def

!IF  "$(CFG)" == "demo40 - Win32 Release"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\demo40.rc

!IF  "$(CFG)" == "demo40 - Win32 Release"

DEP_RSC_DEMO40=\
	".\demo40.ico"\
	".\Demo40Ctl.bmp"\
	
NODEP_RSC_DEMO40=\
	".\Release\demo40.tlb"\
	

"$(INTDIR)\demo40.res" : $(SOURCE) $(DEP_RSC_DEMO40) "$(INTDIR)"\
 "$(INTDIR)\demo40.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/demo40.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"

DEP_RSC_DEMO40=\
	".\demo40.ico"\
	".\Demo40Ctl.bmp"\
	
NODEP_RSC_DEMO40=\
	".\Debug\demo40.tlb"\
	

"$(INTDIR)\demo40.res" : $(SOURCE) $(DEP_RSC_DEMO40) "$(INTDIR)"\
 "$(INTDIR)\demo40.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/demo40.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"

DEP_RSC_DEMO40=\
	".\demo40.ico"\
	".\Demo40Ctl.bmp"\
	
NODEP_RSC_DEMO40=\
	".\DebugU\demo40.tlb"\
	

"$(INTDIR)\demo40.res" : $(SOURCE) $(DEP_RSC_DEMO40) "$(INTDIR)"\
 "$(INTDIR)\demo40.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/demo40.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"

DEP_RSC_DEMO40=\
	".\demo40.ico"\
	".\Demo40Ctl.bmp"\
	
NODEP_RSC_DEMO40=\
	".\ReleaseU\demo40.tlb"\
	

"$(INTDIR)\demo40.res" : $(SOURCE) $(DEP_RSC_DEMO40) "$(INTDIR)"\
 "$(INTDIR)\demo40.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/demo40.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\demo40.odl

!IF  "$(CFG)" == "demo40 - Win32 Release"


"$(OUTDIR)\demo40.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/demo40.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"


"$(OUTDIR)\demo40.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/demo40.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"


"$(OUTDIR)\demo40.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/demo40.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"


"$(OUTDIR)\demo40.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/demo40.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Demo40Ctl.cpp
DEP_CPP_DEMO40C=\
	".\StdAfx.h"\
	".\demo40.h"\
	".\Demo40Ctl.h"\
	".\Demo40Ppg.h"\
	

!IF  "$(CFG)" == "demo40 - Win32 Release"


"$(INTDIR)\Demo40Ctl.obj" : $(SOURCE) $(DEP_CPP_DEMO40C) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"


"$(INTDIR)\Demo40Ctl.obj" : $(SOURCE) $(DEP_CPP_DEMO40C) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"


"$(INTDIR)\Demo40Ctl.obj" : $(SOURCE) $(DEP_CPP_DEMO40C) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"


"$(INTDIR)\Demo40Ctl.obj" : $(SOURCE) $(DEP_CPP_DEMO40C) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Demo40Ppg.cpp
DEP_CPP_DEMO40P=\
	".\StdAfx.h"\
	".\demo40.h"\
	".\Demo40Ppg.h"\
	

!IF  "$(CFG)" == "demo40 - Win32 Release"


"$(INTDIR)\Demo40Ppg.obj" : $(SOURCE) $(DEP_CPP_DEMO40P) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Debug"


"$(INTDIR)\Demo40Ppg.obj" : $(SOURCE) $(DEP_CPP_DEMO40P) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Debug"


"$(INTDIR)\Demo40Ppg.obj" : $(SOURCE) $(DEP_CPP_DEMO40P) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ELSEIF  "$(CFG)" == "demo40 - Win32 Unicode Release"


"$(INTDIR)\Demo40Ppg.obj" : $(SOURCE) $(DEP_CPP_DEMO40P) "$(INTDIR)"\
 "$(INTDIR)\demo40.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
