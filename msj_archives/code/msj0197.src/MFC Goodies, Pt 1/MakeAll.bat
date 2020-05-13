@echo off
set CFG=dibview - Win32 DebugMDI
nmake -f dibview.mak %1 %2 %3
set CFG=dibview - Win32 DebugSDI
nmake -f dibview.mak %1 %2 %3
