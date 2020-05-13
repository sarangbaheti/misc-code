# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TTDemo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TTDemo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TTDemo - Win32 Release" && "$(CFG)" != "TTDemo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TTDemo.mak" CFG="TTDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TTDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TTDemo - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "TTDemo - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "TTDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\TTDemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\ODListBox.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TitleTip.obj"
	-@erase "$(INTDIR)\TitleTipListBox.obj"
	-@erase "$(INTDIR)\TTDemo.obj"
	-@erase "$(INTDIR)\TTDemo.pch"
	-@erase "$(INTDIR)\TTDemo.res"
	-@erase "$(INTDIR)\TTDemoDlg.obj"
	-@erase "$(OUTDIR)\TTDemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TTDemo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TTDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TTDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/TTDemo.pdb" /machine:I386 /out:"$(OUTDIR)/TTDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ODListBox.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TitleTip.obj" \
	"$(INTDIR)\TitleTipListBox.obj" \
	"$(INTDIR)\TTDemo.obj" \
	"$(INTDIR)\TTDemo.res" \
	"$(INTDIR)\TTDemoDlg.obj"

"$(OUTDIR)\TTDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TTDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\TTDemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\ODListBox.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TitleTip.obj"
	-@erase "$(INTDIR)\TitleTipListBox.obj"
	-@erase "$(INTDIR)\TTDemo.obj"
	-@erase "$(INTDIR)\TTDemo.pch"
	-@erase "$(INTDIR)\TTDemo.res"
	-@erase "$(INTDIR)\TTDemoDlg.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\TTDemo.exe"
	-@erase "$(OUTDIR)\TTDemo.ilk"
	-@erase "$(OUTDIR)\TTDemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TTDemo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TTDemo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TTDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/TTDemo.pdb" /debug /machine:I386 /out:"$(OUTDIR)/TTDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ODListBox.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TitleTip.obj" \
	"$(INTDIR)\TitleTipListBox.obj" \
	"$(INTDIR)\TTDemo.obj" \
	"$(INTDIR)\TTDemo.res" \
	"$(INTDIR)\TTDemoDlg.obj"

"$(OUTDIR)\TTDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "TTDemo - Win32 Release"
# Name "TTDemo - Win32 Debug"

!IF  "$(CFG)" == "TTDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "TTDemo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "TTDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "TTDemo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TTDemo.cpp
DEP_CPP_TTDEM=\
	".\ODListBox.h"\
	".\StdAfx.h"\
	".\TitleTip.h"\
	".\TitleTipListBox.h"\
	".\TTDemo.h"\
	".\TTDemoDlg.h"\
	

"$(INTDIR)\TTDemo.obj" : $(SOURCE) $(DEP_CPP_TTDEM) "$(INTDIR)"\
 "$(INTDIR)\TTDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TTDemoDlg.cpp
DEP_CPP_TTDEMO=\
	".\ODListBox.h"\
	".\StdAfx.h"\
	".\TitleTip.h"\
	".\TitleTipListBox.h"\
	".\TTDemo.h"\
	".\TTDemoDlg.h"\
	

"$(INTDIR)\TTDemoDlg.obj" : $(SOURCE) $(DEP_CPP_TTDEMO) "$(INTDIR)"\
 "$(INTDIR)\TTDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "TTDemo - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TTDemo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TTDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TTDemo - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TTDemo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TTDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TTDemo.rc
DEP_RSC_TTDEMO_=\
	".\res\TTDemo.ico"\
	".\res\TTDemo.rc2"\
	

"$(INTDIR)\TTDemo.res" : $(SOURCE) $(DEP_RSC_TTDEMO_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ODListBox.cpp
DEP_CPP_ODLIS=\
	".\ODListBox.h"\
	".\StdAfx.h"\
	".\TitleTip.h"\
	".\TitleTipListBox.h"\
	".\TTDemo.h"\
	

"$(INTDIR)\ODListBox.obj" : $(SOURCE) $(DEP_CPP_ODLIS) "$(INTDIR)"\
 "$(INTDIR)\TTDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TitleTipListBox.cpp
DEP_CPP_TITLE=\
	".\StdAfx.h"\
	".\TitleTip.h"\
	".\TitleTipListBox.h"\
	

"$(INTDIR)\TitleTipListBox.obj" : $(SOURCE) $(DEP_CPP_TITLE) "$(INTDIR)"\
 "$(INTDIR)\TTDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TitleTip.cpp
DEP_CPP_TITLET=\
	".\StdAfx.h"\
	".\TitleTip.h"\
	

"$(INTDIR)\TitleTip.obj" : $(SOURCE) $(DEP_CPP_TITLET) "$(INTDIR)"\
 "$(INTDIR)\TTDemo.pch"


# End Source File
# End Target
# End Project
################################################################################
