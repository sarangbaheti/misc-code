#include <windows.h>
#include <string.h>

int __cdecl _strcmpi(const char *s1, const char *s2)
{
    return lstrcmpi( s1, s2 );
}

int __cdecl _stricmp(const char *s1, const char *s2)
{
    return lstrcmpi( s1, s2 );
}
