#include <windows.h>
#include <stdio.h>

int __cdecl puts(const char * s)
{
    DWORD cbWritten;
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

    WriteFile( hStdOut, s, lstrlen(s), &cbWritten, 0 );
    WriteFile( hStdOut, "\r\n", 2, &cbWritten, 0 );

    return (int)(cbWritten ? cbWritten : EOF);
}

