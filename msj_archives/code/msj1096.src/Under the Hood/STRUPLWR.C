#include <windows.h>
#include <string.h>

#ifndef __BORLANDC__
// Force the linker to include USER32.LIB
#pragma comment(linker, "/defaultlib:user32.lib")
#endif

char *  __cdecl strupr(char *s)
{
    CharUpperBuff( s, lstrlen(s) );
    return s;
}

char *  __cdecl strlwr(char *s)
{
    CharLowerBuff( s, lstrlen(s) );
    return s;
}
