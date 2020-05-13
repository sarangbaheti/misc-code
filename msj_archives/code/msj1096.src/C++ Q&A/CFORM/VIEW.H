/////////////////
// Standard CFormView 
//
class CMyFormView : public CFormView {
public:
   virtual ~CMyFormView();
   CMyDoc* GetDocument() { return (CMyDoc*)m_pDocument; }

   //{{AFX_DATA(CMyFormView)
   enum { IDD = IDD_MYFORM };
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CMyFormView)
   public:
   virtual void OnInitialUpdate();
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:
   DECLARE_DYNCREATE(CMyFormView)
   CMyFormView();

   //{{AFX_MSG(CMyFormView)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
