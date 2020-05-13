//================================================
// Matt Pietrek
// Microsoft Systems Journal, March 1997
// FILE: WM_TIMER_TOAST.CPP
// To build: "CL WM_TIMER_TOAST.CPP USER32.LIB"
//================================================
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main()
{
    // Get the HWND of the tray, which is owned by the Explorer process
    HWND hWndToToast = FindWindow( "Shell_TrayWnd", 0 );

    if ( hWndToToast )
    {
        // Post the deadly WM_TIMER message.
        PostMessage( hWndToToast, WM_TIMER, 123, 0x87654321 );
    }

    return 0;
}

