//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: EXEFILE.H
//==========================================
#ifndef __EXEFILE_H__
#define __EXEFILE_H__

#ifndef __MEMMAPFL_H__
#include "memorymappedfile.h"
#endif

// MakePtr is a macro that allows you to easily add to values (including
// pointers) together without dealing with C's pointer arithmetic.  It
// essentially treats the last two parameters as DWORDs.  The first
// parameter is used to typecast the result to the appropriate pointer type.
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (DWORD)(addValue))

enum EXE_TYPE { exeType_Invalid, exeType_DOS, exeType_NE, exeType_VXD,
				exeType_LX, exeType_PE };

class EXE_FILE : public MEMORY_MAPPED_FILE
{
	public:
		
	EXE_FILE( PSTR pszFileName );
	~EXE_FILE( ){ ; }
	
	BOOL	IsValid( void ){ return m_exeType != exeType_Invalid; }
	
	DWORD	GetSecondaryHeaderOffset( void ){ return m_secondaryHeaderOffset; }

	EXE_TYPE	GetExeType( void ){ return m_exeType; }

	PSTR	GetFileTypeDescription( void );
	
	private:

	LONG		m_secondaryHeaderOffset;
	EXE_TYPE	m_exeType;
};

#endif
