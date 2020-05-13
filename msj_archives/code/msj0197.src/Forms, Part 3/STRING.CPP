#include "stdafx.h"
#include "mystring.h"
//=====================================================================
// class String::Buffer
//=====================================================================
const String Empty_string;
//=====================================================================
/*virtual*/ String::Buffer::~Buffer( void )
{
	assert( ref_count == 0 );
	delete[] buf;
}
//=====================================================================
// class String
//=====================================================================
/*virtual*/ String::~String( void )
{
	assert(this);
	assert(buf );

	buf->release();
}
//---------------------------------------------------------------------
/*virtual*/ int String::compare( const String &r ) const
{
	assert( this );
	assert( buf	 );

	return buf->compare( *r.buf );
}
//---------------------------------------------------------------------
/*virtual*/ const String &String::operator=( const String &r )
{
	assert( this );

	if( this != &r )
	{
		buf->release();
		buf = r.buf->attach();
	}

	notify(observer);
	return *this;
}
//---------------------------------------------------------------------
/*virtual*/ const String &String::operator=( const _TCHAR *p )
{
	assert( this );
	buf->release();
	buf = new Buffer( p );
	notify(observer);
	return *this;
}
