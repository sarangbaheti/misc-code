; Hook up Borland C++ console app entry point to CRT0TCON.C
.386
.model flat

extrn _mainCRTStartup : proc

.code
asm_startup:
    JMP _mainCRTStartup
public __setargv__
__setargv__:
end asm_startup
