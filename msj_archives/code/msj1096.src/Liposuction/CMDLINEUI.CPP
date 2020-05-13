//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: CMDLINEUI.CPP
//==========================================
#include <windows.h>
#include <stdio.h>
#pragma hdrstop
#include "lipo32output.h"

void AnalyzeFile( PSTR );

int main( int argc, char *argv[] )
{
	printf( "LIPO32 - Matt Pietrek, 1996 for MSJ\n" );
	if ( argc != 2 )
	{
		printf( "Syntax: LIPO32 <filename>\n"
                "  LIPO32 looks for inefficiencies in PE files\n" );
		return 0;
	}
	
	AnalyzeFile( argv[1] );
	
	return 0;
}

void OutputClearAllFields( void )
{
	// do nothing for command line UI
}

void OutputSetFileName( PSTR pszFileName )
{
	printf( "Report for %s\n", pszFileName );
}

void OutputSetRelocations( unsigned count, BOOL fDLL )
{
	if ( 0 == count )
		return;
	
	if ( fDLL )
		printf( "This file is a DLL: %u bytes can be saved by "
				"eliminating relocations\n", count );
	else
		printf( "This file is an EXE: %u bytes can be saved by "
				"eliminating relocations\n", count );			
}

void OutputAddIncrementalLinking( PSTR pszSection, DWORD index, DWORD count )
{
	printf("Section %u (%s) has %u padded INT 3's\n", index,pszSection,count);
}

void OutputAddUnoptimizedCode( PSTR pszSection, DWORD index, DWORD count )
{
	printf( "section %u (%s) wastes %u bytes with stupid JMPs\n",
			index, pszSection, count );
}

void OutputAddDebugInfo( PSTR pszType, DWORD cbSize )
{
	printf( "Debug info: %u bytes (%s)\n", cbSize, pszType );
}

void OutputAddCombinableSectionsStart( void )
{
	printf( "The following sections can be combined:\n" );
}
	
void OutputAddCombinableSections( PSTR pszName, unsigned cbSize, DWORD flags )
{
	printf( "  %-8s %u bytes (flags: %08X)\n", pszName, cbSize, flags );
}

void OutputAddCombinableSectionsEnd( DWORD cCurrentPages, DWORD cMergedPages )
{
	printf( "  Current pages: %u  Merged pages: %u\n",
			cCurrentPages, cMergedPages );
}

void OutputBSSSection( PSTR pszName, DWORD index )
{
	printf( "Section %u (%s) is uninitialized data\n", index, pszName );
}

void OutputLoadAddressConflicts(	PSTR pszName1,
									DWORD startRVA1, DWORD endRVA1,
									PSTR pszName2,
									DWORD startRVA2, DWORD endRVA2 )
{
	printf( "Load address conflict:\n  (0x%08X-0x%08X) %s\n"
			"  (0x%08X-0x%08X) %s\n",
			startRVA1, endRVA1, pszName1,
			startRVA2, endRVA2, pszName2 );
}

void OutputBindStatus( BOOL fBound )
{
	printf( "Image is %sbound\n", fBound ? "" : "not " );
}

void OutputError( PSTR pszErrString )
{
	printf( "%s\n", pszErrString );
}
