// 1996 - John Robbins, with Matt Pietrek
#include <ctype.h>

int __cdecl _isctype ( int c , int mask )
{
    /* c valid between -1 and 255 */
    if (((unsigned)(c + 1)) <= 256)
    {
        return ( _pctype[c] & mask ) ;
    }
    else
        return 0;
}
