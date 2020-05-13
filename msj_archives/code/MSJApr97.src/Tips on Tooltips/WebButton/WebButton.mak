# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=WebButton - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to WebButton - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WebButton - Win32 Release" && "$(CFG)" !=\
 "WebButton - Win32 Debug" && "$(CFG)" != "WebButton - Win32 Unicode Debug" &&\
 "$(CFG)" != "WebButton - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WebButton.mak" CFG="WebButton - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WebButton - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WebButton - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WebButton - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WebButton - Win32 Unicode Release" (based on\
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
# PROP Target_Last_Scanned "WebButton - Win32 Unicode Release"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "WebButton - Win32 Release"

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

ALL : "$(OUTDIR)\WebButton.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\WebButton.obj"
	-@erase "$(INTDIR)\WebButton.pch"
	-@erase "$(INTDIR)\WebButton.res"
	-@erase "$(INTDIR)\WebButton.tlb"
	-@erase "$(INTDIR)\WebButtonCtl.obj"
	-@erase "$(INTDIR)\WebButtonPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\WebButton.exp"
	-@erase "$(OUTDIR)\WebButton.lib"
	-@erase "$(OUTDIR)\WebButton.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/WebButton.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WebButton.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WebButton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/WebButton.pdb" /machine:I386 /def:".\WebButton.def"\
 /out:"$(OUTDIR)/WebButton.ocx" /implib:"$(OUTDIR)/WebButton.lib" 
DEF_FILE= \
	".\WebButton.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WebButton.obj" \
	"$(INTDIR)\WebButton.res" \
	"$(INTDIR)\WebButtonCtl.obj" \
	"$(INTDIR)\WebButtonPpg.obj"

"$(OUTDIR)\WebButton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\WebButton.ocx
InputPath=.\Release\WebButton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"

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

ALL : "$(OUTDIR)\WebButton.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WebButton.obj"
	-@erase "$(INTDIR)\WebButton.pch"
	-@erase "$(INTDIR)\WebButton.res"
	-@erase "$(INTDIR)\WebButton.tlb"
	-@erase "$(INTDIR)\WebButtonCtl.obj"
	-@erase "$(INTDIR)\WebButtonPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\WebButton.exp"
	-@erase "$(OUTDIR)\WebButton.ilk"
	-@erase "$(OUTDIR)\WebButton.lib"
	-@erase "$(OUTDIR)\WebButton.ocx"
	-@erase "$(OUTDIR)\WebButton.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/WebButton.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WebButton.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WebButton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/WebButton.pdb" /debug /machine:I386 /def:".\WebButton.def"\
 /out:"$(OUTDIR)/WebButton.ocx" /implib:"$(OUTDIR)/WebButton.lib" 
DEF_FILE= \
	".\WebButton.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WebButton.obj" \
	"$(INTDIR)\WebButton.res" \
	"$(INTDIR)\WebButtonCtl.obj" \
	"$(INTDIR)\WebButtonPpg.obj"

"$(OUTDIR)\WebButton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\WebButton.ocx
InputPath=.\Debug\WebButton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\WebButton.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WebButton.obj"
	-@erase "$(INTDIR)\WebButton.pch"
	-@erase "$(INTDIR)\WebButton.res"
	-@erase "$(INTDIR)\WebButton.tlb"
	-@erase "$(INTDIR)\WebButtonCtl.obj"
	-@erase "$(INTDIR)\WebButtonPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\WebButton.exp"
	-@erase "$(OUTDIR)\WebButton.ilk"
	-@erase "$(OUTDIR)\WebButton.lib"
	-@erase "$(OUTDIR)\WebButton.ocx"
	-@erase "$(OUTDIR)\WebButton.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/WebButton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WebButton.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WebButton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/WebButton.pdb" /debug /machine:I386 /def:".\WebButton.def"\
 /out:"$(OUTDIR)/WebButton.ocx" /implib:"$(OUTDIR)/WebButton.lib" 
DEF_FILE= \
	".\WebButton.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WebButton.obj" \
	"$(INTDIR)\WebButton.res" \
	"$(INTDIR)\WebButtonCtl.obj" \
	"$(INTDIR)\WebButtonPpg.obj"

"$(OUTDIR)\WebButton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\WebButton.ocx
InputPath=.\DebugU\WebButton.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\WebButton.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\WebButton.obj"
	-@erase "$(INTDIR)\WebButton.pch"
	-@erase "$(INTDIR)\WebButton.res"
	-@erase "$(INTDIR)\WebButton.tlb"
	-@erase "$(INTDIR)\WebButtonCtl.obj"
	-@erase "$(INTDIR)\WebButtonPpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\WebButton.exp"
	-@erase "$(OUTDIR)\WebButton.lib"
	-@erase "$(OUTDIR)\WebButton.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/WebButton.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WebButton.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WebButton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/WebButton.pdb" /machine:I386 /def:".\WebButton.def"\
 /out:"$(OUTDIR)/WebButton.ocx" /implib:"$(OUTDIR)/WebButton.lib" 
DEF_FILE= \
	".\WebButton.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WebButton.obj" \
	"$(INTDIR)\WebButton.res" \
	"$(INTDIR)\WebButtonCtl.obj" \
	"$(INTDIR)\WebButtonPpg.obj"

"$(OUTDIR)\WebButton.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\WebButton.ocx
InputPath=.\ReleaseU\WebButton.ocx
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

# Name "WebButton - Win32 Release"
# Name "WebButton - Win32 Debug"
# Name "WebButton - Win32 Unicode Debug"
# Name "WebButton - Win32 Unicode Release"

!IF  "$(CFG)" == "WebButton - Win32 Release"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "WebButton - Win32 Release"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "WebButton - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/WebButton.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WebButton.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/WebButton.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WebButton.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/WebButton.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WebButton.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/WebButton.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WebButton.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WebButton.cpp
DEP_CPP_WEBBU=\
	".\StdAfx.h"\
	".\WebButton.h"\
	

!IF  "$(CFG)" == "WebButton - Win32 Release"


"$(INTDIR)\WebButton.obj" : $(SOURCE) $(DEP_CPP_WEBBU) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"


"$(INTDIR)\WebButton.obj" : $(SOURCE) $(DEP_CPP_WEBBU) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"


"$(INTDIR)\WebButton.obj" : $(SOURCE) $(DEP_CPP_WEBBU) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"


"$(INTDIR)\WebButton.obj" : $(SOURCE) $(DEP_CPP_WEBBU) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WebButton.def

!IF  "$(CFG)" == "WebButton - Win32 Release"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WebButton.rc

!IF  "$(CFG)" == "WebButton - Win32 Release"

DEP_RSC_WEBBUT=\
	".\WebButtonCtl.bmp"\
	
NODEP_RSC_WEBBUT=\
	".\Release\WebButton.tlb"\
	

"$(INTDIR)\WebButton.res" : $(SOURCE) $(DEP_RSC_WEBBUT) "$(INTDIR)"\
 "$(INTDIR)\WebButton.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/WebButton.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"

DEP_RSC_WEBBUT=\
	".\Debug\WebButton.tlb"\
	".\WebButtonCtl.bmp"\
	

"$(INTDIR)\WebButton.res" : $(SOURCE) $(DEP_RSC_WEBBUT) "$(INTDIR)"\
 "$(INTDIR)\WebButton.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/WebButton.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"

DEP_RSC_WEBBUT=\
	".\WebButtonCtl.bmp"\
	
NODEP_RSC_WEBBUT=\
	".\DebugU\WebButton.tlb"\
	

"$(INTDIR)\WebButton.res" : $(SOURCE) $(DEP_RSC_WEBBUT) "$(INTDIR)"\
 "$(INTDIR)\WebButton.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/WebButton.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"

DEP_RSC_WEBBUT=\
	".\WebButtonCtl.bmp"\
	
NODEP_RSC_WEBBUT=\
	".\ReleaseU\WebButton.tlb"\
	

"$(INTDIR)\WebButton.res" : $(SOURCE) $(DEP_RSC_WEBBUT) "$(INTDIR)"\
 "$(INTDIR)\WebButton.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/WebButton.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WebButton.odl

!IF  "$(CFG)" == "WebButton - Win32 Release"


"$(OUTDIR)\WebButton.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/WebButton.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"


"$(OUTDIR)\WebButton.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/WebButton.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"


"$(OUTDIR)\WebButton.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/WebButton.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"


"$(OUTDIR)\WebButton.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/WebButton.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WebButtonCtl.cpp
DEP_CPP_WEBBUTT=\
	".\StdAfx.h"\
	".\WebButton.h"\
	".\WebButtonCtl.h"\
	".\WebButtonPpg.h"\
	

!IF  "$(CFG)" == "WebButton - Win32 Release"


"$(INTDIR)\WebButtonCtl.obj" : $(SOURCE) $(DEP_CPP_WEBBUTT) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"


"$(INTDIR)\WebButtonCtl.obj" : $(SOURCE) $(DEP_CPP_WEBBUTT) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"


"$(INTDIR)\WebButtonCtl.obj" : $(SOURCE) $(DEP_CPP_WEBBUTT) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"


"$(INTDIR)\WebButtonCtl.obj" : $(SOURCE) $(DEP_CPP_WEBBUTT) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WebButtonPpg.cpp
DEP_CPP_WEBBUTTO=\
	".\StdAfx.h"\
	".\WebButton.h"\
	".\WebButtonPpg.h"\
	

!IF  "$(CFG)" == "WebButton - Win32 Release"


"$(INTDIR)\WebButtonPpg.obj" : $(SOURCE) $(DEP_CPP_WEBBUTTO) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Debug"


"$(INTDIR)\WebButtonPpg.obj" : $(SOURCE) $(DEP_CPP_WEBBUTTO) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Debug"


"$(INTDIR)\WebButtonPpg.obj" : $(SOURCE) $(DEP_CPP_WEBBUTTO) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ELSEIF  "$(CFG)" == "WebButton - Win32 Unicode Release"


"$(INTDIR)\WebButtonPpg.obj" : $(SOURCE) $(DEP_CPP_WEBBUTTO) "$(INTDIR)"\
 "$(INTDIR)\WebButton.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
