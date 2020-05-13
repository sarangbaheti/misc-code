#ifndef WRAPPERS_H__
#define WRAPPERS_H__

#include <stddef.h>
#include "ansi.h"
#include "mystring.h"
#include "userintf.h"

#ifdef STD_DEBUG
	#include <dbg_out.h>
	using namespace Tools;
#endif

extern void ok_box( const String &s );	// generic message box

//======================================================================
// Rect
//======================================================================

class Rect: public CRect	// Can't use "Rectangle" because there's
{							// a global function with that name.
public:
	Rect( int l, int t, int r, int b ): CRect(l,t,r,b) {}
	Rect( const Rect &source		 ): CRect(source ) {}

	const Rect &expand_to_include( const Rect &rect );
}; 

#ifdef STD_DEBUG
	inline Debug_out &operator<<( Debug_out &out, Rect r )
	{
		out	<< "(l="	<< r.left
			<< ",t="	<< r.top
			<< ",r="	<< r.right
			<< ",b="	<< r.bottom
			<< ")";
		return out;
	}
#endif

//======================================================================
// Text_control
//======================================================================
// A text control handles both the display and input of text. It's
// an amalgam of a Windows Edit and Static-Text control.
//
// We must have an operator delete function because the one defined
// in CObject (which is an indirect base class of CEdit) will be
// unaccessable otherwise. We'd get:
//
//	 error C2247: 'delete' not accessible because 'Text_control'
//					uses 'private' to inherit from 'CEdit'
//
// MFC #defines new to DEBUG_NEW, so we have to undef it before
// we can declare the function.
#ifdef new
#undef new
#endif

class Text_control: private	CEdit
				  ,	public  Notifier
{
private:
	Notifiable		*observer;
	CWnd			*windows_obj;

	const Text_control &operator=( const Text_control &r );
	Text_control( const Text_control &r );

public:
	enum ctrl_type{ write_only, read_write };

	Text_control( ctrl_type		type,
				  const Rect	&position,
				  Window		*parent,
				  const String	&initial_value	= Empty_string,
				  Notifiable	*tell			= &Nobody );

	virtual ~Text_control();

	void import ( const String &s	);
	void export ( String *s			);
	void enable ( void				);
	void disable( void				);


public: // MFC Stuff required because of private inheritance

	void* PASCAL	operator new(size_t nSize);
	void* PASCAL	operator new(size_t, void* p);
	void PASCAL		operator delete(void* p);

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
	void* PASCAL	operator new(size_t nSize, LPCSTR lpszFileName, int nLine);
#endif

private: // MFC Stuff

	//{{AFX_VIRTUAL(Text_control)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Text_control)
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
//----------------------------------------------------------------------
inline void Text_control::enable( void )
{
	assert( windows_obj->m_hWnd );
	windows_obj->EnableWindow( TRUE );
}
//----------------------------------------------------------------------
inline void Text_control::disable( void )
{
	assert( windows_obj->m_hWnd );
	windows_obj->EnableWindow( FALSE );
}
//----------------------------------------------------------------------
inline void* PASCAL Text_control::operator new(size_t nSize)
{
	return CEdit::operator new(nSize);
}

inline void* PASCAL Text_control::operator new(size_t size, void* p)
{
	return CEdit::operator new( size, p );
}

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
inline void* PASCAL Text_control::operator new(size_t nSize, LPCSTR lpszFileName, int nLine)
{
	return CEdit::operator new(nSize, lpszFileName, nLine);
}
#endif

inline void Text_control::operator delete(void *p)
{
	CEdit::operator delete(p);
}

#ifdef _DEBUG	// put back standard mfc macro
#define new DEBUG_NEW
#endif


// include extensios for part 2 of the article:

#include "wrapper2.h"

#endif // WRAPPERS_H__
