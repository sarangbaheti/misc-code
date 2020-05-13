#ifndef MYSTRING_H__
#define MYSTRING_H__

#include "ansi.h"
#include "notify.h"

#include <iostream.h>
#include <iomanip.h>

#ifdef STD_DEBUG
	#include <dbg_out.h>	// Definition for std_debug and Debug_out
	using namespace Tools;
#endif

//=====================================================================
// Microsoft's <tchar.h> file contains support for (ANSI-compatible)
// UNICODE and (Microsoft-specific) multi-byte character Strings.
// The macros map to one of two values, depending on whether _UNICODE
// or _MBCS is defined. The mappings used in the current file are:
//
//			_UNICODE and		_UNICODE		_MBCS
//			_MBCS not defined	defined			defined
//
// _TCHAR		char			wchar_t			char
// _T("x")		"x"				L"x"			"x"
// _TEXT("x")	"x"				L"x"			"x"
// _tcscpy		strcmp			wcscmp			_mbscmp
// _tcslen		strlen			wcslen			_mbslen
// _tcscmp		strcpy			wcscpy			_mbscpy

#include <tchar.h>

//=====================================================================
class String : public Notifier
{
	class Buffer; // Buffer is a nested class, but I've moved the class
				  // declaration out of the class definition to reduce
				  // clutter;

	Buffer		*buf;
	Notifiable	*observer;
public:
	virtual
	~String( void										  );
	 String(				   Notifiable *tell = &Nobody );
	 String( const _TCHAR *p , Notifiable *tell = &Nobody );
	 String( const String &r , Notifiable *tell = &Nobody );

	const virtual String &operator= ( const String &r	);
	const virtual String &operator= ( const _TCHAR *p	);

	bool operator< ( const String &r ) const;
	bool operator> ( const String &r ) const;
	bool operator<=( const String &r ) const;
	bool operator>=( const String &r ) const;
	bool operator==( const String &r ) const;
	bool operator!=( const String &r ) const;

	virtual int			compare		( const String &r	) const;
	virtual ostream		&print		( ostream &dst		) const;
			bool		is_empty	( void				) const;

	#ifdef STD_DEBUG
		Debug_out &print_dbg( Debug_out &dst ) const;
	#endif

	#ifdef MFC
		String( const CString &s, Notifiable *tell = &Nobody);
		operator CString( void );
	#endif
};

extern const String Empty_string;
//=====================================================================
// class String::Buffer
//=====================================================================
// This is actually a nested-class definition. You could remove the
// String:: and move the following class definition inside the String
// class definition without affecting anything. Note that the
// "Class View" window in the MS Developer's Studio gets confused and
// doesn't list the class name, however (there's a little icon but not
// identifying class name).

class String::Buffer
{
	int		 ref_count;
	_TCHAR	 *buf;
public:
	virtual
	~Buffer	( void				);
	 Buffer	( const _TCHAR *p 	);
	 Buffer	( const Buffer &r	);

	Buffer		*attach		( void				);
	void		release		( void				);
	int			compare		( const Buffer &r	) const;
	ostream		&print		( ostream &dst		) const;
	bool		is_empty	( void				) const;

	#ifdef STD_DEBUG
		Debug_out &print_dbg( Debug_out &out ) const;
	#endif

	#ifdef MFC
		operator CString( void );
	#endif
};
//---------------------------------------------------------------------
inline String::Buffer::Buffer( const _TCHAR *p )
					: buf		( new _TCHAR[_tcsclen(p) + 1] )
					, ref_count	( 1 )
{
	assert( p );
	_tcscpy( buf, p );		// generic strcmp()
}
//---------------------------------------------------------------------
// The copy constructor should never be called. Declare a private version
// to prevent it from being called externally. Deliberately do not
// implement it so that the linker will kick out an error if anyone
// (like a friend or local function) manages to call it anyway. Note
// that this strategy (of forcing a link error) won't work on all
// compilers, since some will generate a default copy constructor even
// if a prototype is present in the class declaration. If this is
// the case, uncomment the function body, below, so you'll at least
// get a runtime error.
//
// inline String::Buffer::Buffer( const Buffer &r )
// {
//		assert(0);
// }
//---------------------------------------------------------------------
inline bool String::Buffer::is_empty( void ) const
{
	return *buf == '\0';
}
//---------------------------------------------------------------------
inline String::Buffer *String::Buffer::attach( void )
{
	assert(this);
	++ref_count;
	return this;
}
//---------------------------------------------------------------------
inline void String::Buffer::release( void )
{
	// The assert(this) assures that the function isn't called through
	// a null pointer. It probably wouldn't hurt to do it everywhere,
	// but doing it here saves me from having to do an assert(buf)
	// everywhere before release() is called in the String members.

	assert( this );
	assert( ref_count > 0 );

	if( --ref_count <= 0 )
		delete this;
}
//---------------------------------------------------------------------
inline int	String::Buffer::compare( const Buffer &r ) const
{
	assert( this	);
	assert( buf		);
	assert( r.buf	);

	return _tcscmp( buf, r.buf );	// generic strcmp()
}
//---------------------------------------------------------------------
inline ostream &String::Buffer::print( ostream &dst ) const
{
	#ifndef NDEBUG
		assert( this );
		dst << "ref_count=" << dec << ref_count
			<< ", buf=";
	#endif

	return dst << buf;
}
//---------------------------------------------------------------------
#ifdef STD_DEBUG
inline Debug_out &String::Buffer::print_dbg( Debug_out &dst ) const
{
	return dst << buf;
}
#endif
//---------------------------------------------------------------------
#ifdef MFC
inline String::Buffer::operator CString( void )
{
	// This function is resonably efficient only because the CString
	// itself is reference counted. If it weren't, I'd have to expose
	// the _TCHAR buf to the containing string class to avoid an
	// unnecessary copy of the string's contents.

	return CString( buf );
}
#endif
//=====================================================================
// class String
//=====================================================================
inline String::String( Notifiable *tell	)
						: buf	   (new Buffer(_T("")))
						, observer ( tell			  )
{}
//---------------------------------------------------------------------
inline String::String( const _TCHAR *p, Notifiable *tell )
						: buf	   ( new Buffer(p)	  )
						, observer ( tell			  )
{}
//---------------------------------------------------------------------
inline String::String( const String &r, Notifiable *tell	)
						: buf	   ( r.buf->attach()  )
						, observer ( tell			  )
{}
//---------------------------------------------------------------------
#ifdef MFC
inline String::String( const CString &s, Notifiable *tell	)
						: buf	  ( new Buffer( (const _TCHAR *)s ) )
						, observer( tell							)
{}
#endif
//---------------------------------------------------------------------
inline bool String::operator< (const String &r)const{ return compare(r)< 0;}
inline bool String::operator> (const String &r)const{ return compare(r)> 0;}
inline bool String::operator<=(const String &r)const{ return compare(r)<=0;}
inline bool String::operator>=(const String &r)const{ return compare(r)>=0;}
inline bool String::operator==(const String &r)const{ return compare(r)==0;}
inline bool String::operator!=(const String &r)const{ return compare(r)!=0;}
inline bool String::is_empty  ( void		  )const{ return buf->is_empty(); }
//---------------------------------------------------------------------
inline ostream &String::print( ostream &dst ) const
{
	#ifndef NDEBUG
		assert( this );
		dst << "buf=0x" << hex << setw(8) << buf
			<< ", ";
	#endif

	return buf->print( dst );
}
//---------------------------------------------------------------------
#ifdef STD_DEBUG
inline Debug_out &String::print_dbg( Debug_out &dst ) const
{
	return buf->print_dbg( dst );
}
#endif
//---------------------------------------------------------------------
#ifdef MFC
inline String::operator CString( void )
{
	return CString( *buf );
}
#endif
//=====================================================================
// Global functions
//=====================================================================
inline ostream &operator<<( ostream &out, const String &s )
{
	return s.print( out );
}
//---------------------------------------------------------------------
#ifdef STD_DEBUG
inline Debug_out &operator<<(Debug_out &out, const String &s )
{
	return s.print_dbg(out);
}
#endif
//=====================================================================
#endif // MYSTRING_H__
