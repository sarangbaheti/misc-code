//==========================================
// Matt Pietrek
// Microsoft Systems Journal, December 1997
// FILE: AnsiUniTiming.CPP
// To compile: CL /O2 AnsiUniTiming.CPP
//==========================================
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

#define LOOP_ITERATIONS 50000

int main()
{
    LARGE_INTEGER tBefore, tAfter, i64PerfFrequency;
    float tAnsi, tUnicode;
    char szAnsiBuffer[ MAX_PATH ];
    WCHAR wszUnicodeBuffer[ MAX_PATH ];
    unsigned i;

    // Figure out how often the performance counter increments
    QueryPerformanceFrequency( &i64PerfFrequency );

    // Set this thread's priority as high as reasonably possible to prevent
    // timeslice interruptions
    SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL );
    
    // ======================== ANSI Portion =================================

    Sleep( 0 ); // Try to start on a fresh timeslice

    // Get performance counter before the ANSI API loop
    QueryPerformanceCounter( &tBefore );

    // ANSI API loop    
    for ( i = 0; i < LOOP_ITERATIONS; i++ )
    {
        HMODULE hMod = GetModuleHandleA( "KERNEL32.DLL" );

        GetModuleFileNameA( hMod, szAnsiBuffer, sizeof(szAnsiBuffer) );
        
        GetCurrentDirectoryA( sizeof(szAnsiBuffer), szAnsiBuffer );
    }

    // Get performance counter after the ANSI API loop
    QueryPerformanceCounter( &tAfter );

    // "QuadPart" is a 64 bit integer (__int64).  VC++ supports them!
    tAnsi = tAfter.QuadPart - tBefore.QuadPart;
    tAnsi = tAnsi / i64PerfFrequency.QuadPart;
            
    printf( "ANSI version took %.4f seconds\n", tAnsi );

    // ====================== Unicode Portion =================================

    Sleep( 0 ); // Try to start on a fresh timeslice
        
    // Get performance counter before the unicode API loop
    QueryPerformanceCounter( &tBefore );
    
    // unicode API loop 
    for ( i = 0; i < LOOP_ITERATIONS; i++ )
    {
        HMODULE hMod = GetModuleHandleW( L"KERNEL32.DLL" );

        GetModuleFileNameW( hMod, wszUnicodeBuffer, sizeof(wszUnicodeBuffer) );
        
        GetCurrentDirectoryW( sizeof(wszUnicodeBuffer), wszUnicodeBuffer );
    }

    // Get performance counter after the unicode API loop
    QueryPerformanceCounter( &tAfter );

    tUnicode = tAfter.QuadPart - tBefore.QuadPart;
    tUnicode = tUnicode / i64PerfFrequency.QuadPart;
            
    printf( "Unicode version took %.4f seconds", tUnicode );
            
    return 0;
}
