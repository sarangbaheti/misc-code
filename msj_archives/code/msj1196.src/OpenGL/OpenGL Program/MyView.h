// MyView.h : subclass of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#include "OpenGLView.h"     // Include the standard OpenGL headers

/////////////////////////////////////////////////////////////////////////////
class CMyView : public COpenGLView
{
private:

	DECLARE_DYNCREATE(CMyView)

protected:

	virtual void RenderScene( void );
	virtual void RenderStockScene( void );
	
};