////////////////////////////////////////////////////////////////
// CWindowPlacement Copyright 1996 Microsoft Systems Journal.
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.

////////////////
// CWindowPlacement reads and writes WINDOWPLACEMENT 
// from/to application profile and CArchive.
//
struct CWindowPlacement : public WINDOWPLACEMENT {
	CWindowPlacement();
	~CWindowPlacement();
	
	// Read/write to app profile
	BOOL GetProfileWP(LPCTSTR lpszKey, LPCTSTR lpszVal);
	BOOL WriteProfileWP(LPCTSTR lpszKey, LPCTSTR lpszVal);

	// Save/restore window pos (from app profile)
	void Save(LPCTSTR lpszKey, LPCTSTR lpszVal, CWnd* pWnd);
	BOOL Restore(LPCTSTR lpszKey, LPCTSTR lpszVal, CWnd* pWnd);

	// Save/restore from archive
	friend CArchive& operator<<(CArchive& ar, const CWindowPlacement& wp);
	friend CArchive& operator>>(CArchive& ar, CWindowPlacement& wp);
};
