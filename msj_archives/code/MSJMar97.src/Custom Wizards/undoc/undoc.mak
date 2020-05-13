# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=undoc - Win32 Pseudo-Debug
!MESSAGE No configuration specified.  Defaulting to undoc - Win32 Pseudo-Debug.
!ENDIF 

!IF "$(CFG)" != "undoc - Win32 Release" && "$(CFG)" !=\
 "undoc - Win32 Pseudo-Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "undoc.mak" CFG="undoc - Win32 Pseudo-Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "undoc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "undoc - Win32 Pseudo-Debug" (based on\
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
# PROP Target_Last_Scanned "undoc - Win32 Pseudo-Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "undoc - Win32 Release"

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
TargetName=undoc
# End Custom Macros

ALL : "$(OUTDIR)\undoc.awx" "..\..\MSDEV\Template\undoc.awx"

CLEAN : 
	-@erase ".\Release\undoc.lib"
	-@erase ".\Release\Debug.obj"
	-@erase ".\Release\undoc.pch"
	-@erase ".\Release\undocAw.obj"
	-@erase ".\Release\Cstm1Dlg.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\undoc.obj"
	-@erase ".\Release\Chooser.obj"
	-@erase ".\Release\undoc.res"
	-@erase ".\Release\undoc.exp"
	-@erase "..\..\MSDEV\Template\undoc.awx"
	-@erase ".\Release\undoc.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/undoc.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/undoc.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/undoc.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/undoc.pdb" /machine:I386 /out:"$(OUTDIR)/undoc.awx"\
 /implib:"$(OUTDIR)/undoc.lib" 
LINK32_OBJS= \
	"$(INTDIR)/Debug.obj" \
	"$(INTDIR)/undocAw.obj" \
	"$(INTDIR)/Cstm1Dlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/undoc.obj" \
	"$(INTDIR)/Chooser.obj" \
	"$(INTDIR)/undoc.res"

"$(OUTDIR)\undoc.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Release
TargetPath=.\Release\undoc.awx
TargetName=undoc
InputPath=.\Release\undoc.awx
SOURCE=$(InputPath)

"$(MSDevDir)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   if not exist $(MSDevDir)\Template\nul md $(MSDevDir)\Template
   copy "$(TargetPath)" "$(MSDevDir)\Template"
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
   "$(MSDevDir)\Template"

# End Custom Build

!ELSEIF  "$(CFG)" == "undoc - Win32 Pseudo-Debug"

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
TargetName=undoc
# End Custom Macros

ALL : "$(OUTDIR)\undoc.awx" "..\..\MSDEV\Template\undoc.awx"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\undoc.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\undoc.ilk"
	-@erase ".\Debug\Cstm1Dlg.obj"
	-@erase ".\Debug\undoc.obj"
	-@erase ".\Debug\undocAw.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\Chooser.obj"
	-@erase ".\Debug\Debug.obj"
	-@erase ".\Debug\undoc.res"
	-@erase ".\Debug\undoc.lib"
	-@erase ".\Debug\undoc.exp"
	-@erase ".\Debug\undoc.pdb"
	-@erase "..\..\MSDEV\Template\undoc.awx"
	-@erase ".\Debug\undoc.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT"\
 /Fp"$(INTDIR)/undoc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/undoc.res" /d "NDEBUG" /d "_PSEUDO_DEBUG" /d\
 "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/undoc.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/undoc.pdb" /debug /machine:I386 /out:"$(OUTDIR)/undoc.awx"\
 /implib:"$(OUTDIR)/undoc.lib" 
LINK32_OBJS= \
	"$(INTDIR)/Cstm1Dlg.obj" \
	"$(INTDIR)/undoc.obj" \
	"$(INTDIR)/undocAw.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Chooser.obj" \
	"$(INTDIR)/Debug.obj" \
	"$(INTDIR)/undoc.res"

"$(OUTDIR)\undoc.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Debug
TargetPath=.\Debug\undoc.awx
TargetName=undoc
InputPath=.\Debug\undoc.awx
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

# Name "undoc - Win32 Release"
# Name "undoc - Win32 Pseudo-Debug"

!IF  "$(CFG)" == "undoc - Win32 Release"

!ELSEIF  "$(CFG)" == "undoc - Win32 Pseudo-Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\undoc.cpp
DEP_CPP_UNDOC=\
	".\StdAfx.h"\
	".\undoc.h"\
	".\undocAw.h"\
	".\Debug.h"\
	

"$(INTDIR)\undoc.obj" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 "$(INTDIR)\undoc.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	".\Debug.h"\
	

!IF  "$(CFG)" == "undoc - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/undoc.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\undoc.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "undoc - Win32 Pseudo-Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT"\
 /Fp"$(INTDIR)/undoc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\undoc.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undocAw.cpp
DEP_CPP_UNDOCA=\
	".\StdAfx.h"\
	".\undoc.h"\
	".\undocAw.h"\
	".\Chooser.h"\
	".\Debug.h"\
	

"$(INTDIR)\undocAw.obj" : $(SOURCE) $(DEP_CPP_UNDOCA) "$(INTDIR)"\
 "$(INTDIR)\undoc.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Debug.cpp
DEP_CPP_DEBUG=\
	".\StdAfx.h"\
	".\Debug.h"\
	

"$(INTDIR)\Debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\undoc.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\undoc.rc
DEP_RSC_UNDOC_=\
	".\template\newproj.inf"\
	".\template\confirm.inf"\
	".\Template\datapane.cpp"\
	".\Template\datapane.h"\
	".\Template\mainwnd.cpp"\
	".\Template\mainwnd.h"\
	".\Template\resource.h"\
	".\Template\root.clw"\
	".\Template\root.cpp"\
	".\Template\root.h"\
	".\Template\root.rc"\
	".\Template\stdafx.cpp"\
	".\Template\stdafx.h"\
	".\Template\stdpane.cpp"\
	".\Template\stdpane.h"\
	".\Template\treepane.cpp"\
	".\Template\treepane.h"\
	".\Template\Toolbar.bmp"\
	".\res\undoc.ico"\
	".\res\tysy_tnd.bmp"\
	".\res\tysy_tyd.bmp"\
	".\res\bmp00001.bmp"\
	".\res\bmp00002.bmp"\
	".\res\bmp00003.bmp"\
	".\res\bmp00004.bmp"\
	".\res\bmp00005.bmp"\
	".\res\bmp00006.bmp"\
	".\res\tnsy_tnd.bmp"\
	".\res\bmp00007.bmp"\
	".\res\bmp00008.bmp"\
	".\res\bmp00009.bmp"\
	".\res\tnsy_tyd.bmp"\
	".\res\bmp00010.bmp"\
	".\res\tysn_tyd.bmp"\
	".\res\bmp00011.bmp"\
	".\res\tnsn_tnd.bmp"\
	".\res\bmp00012.bmp"\
	".\res\bmp00013.bmp"\
	".\res\bmp00014.bmp"\
	".\res\tnsn_tyd.bmp"\
	".\res\bmp00015.bmp"\
	".\res\bmp00016.bmp"\
	".\res\tysn_tnd.bmp"\
	".\res\bmp00017.bmp"\
	".\res\bmp00018.bmp"\
	".\res\bmp00019.bmp"\
	".\res\bmp00020.bmp"\
	".\res\bmp00021.bmp"\
	".\res\bmp00022.bmp"\
	".\res\bmp00023.bmp"\
	".\res\bmp00024.bmp"\
	

"$(INTDIR)\undoc.res" : $(SOURCE) $(DEP_RSC_UNDOC_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "undoc - Win32 Release"

!ELSEIF  "$(CFG)" == "undoc - Win32 Pseudo-Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Chooser.cpp
DEP_CPP_CHOOS=\
	".\StdAfx.h"\
	".\undoc.h"\
	".\Chooser.h"\
	".\Cstm1Dlg.h"\
	".\Debug.h"\
	

"$(INTDIR)\Chooser.obj" : $(SOURCE) $(DEP_CPP_CHOOS) "$(INTDIR)"\
 "$(INTDIR)\undoc.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cstm1Dlg.cpp
DEP_CPP_CSTM1=\
	".\StdAfx.h"\
	".\undoc.h"\
	".\Cstm1Dlg.h"\
	".\undocAw.h"\
	".\Debug.h"\
	

"$(INTDIR)\Cstm1Dlg.obj" : $(SOURCE) $(DEP_CPP_CSTM1) "$(INTDIR)"\
 "$(INTDIR)\undoc.pch"


# End Source File
# End Target
# End Project
################################################################################
