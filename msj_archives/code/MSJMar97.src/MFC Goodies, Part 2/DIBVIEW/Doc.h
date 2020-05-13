////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#include "dib.h"

//////////////////
// Document class just holds a DIB
//
class CDIBDoc : public CDocument {
protected:
	DECLARE_DYNCREATE(CDIBDoc)
	CDIBDoc();
	CDib m_dib;		// the DIB
	DECLARE_MESSAGE_MAP()
public:
	virtual ~CDIBDoc();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	CDib* GetDIB() { return &m_dib; }
};
