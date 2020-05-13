#include <windows.h>
#include <stdio.h>

#define EOF     (-1)

#ifndef __BORLANDC__
// Force the linker to include USER32.LIB
#pragma comment(linker, "/defaultlib:user32.lib")
#endif

int __cdecl sprintf(char *buffer, const char * format, ...)
{
    int retValue;
    va_list argptr;
          
    va_start( argptr, format );
    retValue = wvsprintf( buffer, format, argptr );
    va_end( argptr );

    return retValue;
}
