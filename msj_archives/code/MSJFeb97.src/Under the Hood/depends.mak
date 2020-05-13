PROJ = DEPENDS
OBJS = $(PROJ).OBJ memorymappedfile.obj exefile.obj peexe.obj \
        modulefileinfo.obj dependencylist.obj

CFLAGS = $(CFLAGS) /W3 /O1 /DWIN32_LEAN_AND_MEAN /Fd"$(PROJ).PDB"
LIBS = libctiny.lib user32.lib version.lib

!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) /YX  /Fp"$(PROJ).PCH" /D_DEBUG /Zi
LFLAGS = $(LFLAGS) /SUBSYSTEM:console /DEBUG /DEBUGTYPE:CV 
!else
CFLAGS = $(CFLAGS) /DNDEBUG
!endif

$(PROJ).EXE: $(OBJS)
    echo >NUL @<<$(PROJ).CRF
$(LFLAGS) $(OBJS) -OUT:$(PROJ).EXE $(LIBS)
<<
    link @$(PROJ).CRF

.cpp.obj:
    CL $(CFLAGS) /c $<

# $(PROJ).RES: $(PROJ).RC
#  RC -r $(PROJ).RC
