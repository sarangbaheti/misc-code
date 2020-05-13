#include "stdafx.h"
#include "text.h"

/*virtual*/ Text::~Text( void )
{
	delete display_mechanism;	//TO DO
}

/*virtual*/	const String &Text::operator=( const String &r )
{
	return String::operator=(r);
}

/*virtual*/	const String &Text::operator=( const _TCHAR *r )
{
	return String::operator=(r);
}

/*virtual*/	const Text &Text::operator=( const Text &r )
{
	*(String *)this = r;
	return *this;
}

/*virtual*/ void Text::Observer::notify( Notifier *sender )
{
	// This function is a friend of class Text, a pointer
	// to which is in the owner field; It's called when the
	// String base class changes. Note that we have to turn
	// notify off in whichever object is being updated. Otherwise,
	// we'll just end up back here.

	Text *p = dynamic_cast<Text *>(sender);
	if( p )
	{
		// String base class was changed, transfer the new value
		// to the display.

		if( p->display_mechanism )
		{
			p->display_mechanism->notify_off();
			p->display_mechanism->import( *the_text_obj );
			p->display_mechanism->notify_on();
		}
	}
	else // User changed the Text_control, copy new value to
	{	 // the string base class of the associated text object.

		Text_control *display = dynamic_cast<Text_control*>(sender);
		assert(display);
		
		the_text_obj->notify_off();			// prevent string from notifying us
		display		->export(the_text_obj);	// modify the string
		the_text_obj->notify_on();			// re-enable notification
	}
}

/*virtual*/ bool Text::display(Window *win, const Rect &rect)
{
	// Create a static-text object displaying the text in the
	// String base class.
	//
	// This function is a good example of a method that appears
	// to have const behavior with respect to the user (thus
	// the const at the far right of the prototype) but can't
	// actually be const (thus the "myself" variable).

	display_mechanism =	new Text_control(
								Text_control::write_only,
								rect,
								win,
								*(const String *)this,
								&watcher
							  );
	return true;
}

/*virtual*/ void Text::hide( void )
{
	Text *myself = (Text*)this;

	delete myself->display_mechanism;
	myself->display_mechanism = NULL;
}

/*virtual*/ bool Text::interact(Window *win, const Rect &rect)
{
	// Create an editble representation of the String base
	// class. Any changes made by the user will transfer
	// automatically to the string.

	display_mechanism =	new Text_control(
									Text_control::read_write,
									rect,
									win,
									*(String *)this,
									&watcher
								  );
	return true;
}
