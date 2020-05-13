//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: LIPO32.CPP
//==========================================
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop
#include "peexe2.h"
#include "dependencylist.h"
#include "lipo32output.h"

// Prototypes for the analysis routines
void LookForIncrementalLinking( PE_EXE2 & peFile );
void LookForUnoptimizedCode( PE_EXE2 & peFile );
void LookForDebugInfo( PE_EXE2 & peFile );
void LookForRelocations( PE_EXE2 & peFile );
void LookForCombinableSections( PE_EXE2 & peFile );
void LookForBSSSections( PE_EXE2 &peFile );
void LookForLoadAddressConflicts( PSTR pszFileName );
void LookForBoundImage( PE_EXE2 & peFile );

// Helper function prototypes
unsigned ScanForInt3s( PE_SECTION * pSection, unsigned minSequence );
unsigned ScanForJMPsToNoWhere( PE_SECTION * pSection );
PSTR GetDebugTypeName( unsigned type );
int SectSort( const void *a, const void *b );
int ModLoadSort( const void *a, const void *b );

void AnalyzeFile( PSTR pszFileName )
{
	PE_EXE2 peFile( pszFileName );	// Create the PE_EXE2 object to be examined

	char szBuffer[MAX_PATH*2];

	OutputClearAllFields( ); 	// Clear the UI of previous file information
	
	if ( !peFile.IsValid() )	// Make sure it's a PE EXE we're working with
	{
		wsprintf( szBuffer, "%s is not a PE file", pszFileName );
		OutputError( szBuffer );
		return;
	}
	
	if ( IMAGE_FILE_MACHINE_I386 != peFile.GetMachine() )	// 386 only!
	{
		wsprintf(szBuffer, "%s is not an Intel i386 executable", pszFileName );
		OutputError( szBuffer );
		return;		
	}

	// Let the analysis begin!

	OutputSetFileName( pszFileName );

	LookForIncrementalLinking( peFile );

	LookForUnoptimizedCode( peFile );
	
	LookForDebugInfo( peFile );
	
	LookForRelocations( peFile );
	
	LookForCombinableSections( peFile );

	LookForBSSSections( peFile );
	
	LookForLoadAddressConflicts( pszFileName );

	LookForBoundImage( peFile );
}

void LookForIncrementalLinking( PE_EXE2 & peFile )
{
	// Iterate through each section...
	for ( unsigned i=1; i <= peFile.GetNumberOfSections(); i++ )
	{
		PE_SECTION * pSection = peFile.GetSectionByIndex( i );
		
		// If it's not a code section, don't go any further
		if ( !pSection->IsCode() )
			continue;

		// Look for INT 3's, with a minimum sequence of 3 INT 3's before
		// counting starts
		unsigned cInt3s = ScanForInt3s( pSection, 3 );
			
		if ( 0 == cInt3s )
			continue;

		// If INT 3's were found, send to the UI to display
		char szName[10];
		pSection->GetName( szName );
		OutputAddIncrementalLinking( szName, pSection->GetIndex(), cInt3s );
	}	
}

void LookForUnoptimizedCode( PE_EXE2 & peFile )
{
	// Iterate through each section...
	for ( unsigned i=1; i <= peFile.GetNumberOfSections(); i++ )
	{
		PE_SECTION * pSection = peFile.GetSectionByIndex( i );
		
		// If it's not a code section, don't go any further
		if ( !pSection->IsCode() )
			continue;

		// Count how many bytes were taken up by JMPs to the next instruction
		unsigned cStupidJmps = ScanForJMPsToNoWhere( pSection );
			
		if ( cStupidJmps < 25 )	// Cut them a little slack (enough for 5 JMPs)
			continue;
		
		char szName[10];
		pSection->GetName( szName );
		OutputAddUnoptimizedCode( szName, pSection->GetIndex(), cStupidJmps );
	}		
}

void LookForDebugInfo( PE_EXE2 & peFile )
{
	// Find out how many types of debug info are present.  If none, we're done
	unsigned cDebugTypes = peFile.GetDebugInfoTypeCount();
	if ( !cDebugTypes )
		return;

	// Get a pointer to the debug directory	
	PIMAGE_DEBUG_DIRECTORY pDbgDir = peFile.GetDebugDirectory();

	// Emit information on each type of debug information	
	for( unsigned i = 0; i < cDebugTypes; i++, pDbgDir++ )
	{
		OutputAddDebugInfo( GetDebugTypeName(pDbgDir->Type),
							pDbgDir->SizeOfData );
	}
}

void LookForRelocations( PE_EXE2 & peFile )
{
	// Get the number of relocations from the EXE's data directory
	DWORD cbRelocations = 
		peFile.GetDataDirectoryEntrySize(IMAGE_DIRECTORY_ENTRY_BASERELOC);
	
	OutputSetRelocations(	cbRelocations,
							peFile.GetCharacteristics() & IMAGE_FILE_DLL );						
}

// Data structure used by LookForCombinableSections
struct SECTION_ATTRIBUTES
{
	DWORD	Characteristics;
	DWORD	index;
};

void LookForCombinableSections( PE_EXE2 & peFile )
{
	unsigned cSections = peFile.GetNumberOfSections();

	// Allocate an array of SECTION_ATTRIBUTES structures to hold the index
	// and flags for each section
	SECTION_ATTRIBUTES * pAttrs = new SECTION_ATTRIBUTES[ cSections ];

	// Iterate through each section, adding it to the SECTION_ATTRIBUTES array
	unsigned i, cUsed;	
	for ( i=0, cUsed=0; i < cSections; i++ )
	{
		PE_SECTION * pSection = peFile.GetSectionByIndex( i+1 );
		
		char szName[IMAGE_SIZEOF_SHORT_NAME+2];
		
		// Don't put the .rsrc and .reloc sections into the array
		pSection->GetName( szName );
		if ( (0==strcmp(szName, ".reloc")) || (0==strcmp(szName, ".rsrc")) )
			continue;
		
		pAttrs[cUsed].index = i+1;
		pAttrs[cUsed].Characteristics = pSection->GetCharacteristics();
		cUsed++;
	}

	unsigned max_i;	// )(*&)(^*%*$ "goto skips initialization" error!!!

	// Make sure that we put at least 2 items into our pAttrs array.  Otherwise
	// it's not worth looking for combinable sections. 
	if ( cUsed <= 2 )
		goto done_comparing;

	// Sort the sections based on their attributes
	qsort( pAttrs, cUsed, sizeof(SECTION_ATTRIBUTES), SectSort );
	
	max_i = cUsed-1;

	// Now go though the sorted SECTION_ATTRIBUTES array and find sequences
	// of two or more sections with the same flags (characteristics)
	for ( i=0; i < max_i; i++ )
	{
		// first, scan until we find two sections with the same flags
		while (	pAttrs[i].Characteristics != pAttrs[i+1].Characteristics )
		{
			if ( ++i >= max_i )
				goto done_comparing;
		}

		// If we get here, we've found two sections that have the same flags
		// Now find the last section that has the same flags value
		unsigned j = i+1;
		while (	(pAttrs[j].Characteristics == pAttrs[j+1].Characteristics )
				&& (j <= max_i) )
			j++;
		
		DWORD cCurrentPagesUsed = 0;
		DWORD cBytesUsed = 0;

		// Tell the UI that we're about to start emitting a list of
		// combinable sections
		OutputAddCombinableSectionsStart();		

		// Emit the information about each combinable section	
		while ( i <= j )
		{
			PE_SECTION * pSection = peFile.GetSectionByIndex(pAttrs[i].index);
			
			char szName[IMAGE_SIZEOF_SHORT_NAME+2];
			pSection->GetName( szName );
			OutputAddCombinableSections( szName, pSection->GetAccessibleSize(),
										 pSection->GetCharacteristics() );
			i++;
			
			cCurrentPagesUsed += (pSection->GetMaxSizeInMem() + 0xFFF)/0x1000;
			cBytesUsed += pSection->GetMaxSizeInMem();
		}

		// Tell the UI that we're done emitting sections.  Also provide it
		// with the before and after page counts
		OutputAddCombinableSectionsEnd( cCurrentPagesUsed,
										(cBytesUsed + 0xFFF) / 0x1000 );
	}
	
	done_comparing:
	
	delete []pAttrs;
}

void LookForBSSSections( PE_EXE2 &peFile )
{
	// Iterate through every section
	for ( unsigned i=1; i <= peFile.GetNumberOfSections(); i++ )
	{
		PE_SECTION * pSection = peFile.GetSectionByIndex( i );

		// If the section has the uninitialized data flag set, tattle on it		
		if (pSection->GetCharacteristics() & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
		{
			char szName[10];
			pSection->GetName( szName );
			OutputBSSSection( szName, i );
		}
	}	
}

// Data structure used by LookForLoadAddressConflicts
struct MODULE_LOAD_INFO
{
	DWORD	m_baseRVA;		// RVA that module loads at
	DWORD	m_endRVA;		// RVA that module ends at
	PSTR	m_pszFullName;	// Full path to the module
};
typedef MODULE_LOAD_INFO * PMODULE_LOAD_INFO;

void LookForLoadAddressConflicts( PSTR pszFileName )
{
	// Create a module dependency list
	MODULE_DEPENDENCY_LIST depList( pszFileName );

	unsigned cModules = depList.GetNumberOfModules();

	if ( cModules <= 1 )	// At least 2 modules are needed for a conflict
		return;

	// Create an array of MODULE_LOAD_INFOs to store info about each module	
	// pMods is the start of the array, pModCurr is the current
	// MODULE_LOAD_INFO that's being accessed
	PMODULE_LOAD_INFO pMods = new MODULE_LOAD_INFO[ cModules ];
	PMODULE_LOAD_INFO pModCurr = pMods;

	// Get a pointer to the first module in the dependency list	
	PMODULE_FILE_INFO pModFile = depList.GetNextModule( NULL );

	// While there are still modules in the list...	
	while ( pModFile )
	{
		// Make a PE_EXE object to access the module's information
		PE_EXE peFile( pModFile->m_szFullName );
		if ( !peFile.IsValid() )
			break;

		// Add the information about the module to the MODULE_LOAD_INFO
		pModCurr->m_pszFullName = strdup( pModFile->m_szFullName );
		pModCurr->m_baseRVA = peFile.GetImageBase();
		pModCurr->m_endRVA = peFile.GetImageBase() + peFile.GetSizeOfImage();
		// Round up the ending address to a multiple of 64K, since that's the
		// granularity that the OS allocates 
		pModCurr->m_endRVA = (pModCurr->m_endRVA + 0xFFFF) & 0xFFFF0000;

		// Prepare to process the next module			
		pModCurr++;
		pModFile = depList.GetNextModule( pModFile );
	}

	// Sort the MODULE_LOAD_INFO array, based on the load address
	qsort( pMods, cModules, sizeof(MODULE_LOAD_INFO), ModLoadSort );

	unsigned i;

	// Now iterate through the MODULE_LOAD_INFO array, looking for consecutive
	// entries that have an overlap
	pModCurr = pMods;
	for ( i=1; i < cModules; i++, pModCurr++ )
	{
		// Yes, this looks wacky.   But it works.  If the end of the current
		// module's range is after the start of the next module range, there's
		// an overlap.
		if ( pModCurr->m_endRVA > pModCurr[1].m_baseRVA )
		{
			OutputLoadAddressConflicts( 
					pModCurr->m_pszFullName,
					pModCurr->m_baseRVA,
					pModCurr->m_endRVA,
					pModCurr[1].m_pszFullName,
					pModCurr[1].m_baseRVA,
					pModCurr[1].m_endRVA
				);
		}
	}
	
	// Clean up all the filename strings we strdup'ed earlier
	pModCurr = pMods;
	for ( i=0; i < cModules; i++, pModCurr++ )
		free( pModCurr->m_pszFullName );
	delete []pMods;		// Delete the MODULE_LOAD_INFO array
}

void LookForBoundImage( PE_EXE2 & peFile )
{
	// Look in the appropriate data directory slot in the executable.  Note
	// that in NT 3.5 and earlier, this field wasn't set by BIND.
	BOOL fBound = (BOOL)
		peFile.GetDataDirectoryEntrySize(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT);

	OutputBindStatus( fBound );
}

//======================== Helper functions ================================

unsigned ScanForInt3s( PE_SECTION * pSection, unsigned minSequence )
{
	// Scan the specified section, looking for as strings of INT 3s.  The
	// minimum length for a match is given by the minSequence parameter
	DWORD len = pSection->GetAccessibleSize();

	// Get a pointer to the start of the data	
	PBYTE pData = (PBYTE)pSection->GetPointer();
	
	if ( minSequence > len )
		return 0;
	
	PBYTE pEnd = pData + len;	// Get a pointer to the end of the data
	DWORD count = 0;
	
	while ( pData < pEnd )	// While still more data...
	{
		// use memchr to quickly find the first 0xCC byte
		pData = (PBYTE)memchr( pData, 0xCC, pEnd - pData );
		if ( !pData )
			break;

		DWORD cThisRun = 0;

		// Count how many INT 3's are in this sequence.		
		while ( pData < pEnd )
		{
			if ( *pData++ != 0xCC )
				break;
			
			cThisRun++;
		}

		// If the minimum length was met, add it to our running total
		if ( cThisRun >= minSequence )
			count += cThisRun;
	}
		
	return count;	// Return final total
}

unsigned ScanForJMPsToNoWhere( PE_SECTION * pSection )
{
	DWORD len = pSection->GetAccessibleSize();

	// Get pointer to the start of the data	
	PBYTE pData = (PBYTE)pSection->GetPointer();
	
	if ( len < 6 )
		return 0;

	// Get pointer to the last possible byte where we could find a JMP	
	PBYTE pEnd = pData + len - 6;

	DWORD count = 0;
	
	// Scan for JMPs to the next instruction, followed by a MOV XXX,[XXX]
	// or POP XXX instruction.  These are the most common sequences produced
	// by a compiler in non-optimizing mode
	while ( pData < pEnd )
	{
		pData = (PBYTE)memchr( pData, 0xE9, pEnd - pData );
		if ( !pData )
			break;

		pData++;
		if ( 0 == *(PDWORD)pData )	// Is the relative offset == 0?
		{
			// It sure looks like a wasted JMP, but verify by looking
			// at the next instruction to see if it's a common instruction.
			// 0x8B = MOV, 0x58-0x5F = POP XXX
			if ( pData[4] == 0x8B || ( 0x58 == (pData[4] & 0xF8) ) )
				count += 5;		// The length of the JMP 00000000
		}
	}
		
	return count;	
}

PSTR GetDebugTypeName( unsigned type )
{
	// Given an IMAGE_DEBUG_TYPE_XXX value (see WINNT.H), return a static
	// string describing what type of debug information it is.
	switch ( type )
	{
		case IMAGE_DEBUG_TYPE_COFF: return "COFF";
		case IMAGE_DEBUG_TYPE_CODEVIEW: return "CODEVIEW";
		case IMAGE_DEBUG_TYPE_FPO: return "FPO";
		case IMAGE_DEBUG_TYPE_MISC: return "MISC";
		case IMAGE_DEBUG_TYPE_EXCEPTION: return "EXCEPTION";
		case IMAGE_DEBUG_TYPE_FIXUP: return "FIXUP";
		case IMAGE_DEBUG_TYPE_OMAP_TO_SRC: return "OMAP_TO_SRC";
		case IMAGE_DEBUG_TYPE_OMAP_FROM_SRC: return "OMAP_FROM_SRC";
		case 0: return "BORLAND";
		default: return "UNKNOWN";
	}
}

// Comparison routine used by the qsort call in LookForCombinableSections
int SectSort( const void *a, const void *b )
{
	// First, sort by characteristics
	DWORD x = ((SECTION_ATTRIBUTES*)a)->Characteristics 
			- ((SECTION_ATTRIBUTES*)b)->Characteristics;
	if ( x )
		return x;
	
	// If the characteristics match, sort by indexes, with lower values first
	x =	((SECTION_ATTRIBUTES*)a)->index 
	  - ((SECTION_ATTRIBUTES*)b)->index;

	return x;
}

// Comparison routine used by the qsort call in LookForAddressConflicts
int ModLoadSort( const void *a, const void *b )
{
	// Sort based on the base (load) RVA
	DWORD first = ((PMODULE_LOAD_INFO)a)->m_baseRVA;
	DWORD second = ((PMODULE_LOAD_INFO)b)->m_baseRVA;
	
	if ( first == second )
		return 0;
	
	return (first > second) ? 1 : -1;
}
