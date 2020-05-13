# Microsoft Developer Studio Generated NMAKE File, Format Version 42001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Virgil - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Virgil - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Virgil - Win32 Release" && "$(CFG)" != "Virgil - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Virgil.mak" CFG="Virgil - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Virgil - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Virgil - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Virgil - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Virgil - Win32 Release"

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

ALL : "$(OUTDIR)\Virgil.exe"

CLEAN : 
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Dib.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\MsgHook.obj"
	-@erase "$(INTDIR)\PalHook.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Virgil.obj"
	-@erase "$(INTDIR)\Virgil.pch"
	-@erase "$(INTDIR)\Virgil.res"
	-@erase "$(OUTDIR)\Virgil.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Virgil.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Virgil.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Virgil.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=vfw32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Virgil.pdb" /machine:I386 /out:"$(OUTDIR)/Virgil.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\Dib.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\MsgHook.obj" \
	"$(INTDIR)\PalHook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Virgil.obj" \
	"$(INTDIR)\Virgil.res"

"$(OUTDIR)\Virgil.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Virgil - Win32 Debug"

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

ALL : "$(OUTDIR)\Virgil.exe"

CLEAN : 
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Dib.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\MsgHook.obj"
	-@erase "$(INTDIR)\PalHook.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Virgil.obj"
	-@erase "$(INTDIR)\Virgil.pch"
	-@erase "$(INTDIR)\Virgil.res"
	-@erase "$(OUTDIR)\Virgil.exe"
	-@erase "$(OUTDIR)\Virgil.ilk"
	-@erase "$(OUTDIR)\Virgil.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Virgil.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Virgil.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Virgil.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=vfw32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Virgil.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Virgil.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\Dib.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\MsgHook.obj" \
	"$(INTDIR)\PalHook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Virgil.obj" \
	"$(INTDIR)\Virgil.res"

"$(OUTDIR)\Virgil.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Virgil - Win32 Release"
# Name "Virgil - Win32 Debug"

!IF  "$(CFG)" == "Virgil - Win32 Release"

!ELSEIF  "$(CFG)" == "Virgil - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Virgil - Win32 Release"

!ELSEIF  "$(CFG)" == "Virgil - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Virgil.cpp
DEP_CPP_VIRGI=\
	".\Dib.h"\
	".\mainfrm.h"\
	".\MsgHook.h"\
	".\PalHook.h"\
	".\StdAfx.h"\
	".\TraceWin.h"\
	".\Virgil.h"\
	

"$(INTDIR)\Virgil.obj" : $(SOURCE) $(DEP_CPP_VIRGI) "$(INTDIR)"\
 "$(INTDIR)\Virgil.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Virgil - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Virgil.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Virgil.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Virgil - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Virgil.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Virgil.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Virgil.rc
DEP_RSC_VIRGIL=\
	".\res\app.ico"\
	".\res\app.rc2"\
	".\res\head.bmp"\
	".\res\mask.bmp"\
	".\res\virgil.bmp"\
	

"$(INTDIR)\Virgil.res" : $(SOURCE) $(DEP_RSC_VIRGIL) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\Dib.h"\
	".\mainfrm.h"\
	".\MsgHook.h"\
	".\PalHook.h"\
	".\StdAfx.h"\
	".\Virgil.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Virgil.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dib.cpp
DEP_CPP_DIB_C=\
	".\Dib.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"\
 "$(INTDIR)\Virgil.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsgHook.cpp
DEP_CPP_MSGHO=\
	".\Debug.h"\
	".\MsgHook.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MsgHook.obj" : $(SOURCE) $(DEP_CPP_MSGHO) "$(INTDIR)"\
 "$(INTDIR)\Virgil.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PalHook.cpp
DEP_CPP_PALHO=\
	".\Debug.h"\
	".\MsgHook.h"\
	".\PalHook.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\PalHook.obj" : $(SOURCE) $(DEP_CPP_PALHO) "$(INTDIR)"\
 "$(INTDIR)\Virgil.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Debug.cpp
DEP_CPP_DEBUG=\
	".\Debug.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Virgil.pch"


# End Source File
# End Target
# End Project
################################################################################
