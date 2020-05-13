# Microsoft Developer Studio Generated NMAKE File, Format Version 42001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Shadecap - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Shadecap - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Shadecap - Win32 Release" && "$(CFG)" !=\
 "Shadecap - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ShadeCap.mak" CFG="Shadecap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Shadecap - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Shadecap - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Shadecap - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Shadecap - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\Release\ShadeCap.exe" ".\Release\ShadeCap.bsc"

CLEAN : 
	-@erase ".\Release\Doc.obj"
	-@erase ".\Release\Doc.sbr"
	-@erase ".\Release\Mainfrm.obj"
	-@erase ".\Release\Mainfrm.sbr"
	-@erase ".\Release\ShadeCap.bsc"
	-@erase ".\Release\ShadeCap.exe"
	-@erase ".\Release\Shadecap.obj"
	-@erase ".\Release\ShadeCap.pch"
	-@erase ".\Release\Shadecap.res"
	-@erase ".\Release\Shadecap.sbr"
	-@erase ".\Release\Stdafx.obj"
	-@erase ".\Release\Stdafx.sbr"
	-@erase ".\Release\View.obj"
	-@erase ".\Release\View.sbr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"STDAFX.H" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ShadeCap.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Shadecap.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ShadeCap.bsc" 
BSC32_SBRS= \
	".\Release\Doc.sbr" \
	".\Release\Mainfrm.sbr" \
	".\Release\Shadecap.sbr" \
	".\Release\Stdafx.sbr" \
	".\Release\View.sbr"

".\Release\ShadeCap.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/ShadeCap.pdb" /machine:IX86\
 /out:"$(OUTDIR)/ShadeCap.exe" 
LINK32_OBJS= \
	".\Release\Doc.obj" \
	".\Release\Mainfrm.obj" \
	".\Release\Shadecap.obj" \
	".\Release\Shadecap.res" \
	".\Release\Stdafx.obj" \
	".\Release\View.obj"

".\Release\ShadeCap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Shadecap - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\Debug\ShadeCap.exe"

CLEAN : 
	-@erase ".\Debug\Doc.obj"
	-@erase ".\Debug\Mainfrm.obj"
	-@erase ".\Debug\ShadeCap.exe"
	-@erase ".\Debug\ShadeCap.ilk"
	-@erase ".\Debug\Shadecap.obj"
	-@erase ".\Debug\ShadeCap.pch"
	-@erase ".\Debug\ShadeCap.pdb"
	-@erase ".\Debug\Shadecap.res"
	-@erase ".\Debug\Stdafx.obj"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\View.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ShadeCap.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Shadecap.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ShadeCap.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/ShadeCap.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)/ShadeCap.exe" 
LINK32_OBJS= \
	".\Debug\Doc.obj" \
	".\Debug\Mainfrm.obj" \
	".\Debug\Shadecap.obj" \
	".\Debug\Shadecap.res" \
	".\Debug\Stdafx.obj" \
	".\Debug\View.obj"

".\Debug\ShadeCap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Shadecap - Win32 Release"
# Name "Shadecap - Win32 Debug"

!IF  "$(CFG)" == "Shadecap - Win32 Release"

!ELSEIF  "$(CFG)" == "Shadecap - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Shadecap.rc
DEP_RSC_SHADE=\
	".\Res\App.ico"\
	".\Res\App.rc2"\
	".\Res\Toolbar.bmp"\
	

!IF  "$(CFG)" == "Shadecap - Win32 Release"


".\Release\Shadecap.res" : $(SOURCE) $(DEP_RSC_SHADE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Shadecap - Win32 Debug"


".\Debug\Shadecap.res" : $(SOURCE) $(DEP_RSC_SHADE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Shadecap - Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ShadeCap.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

".\Release\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Release\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Release\ShadeCap.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Shadecap - Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ShadeCap.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

".\Debug\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Debug\ShadeCap.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Shadecap.cpp
DEP_CPP_SHADEC=\
	".\Doc.h"\
	".\mainfrm.h"\
	".\Shadecap.h"\
	".\stdafx.h"\
	".\TraceWin.h"\
	".\View.h"\
	

!IF  "$(CFG)" == "Shadecap - Win32 Release"


".\Release\Shadecap.obj" : $(SOURCE) $(DEP_CPP_SHADEC) "$(INTDIR)"\
 ".\Release\ShadeCap.pch"

".\Release\Shadecap.sbr" : $(SOURCE) $(DEP_CPP_SHADEC) "$(INTDIR)"\
 ".\Release\ShadeCap.pch"


!ELSEIF  "$(CFG)" == "Shadecap - Win32 Debug"


".\Debug\Shadecap.obj" : $(SOURCE) $(DEP_CPP_SHADEC) "$(INTDIR)"\
 ".\Debug\ShadeCap.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mainfrm.cpp
DEP_CPP_MAINF=\
	".\mainfrm.h"\
	".\Shadecap.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Shadecap - Win32 Release"


".\Release\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 ".\Release\ShadeCap.pch"

".\Release\Mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 ".\Release\ShadeCap.pch"


!ELSEIF  "$(CFG)" == "Shadecap - Win32 Debug"


".\Debug\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 ".\Debug\ShadeCap.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doc.cpp
DEP_CPP_DOC_C=\
	".\Doc.h"\
	".\Shadecap.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Shadecap - Win32 Release"


".\Release\Doc.obj" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 ".\Release\ShadeCap.pch"

".\Release\Doc.sbr" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 ".\Release\ShadeCap.pch"


!ELSEIF  "$(CFG)" == "Shadecap - Win32 Debug"


".\Debug\Doc.obj" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 ".\Debug\ShadeCap.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\View.cpp
DEP_CPP_VIEW_=\
	".\Doc.h"\
	".\Shadecap.h"\
	".\stdafx.h"\
	".\View.h"\
	

!IF  "$(CFG)" == "Shadecap - Win32 Release"


".\Release\View.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 ".\Release\ShadeCap.pch"

".\Release\View.sbr" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 ".\Release\ShadeCap.pch"


!ELSEIF  "$(CFG)" == "Shadecap - Win32 Debug"


".\Debug\View.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 ".\Debug\ShadeCap.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
