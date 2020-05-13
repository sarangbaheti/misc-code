# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=TippyDialog - Win32 Pseudo-Debug
!MESSAGE No configuration specified.  Defaulting to TippyDialog - Win32\
 Pseudo-Debug.
!ENDIF 

!IF "$(CFG)" != "TippyDialog - Win32 Release" && "$(CFG)" !=\
 "TippyDialog - Win32 Pseudo-Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TippyDialog.mak" CFG="TippyDialog - Win32 Pseudo-Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TippyDialog - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TippyDialog - Win32 Pseudo-Debug" (based on\
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

!IF  "$(CFG)" == "TippyDialog - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "awx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Target_Ext "awx"
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
TargetName=TippyDialog
# End Custom Macros

ALL : "$(OUTDIR)\TippyDialog.awx" "$(MSDevDir)\Template\$(TargetName).awx"

CLEAN : 
	-@erase ".\Release\TippyDialog.awx"
	-@erase ".\Release\TippyDialog.obj"
	-@erase ".\Release\TippyDialog.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\TippyDialogAw.obj"
	-@erase ".\Release\Debug.obj"
	-@erase ".\Release\TippyDialog.res"
	-@erase ".\Release\TippyDialog.lib"
	-@erase ".\Release\TippyDialog.exp"
	-@erase  "$(MSDevDir)\Template\$(TargetName).awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/TippyDialog.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TippyDialog.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TippyDialog.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/TippyDialog.pdb" /machine:I386 /out:"$(OUTDIR)/TippyDialog.awx"\
 /implib:"$(OUTDIR)/TippyDialog.lib" 
LINK32_OBJS= \
	"$(INTDIR)/TippyDialog.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TippyDialogAw.obj" \
	"$(INTDIR)/Debug.obj" \
	"$(INTDIR)/TippyDialog.res"

"$(OUTDIR)\TippyDialog.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Release
TargetPath=.\Release\TippyDialog.awx
TargetName=TippyDialog
InputPath=.\Release\TippyDialog.awx
SOURCE=$(InputPath)

"$(MSDevDir)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   if not exist $(MSDevDir)\Template\nul md $(MSDevDir)\Template
   copy "$(TargetPath)" "$(MSDevDir)\Template"
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
 "$(MSDevDir)\Template"

# End Custom Build

!ELSEIF  "$(CFG)" == "TippyDialog - Win32 Pseudo-Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "awx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Target_Ext "awx"
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
TargetName=TippyDialog
# End Custom Macros

ALL : "$(OUTDIR)\TippyDialog.awx" "$(MSDevDir)\Template\$(TargetName).awx"

CLEAN : 
	-@erase ".\Debug\TippyDialog.awx"
	-@erase ".\Debug\TippyDialog.obj"
	-@erase ".\Debug\TippyDialog.pch"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\TippyDialogAw.obj"
	-@erase ".\Debug\Debug.obj"
	-@erase ".\Debug\TippyDialog.res"
	-@erase ".\Debug\TippyDialog.ilk"
	-@erase ".\Debug\TippyDialog.lib"
	-@erase ".\Debug\TippyDialog.exp"
	-@erase ".\Debug\TippyDialog.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase  "$(MSDevDir)\Template\$(TargetName).awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT"\
 /Fp"$(INTDIR)/TippyDialog.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TippyDialog.res" /d "NDEBUG" /d "_PSEUDO_DEBUG"\
 /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TippyDialog.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/TippyDialog.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/TippyDialog.awx" /implib:"$(OUTDIR)/TippyDialog.lib" 
LINK32_OBJS= \
	"$(INTDIR)/TippyDialog.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TippyDialogAw.obj" \
	"$(INTDIR)/Debug.obj" \
	"$(INTDIR)/TippyDialog.res"

"$(OUTDIR)\TippyDialog.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Debug
TargetPath=.\Debug\TippyDialog.awx
TargetName=TippyDialog
InputPath=.\Debug\TippyDialog.awx
SOURCE=$(InputPath)

"$(MSDevDir)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   if not exist $(MSDevDir)\Template\nul md $(MSDevDir)\Template
   copy "$(TargetPath)" "$(MSDevDir)\Template"
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
 "$(MSDevDir)\Template"

# End Custom Build

!ENDIF 

MTL_PROJ=/nologo /D "NDEBUG" /win32 

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

# Name "TippyDialog - Win32 Release"
# Name "TippyDialog - Win32 Pseudo-Debug"

!IF  "$(CFG)" == "TippyDialog - Win32 Release"

!ELSEIF  "$(CFG)" == "TippyDialog - Win32 Pseudo-Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TippyDialog.cpp
DEP_CPP_TIPPY=\
	".\StdAfx.h"\
	".\TippyDialog.h"\
	".\TippyDialogAw.h"\
	".\Debug.h"\
	

"$(INTDIR)\TippyDialog.obj" : $(SOURCE) $(DEP_CPP_TIPPY) "$(INTDIR)"\
 "$(INTDIR)\TippyDialog.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "TippyDialog - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/TippyDialog.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TippyDialog.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TippyDialog - Win32 Pseudo-Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT"\
 /Fp"$(INTDIR)/TippyDialog.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TippyDialog.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TippyDialogAw.cpp
DEP_CPP_TIPPYD=\
	".\StdAfx.h"\
	".\TippyDialog.h"\
	".\TippyDialogAw.h"\
	".\Debug.h"\
	

"$(INTDIR)\TippyDialogAw.obj" : $(SOURCE) $(DEP_CPP_TIPPYD) "$(INTDIR)"\
 "$(INTDIR)\TippyDialog.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Debug.cpp
DEP_CPP_DEBUG=\
	".\StdAfx.h"\
	".\Debug.h"\
	

"$(INTDIR)\Debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\TippyDialog.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TippyDialog.rc
DEP_RSC_TIPPYDI=\
	".\template\newproj.inf"\
	".\template\confirm.inf"\
	".\template\MainFrm.cpp"\
	".\template\MainFrm.h"\
	".\template\ReadMe.txt"\
	".\template\Resource.h"\
	".\template\StdAfx.cpp"\
	".\template\StdAfx.h"\
	".\template\root.clw"\
	".\template\root.cpp"\
	".\template\root.h"\
	".\template\root.rc"\
	".\template\Doc.cpp"\
	".\template\Doc.h"\
	".\template\View.cpp"\
	".\template\View.h"\
	".\template\res\root.ico"\
	".\template\res\root.rc2"\
	".\template\res\Doc.ico"\
	".\template\res\Toolbar.bmp"\
	".\res\TippyDialog.ico"\
	

"$(INTDIR)\TippyDialog.res" : $(SOURCE) $(DEP_RSC_TIPPYDI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "TippyDialog - Win32 Release"

!ELSEIF  "$(CFG)" == "TippyDialog - Win32 Pseudo-Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
