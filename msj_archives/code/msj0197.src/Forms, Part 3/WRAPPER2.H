// wrappers2.h:
// 
// This file is an extension of the Wrappers.h file discussed in Part
// one of the article. It is included at the end of wrappers.h and
// should not be included directly by you in your programs (include
// wrappers.h instead). Were this not a two-part article, I would have
// just put everything in the current file into wrappers.h and gotten
// it over with.
//
// The following #if makes sure that wrappers2.h is being expanded
// from within wrappers.h. The test fails if the #include occurs
// anywhere else.

#if (!defined(WRAPPERS_H__) || defined(WRAPPERS2_H_))
#error Do not include wrappers2.h directly, include wrappers.h instead.
#endif

#define WRAPPERS2_H__
//======================================================================
// Window
//======================================================================

class Window: public CWnd
			, public Notifier
{
	//{{AFX_VIRTUAL(Window)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Window)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	static const String no_title;

	Window( const Rect &position, const String &title	= no_title,
							Notifiable *notify_on_close = &Nobody );
	virtual ~Window();

	void show( void );
	void hide( void );

	void destroy( void );
private:
	Notifiable *notify_on_close;
};
//------------------------------------------------------------------------
inline void Window::show( void )
{
	ShowWindow( SW_SHOW );
}
//------------------------------------------------------------------------
inline void Window::hide( void )
{
	ShowWindow( SW_HIDE );
}
//------------------------------------------------------------------------
inline void Window::destroy( void )
{
	// A Window must be allocated from new. It is deleted automatically
	// when the user shuts down the window. DO NOT PASS THE Window POINTER
	// TO DELETE EVER. Instead, call p->destroy();

	DestroyWindow();
}

//======================================================================
// Button
//======================================================================

class Button : public CButton
			 , public Notifier
{
public:
	virtual ~Button(void);
	Button( const String &caption,	const Rect	&position,
			Notifiable	*notify = &Nobody );

	void show( Window *parent );
	void hide( void			  );

private:
	Notifiable *notify_on_press;
	String		caption;
	Rect		position;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Button)
	//}}AFX_VIRTUAL
	//{{AFX_MSG(Button)

	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
