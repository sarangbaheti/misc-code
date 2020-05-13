////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// 

//////////////////
// Standard view class
//
class CMyView : public CEditView {
public:
	CMyView();
	virtual ~CMyView();
	CSharedDoc* GetDocument() { return (CSharedDoc*)m_pDocument; }
	virtual void OnDraw(CDC* pDC);
protected:
	DECLARE_DYNCREATE(CMyView)
	DECLARE_MESSAGE_MAP()
};
