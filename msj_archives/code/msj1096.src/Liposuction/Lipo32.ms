#
# LIPO32 / LIPOSUCTION32 makefile for Microsoft Visual C++ 4.1
#
!ifdef HARDCORE
# command line version
PROJ = LIPO32
LFLAGS = /SUBSYSTEM:console
CFLAGS = /DCMDLINE
OBJS = CMDLINEUI.OBJ
!else
# GUI version
PROJ = LIPOSUCTION32
RSRC = LIPOGUI
OBJS = LIPOGUI.OBJ $(RSRC).RES
LIBS = USER32.LIB SHELL32.LIB
LFLAGS = /SUBSYSTEM:windows,4
!endif

OBJS =  $(OBJS) MemoryMappedFile.OBJ EXEFILE.OBJ PEEXE.OBJ PEEXE2.OBJ \
		PESection.OBJ LIPO32.OBJ DependencyList.OBJ

CFLAGS = $(CFLAGS) /W3 /DWIN32_LEAN_AND_MEAN /YX \
        /Fd"$(PROJ).PDB" /Fp"$(PROJ).PCH"

!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) /D_DEBUG /Zi
LFLAGS = $(LFLAGS) /DEBUG /DEBUGTYPE:CV 
!else
CFLAGS = $(CFLAGS) /O1 /DNDEBUG
!endif

LIBS = $(LIBS) kernel32.lib USER32.LIB
LFLAGS = $(LFLAGS) /FIXED

$(PROJ).EXE: $(OBJS)
    echo >NUL @<<$(PROJ).CRF
$(LFLAGS) $(OBJS) -OUT:$(PROJ).EXE $(LIBS)
<<
    link @$(PROJ).CRF

.cpp.obj:
    CL $(CFLAGS) /c $<

$(RSRC).RES: $(RSRC).RC
  RC -r $(RSRC).RC
