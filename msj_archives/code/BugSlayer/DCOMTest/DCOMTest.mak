# Microsoft Developer Studio Generated NMAKE File, Based on DCOMTest.dsp
!IF "$(CFG)" == ""
CFG=DCOMTest - Win32 ALPHA Debug
!MESSAGE No configuration specified. Defaulting to DCOMTest - Win32 ALPHA\
 Debug.
!ENDIF 

!IF "$(CFG)" != "DCOMTest - Win32 Release" && "$(CFG)" !=\
 "DCOMTest - Win32 Debug" && "$(CFG)" != "DCOMTest - Win32 ALPHA Release" &&\
 "$(CFG)" != "DCOMTest - Win32 ALPHA Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DCOMTest.mak" CFG="DCOMTest - Win32 ALPHA Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DCOMTest - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "DCOMTest - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "DCOMTest - Win32 ALPHA Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "DCOMTest - Win32 ALPHA Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DCOMTest - Win32 Release"

OUTDIR=.\..\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DCOMTest.exe"

!ELSE 

ALL : "$(OUTDIR)\DCOMTest.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DCOMTest.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\DCOMTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W4 /WX /GX /O2 /I "..\TraceSrv" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DCOMTest.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DCOMTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\DCOMTest.pdb" /machine:I386 /out:"$(OUTDIR)\DCOMTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DCOMTest.obj"

"$(OUTDIR)\DCOMTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DCOMTest - Win32 Debug"

OUTDIR=.\..\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DCOMTest.exe"

!ELSE 

ALL : "$(OUTDIR)\DCOMTest.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DCOMTest.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\DCOMTest.exe"
	-@erase "$(OUTDIR)\DCOMTest.ilk"
	-@erase "$(OUTDIR)\DCOMTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W4 /WX /Gm /GX /Zi /Od /I "..\TraceSrv" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\DCOMTest.pch"\
 /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DCOMTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ole32.lib oleaut32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\DCOMTest.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\DCOMTest.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DCOMTest.obj"

"$(OUTDIR)\DCOMTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DCOMTest - Win32 ALPHA Release"

OUTDIR=.\..\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DCOMTest.exe"

!ELSE 

ALL : "$(OUTDIR)\DCOMTest.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DCOMTest.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\DCOMTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W4 /WX /GX /O2 /I "..\TraceSrv" /D "WIN32" /D "NDEBUG"\
 /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DCOMTest.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DCOMTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:console /pdb:"$(OUTDIR)\DCOMTest.pdb" /machine:ALPHA\
 /out:"$(OUTDIR)\DCOMTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DCOMTest.obj"

"$(OUTDIR)\DCOMTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DCOMTest - Win32 ALPHA Debug"

OUTDIR=.\..\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\DCOMTest.exe"

!ELSE 

ALL : "$(OUTDIR)\DCOMTest.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\DCOMTest.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\DCOMTest.exe"
	-@erase "$(OUTDIR)\DCOMTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W4 /WX /GX /Zi /Od /I "..\TraceSrv" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\DCOMTest.pch"\
 /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DCOMTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:console /pdb:"$(OUTDIR)\DCOMTest.pdb" /debug /machine:ALPHA\
 /out:"$(OUTDIR)\DCOMTest.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DCOMTest.obj"

"$(OUTDIR)\DCOMTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "DCOMTest - Win32 Release" || "$(CFG)" ==\
 "DCOMTest - Win32 Debug" || "$(CFG)" == "DCOMTest - Win32 ALPHA Release" ||\
 "$(CFG)" == "DCOMTest - Win32 ALPHA Debug"
SOURCE=.\DCOMTest.cpp

!IF  "$(CFG)" == "DCOMTest - Win32 Release"

DEP_CPP_DCOMT=\
	"..\TraceSrv\TraceSrv.h"\
	"..\TraceSrv\TraceSrv_i.c"\
	

"$(INTDIR)\DCOMTest.obj" : $(SOURCE) $(DEP_CPP_DCOMT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DCOMTest - Win32 Debug"

DEP_CPP_DCOMT=\
	"..\TraceSrv\TraceSrv.h"\
	"..\TraceSrv\TraceSrv_i.c"\
	

"$(INTDIR)\DCOMTest.obj" : $(SOURCE) $(DEP_CPP_DCOMT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DCOMTest - Win32 ALPHA Release"

DEP_CPP_DCOMT=\
	"..\TraceSrv\TraceSrv.h"\
	"..\TraceSrv\TraceSrv_i.c"\
	

"$(INTDIR)\DCOMTest.obj" : $(SOURCE) $(DEP_CPP_DCOMT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DCOMTest - Win32 ALPHA Debug"

DEP_CPP_DCOMT=\
	"..\TraceSrv\TraceSrv.h"\
	"..\TraceSrv\TraceSrv_i.c"\
	

"$(INTDIR)\DCOMTest.obj" : $(SOURCE) $(DEP_CPP_DCOMT) "$(INTDIR)"


!ENDIF 


!ENDIF 

