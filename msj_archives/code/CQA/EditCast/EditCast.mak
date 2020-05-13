# Microsoft Developer Studio Generated NMAKE File, Based on EditCast.dsp
!IF "$(CFG)" == ""
CFG=EditCast - Win32 Debug
!MESSAGE No configuration specified. Defaulting to EditCast - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "EditCast - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EditCast.mak" CFG="EditCast - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EditCast - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\EditCast.exe"

!ELSE 

ALL : "$(OUTDIR)\EditCast.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\EditCast.obj"
	-@erase "$(INTDIR)\EditCast.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\EditCast.exe"
	-@erase "$(OUTDIR)\EditCast.ilk"
	-@erase "$(OUTDIR)\EditCast.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EditCast.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=rasapi32.lib oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\EditCast.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)\EditCast.exe" 
LINK32_OBJS= \
	"$(INTDIR)\EditCast.obj" \
	"$(INTDIR)\EditCast.res"

"$(OUTDIR)\EditCast.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EditCast.res" /d "_DEBUG" /d "_AFXDLL" 

!IF "$(CFG)" == "EditCast - Win32 Debug"
SOURCE=.\EditCast.cpp
DEP_CPP_TABDL=\
	".\tracewin.h"\
	

"$(INTDIR)\EditCast.obj" : $(SOURCE) $(DEP_CPP_TABDL) "$(INTDIR)"


SOURCE=.\EditCast.rc
DEP_RSC_EDITCAST=\
	".\Res\App.ico"\
	".\Res\App.rc2"\
	".\Res\Toolbar.bmp"\
	

"$(INTDIR)\EditCast.res" : $(SOURCE) $(DEP_RSC_EDITCAST) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

