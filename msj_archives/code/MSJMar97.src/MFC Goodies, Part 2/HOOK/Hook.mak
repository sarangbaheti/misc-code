# Microsoft Developer Studio Generated NMAKE File, Format Version 42001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Hook - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Hook - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Hook - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Hook.mak" CFG="Hook - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Hook - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Hook - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe
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

ALL : "$(OUTDIR)\Hook.exe"

CLEAN : 
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Hook.pch"
	-@erase "$(INTDIR)\Hook.res"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\MsgHook.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Hook.exe"
	-@erase "$(OUTDIR)\Hook.ilk"
	-@erase "$(OUTDIR)\Hook.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Hook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Hook.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)/Hook.exe" 
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Hook.res" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\MsgHook.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\Hook.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Hook.res" /d "_DEBUG" /d "_AFXDLL" 
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Hook.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.

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

# Name "Hook - Win32 Debug"
################################################################################
# Begin Source File

SOURCE=.\Hook.rc
DEP_RSC_HOOK_=\
	".\Res\App.ico"\
	".\Res\App.rc2"\
	".\Res\Toolbar.bmp"\
	

"$(INTDIR)\Hook.res" : $(SOURCE) $(DEP_RSC_HOOK_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	
# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Hook.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Hook.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hook.cpp
DEP_CPP_HOOK_C=\
	".\hook.h"\
	".\mainfrm.h"\
	".\MsgHook.h"\
	".\stdafx.h"\
	".\TraceWin.h"\
	

"$(INTDIR)\Hook.obj" : $(SOURCE) $(DEP_CPP_HOOK_C) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mainfrm.cpp
DEP_CPP_MAINF=\
	".\debug.h"\
	".\hook.h"\
	".\mainfrm.h"\
	".\MsgHook.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\debug.cpp
DEP_CPP_DEBUG=\
	".\debug.h"\
	".\stdafx.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsgHook.cpp
DEP_CPP_MSGHO=\
	".\debug.h"\
	".\MsgHook.h"\
	".\stdafx.h"\
	

"$(INTDIR)\MsgHook.obj" : $(SOURCE) $(DEP_CPP_MSGHO) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


# End Source File
# End Target
# End Project
################################################################################
