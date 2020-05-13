//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: EXEFILE.CPP
//==========================================
#include <windows.h>
#pragma hdrstop
#include "exefile.h"

EXE_FILE::EXE_FILE( PSTR pszFileName ) : MEMORY_MAPPED_FILE( pszFileName )
{
	m_secondaryHeaderOffset = -1;	// A bogus value to catch bugs
	m_exeType = exeType_Invalid;

	if ( FALSE == MEMORY_MAPPED_FILE::IsValid() )
		return;
	
	if ( GetFileSize() < sizeof(IMAGE_DOS_HEADER) )
		return;
	
	PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)GetBase();
	if ( IMAGE_DOS_SIGNATURE != pDosHdr->e_magic )
		return;
	
	if ( pDosHdr->e_lfarlc < 0x40 )	// Theoretically, this field must be >=
	{								// 0x40 for it to be a non-DOS executable
		m_exeType = exeType_DOS;
		return;
	}

	// Sanity check.  Make sure the "new header" offset isn't past the end
	// of the file
	if ( pDosHdr->e_lfanew > (LONG)GetFileSize() )
		return;

	// Make a pointer to the secondary header	
	m_secondaryHeaderOffset = pDosHdr->e_lfanew;
	PWORD pSecondHdr = MakePtr( PWORD, GetBase(), m_secondaryHeaderOffset );

	// Decide what type of EXE, based on the start of the secondary header
	switch ( *pSecondHdr )
	{
		case IMAGE_OS2_SIGNATURE: m_exeType = exeType_NE; break;
		case IMAGE_VXD_SIGNATURE: m_exeType = exeType_VXD; break;
		case 0x4558: m_exeType = exeType_LX; break;		// OS/2 2.X
	}
	
	if ( *(PDWORD)pSecondHdr == IMAGE_NT_SIGNATURE )
		m_exeType = exeType_PE;
}

PSTR EXE_FILE::GetFileTypeDescription( void )
{
	// Returns a static string that describes what type this file is
	switch ( m_exeType )
	{
		case exeType_DOS:	return "DOS";
		case exeType_NE:	return "NE";
		case exeType_VXD:	return "VXD";
		case exeType_LX:	return "LX";
		case exeType_PE:	return "PE";
		default:			return "Invalid";
	}
}
