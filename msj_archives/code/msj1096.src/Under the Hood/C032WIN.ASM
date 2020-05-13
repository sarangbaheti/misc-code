; Hook up Borland C++ GUI app entry point to CRT0TWIN.C
.386
.model flat

extrn _WinMainCRTStartup : proc

.code
asm_startup:
    JMP _WinMainCRTStartup
end asm_startup
