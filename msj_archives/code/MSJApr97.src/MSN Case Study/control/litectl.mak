# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=litectl - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to litectl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "litectl - Win32 Release" && "$(CFG)" !=\
 "litectl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "litectl.mak" CFG="litectl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "litectl - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "litectl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "litectl - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "litectl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\litectl.dll"

CLEAN : 
	-@erase "$(INTDIR)\cathelp.obj"
	-@erase "$(INTDIR)\guids.obj"
	-@erase "$(INTDIR)\litctl.obj"
	-@erase "$(INTDIR)\litctl.res"
	-@erase "$(INTDIR)\litctl.tlb"
	-@erase "$(OUTDIR)\litectl.dll"
	-@erase "$(OUTDIR)\litectl.exp"
	-@erase "$(OUTDIR)\litectl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/litectl.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/litctl.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/litectl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/litectl.pdb" /machine:I386 /def:".\litctl.def"\
 /out:"$(OUTDIR)/litectl.dll" /implib:"$(OUTDIR)/litectl.lib" 
DEF_FILE= \
	".\litctl.def"
LINK32_OBJS= \
	"$(INTDIR)\cathelp.obj" \
	"$(INTDIR)\guids.obj" \
	"$(INTDIR)\litctl.obj" \
	"$(INTDIR)\litctl.res"

"$(OUTDIR)\litectl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "litectl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\litectl.dll"

CLEAN : 
	-@erase "$(INTDIR)\cathelp.obj"
	-@erase "$(INTDIR)\guids.obj"
	-@erase "$(INTDIR)\litctl.obj"
	-@erase "$(INTDIR)\litctl.res"
	-@erase "$(INTDIR)\litctl.tlb"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\litectl.dll"
	-@erase "$(OUTDIR)\litectl.exp"
	-@erase "$(OUTDIR)\litectl.ilk"
	-@erase "$(OUTDIR)\litectl.lib"
	-@erase "$(OUTDIR)\litectl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/litectl.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/litctl.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/litectl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/litectl.pdb" /debug /machine:I386 /def:".\litctl.def"\
 /out:"$(OUTDIR)/litectl.dll" /implib:"$(OUTDIR)/litectl.lib" 
DEF_FILE= \
	".\litctl.def"
LINK32_OBJS= \
	"$(INTDIR)\cathelp.obj" \
	"$(INTDIR)\guids.obj" \
	"$(INTDIR)\litctl.obj" \
	"$(INTDIR)\litctl.res"

"$(OUTDIR)\litectl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "litectl - Win32 Release"
# Name "litectl - Win32 Debug"

!IF  "$(CFG)" == "litectl - Win32 Release"

!ELSEIF  "$(CFG)" == "litectl - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\litctl.rc

!IF  "$(CFG)" == "litectl - Win32 Release"

NODEP_RSC_LITCT=\
	".\Release\litctl.tlb"\
	

"$(INTDIR)\litctl.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\litctl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/litctl.res" /i "Release" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "litectl - Win32 Debug"

DEP_RSC_LITCT=\
	".\Debug\litctl.tlb"\
	

"$(INTDIR)\litctl.res" : $(SOURCE) $(DEP_RSC_LITCT) "$(INTDIR)"\
 "$(INTDIR)\litctl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/litctl.res" /i "Debug" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cathelp.h

!IF  "$(CFG)" == "litectl - Win32 Release"

!ELSEIF  "$(CFG)" == "litectl - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\guids.c
DEP_CPP_GUIDS=\
	".\guids.h"\
	

"$(INTDIR)\guids.obj" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\litctl.cpp

"$(INTDIR)\litctl.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cathelp.cpp
DEP_CPP_CATHE=\
	{$(INCLUDE)}"\comcat.h"\
	

"$(INTDIR)\cathelp.obj" : $(SOURCE) $(DEP_CPP_CATHE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\litctl.odl

!IF  "$(CFG)" == "litectl - Win32 Release"


"$(OUTDIR)\litctl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/litctl.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "litectl - Win32 Debug"


"$(OUTDIR)\litctl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/litctl.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\litctl.def

!IF  "$(CFG)" == "litectl - Win32 Release"

!ELSEIF  "$(CFG)" == "litectl - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
