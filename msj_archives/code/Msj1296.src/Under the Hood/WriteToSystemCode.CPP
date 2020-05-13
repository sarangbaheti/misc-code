//=========================================
// WriteToSystemCode - Matt Pietrek 1996
// Microsoft Systems Journal, December 1996
// FILE: WriteToSystemCode.CPP
// To compile: "CL WriteToSystemCode.CPP"
//=======================================
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

void OutputPageProtection( DWORD flags );

int main()
{
    // Assign 'p' to the address of the CreateProcessA function in KERNEL32.DLL
    PBYTE p = (PBYTE)GetProcAddress( GetModuleHandle("KERNEL32.DLL"),
                                     "CreateProcessA" );
    if ( !p )
    {
        printf( "Oops! CreateProcessA not found\n" );
        return 0;
    }

    printf( "CreateProcessA is at address 0x%08X\n", p );

    BYTE c = *p;    // Read the first byte of the CreateProcess function
                    // No fault here means that the page is at least readable

    //
    // Now, let's change the protection of the page with VirtualProtect and
    // try to write to the page.  First, we'll declare some variables
    //
    MEMORY_BASIC_INFORMATION mbi;
    DWORD newFlags, oldFlags;   // Original and modified PAGE_xxx flags
    DWORD dwScratch;            // throwaway DWORD that VirtualProtect needs

    // Next, use VirtualQuery to get the original protection attributes
    VirtualQuery( p, &mbi, sizeof(mbi) );
    newFlags = oldFlags = mbi.Protect;

    OutputPageProtection( oldFlags );

    // Tweak the protection attributes to something that should be writeable
    newFlags &= ~PAGE_READONLY;     // Turn off READONLY flag if set
    newFlags &= ~PAGE_EXECUTE_READ; // Turn off EXECUTE_READ flag if set
    newFlags |= PAGE_READWRITE;     // Turn on readwrite flag

    // Modify the page's protection attributes (hopefully!) with VirtualProtect
    if ( !VirtualProtect( p, 1, newFlags, &dwScratch ) )
    {
        printf( "Oops! VirtualProtect didn't work - plunging ahead\n" );
    }

    //
    // The moment of truth: Can we write to the page?  Just in case, we'll
    // use a __try/__except block
    //

    BOOL fFaulted = FALSE;

    __try
    {
        *p = c;     // Write back the first byte of the CreateProcess function
    }               // and see if a fault occurs
    __except( 1 )
    {
        fFaulted = TRUE;
    }

    if ( fFaulted )
        printf( "The page was not written successfully\n" );
    else
        printf( "The page was written successfully\n" );

    // Put everything back to the way we found it.
    VirtualProtect( p, 1, oldFlags, &dwScratch);

    return 0;
}

void OutputPageProtection( DWORD flags )
{
    printf( "PAGE_xxx flags are: %08X ", flags );

    if ( flags & PAGE_NOACCESS ) printf( "PAGE_NOACCESS " );
    if ( flags & PAGE_READONLY ) printf( "PAGE_READONLY " );
    if ( flags & PAGE_READWRITE ) printf( "PAGE_READWRITE " );
    if ( flags & PAGE_WRITECOPY ) printf( "PAGE_WRITECOPY " );
    if ( flags & PAGE_EXECUTE ) printf( "PAGE_EXECUTE " );
    if ( flags & PAGE_EXECUTE_READ ) printf( "PAGE_EXECUTE_READ " );
    if ( flags & PAGE_EXECUTE_READWRITE ) printf( "PAGE_EXECUTE_READWRITE " );
    if ( flags & PAGE_EXECUTE_WRITECOPY ) printf( "PAGE_EXECUTE_WRITECOPY " );
    if ( flags & PAGE_GUARD ) printf( "PAGE_GUARD " );
    if ( flags & PAGE_NOCACHE ) printf( "PAGE_NOCACHE " );

    printf( "\n" );
}

