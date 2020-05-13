@echo off
rem WDMBUILD ddkpath driverpath checked/free [args]
call %1\bin\setenv %1 %3
cd %2
build -b -w %4 %5 %6 %7 %8 %9
