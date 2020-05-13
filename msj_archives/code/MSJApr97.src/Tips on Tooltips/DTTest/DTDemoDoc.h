// DTDemoDoc.h : interface of the CDTDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "Circle.h"

class CDTDemoDoc : public CDocument
{
protected: // create from serialization only
	CDTDemoDoc();
	DECLARE_DYNCREATE(CDTDemoDoc)

// Attributes
public:
	int GetCircleCount() { return CIRCLECOUNT; }
	const CCircle& GetCircle(int nIndex) { return m_CircleArray[nIndex]; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDTDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	enum { CIRCLECOUNT = 10 };
	CCircle m_CircleArray[CIRCLECOUNT];

// Generated message map functions
protected:
	//{{AFX_MSG(CDTDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
