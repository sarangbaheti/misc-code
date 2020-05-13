#include "stdafx.h"
#include "formapp.h"
#include "text.h"

#include "formsDoc.h"
#include "formview.h"
#include "form.h"
//----------------------------------------------------------------------
#include "wrappers.h"
#include "form.h"
//----------------------------------------------------------------------
class Employee: public Form::Element
{
	Text name;

private: // Form-related functions
	virtual Form::Proxy *give_me_proxy_for(	const String &form_name,
											const String &attribute_id );
	virtual void		release_proxy	  (Form::Proxy *p);


public:
	Employee(const String &in_name): name(in_name){}
	void print(void) const{	ok_box( name );	}
};
//----------------------------------------------------------------------
Form::Proxy *Employee::give_me_proxy_for( const String &form_name,
										  const String &attribute_id )
{
	// Set things up so input flows directly from the Form into the
	// Employee's Name field.
	//
	// Since "this" is passed as a second argument to the Proxy
	// constructor, the Employee will be notified (with a release_proxy
	// message) when the Form shuts down.

	Form::Proxy *p = new Form::Proxy( &name, this );
	assert( p );
	return p;
}
//----------------------------------------------------------------------
void Employee::release_proxy(Form::Proxy *p)
{
	// Sent from the form when it shuts down instead of deleting the
	// proxy (because we passed our address to the Proxy's constructor).

	ok_box("Form has shut down\n");
	delete p;						// Form does not delete the proxy if
}									// we're notified. Proxy's destructor
									// never deletes the associated
									// User_interface object.
//----------------------------------------------------------------------
Form *make_form(void)
{
	// I get an internal compiler error if I try to just initialize
	// my_form, below, with the following new invocation. Putting the
	// new in a function call and initializing my_form with the
	// function's return value works fine, though.

	Form *form = new Form( "Test Form",
		new Form::Field( new Text("Name:"),		   Rect(0, 0, 50, 20)),
		new Form::Field("Employee", "Name",		   Rect(50,0, 200,20)),
		new Form::Field( new Form::Close_button(), Rect(80,25,120,45)),
		NULL
		);

	form->debug_print();
 	return form;
}

//----------------------------------------------------------------------
Form *form = make_form();
Employee homer("Homer");
//----------------------------------------------------------------------
void CFormsView::OnTest()
{
	form->debug_print();
	form->put_me_on_you( "Employee", homer );	// Put the employee on

	form->debug_print();
	form->interact(NULL, Rect(0,0,200,200));	// the form & display it.
}
//----------------------------------------------------------------------
void CFormsView::OnReport() 
{
	homer.print();
}


















void test( void ){}	// Called at top of CFormsApp::InitInstance()


#ifdef TEST_TEXT_CONTROL
	Text_control *p2 =
					new Text_control( Text_control::read_write,
					Rect(0,0,100,20),
					this,
					"Initial value",
					&fred
				  );
#endif
#ifdef TEST_USING_WINDOW
// It's really a kluge to put s at the global level (it's a memory
// leak), but I wanted all the test code in one place, and if I made it
// local to a function, it would go away when the function returned.
// Should probably make it a field in the CView derivative.

class Test {};
static Text s = "Initial Value";


void test( void )
{
	Window *p = new Window( Rect(0,0, 300, 300), "title");
	p->show();

	s.interact( p, Rect(0,0,100,20) ); // Request interactive I/O
}
	
void CFormsView::OnReport() 
{
	ok_box( s );
}
#endif

void CFormsView::OnModifyString() 
{
//	s = "Modified value";
}

void CFormsView::OnModifyCtrl() 
{
	// TODO: Add your command handler code here
	
}

