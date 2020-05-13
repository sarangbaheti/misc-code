//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: PESECTION.CPP
//==========================================
#include <windows.h>
#include <stdlib.h>
#pragma hdrstop
#include "pesection.h"

PE_SECTION::PE_SECTION( PIMAGE_SECTION_HEADER pSectHdr,
						PVOID pMappedAddr,
						unsigned index )
{
	m_pSectHdr = pSectHdr;
	m_pMappedAddr = pMappedAddr;
	m_index = index;
}

void PE_SECTION::GetName( PSTR pszName )
{
	//  input buffer must be at least IMAGE_SIZEOF_SHORT_NAME +1 bytes

	// Copy the max name size, even if the string is less than the max
	// length.  Next, null terminate it.
	memcpy( pszName, m_pSectHdr->Name, IMAGE_SIZEOF_SHORT_NAME );
	pszName[ IMAGE_SIZEOF_SHORT_NAME ] = 0;
}
