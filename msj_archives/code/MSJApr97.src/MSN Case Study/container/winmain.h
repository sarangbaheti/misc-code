#ifndef __WINMAIN_H__
#define __WINMAIN_H__

// the real max is about 2K
#define CCHMAXURL           INTERNET_MAX_URL_LENGTH


const ULONG CXBROWSER=640;
const ULONG CYBROWSER=480;
const ULONG MAX_OLECMD_BUFFER_SIZE = 60;
const ULONG MAX_STATUS_TEXT = MAX_PATH;

const ULONG ID_BASE = 500;
const ULONG ID_FRAME      = ID_BASE + 0;
const ULONG ID_EDIT       = ID_BASE + 1;
const ULONG ID_NAVIGATE   = ID_BASE + 2;
const ULONG ID_BACK       = ID_BASE + 3;
const ULONG ID_FORWARD    = ID_BASE + 4;
const ULONG ID_REFRESH    = ID_BASE + 5;

extern HINSTANCE    g_hInst;
extern HWND         g_hWndBrowser;
extern HWND         g_hWndFrame;

#define NElems(a)  (sizeof a / sizeof a[0])

// move (translate) the rectangle by (dx, dy)
inline VOID MoveRect(LPRECT prc, int dx, int dy)
{
    prc->left += dx;
    prc->right += dx;
    prc->top += dy;
    prc->bottom += dy;
}
const ULONG CYEDIT   = 20;
const ULONG CYBUTTON = 20;
const ULONG CXEDIT = 300;
const ULONG CXBUTTON = 100;

// debugging functions
#ifdef _DEBUG

#define _SIDE_ASSERT(b)     _ASSERT(b)
#define _SIDE_ASSERTE(b)    _ASSERTE(b)
#else
#define _SIDE_ASSERT(b)     (b)
#define _SIDE_ASSERTE(b)    (b)
#endif  // !_DEBUG

#endif
