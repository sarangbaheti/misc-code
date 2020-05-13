#include "stdafx.h"
#include "wrappers.h"
#include "notify.h"

//======================================================================
// Global Functions
//======================================================================
void ok_box( const String &s )
{
	CString cs = (CString)s;
	AfxMessageBox( (const _TCHAR *)cs );
}

//======================================================================
// Rect
//======================================================================

const Rect &Rect::expand_to_include( const Rect &r )
{
   left		= min( left,	r.left		);
   top		= min( top,		r.top		);
   right	= max( right,	r.right		);
   bottom	= max( bottom,  r.bottom	);
   return *this;
}

//======================================================================
// Text_control
//======================================================================
Text_control::Text_control( ctrl_type	 type,
							const Rect	 &position,
							Window		 *parent,
							const String &initial_value,
							Notifiable	 *tell )
			: observer	 ( tell )
{
	#ifdef STD_DEBUG
		std_debug << "Creating "
				  << (type == write_only ? "write only" : "read/write")
				  << " Text_control at "
				  << position
				  << " ["
				  << initial_value
				  << "]\n" ;
	#endif

	bool success = false;

	// Casts in the conditional, below, are required because the ?
	// and : phrases must evaluate to objects of the same type.

	windows_obj = (type==write_only) ? (CWnd*)(new CStatic())
									 : (CWnd*)(CEdit*)this ;
	if(windows_obj == this)
	{
		success = CEdit::Create(
						WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER
						| ES_AUTOHSCROLL | ES_LEFT,
						position,
						parent,
						~0U );	// ID is immaterial
	}
	else
	{
		success = ((CStatic *)windows_obj)->Create( 
						"",
						WS_CHILD | WS_VISIBLE | WS_TABSTOP,
					    position,
					    parent,
					    ~0U ); // ID is immaterial
	}

	assert(success);  // Maybe throw an exception here instead of assert.

	// The SetWindowText sends an EN_CHANGE, which calls OnChange, which
	// notifies the Text_control, which updates the String, which notifies
	// the Text_control, which updates the window text, and around and
	// and around. Solve the problem in the OnChange() function, but set
	// "initializing" true to tell OnChange what's going on. Turn off
	// notification to prevent this.
	//
	// I'm assuming synchronous behavior; I don't expect SentWindowText
	// to return until AFTER the EnChange() handler has been executed.
	// If this turns out not to be the case in the future, you'll have
	// to modify this code: add an "initializing" field to the class,
	// set it true instead of calling notify_off, set it false instead
	// of calling notify_on, and modify OnChange to not notify anybody
	// if "initializing" is true.


	if( !initial_value.is_empty() )
	{
		notify_off();
		windows_obj->SetWindowText( (const _TCHAR *)(CString)initial_value );
		notify_on();
	}
}
//----------------------------------------------------------------------
/*virtual*/ Text_control::~Text_control( void )
{
	if( windows_obj != this )	// it came from new
		delete windows_obj;
}
//----------------------------------------------------------------------
void Text_control::import( const String &s )
{
	assert( windows_obj->m_hWnd );				// Make sure there's a window
	windows_obj->SetWindowText( (const _TCHAR *)(CString)s );
	notify(observer);
}
//----------------------------------------------------------------------
void Text_control::export( String *s )
{
	_TCHAR buf[255];

	// Get the text from Windows. Note that the buffer size has to be
	// computed with sizeof(buf)/sizeof(*buf) because a _TCHAR can
	// evaluate to a wchar_t, which will be two bytes. A simple
	// sizeof(buf) without the subsequent divide could yield a number
	// twice the actual buffer size.

	assert( windows_obj->m_hWnd );			// Make sure there's a window
	windows_obj->GetWindowText( buf, sizeof(buf)/sizeof(*buf) );
	
	*s = buf;
}
//----------------------------------------------------------------------
void Text_control::OnChange() 
{
	notify( observer );
}
//----------------------------------------------------------------------
BEGIN_MESSAGE_MAP(Text_control, CEdit)
	//{{AFX_MSG_MAP(Text_control)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

