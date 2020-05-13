////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// 

/////////////////
// CCharedDoc implements shareable documents that are kept open
// for the duration of the edit session
//
class CSharedDoc : public CDocument {
protected:
	CFile* m_pFile;		// the file kept open during editing
	BOOL	 m_bReadOnly;	// whether read-only access

	// helpers
	CFile* OpenFile(LPCTSTR lpszPathName, BOOL& bReadOnly, BOOL bCreate=FALSE);
	void   CloseFile();
	DECLARE_DYNCREATE(CSharedDoc)
	DECLARE_MESSAGE_MAP()

public:
	CSharedDoc();
	virtual ~CSharedDoc();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void ReleaseFile(CFile* pFile, BOOL bAbort);
	virtual BOOL DoFileSave();
	virtual CFile* GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
		CFileException* pError);
};
