// 1996 - John Robbins, with Matt Pietrek
#include <stdlib.h>
#include <ctype.h>

long __cdecl atol ( const char * pstr )
{
    // The current character.
    int  cCurr ;
    // The running total.
    long lTotal ;
    // Holds the '-' sign.
    int  iIsNeg ;

    // Slide past any whitespace.
    while ( isspace ( *pstr ) )
    {
        ++pstr ;
    }

    // Get the current character.
    cCurr = *pstr++ ;
    // Save the negative sign.
    iIsNeg = cCurr ;
    if ( ( '-' == cCurr ) || ( '+' == cCurr ) )
    {
        // We have a sign, so skip it.
        cCurr = *pstr++ ;
    }

    // Initialize the total.
    lTotal = 0 ;

    // While we have digits, addem up.
    while ( isdigit ( cCurr ) )
    {
        // Add this digit to the total.
        lTotal = 10 * lTotal + ( cCurr - '0' ) ;
        // Do the next character.
        cCurr = *pstr++ ;
    }

    // If we have a negative sign, convert the value.
    if ( '-' == iIsNeg )
    {
        return ( -lTotal ) ;
    }
    else
    {
        return ( lTotal ) ;
    }
}

#ifdef __BORLANDC__
#undef atoi // Really... This is what the Borland RTL code does too!
#endif

int __cdecl atoi ( const char * pstr )
{
    return ( (int)atol ( pstr ) ) ;
}

