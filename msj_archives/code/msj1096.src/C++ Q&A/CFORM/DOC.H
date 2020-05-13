//////////////////
// Standard doc
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
