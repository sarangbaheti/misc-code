// form.cpp

#include "stdafx.h" // Needed only to keep compiler happy
#include "form.h"
#include <stdarg.h>

//===================================================================
// Form
//===================================================================

/*virtual*/ Form::~Form( void )
{
	assert( this );

	// Delete the fields, first releasing the proxies

	for(Field **p=fields; p < &fields[max_fields] && *p ;)
	{
		(*p)->release_proxy();
		delete( *p++ );
	}
}
//-------------------------------------------------------------------
// The initializer-list element "observer(this)" causes the compiler
// to kick out a:
//
// warning C4355: 'this' : used in base member initializer list.
//
// Normally, it would be dangerous for the contained-object
// constructor to access the container class because the contained
// objects are initialized before the container is initialized.
// We don't do that here, and it's convient to pass a pointer
// to the container at construction time, so turn off the warning.

#pragma warning( disable : 4355 )

Form::Form( const String &form_name, Field *first, ... )
					: current	( fields	 )
					, name		( form_name	 )
					, size		( 0, 0, 0, 0 )
					, destroyer	( this		 )
{
	// Initialize the Form with its name and fields. Any
	// fields in excess of max_fields are silently discarded.
	//
	// There's nothing wrong with any function (including a constructor)
	// having a variable number of arguments. The argument passed
	// to va_start MAY NOT be a reference, however becuase taking
	// the address of the reference gets you the referenced thing.

	va_list	field_list;
	va_start( field_list, first );

	memset( fields, 0, sizeof(fields) );

	Field *field = first;
	while( field && (current < &fields[max_fields]) )
	{
		size.expand_to_include( field->size() );
		*current++ = field;
		field = va_arg(field_list, Field *);
	}

	va_end( field_list );
}

#pragma warning( default : 4355 )
//-------------------------------------------------------------------
bool Form::add_field( Field *new_field	)
{
	assert( this	  );
	assert( new_field );

	if( current < &fields[max_fields] )
	{
		*current++ = new_field;
		size.expand_to_include( new_field->size() );
		return true;
	}
	return false;
}
//-------------------------------------------------------------------
void Form::release_proxies( void )
{
	assert( this );

	Field **current = fields;	
	while( current < &fields[max_fields] && *current )
		(*current++)->release_proxy();
}
//-------------------------------------------------------------------
void Form::put_me_on_you( const String 	&class_name,
						  const	Element &element )
{
	assert( this		 );
	assert( &element	 );
	assert( &class_name	 );

	Field **current = fields;	
	for(; current < &fields[max_fields] && *current; ++current )
	{
		const String *id = (*current)->if_in_class_return_id(class_name);
		if( id )
		{
			Element &e	= (Element &)element;
			Proxy *p	= e.give_me_proxy_for( name, *id );
			if( p )
				(*current)->attach_proxy( p );
		}
	}
}
//-------------------------------------------------------------------
void Form::remove_me_from_you( const String &class_name )
{
	assert( this		 );
	assert( &class_name	 );

	// Remove all proxies on fields associated with given class_name

	Field **current = fields;	
	for(; current < &fields[max_fields] && *current; ++current )
	{
		if( (*current)->if_in_class_return_id(class_name) )
			(*current)->release_proxy();
	}
}
//-------------------------------------------------------------------
/*virtual*/ void Form::hide( void )
{
	assert( this		 );

	Field *const *current = fields;	
	while( current < &fields[max_fields] )
		(*current++)->hide();
}
//-------------------------------------------------------------------
/*virtual*/ bool Form::display( Window *win, const Rect &rect )
{
	assert( this	 );
	assert( win		 );
	assert( &rect	 );

	// Display the form, either on the indicated Window or on a
	// manufactured popup window if win is NULL. The Rect argument
	// is ignored. (Note that, since the Field's display and interact
	// handlers also ignore the rect argument, I just pass it through
	// to avoid having to create a dummy rectangle).
	//
	// If a popup window is created, the form name is used for the
	// title and the windows size is exactly large enough to hold
	// all fields.

	Window *surface= win ? win
						 : new Window(size, name, &destroyer) ;

	Field *const *current = fields;
	while( current < &fields[max_fields] )
		(*current++)->display(surface, rect);
	return true;
}
//-------------------------------------------------------------------
/*virtual*/ bool Form::interact( Window *win, const Rect &rect )
{
	assert( this	);
	assert( &rect	);

	// See comments in display() function, above.
	Window *surface = win ? win : new Window(size, name, &destroyer);
	surface->show();

	Field **fieldv = fields;	
	while( *fieldv &&  (fieldv < &fields[max_fields]) )
		(*fieldv++)->interact(surface, rect);

	return true;
}
//-------------------------------------------------------------------
#if !defined(NDEBUG) && defined(STD_DEBUG)
#include "text.h"

void Form::debug_print(void)
{
	std_debug << "Form @" << this
			  << " name[" << name << "]"
			  << " size"  << size
			  << " fields:\n" ;

	Field **fieldv = fields;	
	for(; *fieldv &&  (fieldv < &fields[max_fields]) ; ++fieldv)
	{
		std_debug << "   Field["<< (fieldv-fields)			<< "]";
		std_debug << " class("	<< (*fieldv)->class_name	<< ")";
		std_debug << " attrib("	<< (*fieldv)->attribute_id	<< ")";
		std_debug << " posn"	<< (*fieldv)->position		<< ")";
		std_debug << " proxy @" << (*fieldv)->proxy	;
		if( (*fieldv)->proxy )
		{
			std_debug << " crtr @"	<< (*fieldv)->proxy->creator ;
			
			Text *text = dynamic_cast<Text *>( (*fieldv)->proxy->ui );
			if( text )
				std_debug << " Text(\"" << *text << ")\n" ;

			else if( dynamic_cast<Form::Close_button *>( (*fieldv)->proxy->ui ) )
				std_debug << "(close button)\n";

			else
				std_debug << "***UNKNOWN PROXY***" ;
		}
		std_debug << "\n";
	}
}

#endif

//===================================================================
// Form::Destroyer
//===================================================================

/*virtual*/ void Form::Destroyer::notify( class Notifier *sender )
{
	// This function is called when the window that the form is
	// using as its drawing surface is shut down by the user. It
	// destroys the associated Form, which causes the proxies to
	// be released.

	assert( dynamic_cast<Window*>(sender) );
	delete form;
}

//===================================================================
// Form::Field
//===================================================================

/*virtual*/ Form::Field::~Field( void )
{
}
//-------------------------------------------------------------------
#include "text.h"
Form::Field::Field( User_interface	*static_attrib,
					const Rect		 &position_in )
			: mode			( output )
			, class_name	( "" )
			, attribute_id	( "" )
			, position		( position_in	)
			, proxy			( new Proxy(static_attrib) )
{
	#if (!defined(NDEBUG) && defined(STD_DEBUG))
		std_debug << "Adding static_attrib @" << static_attrib << "\n";
	
		Text *txt = dynamic_cast<Text*>(static_attrib);
		if( txt )
		{
			std_debug << "\t(value is " << *txt << " @" << txt << ")\n" ;
			return;
		}
	#endif
}
//-------------------------------------------------------------------
Form::Field::Field( const String	&class_name_in,
					const String	&attribute_id_in,
					const Rect		&position_in,
					const Behavior	mode_in /*= input_output */ )
			: mode			( mode_in			)
			, class_name	( class_name_in		)
			, attribute_id	( attribute_id_in	)
			, position		( position_in		)
			, proxy			( NULL				)
{
}
//-------------------------------------------------------------------
const String *Form::Field::
if_in_class_return_id(const String &candidate )const
{
	assert( this		);
	assert( &candidate	);

	return (class_name == candidate) ? &attribute_id : NULL;
}
//-------------------------------------------------------------------
void Form::Field::attach_proxy(Proxy *proxy)
{
	assert( this			  );
	assert( proxy			  );
	assert( this->proxy==NULL ); // Illegal if a proxy already attached

	this->proxy = proxy;
}
//-------------------------------------------------------------------
// Note for release_proxy, hide, display, interact. It's not an error
// if a field that doesn't have a proxy attached to itself is displayed,
// etc. It's just a no-op.
//
void Form::Field::release_proxy(void)
{
	assert( this );

	if( proxy )
		proxy->release();
	proxy = NULL;
}
//-------------------------------------------------------------------
/*virtual*/ void Form::Field::hide( void )
{
	assert( this	);

	if( proxy )
		proxy->hide();
}
//-------------------------------------------------------------------
/*virtual*/ bool Form::Field::display( Window *win, const Rect &rect )
{
	assert( this	);
	assert( win		);
	assert( &rect	);
	
	return proxy ? proxy->display( win, rect ) : true;
}
//-------------------------------------------------------------------
/*virtual*/ bool Form::Field::interact( Window *win, const Rect &rect )
{
	// Display the current field. The rect argument is ignored in
	// favor of the position rectangle stored in the Field itself.

	assert( this  );
	assert( win	  );
	assert( &rect );
	assert( proxy );

	return	(proxy==NULL  ) ? true :
			(mode == input)	? proxy->interact( win, position ) :
							  proxy->display ( win, position ) ;
}
//-------------------------------------------------------------------
const Rect &Form::Field::size( void )
{
	// Normally, I wouldn't return a reference to a field in an object
	// because the caller could modify the field. Here, it seems safe
	// because the fuction is private, and called only from the Form
	// class.

	return position;
}

//===================================================================
// Form::Proxy
//===================================================================

/*virtual*/ Form::Proxy::~Proxy(void){}
//-------------------------------------------------------------------
Form::Proxy::Proxy(	User_interface *attribute,
					Form::Element  *notify_me_rather_than_delete_proxy )
		: ui		( attribute	)
		, creator	( notify_me_rather_than_delete_proxy /*=NULL*/ )
{}
//-------------------------------------------------------------------
void Form::Proxy::release( void )
{
	assert( this );

	if( creator )
		creator->release_proxy(this);
	else
	{
		if( ui )
			delete ui;
		delete this;
	}
}
//-------------------------------------------------------------------
/*virtual*/ void Form::Proxy::hide( void )
{
	assert( this );
	assert( ui	 );
	ui->hide();
}
//-------------------------------------------------------------------
/*virtual*/ bool Form::Proxy::display( Window *win, const Rect &rect )
{
	assert( this );
	assert( ui	 );
	return ui->display( win, rect );
}
//-------------------------------------------------------------------
/*virtual*/ bool Form::Proxy::interact( Window *win, const Rect &rect )
{
	assert( this );
	assert( ui	 );
	return ui->interact( win, rect );
}

//===================================================================
// Form::Element
//===================================================================

/*virtual*/ Form::Element::~Element(void){}
//-------------------------------------------------------------------
/*virtual*/ void Form::Element::release_proxy(Proxy *p)
{
	// Empty on purpose. The default action is to not release
	// anything. The derived class can define an override if it
	// provides proxies that need to be released.
}

//===================================================================
// Form::Close_button
//===================================================================
Form::Close_button::~Close_button(){ if(button) delete button; }
Form::Close_button::Close_button() : button(NULL), parent(NULL){}
//-------------------------------------------------------------------
/*virtual*/ 
void Form::Close_button::hide( void )
{
	assert( this );

	if( button )
	{
		delete button;
		button = NULL;
	}
}
//-------------------------------------------------------------------
/*virtual*/ 
bool Form::Close_button::display( Window *win, const Rect &position )
{
	assert(this);
	assert(win );
	assert(&position);

	parent = win;
	button = new Button( "Close", position, this );
	button->show(win);
	return true;
}
//-------------------------------------------------------------------
/*virtual*/ 
bool Form::Close_button::interact( Window *win, const Rect &position )
{
	return display(win, position);
}
//-------------------------------------------------------------------
/*virtual*/
void Form::Close_button::notify( class Notifier *sender )
{
	// This function is called when the window that the form is
	// using as its drawing surface is shut down by the user. It
	// destroys the associated Form, which causes the proxies to
	// be released.

	Button *b = dynamic_cast<Button*>(sender);
	assert(b);
	assert(b==button);
	assert(parent);

	parent->DestroyWindow();
}

