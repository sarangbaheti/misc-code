#include <windows.h>
#include <malloc.h>

void * __cdecl malloc(size_t size)
{
    return HeapAlloc( GetProcessHeap(), 0, size );
}

void __cdecl free(void * p)
{
    HeapFree( GetProcessHeap(), 0, p );
}
