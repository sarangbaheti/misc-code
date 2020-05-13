# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (PegSH) Application" 0x0901
# TARGTYPE "Win32 (x86em) Application" 0x0101
# TARGTYPE "Win32 (PegMIPS) Application" 0x0801

!IF "$(CFG)" == ""
CFG=NYCAddress - Win32 (x86em) Debug
!MESSAGE No configuration specified.  Defaulting to NYCAddress - Win32 (x86em)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "NYCAddress - Win32 (PegMIPS) Release" && "$(CFG)" !=\
 "NYCAddress - Win32 (PegMIPS) Debug" && "$(CFG)" !=\
 "NYCAddress - Win32 (PegSH) Release" && "$(CFG)" !=\
 "NYCAddress - Win32 (PegSH) Debug" && "$(CFG)" !=\
 "NYCAddress - Win32 (x86em) Release" && "$(CFG)" !=\
 "NYCAddress - Win32 (x86em) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "NYCAddress.mak" CFG="NYCAddress - Win32 (x86em) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NYCAddress - Win32 (PegMIPS) Release" (based on\
 "Win32 (PegMIPS) Application")
!MESSAGE "NYCAddress - Win32 (PegMIPS) Debug" (based on\
 "Win32 (PegMIPS) Application")
!MESSAGE "NYCAddress - Win32 (PegSH) Release" (based on\
 "Win32 (PegSH) Application")
!MESSAGE "NYCAddress - Win32 (PegSH) Debug" (based on\
 "Win32 (PegSH) Application")
!MESSAGE "NYCAddress - Win32 (x86em) Release" (based on\
 "Win32 (x86em) Application")
!MESSAGE "NYCAddress - Win32 (x86em) Debug" (based on\
 "Win32 (x86em) Application")
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
# PROP Target_Last_Scanned "NYCAddress - Win32 (x86em) Debug"

!IF  "$(CFG)" == "NYCAddress - Win32 (PegMIPS) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "PMIPSRel"
# PROP BASE Intermediate_Dir "PMIPSRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PMIPSRel"
# PROP Intermediate_Dir "PMIPSRel"
# PROP Target_Dir ""
OUTDIR=.\PMIPSRel
INTDIR=.\PMIPSRel

ALL : "$(OUTDIR)\NYCAddress.exe" "$(OUTDIR)\NYCAddress.trg"

CLEAN : 
	-@erase ".\PMIPSRel\NYCAddress.trg"
	-@erase ".\PMIPSRel\NYCAddress.exe"
	-@erase ".\PMIPSRel\NYCAddress.rsc"
	-@erase ".\PMIPSRel\NYCAddress.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=clmips.exe
# ADD BASE CPP /nologo /W3 /GX- /O2 /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D "PEGASUS" /D "UNICODE" /YX /QMRPeg /c
# ADD CPP /nologo /W3 /GX- /O2 /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D "PEGASUS" /D "UNICODE" /YX /QMRPeg /c
CPP_PROJ=/nologo /W3 /GX- /O2 /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D "PEGASUS" /D\
 "UNICODE" /Fp"$(INTDIR)/NYCAddress.pch" /YX /Fo"$(INTDIR)/" /QMRPeg /c 
CPP_OBJS=.\PMIPSRel/
CPP_SBRS=

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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d "PEGASUS" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d "PEGASUS" /d "NDEBUG"
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)/NYCAddress.rsc" /d "MIPS" /d "_MIPS_" /d\
 "PEGASUS" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NYCAddress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib libc.lib /nologo /pdb:none /machine:MIPS /subsystem:pegasus
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib libc.lib /nologo /pdb:none /machine:MIPS /subsystem:pegasus
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=commctrl.lib coredll.lib libc.lib /nologo\
 /entry:"WinMainCRTStartup" /base:"0x10000" /align:"4096" /pdb:none\
 /machine:MIPS /out:"$(OUTDIR)/NYCAddress.exe" /subsystem:pegasus 
LINK32_OBJS= \
	"$(INTDIR)/NYCAddress.obj" \
	"$(INTDIR)/NYCAddress.rsc"

"$(OUTDIR)\NYCAddress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY
PFILE_FLAGS=COPY 
PFILE_FILES= \
	"$(OUTDIR)/NYCAddress.exe"

"$(OUTDIR)\NYCAddress.trg" : "$(OUTDIR)" $(PFILE_FILES)
    $(PFILE) $(PFILE_FLAGS) ".\PMIPSRel\NYCAddress.exe"\
 "$(PFILE_DEST)PEG:NYCAddress.exe">"$(OUTDIR)\NYCAddress.trg"

DOWNLOAD : "$(OUTDIR)" $(PFILE_FILES)
    $(PFILE) $(PFILE_FLAGS) ".\PMIPSRel\NYCAddress.exe"\
 "$(PFILE_DEST)PEG:NYCAddress.exe">"$(OUTDIR)\NYCAddress.trg"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegMIPS) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "PMIPSDbg"
# PROP BASE Intermediate_Dir "PMIPSDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PMIPSDbg"
# PROP Intermediate_Dir "PMIPSDbg"
# PROP Target_Dir ""
OUTDIR=.\PMIPSDbg
INTDIR=.\PMIPSDbg

ALL : "$(OUTDIR)\NYCAddress.exe" "$(OUTDIR)\NYCAddress.trg"

CLEAN : 
	-@erase ".\PMIPSDbg\NYCAddress.trg"
	-@erase ".\PMIPSDbg\NYCAddress.exe"
	-@erase ".\PMIPSDbg\NYCAddress.rsc"
	-@erase ".\PMIPSDbg\NYCAddress.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=clmips.exe
# ADD BASE CPP /nologo /W3 /GX- /Z7 /Od /D "DEBUG" /D "MIPS" /D "_MIPS_" /D "PEGASUS" /D "UNICODE" /YX /QMRPeg /c
# ADD CPP /nologo /W3 /GX- /Z7 /Od /D "DEBUG" /D "MIPS" /D "_MIPS_" /D "PEGASUS" /D "UNICODE" /YX /QMRPeg /c
CPP_PROJ=/nologo /W3 /GX- /Z7 /Od /D "DEBUG" /D "MIPS" /D "_MIPS_" /D "PEGASUS"\
 /D "UNICODE" /Fp"$(INTDIR)/NYCAddress.pch" /YX /Fo"$(INTDIR)/" /QMRPeg /c 
CPP_OBJS=.\PMIPSDbg/
CPP_SBRS=

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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d "PEGASUS" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d "PEGASUS" /d "DEBUG"
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)/NYCAddress.rsc" /d "MIPS" /d "_MIPS_" /d\
 "PEGASUS" /d "DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NYCAddress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib libcd.lib /nologo /pdb:none /debug /machine:MIPS /subsystem:pegasus
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib libcd.lib /nologo /pdb:none /debug /machine:MIPS /subsystem:pegasus
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=commctrl.lib coredll.lib libcd.lib /nologo\
 /entry:"WinMainCRTStartup" /base:"0x10000" /align:"4096" /pdb:none /debug\
 /machine:MIPS /out:"$(OUTDIR)/NYCAddress.exe" /subsystem:pegasus 
LINK32_OBJS= \
	"$(INTDIR)/NYCAddress.obj" \
	"$(INTDIR)/NYCAddress.rsc"

"$(OUTDIR)\NYCAddress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY
PFILE_FLAGS=COPY 
PFILE_FILES= \
	"$(OUTDIR)/NYCAddress.exe"

"$(OUTDIR)\NYCAddress.trg" : "$(OUTDIR)" $(PFILE_FILES)
    $(PFILE) $(PFILE_FLAGS) ".\PMIPSDbg\NYCAddress.exe"\
 "$(PFILE_DEST)PEG:NYCAddress.exe">"$(OUTDIR)\NYCAddress.trg"

DOWNLOAD : "$(OUTDIR)" $(PFILE_FILES)
    $(PFILE) $(PFILE_FLAGS) ".\PMIPSDbg\NYCAddress.exe"\
 "$(PFILE_DEST)PEG:NYCAddress.exe">"$(OUTDIR)\NYCAddress.trg"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegSH) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "PegSHRel"
# PROP BASE Intermediate_Dir "PegSHRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PegSHRel"
# PROP Intermediate_Dir "PegSHRel"
# PROP Target_Dir ""
OUTDIR=.\PegSHRel
INTDIR=.\PegSHRel

ALL : "$(OUTDIR)\NYCAddress.exe" "$(OUTDIR)\NYCAddress.trg"

CLEAN : 
	-@erase ".\PegSHRel\NYCAddress.trg"
	-@erase ".\PegSHRel\NYCAddress.exe"
	-@erase ".\PegSHRel\NYCAddress.rsc"
	-@erase ".\PegSHRel\NYCAddress.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=shcl.exe
# ADD BASE CPP /nologo /W3 /GX- /O2 /D "NDEBUG" /D "SH3" /D "_SH3_" /D "PEGASUS" /D "UNICODE" /YX /c
# ADD CPP /nologo /W3 /GX- /O2 /D "NDEBUG" /D "SH3" /D "_SH3_" /D "PEGASUS" /D "UNICODE" /YX /c
CPP_PROJ=/nologo /W3 /GX- /O2 /D "NDEBUG" /D "SH3" /D "_SH3_" /D "PEGASUS" /D\
 "UNICODE" /Fp"$(INTDIR)/NYCAddress.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\PegSHRel/
CPP_SBRS=

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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "SH3" /d "_SH3_" /d "PEGASUS" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "SH3" /d "_SH3_" /d "PEGASUS" /d "NDEBUG"
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)/NYCAddress.rsc" /d "SH3" /d "_SH3_" /d\
 "PEGASUS" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NYCAddress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib libc.lib /nologo /pdb:none /machine:SH3 /subsystem:pegasus
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib libc.lib /nologo /pdb:none /machine:SH3 /subsystem:pegasus
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=commctrl.lib coredll.lib libc.lib /nologo\
 /entry:"WinMainCRTStartup" /base:"0x0c020000" /align:"4096" /pdb:none\
 /machine:SH3 /out:"$(OUTDIR)/NYCAddress.exe" /subsystem:pegasus 
LINK32_OBJS= \
	"$(INTDIR)/NYCAddress.obj" \
	"$(INTDIR)/NYCAddress.rsc"

"$(OUTDIR)\NYCAddress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY
PFILE_FLAGS=COPY 
PFILE_FILES= \
	"$(OUTDIR)/NYCAddress.exe"

"$(OUTDIR)\NYCAddress.trg" : "$(OUTDIR)" $(PFILE_FILES)
    $(PFILE) $(PFILE_FLAGS) ".\PegSHRel\NYCAddress.exe"\
 "$(PFILE_DEST)PEG:NYCAddress.exe">"$(OUTDIR)\NYCAddress.trg"

DOWNLOAD : "$(OUTDIR)" $(PFILE_FILES)
    $(PFILE) $(PFILE_FLAGS) ".\PegSHRel\NYCAddress.exe"\
 "$(PFILE_DEST)PEG:NYCAddress.exe">"$(OUTDIR)\NYCAddress.trg"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegSH) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "PegSHDbg"
# PROP BASE Intermediate_Dir "PegSHDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PegSHDbg"
# PROP Intermediate_Dir "PegSHDbg"
# PROP Target_Dir ""
OUTDIR=.\PegSHDbg
INTDIR=.\PegSHDbg

ALL : "$(OUTDIR)\NYCAddress.exe" "$(OUTDIR)\NYCAddress.trg"

CLEAN : 
	-@erase ".\PegSHDbg\NYCAddress.trg"
	-@erase ".\PegSHDbg\NYCAddress.exe"
	-@erase ".\PegSHDbg\NYCAddress.rsc"
	-@erase ".\PegSHDbg\NYCAddress.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=shcl.exe
# ADD BASE CPP /nologo /W3 /GX- /Z7 /Od /D "DEBUG" /D "SH3" /D "_SH3_" /D "PEGASUS" /D "UNICODE" /YX /c
# ADD CPP /nologo /W3 /GX- /Z7 /Od /D "DEBUG" /D "SH3" /D "_SH3_" /D "PEGASUS" /D "UNICODE" /YX /c
CPP_PROJ=/nologo /W3 /GX- /Z7 /Od /D "DEBUG" /D "SH3" /D "_SH3_" /D "PEGASUS"\
 /D "UNICODE" /Fp"$(INTDIR)/NYCAddress.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\PegSHDbg/
CPP_SBRS=

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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "SH3" /d "_SH3_" /d "PEGASUS" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "SH3" /d "_SH3_" /d "PEGASUS" /d "DEBUG"
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)/NYCAddress.rsc" /d "SH3" /d "_SH3_" /d\
 "PEGASUS" /d "DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NYCAddress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib libcd.lib /nologo /pdb:none /debug /machine:SH3 /subsystem:pegasus
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib libcd.lib /nologo /pdb:none /debug /machine:SH3 /subsystem:pegasus
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=commctrl.lib coredll.lib libcd.lib /nologo\
 /entry:"WinMainCRTStartup" /base:"0x0c020000" /align:"4096" /pdb:none /debug\
 /machine:SH3 /out:"$(OUTDIR)/NYCAddress.exe" /subsystem:pegasus 
LINK32_OBJS= \
	"$(INTDIR)/NYCAddress.obj" \
	"$(INTDIR)/NYCAddress.rsc"

"$(OUTDIR)\NYCAddress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY
PFILE_FLAGS=COPY 
PFILE_FILES= \
	"$(OUTDIR)/NYCAddress.exe"

"$(OUTDIR)\NYCAddress.trg" : "$(OUTDIR)" $(PFILE_FILES)
    $(PFILE) $(PFILE_FLAGS) ".\PegSHDbg\NYCAddress.exe"\
 "$(PFILE_DEST)PEG:NYCAddress.exe">"$(OUTDIR)\NYCAddress.trg"

DOWNLOAD : "$(OUTDIR)" $(PFILE_FILES)
    $(PFILE) $(PFILE_FLAGS) ".\PegSHDbg\NYCAddress.exe"\
 "$(PFILE_DEST)PEG:NYCAddress.exe">"$(OUTDIR)\NYCAddress.trg"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (x86em) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x86emRel"
# PROP BASE Intermediate_Dir "x86emRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86emRel"
# PROP Intermediate_Dir "x86emRel"
# PROP Target_Dir ""
OUTDIR=.\x86emRel
INTDIR=.\x86emRel

ALL : "$(OUTDIR)\NYCAddress.exe"

CLEAN : 
	-@erase ".\x86emRel\NYCAddress.exe"
	-@erase ".\x86emRel\NYCAddress.res"
	-@erase ".\x86emRel\NYCAddress.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX- /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "STRICT" /D "PEGASUS" /D "UNDER_NT" /D "TARGET_NT" /D "UNICODE" /D "_UNICODE" /D "_X86_" /YX /c
# ADD CPP /nologo /W3 /GX- /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "STRICT" /D "PEGASUS" /D "UNDER_NT" /D "TARGET_NT" /D "UNICODE" /D "_UNICODE" /D "_X86_" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX- /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "STRICT" /D "PEGASUS" /D "UNDER_NT" /D "TARGET_NT" /D "UNICODE" /D "_UNICODE"\
 /D "_X86_" /Fp"$(INTDIR)/NYCAddress.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\x86emRel/
CPP_SBRS=

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "PEGASUS" /d "UNDER_NT" /d "TARGET_NT" /d "NDEBUG"
# ADD RSC /l 0x409 /d "PEGASUS" /d "UNDER_NT" /d "TARGET_NT" /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NYCAddress.res" /d "PEGASUS" /d "UNDER_NT" /d\
 "TARGET_NT" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NYCAddress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib filesys.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 commctrl.lib filesys.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=commctrl.lib filesys.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/NYCAddress.pdb" /machine:I386 /out:"$(OUTDIR)/NYCAddress.exe" 
LINK32_OBJS= \
	"$(INTDIR)/NYCAddress.obj" \
	"$(INTDIR)/NYCAddress.res"

"$(OUTDIR)\NYCAddress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (x86em) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "x86emDbg"
# PROP BASE Intermediate_Dir "x86emDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86emDbg"
# PROP Intermediate_Dir "x86emDbg"
# PROP Target_Dir ""
OUTDIR=.\x86emDbg
INTDIR=.\x86emDbg

ALL : "$(OUTDIR)\NYCAddress.exe" "$(OUTDIR)\NYCAddress.bsc"

CLEAN : 
	-@erase ".\x86emDbg\NYCAddress.exe"
	-@erase ".\x86emDbg\NYCAddress.res"
	-@erase ".\x86emDbg\NYCAddress.obj"
	-@erase ".\x86emDbg\NYCAddress.ilk"
	-@erase ".\x86emDbg\NYCAddress.pdb"
	-@erase ".\x86emDbg\vc40.pdb"
	-@erase ".\x86emDbg\vc40.idb"
	-@erase ".\x86emDbg\NYCAddress.bsc"
	-@erase ".\x86emDbg\NYCAddress.sbr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX- /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "PEGASUS" /D "UNDER_NT" /D "TARGET_NT" /D "UNICODE" /D "_UNICODE" /D "_X86_" /YX /c
# ADD CPP /nologo /W3 /Gm /GX- /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "PEGASUS" /D "UNDER_NT" /D "TARGET_NT" /D "UNICODE" /D "_UNICODE" /D "_X86_" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX- /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "STRICT" /D "PEGASUS" /D "UNDER_NT" /D "TARGET_NT" /D "UNICODE" /D\
 "_UNICODE" /D "_X86_" /FR"$(INTDIR)/" /Fp"$(INTDIR)/NYCAddress.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\x86emDbg/
CPP_SBRS=.\x86emDbg/

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "PEGASUS" /d "UNDER_NT" /d "TARGET_NT" /d "_DEBUG"
# ADD RSC /l 0x409 /d "PEGASUS" /d "UNDER_NT" /d "TARGET_NT" /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NYCAddress.res" /d "PEGASUS" /d "UNDER_NT" /d\
 "TARGET_NT" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NYCAddress.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/NYCAddress.sbr"

"$(OUTDIR)\NYCAddress.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 commctrl.lib filesys.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 commctrl.lib filesys.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=commctrl.lib filesys.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/NYCAddress.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/NYCAddress.exe" 
LINK32_OBJS= \
	"$(INTDIR)/NYCAddress.obj" \
	"$(INTDIR)/NYCAddress.res"

"$(OUTDIR)\NYCAddress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "NYCAddress - Win32 (PegMIPS) Release"
# Name "NYCAddress - Win32 (PegMIPS) Debug"
# Name "NYCAddress - Win32 (PegSH) Release"
# Name "NYCAddress - Win32 (PegSH) Debug"
# Name "NYCAddress - Win32 (x86em) Release"
# Name "NYCAddress - Win32 (x86em) Debug"

!IF  "$(CFG)" == "NYCAddress - Win32 (PegMIPS) Release"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegMIPS) Debug"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegSH) Release"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegSH) Debug"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (x86em) Release"

!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (x86em) Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\NYCAddress.rc

!IF  "$(CFG)" == "NYCAddress - Win32 (PegMIPS) Release"


"$(INTDIR)\NYCAddress.rsc" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegMIPS) Debug"


"$(INTDIR)\NYCAddress.rsc" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegSH) Release"


"$(INTDIR)\NYCAddress.rsc" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegSH) Debug"


"$(INTDIR)\NYCAddress.rsc" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (x86em) Release"


"$(INTDIR)\NYCAddress.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/NYCAddress.res" /d "PEGASUS" /d "UNDER_NT" /d\
 "TARGET_NT" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (x86em) Debug"


"$(INTDIR)\NYCAddress.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/NYCAddress.res" /d "PEGASUS" /d "UNDER_NT" /d\
 "TARGET_NT" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NYCAddress.c

!IF  "$(CFG)" == "NYCAddress - Win32 (PegMIPS) Release"


"$(INTDIR)\NYCAddress.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegMIPS) Debug"


"$(INTDIR)\NYCAddress.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegSH) Release"


"$(INTDIR)\NYCAddress.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (PegSH) Debug"


"$(INTDIR)\NYCAddress.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (x86em) Release"


"$(INTDIR)\NYCAddress.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NYCAddress - Win32 (x86em) Debug"


"$(INTDIR)\NYCAddress.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\NYCAddress.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
