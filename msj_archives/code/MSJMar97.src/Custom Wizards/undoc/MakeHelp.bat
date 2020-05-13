@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by UNDOC.HPJ. >hlp\undoc.hm
echo. >>hlp\undoc.hm
echo // Dialogs (IDD_*) >>hlp\undoc.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\undoc.hm
echo. >>hlp\undoc.hm

REM -- Make help for Project UNDOC

call hc31 undoc.hpj
if exist windebug copy undoc.hlp windebug
if exist winrel copy undoc.hlp winrel
