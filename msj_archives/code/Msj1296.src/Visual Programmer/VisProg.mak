# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Java Virtual Machine Java Workspace" 0x0809

!IF "$(CFG)" == ""
CFG=VisProg - Java Virtual Machine Debug
!MESSAGE No configuration specified.  Defaulting to VisProg - Java Virtual\
 Machine Debug.
!ENDIF 

!IF "$(CFG)" != "VisProg - Java Virtual Machine Release" && "$(CFG)" !=\
 "VisProg - Java Virtual Machine Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "VisProg.mak" CFG="VisProg - Java Virtual Machine Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisProg - Java Virtual Machine Release" (based on\
 "Java Virtual Machine Java Workspace")
!MESSAGE "VisProg - Java Virtual Machine Debug" (based on\
 "Java Virtual Machine Java Workspace")
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
# PROP Target_Last_Scanned "VisProg - Java Virtual Machine Debug"
JAVA=jvc.exe

!IF  "$(CFG)" == "VisProg - Java Virtual Machine Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\VisProg.class"

CLEAN : 
	-@erase "$(INTDIR)\VisProg.class"

# ADD BASE JAVA /O
# ADD JAVA /O

!ELSEIF  "$(CFG)" == "VisProg - Java Virtual Machine Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\VisProg.class"

CLEAN : 
	-@erase "$(INTDIR)\VisProg.class"

# ADD BASE JAVA /g
# ADD JAVA /g

!ENDIF 

################################################################################
# Begin Target

# Name "VisProg - Java Virtual Machine Release"
# Name "VisProg - Java Virtual Machine Debug"

!IF  "$(CFG)" == "VisProg - Java Virtual Machine Release"

!ELSEIF  "$(CFG)" == "VisProg - Java Virtual Machine Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\vpview.htm

!IF  "$(CFG)" == "VisProg - Java Virtual Machine Release"

!ELSEIF  "$(CFG)" == "VisProg - Java Virtual Machine Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VisProg.htm

!IF  "$(CFG)" == "VisProg - Java Virtual Machine Release"

!ELSEIF  "$(CFG)" == "VisProg - Java Virtual Machine Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VisProg.java

!IF  "$(CFG)" == "VisProg - Java Virtual Machine Release"


"$(INTDIR)\VisProg.class" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VisProg - Java Virtual Machine Debug"


"$(INTDIR)\VisProg.class" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vptop.htm

!IF  "$(CFG)" == "VisProg - Java Virtual Machine Release"

!ELSEIF  "$(CFG)" == "VisProg - Java Virtual Machine Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\blank.htm

!IF  "$(CFG)" == "VisProg - Java Virtual Machine Release"

!ELSEIF  "$(CFG)" == "VisProg - Java Virtual Machine Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
