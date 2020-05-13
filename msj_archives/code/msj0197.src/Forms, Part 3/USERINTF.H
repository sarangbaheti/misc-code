#ifndef USERINTF_H__
#define USERINTF_H__

class Window;	// Forward references to classes in wrappers.h,
class Rect;		// avoids circular #include dependency;

class User_interface
{
public:
	virtual void hide	 ( void							 ) = 0;
	virtual bool display ( Window *win, const Rect &rect ) = 0;
	virtual bool interact( Window *win, const Rect &rect ) = 0;

	virtual ~User_interface( void ){}
};

#endif // USERINTF_H__