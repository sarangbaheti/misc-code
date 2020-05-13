//================================================
// Matt Pietrek
// Microsoft Systems Journal, March 1997
// FILE: CONSOLE_WM_TIMER2.CPP
// To build: "CL CONSOLE_WM_TIMER2.CPP USER32.LIB"
//================================================
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <conio.h>

// A do-nothing TIMERPROC.  Simply prints out the parameters
VOID CALLBACK MyTimerProc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );

int main()
{
    // Set up a 50 millisecond timer which calls MyTimerProc
    SetTimer( 0, 0, 0x50, (TIMERPROC)MyTimerProc );

    printf( "A timer proc has been set up.  Press any key to call "
            "GetMessage/DispatchMessage\n" );

    getch();    // Wait for user response.  This gives enough time for at
                // least one timer cycle to have elapsed

    MSG msg = { 0, 0, 0, 0 };

    // Get the message, and dispatch it.  This causes MyTimerProc to be
    // invoked.
    if ( GetMessage(&msg, 0, 0, 0) )
        DispatchMessage( &msg );
        
    return 0;
}

VOID CALLBACK MyTimerProc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
    printf( "In MyTimerProc: hwnd:%X  uMsg:%X  idEvent:%X  dwTime:%X\n",
            hwnd, uMsg, idEvent, dwTime );
}

