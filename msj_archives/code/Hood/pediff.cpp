//==========================================
// Matt Pietrek
// Microsoft Systems Journal, November 1997
// FILE: PEDIFF.CPP
//==========================================
#include <windows.h>
#include <imagehlp.h>
#include <stdio.h>
#include <malloc.h>
#include "PEExportList.h"

//=============================== Global Variables ============================
char g_szHelpText[] = 
"Syntax: PEDIFF file1 [file2]\n\n" 
"If only one file is specified, it is assumed to be a comparison file to a \n"
"similarly named file in the current directory.\n\n"
"For example: PEDUMP C:\\WINNT\\SYSTEM32\\KERNEL32.DLL will compare that file\n"
"to the KERNEL32.DLL in the current directory.\n";

PSTR pszFile1 = 0;
PSTR pszFile2 = 0;

//==================================== Code ===================================

#define MY_PROCESS_HANDLE 0

BOOL LoadExportInfo( char * pszFilename, PEExportList * pExportList )
{
    LOADED_IMAGE li;
    
    if ( !MapAndLoad( pszFilename, "", &li, TRUE, TRUE ) )
    {
        printf( "Unable to locate or load %s\n", pszFilename );
        return FALSE;
    }

    PIMAGE_EXPORT_DIRECTORY pExpDir;

    pExpDir = (PIMAGE_EXPORT_DIRECTORY)(li.FileHeader->OptionalHeader.
                DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

    if ( !pExpDir )
    {
        printf( "No Exports\n" );
        return FALSE;
    }

    pExpDir = (PIMAGE_EXPORT_DIRECTORY)ImageRvaToVa(
                    li.FileHeader, li.MappedAddress, (DWORD)pExpDir, 0 );

    PDWORD * pExpNames = pExpDir->AddressOfNames;
    pExpNames = (PDWORD *)ImageRvaToVa(
                    li.FileHeader, li.MappedAddress, (DWORD)pExpNames, 0 );
    
    for ( unsigned i=0; i < pExpDir->NumberOfNames; i++ )
    {
        PSTR p = (PSTR)ImageRvaToVa(
                    li.FileHeader, li.MappedAddress, (DWORD)*pExpNames, 0 );
                    
        pExportList->AddSymbol( p );
        
        pExpNames++;
    }
        

    //
    // In case the DLL exports any APIs by ordinal only, we need to
    // synthesize a name (e.g., "ordinal_102", and add it to the list
    //
    if ( pExpDir->NumberOfNames < pExpDir->NumberOfFunctions )
    {
        // First, get a pointer to the AddressOfNameOrdinals array
        PWORD pNameOrdinals = (PWORD)ImageRvaToVa(
                        li.FileHeader, li.MappedAddress,
                        (DWORD)pExpDir->AddressOfNameOrdinals, 0 );

        // Nextt, get a pointer to the AddressOfFunctions array
        PDWORD pFunctions = (PDWORD)ImageRvaToVa(
                        li.FileHeader, li.MappedAddress,
                        (DWORD)pExpDir->AddressOfFunctions, 0 );

        DWORD cNamedOrdinals = pExpDir->NumberOfNames;
        DWORD cFunctions = pExpDir->NumberOfFunctions;
        
        // Allocate memory for an array of BYTEs, each BYTE indicating if
        // a function is exported by name.  Initially, all entries are set to
        // 0, meaning they're exported by ordinal
        PBYTE pNamedFuncs = (PBYTE)calloc( cFunctions, sizeof(BYTE) );
        
        // Iterate through the NamedOrdinals array, and for each ordinal,
        // set the corresponding entry in the pNamedFunctions array to 1
        // (meaning "exported by name"
        PWORD pCurrOrd = pNameOrdinals;
        for ( unsigned i = 0; i < cNamedOrdinals; i++, pCurrOrd++ )
            pNamedFuncs[ *pCurrOrd ] = 1;

        // Finally, iterate through the pNamedFunctions array.  For each
        // function, check if it's named, or if its address is 0.  If neither
        // is true, the function is exported by ordinal only, so synthesize
        // a name and add it to the PEExportList
        for ( i = 0; i < cFunctions; i++ )
        {
            if ( pNamedFuncs[i] )   // If marked, it's a named export
                continue;

            if ( 0 == pFunctions[i] )   // If the address is 0, it's not
                continue;               // a blank (non-exported) function
                
            char szMadeUpName[64];
            
            wsprintf( szMadeUpName, "ordinal_%u", pExpDir->Base + i );
    
            pExportList->AddSymbol( szMadeUpName );
        }
                        
        free( pNamedFuncs );    // Free our allocated buffer
    }
                    
    UnMapAndLoad( &li );  // Close the PE file and debug info mapping
    
    return TRUE;
}

BOOL ProcessCommandLine( int argc, char *argv[] )
{
    if ( (argc < 2) || (argc > 3) )
        return FALSE;

    pszFile1 = argv[1];         // First real argument is first filename
    
    if ( 3 == argc )            // If 2 real arguments, second arg is the
    {                           // the second filename
        pszFile2 = argv[2];
        return TRUE;        
    }

    // If we get here, only one filename was specified.  It should contain
    // a path.  Therefore, we should be able to point pszFile2 to the
    // character after the final blackslash, and be done with it.

    pszFile2 = strrchr( pszFile1, '\\' );
    
    if ( !pszFile2 )        // Hmmm... No blackslash.. Something's not right.
        return FALSE;
        
    pszFile2++;             // Increment past the backslash to the filename
                    
    return TRUE;
}

int main( int argc, char * argv[] )
{   
    if ( !ProcessCommandLine( argc, argv ) )
    {
        printf( g_szHelpText );
                
        return 0;
    }
    
    PEExportList file1;

    if ( !LoadExportInfo( pszFile1, &file1 ) )
        return 1;
            
    PEExportList file2;
    
    if ( !LoadExportInfo( pszFile2, &file2 ) )
        return 1;


    ExportedSymbolInfo * pCurrent = 0;
    
    while ( pCurrent = file1.GetNextSymbol(pCurrent) )
    {
        ExportedSymbolInfo * pMatch = file2.LookupSymbol( pCurrent->m_pszName );
        
        if ( pMatch )
        {
            pCurrent->m_flags |= EXPSYMINFO_MATCH;
            pMatch->m_flags   |= EXPSYMINFO_MATCH;
        }       
    }
    
    printf( "File: %s\n", pszFile1 );
    
    pCurrent = 0;
    
    while ( pCurrent = file1.GetNextSymbol(pCurrent) )
    {
        if ( 0 == pCurrent->m_flags & EXPSYMINFO_MATCH )
        {
            printf( "  %s\n", pCurrent->m_pszName );
        }       
    }

    printf( "File: %s\n", pszFile2 );
    
    pCurrent = 0;
    
    while ( pCurrent = file2.GetNextSymbol(pCurrent) )
    {
        if ( 0 == pCurrent->m_flags & EXPSYMINFO_MATCH )
        {
            printf( "  %s\n", pCurrent->m_pszName );
        }       
    }
            
    return 0;
}
