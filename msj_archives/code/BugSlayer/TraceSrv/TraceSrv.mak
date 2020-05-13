# Microsoft Developer Studio Generated NMAKE File, Based on TraceSrv.dsp
!IF "$(CFG)" == ""
CFG=TraceSrv - Win32 ALPHA Unicode Debug
!MESSAGE No configuration specified. Defaulting to TraceSrv - Win32 ALPHA\
 Unicode Debug.
!ENDIF 

!IF "$(CFG)" != "TraceSrv - Win32 Unicode Debug" && "$(CFG)" !=\
 "TraceSrv - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "TraceSrv - Win32 ALPHA Unicode Debug" && "$(CFG)" !=\
 "TraceSrv - Win32 ALPHA Unicode Release MinSize"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TraceSrv.mak" CFG="TraceSrv - Win32 ALPHA Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TraceSrv - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "TraceSrv - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Application")
!MESSAGE "TraceSrv - Win32 ALPHA Unicode Debug" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "TraceSrv - Win32 ALPHA Unicode Release MinSize" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

OUTDIR=.\..\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TraceSrv.exe" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\TraceSrv.exe" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\FastBSTR.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Trace.obj"
	-@erase "$(INTDIR)\TraceSrv.obj"
	-@erase "$(INTDIR)\TraceSrv.pch"
	-@erase "$(INTDIR)\TraceSrv.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\TraceSrv.exe"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W4 /Z7 /Od /I "..\Include" /D "_DEBUG" /D "_UNICODE" /D\
 "WIN32" /D "_WINDOWS" /D "UNICODE" /Fp"$(INTDIR)\TraceSrv.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GF /c 
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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TraceSrv.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TraceSrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 ..\Lib\Intel\MemDumperValidator.lib /nologo /entry:"wWinMainCRTStartup"\
 /subsystem:windows /pdb:none /debug /machine:I386 /out:"$(OUTDIR)\TraceSrv.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\FastBSTR.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Trace.obj" \
	"$(INTDIR)\TraceSrv.obj" \
	"$(INTDIR)\TraceSrv.res"

"$(OUTDIR)\TraceSrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Debug
TargetPath=\Dev\Column\Dec97\SourceCode\Debug\TraceSrv.exe
InputPath=\Dev\Column\Dec97\SourceCode\Debug\TraceSrv.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

OUTDIR=.\..\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TraceSrv.exe" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\TraceSrv.exe" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\FastBSTR.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Trace.obj"
	-@erase "$(INTDIR)\TraceSrv.obj"
	-@erase "$(INTDIR)\TraceSrv.pch"
	-@erase "$(INTDIR)\TraceSrv.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\TraceSrv.exe"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W4 /WX /Z7 /O1 /I "..\Include" /D "NDEBUG" /D "_UNICODE"\
 /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /Fp"$(INTDIR)\TraceSrv.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GF /c 
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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TraceSrv.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TraceSrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /pdb:none /debug /machine:I386 /out:"$(OUTDIR)\TraceSrv.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\FastBSTR.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Trace.obj" \
	"$(INTDIR)\TraceSrv.obj" \
	"$(INTDIR)\TraceSrv.res"

"$(OUTDIR)\TraceSrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Release
TargetPath=\Dev\Column\Dec97\SourceCode\Release\TraceSrv.exe
InputPath=\Dev\Column\Dec97\SourceCode\Release\TraceSrv.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

OUTDIR=.\..\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TraceSrv.exe" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\TraceSrv.exe" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\FastBSTR.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Trace.obj"
	-@erase "$(INTDIR)\TraceSrv.obj"
	-@erase "$(INTDIR)\TraceSrv.pch"
	-@erase "$(INTDIR)\TraceSrv.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\TraceSrv.exe"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /MLd /Gt0 /W4 /GX /Z7 /Od /I "..\Include" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\TraceSrv.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GF /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TraceSrv.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TraceSrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib ..\Lib\Alpha\MemDumperValidator.lib /nologo\
 /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:none /debug /machine:ALPHA\
 /out:"$(OUTDIR)\TraceSrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FastBSTR.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Trace.obj" \
	"$(INTDIR)\TraceSrv.obj" \
	"$(INTDIR)\TraceSrv.res"

"$(OUTDIR)\TraceSrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Debug
TargetPath=\Dev\Column\Dec97\SourceCode\Debug\TraceSrv.exe
InputPath=\Dev\Column\Dec97\SourceCode\Debug\TraceSrv.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

OUTDIR=.\..\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TraceSrv.exe" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\TraceSrv.exe" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\FastBSTR.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Trace.obj"
	-@erase "$(INTDIR)\TraceSrv.obj"
	-@erase "$(INTDIR)\TraceSrv.pch"
	-@erase "$(INTDIR)\TraceSrv.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\TraceSrv.exe"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /ML /Gt0 /W4 /WX /GX /Z7 /O1 /I "..\Include" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\TraceSrv.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GF /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TraceSrv.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TraceSrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /pdb:none /debug\
 /machine:ALPHA /out:"$(OUTDIR)\TraceSrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FastBSTR.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Trace.obj" \
	"$(INTDIR)\TraceSrv.obj" \
	"$(INTDIR)\TraceSrv.res"

"$(OUTDIR)\TraceSrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Release
TargetPath=\Dev\Column\Dec97\SourceCode\Release\TraceSrv.exe
InputPath=\Dev\Column\Dec97\SourceCode\Release\TraceSrv.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	

!ENDIF 


!IF "$(CFG)" == "TraceSrv - Win32 Unicode Debug" || "$(CFG)" ==\
 "TraceSrv - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "TraceSrv - Win32 ALPHA Unicode Debug" || "$(CFG)" ==\
 "TraceSrv - Win32 ALPHA Unicode Release MinSize"
SOURCE=.\FastBSTR.cpp

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

DEP_CPP_FASTB=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FastBSTR.obj" : $(SOURCE) $(DEP_CPP_FASTB) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

DEP_CPP_FASTB=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FastBSTR.obj" : $(SOURCE) $(DEP_CPP_FASTB) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

DEP_CPP_FASTB=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FastBSTR.obj" : $(SOURCE) $(DEP_CPP_FASTB) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

DEP_CPP_FASTB=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FastBSTR.obj" : $(SOURCE) $(DEP_CPP_FASTB) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

DEP_CPP_STDAF=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MLd /W4 /Z7 /Od /I "..\Include" /D "_DEBUG" /D "_UNICODE"\
 /D "WIN32" /D "_WINDOWS" /D "UNICODE" /Fp"$(INTDIR)\TraceSrv.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GF /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TraceSrv.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

DEP_CPP_STDAF=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /ML /W4 /WX /Z7 /O1 /I "..\Include" /D "NDEBUG" /D\
 "_UNICODE" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "UNICODE"\
 /Fp"$(INTDIR)\TraceSrv.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /GF /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TraceSrv.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

DEP_CPP_STDAF=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MLd /Gt0 /W4 /GX /Z7 /Od /I "..\Include" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\TraceSrv.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GF /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TraceSrv.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

DEP_CPP_STDAF=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /ML /Gt0 /W4 /WX /GX /Z7 /O1 /I "..\Include" /D "NDEBUG"\
 /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\TraceSrv.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GF /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TraceSrv.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Trace.cpp

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

DEP_CPP_TRACE=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	

"$(INTDIR)\Trace.obj" : $(SOURCE) $(DEP_CPP_TRACE) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch" ".\TraceSrv.h"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

DEP_CPP_TRACE=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	

"$(INTDIR)\Trace.obj" : $(SOURCE) $(DEP_CPP_TRACE) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch" ".\TraceSrv.h"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

DEP_CPP_TRACE=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	

"$(INTDIR)\Trace.obj" : $(SOURCE) $(DEP_CPP_TRACE) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch" ".\TraceSrv.h"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

DEP_CPP_TRACE=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	

"$(INTDIR)\Trace.obj" : $(SOURCE) $(DEP_CPP_TRACE) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch" ".\TraceSrv.h"


!ENDIF 

SOURCE=.\TraceSrv.cpp

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

DEP_CPP_TRACES=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	".\TraceSrv_i.c"\
	

"$(INTDIR)\TraceSrv.obj" : $(SOURCE) $(DEP_CPP_TRACES) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch" ".\TraceSrv.h" ".\TraceSrv_i.c"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

DEP_CPP_TRACES=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	".\TraceSrv_i.c"\
	

"$(INTDIR)\TraceSrv.obj" : $(SOURCE) $(DEP_CPP_TRACES) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch" ".\TraceSrv.h" ".\TraceSrv_i.c"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

DEP_CPP_TRACES=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	".\TraceSrv_i.c"\
	

"$(INTDIR)\TraceSrv.obj" : $(SOURCE) $(DEP_CPP_TRACES) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch" ".\TraceSrv.h" ".\TraceSrv_i.c"


!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

DEP_CPP_TRACES=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	".\TraceSrv_i.c"\
	

"$(INTDIR)\TraceSrv.obj" : $(SOURCE) $(DEP_CPP_TRACES) "$(INTDIR)"\
 "$(INTDIR)\TraceSrv.pch" ".\TraceSrv.h" ".\TraceSrv_i.c"


!ENDIF 

SOURCE=.\TraceSrv.idl

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

InputPath=.\TraceSrv.idl

".\TraceSrv.tlb"	".\TraceSrv.h"	".\TraceSrv_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "TraceSrv.h" /iid "TraceSrv_i.c" "TraceSrv.idl"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

InputPath=.\TraceSrv.idl

".\TraceSrv.tlb"	".\TraceSrv.h"	".\TraceSrv_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "TraceSrv.h" /iid "TraceSrv_i.c" "TraceSrv.idl"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

InputPath=.\TraceSrv.idl

".\TraceSrv.tlb"	".\TraceSrv.h"	".\TraceSrv_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "TraceSrv.h" /iid "TraceSrv_i.c" "TraceSrv.idl"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

InputPath=.\TraceSrv.idl

".\TraceSrv.tlb"	".\TraceSrv.h"	".\TraceSrv_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "TraceSrv.h" /iid "TraceSrv_i.c" "TraceSrv.idl"

!ENDIF 

SOURCE=.\TraceSrv.rc
DEP_RSC_TRACESR=\
	".\Trace.rgs"\
	".\TraceSrv.rgs"\
	".\TraceSrv.tlb"\
	

"$(INTDIR)\TraceSrv.res" : $(SOURCE) $(DEP_RSC_TRACESR) "$(INTDIR)"\
 ".\TraceSrv.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

