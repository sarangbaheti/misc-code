PROJ = PEDIFF

OBJS = $(PROJ).OBJ PEExportList.OBJ

CFLAGS = $(CFLAGS) /W3 /DWIN32_LEAN_AND_MEAN /Fd"$(PROJ).PDB"
LFLAGS =  /FIXED

# LIBCTINY.LIB (& USER32.LIB) can be removed if necessary.  They're used to
# keep the program size as small as possible.  LIBCTINY is a stripped down
# version of the C++ runtime library from the October 1996 column.
LIBS = libctiny.lib user32.lib imagehlp.lib

!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) /YX  /Fp"$(PROJ).PCH" /D_DEBUG /Zi
LFLAGS = $(LFLAGS) /SUBSYSTEM:console /DEBUG /DEBUGTYPE:CV 
!else
CFLAGS = $(CFLAGS) /O1 /DNDEBUG
LFLAGS = $(LFLAGS) /MERGE:.idata=.text
!endif

$(PROJ).EXE: $(OBJS)
    echo >NUL @<<$(PROJ).CRF
$(LFLAGS) $(OBJS) -OUT:$(PROJ).EXE $(LIBS)
<<
    link @$(PROJ).CRF

.cpp.obj:
    CL $(CFLAGS) /c $<
