# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=forms - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to forms - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "forms - Win32 Release" && "$(CFG)" != "forms - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "forms.mak" CFG="forms - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "forms - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "forms - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "forms - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "forms - Win32 Release"

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

ALL : "$(OUTDIR)\forms.exe"

CLEAN : 
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\form.obj"
	-@erase "$(INTDIR)\formapp.obj"
	-@erase "$(INTDIR)\forms.pch"
	-@erase "$(INTDIR)\forms.res"
	-@erase "$(INTDIR)\formsDoc.obj"
	-@erase "$(INTDIR)\formview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\string.obj"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\text.obj"
	-@erase "$(INTDIR)\wrapper2.obj"
	-@erase "$(INTDIR)\wrappers.obj"
	-@erase "$(OUTDIR)\forms.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TEST_STUFF" /D "MFC" /D "DEBUG" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "TEST_STUFF" /D "MFC" /D "DEBUG"\
 /Fp"$(INTDIR)/forms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/forms.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/forms.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/forms.pdb" /machine:I386 /out:"$(OUTDIR)/forms.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\form.obj" \
	"$(INTDIR)\formapp.obj" \
	"$(INTDIR)\forms.res" \
	"$(INTDIR)\formsDoc.obj" \
	"$(INTDIR)\formview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\string.obj" \
	"$(INTDIR)\test.obj" \
	"$(INTDIR)\text.obj" \
	"$(INTDIR)\wrapper2.obj" \
	"$(INTDIR)\wrappers.obj"

"$(OUTDIR)\forms.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

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

ALL : "$(OUTDIR)\forms.exe" "$(OUTDIR)\forms.bsc"

CLEAN : 
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\form.obj"
	-@erase "$(INTDIR)\form.sbr"
	-@erase "$(INTDIR)\formapp.obj"
	-@erase "$(INTDIR)\formapp.sbr"
	-@erase "$(INTDIR)\forms.pch"
	-@erase "$(INTDIR)\forms.res"
	-@erase "$(INTDIR)\formsDoc.obj"
	-@erase "$(INTDIR)\formsDoc.sbr"
	-@erase "$(INTDIR)\formview.obj"
	-@erase "$(INTDIR)\formview.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\string.obj"
	-@erase "$(INTDIR)\string.sbr"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\test.sbr"
	-@erase "$(INTDIR)\text.obj"
	-@erase "$(INTDIR)\text.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\wrapper2.obj"
	-@erase "$(INTDIR)\wrapper2.sbr"
	-@erase "$(INTDIR)\wrappers.obj"
	-@erase "$(INTDIR)\wrappers.sbr"
	-@erase "$(OUTDIR)\forms.bsc"
	-@erase "$(OUTDIR)\forms.exe"
	-@erase "$(OUTDIR)\forms.ilk"
	-@erase "$(OUTDIR)\forms.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TEST_STUFF" /D "MFC" /D "DEBUG" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TEST_STUFF" /D "MFC" /D "DEBUG"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/forms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/forms.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/forms.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\form.sbr" \
	"$(INTDIR)\formapp.sbr" \
	"$(INTDIR)\formsDoc.sbr" \
	"$(INTDIR)\formview.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\string.sbr" \
	"$(INTDIR)\test.sbr" \
	"$(INTDIR)\text.sbr" \
	"$(INTDIR)\wrapper2.sbr" \
	"$(INTDIR)\wrappers.sbr"

"$(OUTDIR)\forms.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/forms.pdb" /debug /machine:I386 /out:"$(OUTDIR)/forms.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\form.obj" \
	"$(INTDIR)\formapp.obj" \
	"$(INTDIR)\forms.res" \
	"$(INTDIR)\formsDoc.obj" \
	"$(INTDIR)\formview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\string.obj" \
	"$(INTDIR)\test.obj" \
	"$(INTDIR)\text.obj" \
	"$(INTDIR)\wrapper2.obj" \
	"$(INTDIR)\wrappers.obj"

"$(OUTDIR)\forms.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "forms - Win32 Release"
# Name "forms - Win32 Debug"

!IF  "$(CFG)" == "forms - Win32 Release"

!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "forms - Win32 Release"

!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "forms - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "TEST_STUFF" /D "MFC" /D "DEBUG"\
 /Fp"$(INTDIR)/forms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\forms.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TEST_STUFF" /D "MFC" /D "DEBUG"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/forms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\forms.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\formapp.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "forms - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\formapp.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "forms - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\formsDoc.cpp
DEP_CPP_FORMS=\
	".\formapp.h"\
	".\formsDoc.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "forms - Win32 Release"


"$(INTDIR)\formsDoc.obj" : $(SOURCE) $(DEP_CPP_FORMS) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"


"$(INTDIR)\formsDoc.obj" : $(SOURCE) $(DEP_CPP_FORMS) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\formsDoc.sbr" : $(SOURCE) $(DEP_CPP_FORMS) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\forms.rc
DEP_RSC_FORMS_=\
	".\res\forms.ico"\
	".\res\forms.rc2"\
	".\res\formsDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\forms.res" : $(SOURCE) $(DEP_RSC_FORMS_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\string.cpp
DEP_CPP_STRIN=\
	".\ansi.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

!IF  "$(CFG)" == "forms - Win32 Release"


"$(INTDIR)\string.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"


"$(INTDIR)\string.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\string.sbr" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\text.cpp

!IF  "$(CFG)" == "forms - Win32 Release"

DEP_CPP_TEXT_=\
	".\ansi.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\text.h"\
	".\userintf.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\text.obj" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

DEP_CPP_TEXT_=\
	".\ansi.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\text.h"\
	".\userintf.h"\
	".\wrapper2.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\text.obj" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\text.sbr" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\test.cpp

!IF  "$(CFG)" == "forms - Win32 Release"

DEP_CPP_TEST_=\
	".\ansi.h"\
	".\form.h"\
	".\formapp.h"\
	".\formsDoc.h"\
	".\formview.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\text.h"\
	".\userintf.h"\
	".\wrappers.h"\
	".\wrappers2.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

DEP_CPP_TEST_=\
	".\ansi.h"\
	".\form.h"\
	".\formapp.h"\
	".\formsDoc.h"\
	".\formview.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\text.h"\
	".\userintf.h"\
	".\wrapper2.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\test.sbr" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wrappers.cpp

!IF  "$(CFG)" == "forms - Win32 Release"

DEP_CPP_WRAPP=\
	".\ansi.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\userintf.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\wrappers.obj" : $(SOURCE) $(DEP_CPP_WRAPP) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

DEP_CPP_WRAPP=\
	".\ansi.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\userintf.h"\
	".\wrapper2.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\wrappers.obj" : $(SOURCE) $(DEP_CPP_WRAPP) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\wrappers.sbr" : $(SOURCE) $(DEP_CPP_WRAPP) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\form.cpp

!IF  "$(CFG)" == "forms - Win32 Release"

DEP_CPP_FORM_=\
	".\ansi.h"\
	".\form.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\text.h"\
	".\userintf.h"\
	".\wrappers.h"\
	".\wrappers2.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\form.obj" : $(SOURCE) $(DEP_CPP_FORM_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

DEP_CPP_FORM_=\
	".\ansi.h"\
	".\form.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\text.h"\
	".\userintf.h"\
	".\wrapper2.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\form.obj" : $(SOURCE) $(DEP_CPP_FORM_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\form.sbr" : $(SOURCE) $(DEP_CPP_FORM_) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\formapp.cpp

!IF  "$(CFG)" == "forms - Win32 Release"

DEP_CPP_FORMA=\
	".\ChildFrm.h"\
	".\formapp.h"\
	".\formsDoc.h"\
	".\formsView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\formapp.obj" : $(SOURCE) $(DEP_CPP_FORMA) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

DEP_CPP_FORMA=\
	".\ChildFrm.h"\
	".\formapp.h"\
	".\formsDoc.h"\
	".\formview.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\formapp.obj" : $(SOURCE) $(DEP_CPP_FORMA) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\formapp.sbr" : $(SOURCE) $(DEP_CPP_FORMA) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\formview.cpp

!IF  "$(CFG)" == "forms - Win32 Release"

DEP_CPP_FORMV=\
	".\ansi.h"\
	".\formapp.h"\
	".\formsDoc.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\text.h"\
	".\userintf.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	
NODEP_CPP_FORMV=\
	".\formsView.h"\
	".\wrappers2.h"\
	

"$(INTDIR)\formview.obj" : $(SOURCE) $(DEP_CPP_FORMV) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

DEP_CPP_FORMV=\
	".\ansi.h"\
	".\formapp.h"\
	".\formsDoc.h"\
	".\formview.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\text.h"\
	".\userintf.h"\
	".\wrapper2.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\formview.obj" : $(SOURCE) $(DEP_CPP_FORMV) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\formview.sbr" : $(SOURCE) $(DEP_CPP_FORMV) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wrapper2.cpp

!IF  "$(CFG)" == "forms - Win32 Release"

DEP_CPP_WRAPPE=\
	".\ansi.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\userintf.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	
NODEP_CPP_WRAPPE=\
	".\wrappers2.h"\
	

"$(INTDIR)\wrapper2.obj" : $(SOURCE) $(DEP_CPP_WRAPPE) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ELSEIF  "$(CFG)" == "forms - Win32 Debug"

DEP_CPP_WRAPPE=\
	".\ansi.h"\
	".\mystring.h"\
	".\notify.h"\
	".\StdAfx.h"\
	".\userintf.h"\
	".\wrapper2.h"\
	".\wrappers.h"\
	{$(INCLUDE)}"\dbg_out.h"\
	

"$(INTDIR)\wrapper2.obj" : $(SOURCE) $(DEP_CPP_WRAPPE) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"

"$(INTDIR)\wrapper2.sbr" : $(SOURCE) $(DEP_CPP_WRAPPE) "$(INTDIR)"\
 "$(INTDIR)\forms.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
