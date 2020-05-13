////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See ShadeCap.cpp
//

////////////////
// Generic MFC Doc holds a text file.
//
class CMyDoc : public CDocument {
public:
	CMyDoc();
	virtual ~CMyDoc();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	DECLARE_DYNCREATE(CMyDoc)
};
