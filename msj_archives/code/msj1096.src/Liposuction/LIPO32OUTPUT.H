void OutputClearAllFields( void );

void OutputSetFileName( PSTR pszFileName );

void OutputSetRelocations( unsigned count, BOOL fDLL );

void OutputAddIncrementalLinking( PSTR pszSection, DWORD index, DWORD count );

void OutputAddUnoptimizedCode( PSTR pszSection, DWORD index, DWORD count );

void OutputAddDebugInfo( PSTR pszType, DWORD cbSize );

void OutputAddCombinableSectionsStart( void );

void OutputAddCombinableSections( PSTR pszName, unsigned cbSize, DWORD flags );

void OutputAddCombinableSectionsEnd( DWORD cCurrentPages, DWORD cMergedPages );

void OutputBSSSection( PSTR pszName, DWORD index );

void OutputLoadAddressConflicts(	PSTR pszName1,
									DWORD startRVA1, DWORD endRVA1,
									PSTR pszName2,
									DWORD startRVA2, DWORD endRVA2 );

void OutputBindStatus( BOOL fBound );

void OutputError( PSTR pszErrString );
