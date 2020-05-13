//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: PEEXE2.CPP
//==========================================
#include <windows.h>
#include <stdlib.h>
#pragma hdrstop
#include "peexe2.h"

PE_EXE2::PE_EXE2( PSTR pszFileName ) : PE_EXE( pszFileName )
{
	m_ppPeSect = 0;		// Start out with no section table
}

PE_EXE2::~PE_EXE2( )
{
	unsigned i;

	// Clean up the PE_SECTIONs (if we created them)
	if ( m_ppPeSect )
	{
		for ( i = 1; i <= GetNumberOfSections(); i++ )
			delete m_ppPeSect[i];
		
		delete []m_ppPeSect;
	}
}

PE_SECTION * PE_EXE2::GetSectionByName( PSTR pszName )
{
	if ( !m_ppPeSect )	// Make the section table (if not already built)
		MakeSections();	

	char szThisSectName[ IMAGE_SIZEOF_SHORT_NAME ];
	
	for ( unsigned i = 1; i <= GetNumberOfSections(); i++ )
	{
		m_ppPeSect[i]->GetName( szThisSectName );
		if ( 0 == lstrcmp( pszName, szThisSectName) )
			return m_ppPeSect[i];
	}
	
	return 0;
}

PE_SECTION * PE_EXE2::GetSectionByIndex( unsigned index )	// 1 based
{
	if ( index > GetNumberOfSections() )	// Is it a valid section number
		return 0;

	if ( 0 == index )	// Zero is not a valid section number!!!
		return 0;

	if ( !m_ppPeSect )	// Make the section table (if not already built)
		MakeSections();
	
	return m_ppPeSect ? m_ppPeSect[ index ] : 0;
}

PE_SECTION * PE_EXE2::GetSectionByRVA( DWORD rva )
{
	if ( !m_ppPeSect )	// Make the section table (if not already built)
		MakeSections();

	// Iterate through each section looking for one that encompasses the
	// passed in rva.  If found, return a pointer to the PE_SECTION object
	for ( unsigned i = 1; i <= GetNumberOfSections(); i++ )
	{
		PE_SECTION * pSection = m_ppPeSect[i];

		if ( rva >= pSection->GetVirtualAddress() )
			if ( rva < (  pSection->GetVirtualAddress()
						+ pSection->GetMaxSizeInMem() ))
			{
				return pSection;
			}
	}

	return 0;	// Oops.  Not found.
}

unsigned PE_EXE2::GetDebugInfoTypeCount( void )
{
	DWORD cbDebugInfo;

	// Go to the data directory to see how big the debug directory is	
	cbDebugInfo = GetDataDirectoryEntrySize( IMAGE_DIRECTORY_ENTRY_DEBUG );
	if ( !cbDebugInfo )
		return 0;

	// Microsoft puts in the size of the debug directory.  Borland emits
	// the actual number of debug types (i.e., 1 for Borland)	
	if ( cbDebugInfo >= sizeof(IMAGE_DEBUG_DIRECTORY) )
		return cbDebugInfo / sizeof( IMAGE_DEBUG_DIRECTORY );
	else
		return cbDebugInfo;		// Borland has this screwed up!
}

PIMAGE_DEBUG_DIRECTORY PE_EXE2::GetDebugDirectory( void )
{
	// returns a pointer to the array of IMAGE_DEBUG_DIRECTORYs
	if ( GetDebugInfoTypeCount() )	// Is there debug info in the first place?
	{
		return (PIMAGE_DEBUG_DIRECTORY)
				GetDataDirectoryEntryPointer( IMAGE_DIRECTORY_ENTRY_DEBUG );
	}
	else
		return 0;
}

BOOL PE_EXE2::MakeSections( void )
{
	unsigned i;

	// A helper routine, which is called the first time that somebody
	// asks for section related information.

	// Allocate space for our array of pointers to PE_SECTIONs
	// Make space for one extra pointer at the beginning to be "section 0",
	// although this "section" will never be used.
	m_ppPeSect = new PE_SECTION *[ GetNumberOfSections()+1 ];

	PIMAGE_SECTION_HEADER pRawSects
					= IMAGE_FIRST_SECTION( GetIMAGE_NT_HEADERS() );
	
	for ( i = 1; i <= GetNumberOfSections(); i++ )
		m_ppPeSect[i] = new PE_SECTION( pRawSects++, GetBase(), i );
			
	return FALSE;
}
