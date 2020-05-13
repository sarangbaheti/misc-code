PROJ = MSJTESTEXC
OBJS = $(PROJ).OBJ MSJEXHND.OBJ

CFLAGS = $(CFLAGS) /W3 /DWIN32_LEAN_AND_MEAN /Fd"$(PROJ).PDB"
LFLAGS = /SUBSYSTEM:console
LIBS = user32.lib imagehlp.lib


!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) /YX /Fp"$(PROJ).PCH" /D_DEBUG /Zi
LFLAGS = $(LFLAGS) /DEBUG /DEBUGTYPE:CV 
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
