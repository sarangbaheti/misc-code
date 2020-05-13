#==================================================
# TINYCRT - Matt Pietrek 1996
# Microsoft Systems Journal, October 1996
# FILE: TINYCRT.MS - Makefile for Microsoft version
#==================================================
PROJ = LIBCTINY

OBJS =  CRT0TCON.OBJ CRT0TWIN.OBJ ARGCARGV.OBJ PRINTF.OBJ SPRINTF.OBJ PUTS.OBJ \
        ALLOC.OBJ ALLOC2.OBJ ALLOCSUP.OBJ STRUPLWR.OBJ ISCTYPE.OBJ ATOL.OBJ \
        STRICMP.OBJ NEWDEL.OBJ

CC = CL
CC_OPTIONS = /c /W3 /DWIN32_LEAN_AND_MEAN

!ifdef DEBUG
CC_OPTIONS = $(CC_OPTIONS) /YX /Zi
!else
CC_OPTIONS = $(CC_OPTIONS) /O1
!endif

$(PROJ).LIB: $(OBJS)
    LIB /OUT:$(PROJ).LIB $(OBJS)

.C.OBJ:
    $(CC) $(CC_OPTIONS) $<

.CPP.OBJ:
    $(CC) $(CC_OPTIONS) $<
    