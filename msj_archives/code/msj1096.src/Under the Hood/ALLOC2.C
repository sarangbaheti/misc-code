#include <windows.h>
#include <malloc.h>

void * __cdecl realloc(void * p, size_t size)
{
    if ( p )
        return HeapReAlloc( GetProcessHeap(), 0, p, size );
    else    // 'p' is 0, and HeapReAlloc doesn't act like realloc() here
        return HeapAlloc( GetProcessHeap(), 0, size );
}

void * __cdecl calloc(size_t nitems, size_t size)
{
    return HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, nitems * size );
}
