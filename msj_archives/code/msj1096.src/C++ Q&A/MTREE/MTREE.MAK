# Microsoft Developer Studio Generated NMAKE File, Format Version 42001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Mtree - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Mtree - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Mtree - Win32 Release" && "$(CFG)" != "Mtree - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "mtree.mak" CFG="Mtree - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mtree - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Mtree - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Mtree - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Mtree - Win32 Release"

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

ALL : "$(OUTDIR)\mtree.exe" "$(OUTDIR)\mtree.bsc"

CLEAN : 
	-@erase "$(INTDIR)\dlg.obj"
	-@erase "$(INTDIR)\dlg.sbr"
	-@erase "$(INTDIR)\Mtree.obj"
	-@erase "$(INTDIR)\mtree.pch"
	-@erase "$(INTDIR)\Mtree.res"
	-@erase "$(INTDIR)\Mtree.sbr"
	-@erase "$(INTDIR)\multree.obj"
	-@erase "$(INTDIR)\multree.sbr"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\Stdafx.sbr"
	-@erase "$(OUTDIR)\mtree.bsc"
	-@erase "$(OUTDIR)\mtree.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"STDAFX.H" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/mtree.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Mtree.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mtree.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dlg.sbr" \
	"$(INTDIR)\Mtree.sbr" \
	"$(INTDIR)\multree.sbr" \
	"$(INTDIR)\Stdafx.sbr"

"$(OUTDIR)\mtree.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/mtree.pdb" /machine:IX86\
 /out:"$(OUTDIR)/mtree.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dlg.obj" \
	"$(INTDIR)\Mtree.obj" \
	"$(INTDIR)\Mtree.res" \
	"$(INTDIR)\multree.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\mtree.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Mtree - Win32 Debug"

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

ALL : "$(OUTDIR)\mtree.exe"

CLEAN : 
	-@erase "$(INTDIR)\dlg.obj"
	-@erase "$(INTDIR)\Mtree.obj"
	-@erase "$(INTDIR)\mtree.pch"
	-@erase "$(INTDIR)\Mtree.res"
	-@erase "$(INTDIR)\multree.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\mtree.exe"
	-@erase "$(OUTDIR)\mtree.ilk"
	-@erase "$(OUTDIR)\mtree.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mtree.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Mtree.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mtree.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/mtree.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)/mtree.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dlg.obj" \
	"$(INTDIR)\Mtree.obj" \
	"$(INTDIR)\Mtree.res" \
	"$(INTDIR)\multree.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\mtree.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Mtree - Win32 Release"
# Name "Mtree - Win32 Debug"

!IF  "$(CFG)" == "Mtree - Win32 Release"

!ELSEIF  "$(CFG)" == "Mtree - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Mtree.rc
DEP_RSC_MTREE=\
	".\Res\App.ico"\
	".\Res\App.rc2"\
	".\Res\Toolbar.bmp"\
	

"$(INTDIR)\Mtree.res" : $(SOURCE) $(DEP_RSC_MTREE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Mtree - Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/mtree.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\mtree.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Mtree - Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mtree.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\mtree.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mtree.cpp
DEP_CPP_MTREE_=\
	".\dlg.h"\
	".\mtree.h"\
	".\multree.h"\
	".\stdafx.h"\
	".\tracewin.h"\
	

!IF  "$(CFG)" == "Mtree - Win32 Release"


"$(INTDIR)\Mtree.obj" : $(SOURCE) $(DEP_CPP_MTREE_) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"

"$(INTDIR)\Mtree.sbr" : $(SOURCE) $(DEP_CPP_MTREE_) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"


!ELSEIF  "$(CFG)" == "Mtree - Win32 Debug"


"$(INTDIR)\Mtree.obj" : $(SOURCE) $(DEP_CPP_MTREE_) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg.cpp
DEP_CPP_DLG_C=\
	".\dlg.h"\
	".\mtree.h"\
	".\multree.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Mtree - Win32 Release"


"$(INTDIR)\dlg.obj" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"

"$(INTDIR)\dlg.sbr" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"


!ELSEIF  "$(CFG)" == "Mtree - Win32 Debug"


"$(INTDIR)\dlg.obj" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\multree.cpp
DEP_CPP_MULTR=\
	".\multree.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Mtree - Win32 Release"


"$(INTDIR)\multree.obj" : $(SOURCE) $(DEP_CPP_MULTR) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"

"$(INTDIR)\multree.sbr" : $(SOURCE) $(DEP_CPP_MULTR) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"


!ELSEIF  "$(CFG)" == "Mtree - Win32 Debug"


"$(INTDIR)\multree.obj" : $(SOURCE) $(DEP_CPP_MULTR) "$(INTDIR)"\
 "$(INTDIR)\mtree.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
