//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: PEEXE2.H
//==========================================
#ifndef __PEEXE2_H__
#define __PEEXE2_H__

#ifndef __PEEXE_H__
#include "peexe.h"
#endif

#ifndef __PESECT_H__
#include "pesection.h"
#endif

class PE_EXE2 : public PE_EXE
{
	public:
		
	PE_EXE2( PSTR pszFileName );
	~PE_EXE2( );

	PE_SECTION * GetSectionByName( PSTR pszName );
	PE_SECTION * GetSectionByIndex( unsigned index );
	PE_SECTION * GetSectionByRVA( DWORD RVA );

	unsigned GetDebugInfoTypeCount( void );
	PIMAGE_DEBUG_DIRECTORY GetDebugDirectory( void );

	private:
		
	PE_SECTION ** m_ppPeSect;
	
	BOOL MakeSections( void );
};

#endif
