PROJ = MSJTESTEXC
OBJS = $(PROJ).OBJ MSJEXHND.OBJ

# We turn on /Zi so that there's alway debug information generated
# We also turn on /O1 to force optimizations (and hence, no stack frames)
CFLAGS = $(CFLAGS) /O1 /Zi /W3 /DWIN32_LEAN_AND_MEAN /Fd"$(PROJ).PDB"

# We turn on /DEBUG /DEBUGTYPE:CV /PDB:NONE so that debug info
# is generated in the EXE.  We can strip this off into a
# separate file with REBASE.EXE
LFLAGS = /SUBSYSTEM:console /DEBUG /DEBUGTYPE:CV /PDB:NONE
LIBS = user32.lib imagehlp.lib


!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) /YX /Fp"$(PROJ).PCH" /D_DEBUG
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
