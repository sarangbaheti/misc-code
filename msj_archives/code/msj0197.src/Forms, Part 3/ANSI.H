#ifndef ANSI_H__
#define ANSI_H__

// Attempts to bring VC++ into line with the ANSI C++ DWP.

// First, ANSI C defines NDEBUG when you're aren't debugging. MFC defines
// _DEBUG when you are. Set things up so you can use NDEBUG. Also arange
// for an MFC ASSERT macro to be mapped to an ANSI assert macro:

#ifdef ASSERT
#   define assert(x) ASSERT(x)
#else
#   include <assert.h>
#endif

#ifndef _DEBUG
#   define NDEBUG 1
#else
#	undef NDEBUG
#endif

// ANSI/ISO C++ is going to include a bool native type and true and fals
// keywords. These are reserved words to the VC++ 4.x compiler, but
// aren't implemented. Set up some macros so we can use them. (You
// can't use a typedef or enum because the words are reserved.)

#define bool  unsigned
#define true  1	
#define false 0

#endif // ANSI_H__
