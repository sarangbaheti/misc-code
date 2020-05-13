# Microsoft Developer Studio Generated NMAKE File, Based on AboutDlg.dsp
!IF "$(CFG)" == ""
CFG=AboutDlg - Win32 Release
!MESSAGE No configuration specified. Defaulting to AboutDlg - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "AboutDlg - Win32 Release" && "$(CFG)" !=\
 "AboutDlg - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AboutDlg.mak" CFG="AboutDlg - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AboutDlg - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AboutDlg - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "AboutDlg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\AboutDlg.exe" "$(OUTDIR)\AboutDlg.bsc"

!ELSE 

ALL : "$(OUTDIR)\AboutDlg.exe" "$(OUTDIR)\AboutDlg.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\AboutDlg.pch"
	-@erase "$(INTDIR)\AboutDlg.res"
	-@erase "$(INTDIR)\AboutDlg.sbr"
	-@erase "$(INTDIR)\StatLink.obj"
	-@erase "$(INTDIR)\StatLink.sbr"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\Stdafx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\AboutDlg.bsc"
	-@erase "$(OUTDIR)\AboutDlg.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\AboutDlg.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AboutDlg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AboutDlg.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AboutDlg.sbr" \
	"$(INTDIR)\StatLink.sbr" \
	"$(INTDIR)\Stdafx.sbr"

"$(OUTDIR)\AboutDlg.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\AboutDlg.pdb" /machine:IX86\
 /out:"$(OUTDIR)\AboutDlg.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\AboutDlg.res" \
	"$(INTDIR)\StatLink.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\AboutDlg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AboutDlg - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\AboutDlg.exe"

!ELSE 

ALL : "$(OUTDIR)\AboutDlg.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\AboutDlg.pch"
	-@erase "$(INTDIR)\AboutDlg.res"
	-@erase "$(INTDIR)\StatLink.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\AboutDlg.exe"
	-@erase "$(OUTDIR)\AboutDlg.ilk"
	-@erase "$(OUTDIR)\AboutDlg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\AboutDlg.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AboutDlg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AboutDlg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\AboutDlg.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)\AboutDlg.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\AboutDlg.res" \
	"$(INTDIR)\StatLink.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\AboutDlg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(CFG)" == "AboutDlg - Win32 Release" || "$(CFG)" ==\
 "AboutDlg - Win32 Debug"
SOURCE=.\AboutDlg.cpp

!IF  "$(CFG)" == "AboutDlg - Win32 Release"

DEP_CPP_ABOUT=\
	".\StatLink.h"\
	

"$(INTDIR)\AboutDlg.obj"	"$(INTDIR)\AboutDlg.sbr" : $(SOURCE) $(DEP_CPP_ABOUT)\
 "$(INTDIR)" "$(INTDIR)\AboutDlg.pch"


!ELSEIF  "$(CFG)" == "AboutDlg - Win32 Debug"

DEP_CPP_ABOUT=\
	".\StatLink.h"\
	".\stdafx.h"\
	

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\AboutDlg.pch"


!ENDIF 

SOURCE=.\AboutDlg.rc
DEP_RSC_ABOUTD=\
	".\RES\APP.ICO"\
	".\res\app.rc2"\
	".\RES\TOOLBAR.BMP"\
	

"$(INTDIR)\AboutDlg.res" : $(SOURCE) $(DEP_RSC_ABOUTD) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StatLink.cpp

!IF  "$(CFG)" == "AboutDlg - Win32 Release"

DEP_CPP_STATL=\
	".\StatLink.h"\
	

"$(INTDIR)\StatLink.obj"	"$(INTDIR)\StatLink.sbr" : $(SOURCE) $(DEP_CPP_STATL)\
 "$(INTDIR)" "$(INTDIR)\AboutDlg.pch"


!ELSEIF  "$(CFG)" == "AboutDlg - Win32 Debug"

DEP_CPP_STATL=\
	".\StatLink.h"\
	".\stdafx.h"\
	

"$(INTDIR)\StatLink.obj" : $(SOURCE) $(DEP_CPP_STATL) "$(INTDIR)"\
 "$(INTDIR)\AboutDlg.pch"


!ENDIF 

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "AboutDlg - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\AboutDlg.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\Stdafx.sbr"	"$(INTDIR)\AboutDlg.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AboutDlg - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\AboutDlg.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\AboutDlg.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

