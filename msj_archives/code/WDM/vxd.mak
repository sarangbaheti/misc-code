all: MYVXD.VXD

.asm.obj:
   ml -coff -DBLD_COFF -DIS_32 -W2 -c -Cx -DMASM6 -Zi -DDEBUG $*.asm

.c.obj:
   cl -c -Gs -Zipl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.c

.cpp.obj:
   cl -c -Gs -Zipl -Odb2 -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.cpp

OBJECTS = DevCtrl.obj myvxd.obj

myvxd.obj: $*.c $*.h stdvxd.h

MYVXD.VXD: $*.def $(OBJECTS)
   link @<<
-machine:i386 -def:$*.def -out:$@
-debug -debugtype:cv
-merge:.CRT=_IDATA -merge:.xdata=_LDATA
-map:$*.map -vxd vxdwraps.clb -nodefaultlib
$(OBJECTS)
<<
   c:\winice95\nmsym /translate:source,package,always $@
