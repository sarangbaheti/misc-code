// OpenGLView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#include "gl\gl.h"     // Include the standard OpenGL headers
#include "gl\glu.h"
#include "gl\glaux.h"  // Add in the auxiliary library

class COpenGLView : public CView
{
protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	COpenGLDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL InitializeOpenGL( void );
	virtual BOOL SetupPixelFormat( PIXELFORMATDESCRIPTOR* pPFD = 0 );
	virtual	BOOL SetupViewingFrustum( void );
	virtual	BOOL SetupViewingTransform( void );

	virtual void PreRenderScene( void ) // just clear the viewport
		{ ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); }
	virtual void RenderStockScene( void );
	virtual void RenderScene( void );
	virtual void PostRenderScene( void ) { return; }


	void		GenerateDisplayListForFont( const char* const fontname, double xt );
	void		GLTextOut( const char * const textstring );


	GLdouble	m_AspectRatio; // width/height ratio
	GLsizei		m_WindowWidth, m_WindowHeight; // of rendering window
	GLuint		m_TextID;

private:

	HGLRC		m_hRC;	// holds the rendering context
	CDC*		m_pDC; // holds the device context

};

#ifndef _DEBUG  // debug version in OpenGLView.cpp
inline COpenGLDoc* COpenGLView::GetDocument()
   { return (COpenGLDoc*)m_pDocument; }
#endif


