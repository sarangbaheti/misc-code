# Microsoft Developer Studio Generated NMAKE File, Format Version 42001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=dibview - Win32 DebugSDI
!MESSAGE No configuration specified.  Defaulting to dibview - Win32 DebugSDI.
!ENDIF 

!IF "$(CFG)" != "dibview - Win32 DebugMDI" && "$(CFG)" !=\
 "dibview - Win32 DebugSDI"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DibView.mak" CFG="dibview - Win32 DebugSDI"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dibview - Win32 DebugMDI" (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 DebugSDI" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "dibview - Win32 DebugSDI"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "dibview - Win32 DebugMDI"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dibview_"
# PROP BASE Intermediate_Dir "dibview_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMDI"
# PROP Intermediate_Dir "DebugMDI"
# PROP Target_Dir ""
OUTDIR=.\DebugMDI
INTDIR=.\DebugMDI

ALL : "$(OUTDIR)\DibView.exe"

CLEAN : 
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Dib.obj"
	-@erase "$(INTDIR)\DibView.obj"
	-@erase "$(INTDIR)\DibView.pch"
	-@erase "$(INTDIR)\dibview.res"
	-@erase "$(INTDIR)\Doc.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\View.obj"
	-@erase "$(OUTDIR)\DibView.exe"
	-@erase "$(OUTDIR)\DibView.ilk"
	-@erase "$(OUTDIR)\DibView.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MDI" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MDI" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DibView.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugMDI/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DibView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 VFW32.LIB /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 VFW32.LIB /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=VFW32.LIB /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/DibView.pdb" /debug /machine:I386 /out:"$(OUTDIR)/DibView.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\Dib.obj" \
	"$(INTDIR)\DibView.obj" \
	"$(INTDIR)\dibview.res" \
	"$(INTDIR)\Doc.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\View.obj"

"$(OUTDIR)\DibView.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugSDI"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dibview2"
# PROP BASE Intermediate_Dir "dibview2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugSDI"
# PROP Intermediate_Dir "DebugSDI"
# PROP Target_Dir ""
OUTDIR=.\DebugSDI
INTDIR=.\DebugSDI

ALL : "$(OUTDIR)\DibView.exe"

CLEAN : 
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Dib.obj"
	-@erase "$(INTDIR)\DibView.obj"
	-@erase "$(INTDIR)\DibView.pch"
	-@erase "$(INTDIR)\dibview.res"
	-@erase "$(INTDIR)\Doc.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\View.obj"
	-@erase "$(OUTDIR)\DibView.exe"
	-@erase "$(OUTDIR)\DibView.ilk"
	-@erase "$(OUTDIR)\DibView.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DibView.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugSDI/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DibView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 VFW32.LIB /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 VFW32.LIB /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=VFW32.LIB /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/DibView.pdb" /debug /machine:I386 /out:"$(OUTDIR)/DibView.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\Dib.obj" \
	"$(INTDIR)\DibView.obj" \
	"$(INTDIR)\dibview.res" \
	"$(INTDIR)\Doc.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\View.obj"

"$(OUTDIR)\DibView.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

RSC_PROJ=/l 0x409 /fo"$(INTDIR)/dibview.res" /d "_DEBUG" /d "_AFXDLL" 

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

MTL_PROJ=/nologo /D "_DEBUG" /win32 
################################################################################
# Begin Target

# Name "dibview - Win32 DebugMDI"
# Name "dibview - Win32 DebugSDI"

!IF  "$(CFG)" == "dibview - Win32 DebugMDI"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugSDI"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dibview - Win32 DebugMDI"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_MDI" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DibView.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DibView.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugSDI"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DibView.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DibView.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\debug.h"\
	".\dibview.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\DibView.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dib.cpp
DEP_CPP_DIB_C=\
	".\dib.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"\
 "$(INTDIR)\DibView.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\View.cpp
DEP_CPP_VIEW_=\
	".\debug.h"\
	".\dib.h"\
	".\dibview.h"\
	".\Doc.h"\
	".\StdAfx.h"\
	".\View.h"\
	

"$(INTDIR)\View.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"\
 "$(INTDIR)\DibView.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DibView.cpp
DEP_CPP_DIBVI=\
	".\dib.h"\
	".\dibview.h"\
	".\Doc.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\TraceWin.h"\
	".\View.h"\
	

"$(INTDIR)\DibView.obj" : $(SOURCE) $(DEP_CPP_DIBVI) "$(INTDIR)"\
 "$(INTDIR)\DibView.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doc.cpp
DEP_CPP_DOC_C=\
	".\dib.h"\
	".\dibview.h"\
	".\Doc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Doc.obj" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 "$(INTDIR)\DibView.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Debug.cpp
DEP_CPP_DEBUG=\
	".\debug.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\DibView.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dibview.rc
DEP_RSC_DIBVIE=\
	".\res\app.ico"\
	".\res\app.rc2"\
	".\res\doc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\dibview.res" : $(SOURCE) $(DEP_RSC_DIBVIE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
