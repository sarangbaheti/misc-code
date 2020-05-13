#include <windows.h>
#include <malloc.h>

void * __cdecl _malloc_lk(size_t size)
{
    return HeapAlloc( GetProcessHeap(), 0, size );
}

void * __cdecl _nh_malloc(size_t size, int nhFlag)
{
    return HeapAlloc( GetProcessHeap(), 0, size );
}

void __cdecl _free_lk(void * p)
{
    HeapFree( GetProcessHeap(), 0, p );
}

size_t __cdecl _msize(void * p)
{
    return HeapSize( GetProcessHeap(), 0, p );
}

size_t __cdecl _msize_lk(void * p)
{
    return HeapSize( GetProcessHeap(), 0, p );
}


