////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// CSharedDoc implements an MFC doc class that does file sharing by
// locking a file for the duration of an edit session.
// Compiles with VC++ 5.0 or later
// 
#include "stdafx.h"
#include "doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSharedDoc, CDocument)

BEGIN_MESSAGE_MAP(CSharedDoc, CDocument)
END_MESSAGE_MAP()

CSharedDoc::CSharedDoc()
{
	m_pFile = NULL;
}

CSharedDoc::~CSharedDoc()
{
}

//////////////////
// Load/Save doc as normal (use edit view)
//
void CSharedDoc::Serialize(CArchive& ar)
{
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

////////////////////////////////////////////////////////////////
// Below are overrides for shared stuff

/////////////////
// Map "Save" to "Save As" if doc is read-only
//
BOOL CSharedDoc::DoFileSave()
{
	return m_bReadOnly ?
		DoSave(NULL) :					// do Save As
		CDocument::DoFileSave();	// save as normal
}

////////////////
// Create new doc. Close old one in case this is an SDI app
//
BOOL CSharedDoc::OnNewDocument()
{
	CloseFile();  // Required for SDI app only, because MFC re-uses doc.
	BOOL bRet = CDocument::OnNewDocument();

	if (bRet)
		// do normal stuff
		((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);
	return bRet;
}

//////////////////
// Open New doc. Close old one in case this is an SDI app
//
BOOL CSharedDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	CloseFile();  // Required for SDI app only, because MFC re-uses doc

	// Open the file
	CFile* pFile = OpenFile(lpszPathName, m_bReadOnly);
	if (!pFile) {
		// Can't even open file read-only??? punt
		CString s;
		s.Format(_T("Unknown error opening file '%s'"), lpszPathName);
		AfxMessageBox(s);
		return FALSE;
	}

	if (m_bReadOnly) {
		// Doc was opened read-only: tell user
		CString s;
		s.Format(_T("File '%s' is in use.\nIt will be opened read-only"),
			lpszPathName);
		AfxMessageBox(s);
	}
	m_pFile = pFile;

	// Now do standard MFC Open, but close file if the open fails
	BOOL bRet = CDocument::OnOpenDocument(lpszPathName);
	if (!bRet)
		CloseFile();
	return bRet;
}

/////////////////
// Save document. Use already-open file, unless saving to a new name.
// Either way, lock the file and set length to zero before saving it.
// Note: m_pFile could be NULL if this is a new document.
//
BOOL CSharedDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	BOOL bReadOnly = m_bReadOnly;
	CFile* pFile	= m_pFile;

	// Check for new doc
	BOOL bNewFile = (pFile==NULL) || (pFile->GetFilePath() != lpszPathName);
	if (bNewFile) {
		// new file, or saving w/different name: open new file
		pFile = OpenFile(lpszPathName, bReadOnly, TRUE);
	}

	// If can't get write access, can't save.
	// Display message and return FALSE.
	// 
	if (bReadOnly || pFile == NULL) {
		CString s;
		s.Format(_T("File '%s' is in use.\nSave with a different name."),
			lpszPathName);
		AfxMessageBox(s);
		if (bNewFile && pFile)	// if new file was opened:
			pFile->Close();		// close it
		return FALSE;
	}

	if (bNewFile) {
		// new file: close old one and install it
		CloseFile();
		m_pFile = pFile;			// and replace w/new one
		m_bReadOnly = bReadOnly;// read-only flag too
	}

	// Now do normal Serialize. Lock the file first and set length to zero
	// This is required because I opened with modeNoTruncate. You might
	// want to consider "robust" saving here: that is, save to a temp file
	// before destroying the original file; then if the save succeeds, replace
	// the original file with the new one.
	//
	pFile->LockRange(0,(DWORD)-1);	// will throw exception if fails
	pFile->SetLength(0);					// get rid of current contents
	BOOL bRet = CDocument::OnSaveDocument(lpszPathName); // normal MFC save
	pFile->UnlockRange(0,(DWORD)-1);	// unlock
	return bRet;
}

//////////////////
// Close document: time to really close the file too. MFC only calls this
// function in a MDI app, not SDI.
//
void CSharedDoc::OnCloseDocument()
{
	CloseFile(); // close file
	CDocument::OnCloseDocument(); // Warning: must call this last
											// because MFC will "delete this"
}

//////////////////
// "Release" the file. This means either abort or close.
// In the case of close, I don't really close it, but leave
// file open for duration of user session.
//
void CSharedDoc::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	if (bAbort)
		CDocument::ReleaseFile(pFile, bAbort);
	else if (!m_bReadOnly) {
		pFile->Flush(); // write changes to disk, but don't close!
	}
}

//////////////////
// Override to use my always-open CFile object instead
// of creating and opening a new one.
//
CFile* CSharedDoc::GetFile(LPCTSTR, UINT, CFileException*)
{
	ASSERT_VALID(m_pFile);
	return m_pFile;
}

////////////////////////////////////////////////////////////////
// Helper functions

// CFile::Open mode flags
const OPENREAD   = CFile::modeRead      | CFile::shareDenyNone;
const OPENWRITE  = CFile::modeReadWrite | CFile::shareDenyWrite;
const OPENCREATE = CFile::modeCreate    | CFile::modeReadWrite  |
	CFile::shareDenyWrite;

//////////////////
// Open the document file. Try to open with write acess, else read-only.
// bCreate says whether to create the file, used when saving to a new name.
// Returns the CFile opened, and sets bReadOnly.
//
CFile* CSharedDoc::OpenFile(LPCTSTR lpszPathName, BOOL& bReadOnly, BOOL bCreate)
{
	CFile* pFile = new CFile;
	ASSERT(pFile);
	bReadOnly = TRUE; // assume read only 

	// try opening for write
	CFileException fe;
	if (pFile->Open(lpszPathName, bCreate ? OPENCREATE : OPENWRITE, &fe)) {
		bReadOnly = FALSE;		// got write access

	} else if (bCreate || !pFile->Open(lpszPathName, OPENREAD, &fe)) {
		// can't open for read OR write--yikes! Time to punt
		delete pFile;
		pFile = NULL;
	}
	if (pFile)
		pFile->SeekToBegin();

	return pFile;
}

/////////////////
// Close the file if it's open. Called from multiple places for SDI app
//
void CSharedDoc::CloseFile()
{
	if (m_pFile) {
		m_pFile->Close();
		m_pFile = NULL;
	}
}
