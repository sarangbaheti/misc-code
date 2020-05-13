//=============================================================================
// Matt Pietrek
// Microsoft Systems Journal, November 1997
// FILE: ScheduledTasks.CPP
// To compile: CL </DUNICODE=1 /D_UNICODE=1> SystemMetricParams.CPP user32.lib
//=============================================================================
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define WIDTH 40
#define DISPLAY_SM( x ) _tprintf(   _T("%-*s%u\n"), WIDTH, \
                                    _T(#x), GetSystemMetrics(x) );

#define DISPLAY_SPI( x )    dwValue = 0xBAADF00D;                           \
                            SystemParametersInfo( x, 0, &dwValue, 0 );      \
                            _tprintf(   _T("%-*s%u\n"), WIDTH, _T(#x), dwValue);
int main()
{
    DISPLAY_SM( SM_XVIRTUALSCREEN )
    DISPLAY_SM( SM_YVIRTUALSCREEN )
    DISPLAY_SM( SM_CXVIRTUALSCREEN )
    DISPLAY_SM( SM_CYVIRTUALSCREEN )
    DISPLAY_SM( SM_CMONITORS )
    DISPLAY_SM( SM_SAMEDISPLAYFORMAT )

    _tprintf( _T("\n") );   // separator
    
    DWORD dwValue;
    
    DISPLAY_SPI( SPI_GETMOUSESPEED )
    DISPLAY_SPI( SPI_GETSCREENSAVERRUNNING )
    DISPLAY_SPI( SPI_GETACTIVEWINDOWTRACKING )
    DISPLAY_SPI( SPI_GETMENUANIMATION )
    DISPLAY_SPI( SPI_GETCOMBOBOXANIMATION )
    DISPLAY_SPI( SPI_GETLISTBOXSMOOTHSCROLLING )
    DISPLAY_SPI( SPI_GETGRADIENTCAPTIONS )
    DISPLAY_SPI( SPI_GETMENUUNDERLINES )
    DISPLAY_SPI( SPI_GETACTIVEWNDTRKZORDER )
    DISPLAY_SPI( SPI_GETHOTTRACKING )
    DISPLAY_SPI( SPI_GETFOREGROUNDLOCKTIMEOUT )
    
    return 0;
}
