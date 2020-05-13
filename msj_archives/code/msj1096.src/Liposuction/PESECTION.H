//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: PESECTION.H
//==========================================
#ifndef __PESECT_H__
#define __PESECT_H__

#ifndef MakePtr
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (DWORD)(addValue))
#endif

class PE_SECTION
{
	public:
		
	PE_SECTION( PIMAGE_SECTION_HEADER pSectHdr,
				PVOID pMappedAddr,
				unsigned index );
	~PE_SECTION( ) { }

	//
	// Functions for getting at the raw data of an IMAGE_SECTION_HEADER
	//
    void    GetName( PSTR pszName );	// IMAGE_SIZEOF_SHORT_NAME +1 bytes

    DWORD   GetPhysicalAddress( void )
				{ return m_pSectHdr->Misc.PhysicalAddress; }
    DWORD   GetVirtualSize( void )
				{ return m_pSectHdr->Misc.VirtualSize; }
    DWORD   GetVirtualAddress( void )
				{ return m_pSectHdr->VirtualAddress; }
    DWORD   GetSizeOfRawData( void )
				{ return m_pSectHdr->SizeOfRawData; }
    DWORD   GetPointerToRawData( void )		// Really a file offset!
				{ return m_pSectHdr->PointerToRawData; }
    DWORD   GetPointerToRelocations( void )
				{ return m_pSectHdr->PointerToRelocations; }
    DWORD   GetPointerToLinenumbers( void )
				{ return m_pSectHdr->PointerToLinenumbers; }
    WORD    GetNumberOfRelocations( void )
				{ return m_pSectHdr->NumberOfRelocations; }
    WORD    GetNumberOfLinenumbers( void )
				{ return m_pSectHdr->NumberOfLinenumbers; }
    DWORD   GetCharacteristics( void )
				{ return m_pSectHdr->Characteristics; }

	//
	// More intelligent functions that interpret the IMAGE_SECTION_HEADER data
	//

	PVOID	GetPointer( void )	// Returns the *REAL* pointer to raw data
				{ return MakePtr(PVOID, m_pMappedAddr, GetPointerToRawData()); }

	DWORD	GetAccessibleSize( void )
				{ return min(	m_pSectHdr->Misc.VirtualSize,
								m_pSectHdr->SizeOfRawData ); }

	DWORD	GetMaxSizeInMem( void )
				{ return max(	m_pSectHdr->Misc.VirtualSize,
								m_pSectHdr->SizeOfRawData ); }
							
	BOOL	IsCode( void )
				{ return m_pSectHdr->Characteristics & IMAGE_SCN_MEM_EXECUTE; }
	BOOL	IsData( void )
				{ return !IsCode(); }
	BOOL	IsWriteable( void )
				{ return m_pSectHdr->Characteristics & IMAGE_SCN_MEM_WRITE; }
	
	DWORD	GetIndex( void ) { return m_index; }

	private:
	
	PIMAGE_SECTION_HEADER m_pSectHdr;
	PVOID m_pMappedAddr;
	unsigned m_index;
};

#endif
