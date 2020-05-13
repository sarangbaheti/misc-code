#include "stdafx.h"
#include "wrappers.h"
#include "notify.h"

//======================================================================
// Window
//======================================================================
const String Window::no_title;
//----------------------------------------------------------------------
/*virtual*/ Window::~Window(){}
//----------------------------------------------------------------------
Window::Window( const Rect	 &position,
			    const String &title,			/*= no_title */
				Notifiable	 *notify_on_close	/*= &Nobody  */ )
{
	this->notify_on_close = notify_on_close;

	// It's convenient to have a Create() function IN ADDITION to
	// PreCreateWindow(), but you must have PreCreateWindow too in case
	// someone calls CreateEx() or Create() polymorphically through a
	// CWnd pointer. Note that, since the current window is not a child
	// window, the position is screen relative, not parent-window relative.
	// 
	// Note that you can use CWnd::Create() to make a child window but
	// not a popup [Create() requires a be a parent window]. Since the
	// current example IS a popup, I must use CreateEx(), which is
	// a little more awkward to use, but more functional.

	#ifdef STD_DEBUG
		std_debug	<< "Creating Window"
					<< "["			<< title
					<< "] at "		<< position
					<< " width="	<< position.Width()
					<< " height="	<< position.Height()
					<< "\n" ;
	#endif

	// Use CreateEx because this is a popup (Create() requires a parent
	// window). The class name is supplied by PreCreateWindow, as are
	// all attributes except the WS_CAPTION attribute. I add six units
	// to the window width to compensate for the border. If the window
	// has a caption bar (has_title is true), add 25 units for it and
	// the border, else just add 6 units for the border..

	bool has_title = &title != &no_title;

	CreateEx(	0,				// No extended attributes
				NULL,
				!has_title ? "": CString((String &)title),
				!has_title ? 0 : WS_CAPTION,
				position.left,
				position.top,
				position.Width()  + 6,
				position.Height() + (has_title ? 25 : 6),
				NULL,			// no parent 
				NULL			// no menu
			 );
}
//----------------------------------------------------------------------
void Window::PostNcDestroy() 
{
	// Called by the framework after the windows object has been
	// destroyed, frees the memory associated with the current window.
	// That is, I'm assuming that the window is allocated from new and
	// that it will stay around until the user opts to close it.
	// There will be no delete to match the new.

	notify( notify_on_close );
	CWnd::PostNcDestroy();
	delete this;
}
//----------------------------------------------------------------------
BOOL Window::PreCreateWindow(CREATESTRUCT& cs) 
{
	// Replace various arguments to Create (or CreateEx) with values
	// that are required by the current window implemenation. The
	// WS_VISIBLE attribute, though not strictly speaking necessary,
	// lets the caller dispense with the
	//				win->ShowWindow( SW_SHOWNORMAL );
	//				win->UpdateWindow();
	// calls.

	static CString class_name;
	if( class_name.IsEmpty() )
	{
		// If we haven't registered a class with Windows, yet, do it
		// for now. This call usually establishes cursor, brush, and
		// icon all windows of the current class. (Since the windows
		// isn't going to be minimized, I've left out the icon, here).

		HCURSOR	cursor	= AfxGetApp()->LoadStandardCursor( IDC_ARROW );
		HBRUSH	brush	= (HBRUSH) ::GetStockObject( WHITE_BRUSH );
		HICON	icon	= 0;
		class_name = AfxRegisterWndClass(CS_VREDRAW|CS_HREDRAW,
												cursor,	brush,icon);
	}

	// Window is initially hidden, if that's not what
	// you want, OR WS_VISIBLE into the file bit.

	cs.style	 |= WS_OVERLAPPED|WS_POPUPWINDOW ;
	cs.lpszClass = class_name;
	return CWnd::PreCreateWindow(cs);
}
//----------------------------------------------------------------------
BEGIN_MESSAGE_MAP(Window, CWnd)
	//{{AFX_MSG_MAP(Window)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//======================================================================
// Button
//======================================================================
/*virtual*/ Button::~Button(){}
//----------------------------------------------------------------------
Button::Button( const String &in_caption,
			    const Rect	 &in_position,
				Notifiable *notify /*=&Nobody*/): caption ( in_caption )
												, position( in_position )
												, notify_on_press(notify)
{}

void Button::show( Window *parent )
{
	Create( (const CString)caption,
			WS_CHILD|WS_VISIBLE,
			position,
			parent,
			~0U );					// Button ID
}

void Button::hide( void )
{
	DestroyWindow();
}

//----------------------------------------------------------------------
void Button::OnClicked(void) 
{
	notify( notify_on_press );
}
//----------------------------------------------------------------------
BEGIN_MESSAGE_MAP(Button, CButton)
	//{{AFX_MSG_MAP(Button)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
