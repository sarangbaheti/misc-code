// form.h
#ifndef FORM_H__
#define FORM_H__

#include "mystring.h"	// Discussed in Part 1.
#include "userintf.h"	// Discussed in Part 1.
#include "wrappers.h"	// Discussed in Part 1.

// Notes:
// (*)	The Form::fields member is an array for the time
//		being, it should really be variable-length collection.
//
// (*)	Forms cannot be copied, so the operator= and copy ctor are
//		private. There's not need to define the functions, simple
//		prototypes are sufficient. (The linker kicks out an error
//		if the function isn't defined and someone manages to call
//		it.)

class Form : public	 User_interface
{
public:
	class Field;		// These classes are nested inside the Form
	class Element;		// class's name space, not external
	class Proxy;		// references. Definitions are below.
	class Close_button;

public:	
	virtual
	~Form( void	);
	 Form( const String &form_name, Field *first, ... );

private:
	Form			( const Form &r );	// do not define
	Form &operator=	( const Form &r );	// do not define

public:
	bool add_field			( Field *new_field			);
	void release_proxies	( void						);
	void put_me_on_you		( const String  &class_name,
							  const Element &ele		);
	void remove_me_from_you	( const String  &class_name	);

public: // overrides for User_interface base class
	virtual void hide	 ( void							 );
	virtual bool display ( Window *win, const Rect &rect );
	virtual bool interact( Window *win, const Rect &rect );


private:
	String		name;
	Rect		size;
	Form::Field **current;

	enum { max_fields = 32 };
	Form::Field	*fields[max_fields];// fields on the form, should be a
									// "collection" instead of an array.

	// Create an internal class so that the Window can notify us
	// when we're destroyed. Make it a friend so that it can release
	// the proxies.

	class Destroyer: public Notifiable
	{
		Form *form;
		virtual void notify( class Notifier *sender );
	public:
		Destroyer(Form *notifiee): form(notifiee) {}
	}
	destroyer;
	friend class Form::Destroyer;

public:
	void debug_print(void);
};

#if (defined(NDEBUG) || !defined(STD_DEBUG)) // not debuggging
	inline void Form::debug_print(void){}
#endif

//-------------------------------------------------------------------
// Form::Field
//
// It is a serious error for the same attribute proxy to be used in
// more than one form. This problem can be solved by reference-
// counting the proxy, but is not solved in the current implementation.
//
// A Field can't be copied.

class Form::Field: public User_interface
{
public:
	enum Behavior{ input_output=0, input=0, output=1 };

	virtual
	~Field( void										);
	 Field(		  User_interface *static_attrib,
			const Rect			 &position				);
	 Field( const String		 &class_name,
			const String		 &attribute_id,
			const Rect			 &position,
			const Behavior		 behavior= input_output	);

private:
	 Field					(const Field &); // Do not define.
	 const Field &operator=	(const Field &);

public:
	const String *if_in_class_return_id (const String   &cls_name)const;
	void		 attach_proxy		    (Proxy			*proxy   );
	void		 release_proxy			(void					 );

public: // overrides for User_interface base class
	virtual void hide	 ( void							 );
	virtual bool display ( Window *win, const Rect &rect );
	virtual bool interact( Window *win, const Rect &rect );

private:
	Behavior	mode;
	String		class_name;
	String		attribute_id;
	Rect		position;
	Proxy		*proxy;		// Supplied by Form::Element if not
							// static, otherwise comes from user
							// via Form::Form or Form::add_field.
private: friend class Form;
	const Rect	&size( void );

	friend void Form::debug_print(void);
};
//-------------------------------------------------------------------
class Form::Proxy : public User_interface
{
public:
	 virtual
	~Proxy(void);
	 Proxy(	User_interface *attribute_proxy,
			Element		   *notify_me_rather_than_delete_proxy = NULL);

	void release(void);

public: // overrides for User_interface base class
	virtual void hide	 ( void							 );
	virtual bool display ( Window *win, const Rect &rect );
	virtual bool interact( Window *win, const Rect &rect );

protected:	User_interface	*ui;
private:	Form::Element	*creator;

			friend void Form::debug_print(void);
};

//-------------------------------------------------------------------
// Elements can be copied, but there's nothing to copy at this level,
// so leave it up to the derived class. Note that, even though
// give_me_a_proxy_for(...) doesn't modify the class, it is not
// const because the returned proxy could modify the class.

class Form::Element
{
public:
	virtual ~Element(void);

private: friend class Form;
	virtual Proxy *give_me_proxy_for(const String &form_name,
									 const String &attribute_id )=0;
private: friend class Proxy;
	virtual void release_proxy(Proxy *p);

	friend void Form::debug_print(void);
};
//----------------------------------------------------------------------
class Form::Close_button: public User_interface
						, public Notifiable
{
	Button *button;
	Window *parent;
public:
	virtual
	~Close_button(void);
	 Close_button(void);

	virtual void hide	 ( void								 );
	virtual bool display ( Window *win, const Rect &position );
	virtual bool interact( Window *win, const Rect &position );
	
	virtual void notify	 ( class Notifier *sender			 );

	friend void Form::debug_print(void);
};
//----------------------------------------------------------------------
#endif FORM_H__
