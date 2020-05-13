////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This program compiles with Visual C++ 4.2 on Windows 95
// See pform.cpp
// 
class CMyDoc : public CDocument {
public:
	virtual ~CMyDoc();

	//{{AFX_VIRTUAL(CMyDoc)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

protected:
	CMyDoc();
	DECLARE_DYNCREATE(CMyDoc)

	//{{AFX_MSG(CMyDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
