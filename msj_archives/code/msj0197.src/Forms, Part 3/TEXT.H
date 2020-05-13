#ifndef TEXT_H__
#define TEXT_H__

#include "ansi.h"
#include "mystring.h"
#include "userintf.h"
#include "wrappers.h"
#include "notify.h"

class Text	: public	String
			, public	User_interface
{
	class Observer: public Notifiable
	{
		Text *the_text_obj;
	public:
		Observer( Text *container ): the_text_obj(container){}
		void notify( Notifier *sender );
	}
	watcher;

	friend void Observer::notify( Notifier *sender );

	Text_control	*display_mechanism;

public: // overrides of User_interface functions
	Text( void );
	Text( const String &r );

	virtual ~Text( void );

	virtual	const String &operator=( const String &r );
	virtual	const String &operator=( const _TCHAR *p );
	virtual	const Text   &operator=( const Text	  &r );

	virtual void hide	 ( void							 );
	virtual bool display ( Window *win, const Rect &rect );
	virtual bool interact( Window *win, const Rect &rect );
};

//---------------------------------------------------------
// The following code kicks out:
//
// warning C4355: 'this' : used in base member initializer list.
//
// Normally, it would be dangerous for the contained-object
// constructor to access the container class because the contained
// objects are initialized before the container is initialized.
// We don't do that here, and it's convient to pass a pointer
// to the container at construction time, so turn off the warning.

#pragma warning( disable : 4355 )

inline Text::Text( void )	: watcher			( this	)
							, display_mechanism ( NULL	)
							, String			( "", &watcher )
{}

inline Text::Text( const String &r )
							: watcher			( this	)
							, display_mechanism ( NULL	)
							, String			( r, &watcher )
{}

#pragma warning( default : 4355 )

#endif // TEXT_H__