# Microsoft Developer Studio Project File - Name="TraceSrv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=TraceSrv - Win32 ALPHA Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TraceSrv.mak".
!MESSAGE 
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

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W4 /Z7 /Od /I "..\Include" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /Yu"stdafx.h" /FD /GF /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ..\Lib\Intel\MemDumperValidator.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:none /debug /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\..\Debug
TargetPath=\Dev\Column\Dec97\SourceCode\Debug\TraceSrv.exe
InputPath=\Dev\Column\Dec97\SourceCode\Debug\TraceSrv.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W4 /WX /Z7 /O1 /I "..\Include" /D "NDEBUG" /D "_UNICODE" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /Yu"stdafx.h" /FD /GF /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /pdb:none /debug /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\..\Release
TargetPath=\Dev\Column\Dec97\SourceCode\Release\TraceSrv.exe
InputPath=\Dev\Column\Dec97\SourceCode\Release\TraceSrv.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TraceSr0"
# PROP BASE Intermediate_Dir "TraceSr0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W4 /GX /Z7 /Od /I "..\Include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /GF /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ..\Lib\Alpha\MemDumperValidator.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:none /debug /machine:ALPHA
# Begin Custom Build - Performing registration
OutDir=.\..\Debug
TargetPath=\Dev\Column\Dec97\SourceCode\Debug\TraceSrv.exe
InputPath=\Dev\Column\Dec97\SourceCode\Debug\TraceSrv.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TraceSr2"
# PROP BASE Intermediate_Dir "TraceSr2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W4 /WX /GX /Z7 /O1 /I "..\Include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /GF /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /pdb:none /debug /machine:ALPHA
# Begin Custom Build - Performing registration
OutDir=.\..\Release
TargetPath=\Dev\Column\Dec97\SourceCode\Release\TraceSrv.exe
InputPath=\Dev\Column\Dec97\SourceCode\Release\TraceSrv.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TraceSrv - Win32 Unicode Debug"
# Name "TraceSrv - Win32 Unicode Release MinSize"
# Name "TraceSrv - Win32 ALPHA Unicode Debug"
# Name "TraceSrv - Win32 ALPHA Unicode Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\FastBSTR.cpp

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

DEP_CPP_FASTB=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

DEP_CPP_FASTB=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

DEP_CPP_STDAF=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

DEP_CPP_STDAF=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Trace.cpp

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

DEP_CPP_TRACE=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

DEP_CPP_TRACE=\
	"..\include\memdumpervalidator.h"\
	"..\include\msjdbg.h"\
	".\CorrectProxyTraceSrv.h"\
	".\FastBSTR.h"\
	".\StdAfx.h"\
	".\Trace.h"\
	".\TraceSrv.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TraceSrv.cpp

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

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
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TraceSrv.idl

!IF  "$(CFG)" == "TraceSrv - Win32 Unicode Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\TraceSrv.idl

BuildCmds= \
	midl /Oicf /h "TraceSrv.h" /iid "TraceSrv_i.c" "TraceSrv.idl"

".\TraceSrv.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TraceSrv.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TraceSrv_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 Unicode Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\TraceSrv.idl

BuildCmds= \
	midl /Oicf /h "TraceSrv.h" /iid "TraceSrv_i.c" "TraceSrv.idl"

".\TraceSrv.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TraceSrv.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TraceSrv_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\TraceSrv.idl

BuildCmds= \
	midl /Oicf /h "TraceSrv.h" /iid "TraceSrv_i.c" "TraceSrv.idl"

".\TraceSrv.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TraceSrv.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TraceSrv_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TraceSrv - Win32 ALPHA Unicode Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\TraceSrv.idl

BuildCmds= \
	midl /Oicf /h "TraceSrv.h" /iid "TraceSrv_i.c" "TraceSrv.idl"

".\TraceSrv.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TraceSrv.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TraceSrv_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TraceSrv.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\FastBSTR.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Trace.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\Trace.rgs
# End Source File
# Begin Source File

SOURCE=.\TraceSrv.rgs
# End Source File
# End Target
# End Project
