# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=simple - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to simple - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "simple - Win32 Release" && "$(CFG)" != "simple - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "simple.mak" CFG="simple - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "simple - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "simple - Win32 Debug" (based on "Win32 (x86) External Target")
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
# PROP Target_Last_Scanned "simple - Win32 Debug"

!IF  "$(CFG)" == "simple - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f simple.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "simple.exe"
# PROP BASE Bsc_Name "simple.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "wdmbuild c:\wdmddk c:\wdmddk\src\simple free"
# PROP Rebuild_Opt "-nmake /a"
# PROP Target_File "simple.sys"
# PROP Bsc_Name "simple.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "simple - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f simple.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "simple.exe"
# PROP BASE Bsc_Name "simple.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "wdmbuild d:\wdmddk d:\wdmddk\src\simple checked"
# PROP Rebuild_Opt "-nmake /a"
# PROP Target_File "simple.sys"
# PROP Bsc_Name "simple.bsc"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ENDIF 

################################################################################
# Begin Target

# Name "simple - Win32 Release"
# Name "simple - Win32 Debug"

!IF  "$(CFG)" == "simple - Win32 Release"

".\simple.sys" : 
   CD D:\Wdmddk\Src\Simple
   wdmbuild c:\wdmddk c:\wdmddk\src\simple free

!ELSEIF  "$(CFG)" == "simple - Win32 Debug"

".\simple.sys" : 
   CD D:\Wdmddk\Src\Simple
   wdmbuild d:\wdmddk d:\wdmddk\src\simple checked

!ENDIF 

# End Target
# End Project
################################################################################
