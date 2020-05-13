# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DVDemo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DVDemo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DVDemo - Win32 Release" && "$(CFG)" != "DVDemo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DVDemo.mak" CFG="DVDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DVDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DVDemo - Win32 Debug" (based on "Win32 (x86) Application")
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
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DVDemo - Win32 Release"

# PROP BASE Use_MFC 0
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

ALL : "$(OUTDIR)\DVDemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\DemoDoc.obj"
	-@erase "$(INTDIR)\DriveView.obj"
	-@erase "$(INTDIR)\DVDemo.obj"
	-@erase "$(INTDIR)\DVDemo.res"
	-@erase "$(INTDIR)\MainFrame.obj"
	-@erase "$(OUTDIR)\DVDemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DVDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DVDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/DVDemo.pdb" /machine:I386 /out:"$(OUTDIR)/DVDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DemoDoc.obj" \
	"$(INTDIR)\DriveView.obj" \
	"$(INTDIR)\DVDemo.obj" \
	"$(INTDIR)\DVDemo.res" \
	"$(INTDIR)\MainFrame.obj"

"$(OUTDIR)\DVDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DVDemo - Win32 Debug"

# PROP BASE Use_MFC 0
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

ALL : "$(OUTDIR)\DVDemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\DemoDoc.obj"
	-@erase "$(INTDIR)\DriveView.obj"
	-@erase "$(INTDIR)\DVDemo.obj"
	-@erase "$(INTDIR)\DVDemo.res"
	-@erase "$(INTDIR)\MainFrame.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\DVDemo.exe"
	-@erase "$(OUTDIR)\DVDemo.ilk"
	-@erase "$(OUTDIR)\DVDemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DVDemo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DVDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/DVDemo.pdb" /debug /machine:I386 /out:"$(OUTDIR)/DVDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DemoDoc.obj" \
	"$(INTDIR)\DriveView.obj" \
	"$(INTDIR)\DVDemo.obj" \
	"$(INTDIR)\DVDemo.res" \
	"$(INTDIR)\MainFrame.obj"

"$(OUTDIR)\DVDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DVDemo - Win32 Release"
# Name "DVDemo - Win32 Debug"

!IF  "$(CFG)" == "DVDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "DVDemo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MainFrame.cpp
DEP_CPP_MAINF=\
	".\DriveView.h"\
	".\MainFrame.h"\
	".\Resource.h"\
	

"$(INTDIR)\MainFrame.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DriveView.cpp
DEP_CPP_DRIVE=\
	".\DriveView.h"\
	".\Resource.h"\
	

"$(INTDIR)\DriveView.obj" : $(SOURCE) $(DEP_CPP_DRIVE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DVDemo.cpp
DEP_CPP_DVDEM=\
	".\DemoDoc.h"\
	".\DriveView.h"\
	".\DVDemo.h"\
	".\MainFrame.h"\
	".\Resource.h"\
	

"$(INTDIR)\DVDemo.obj" : $(SOURCE) $(DEP_CPP_DVDEM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DVDemo.rc
DEP_RSC_DVDEMO=\
	".\Drives.bmp"\
	".\Resource.h"\
	

"$(INTDIR)\DVDemo.res" : $(SOURCE) $(DEP_RSC_DVDEMO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DemoDoc.cpp
DEP_CPP_DEMOD=\
	".\DemoDoc.h"\
	

"$(INTDIR)\DemoDoc.obj" : $(SOURCE) $(DEP_CPP_DEMOD) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################

