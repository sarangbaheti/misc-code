#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <crtdbg.h>
#include <olectl.h>
#include <shlobj.h>
#include <docobj.h>
#include <servprov.h>
#include <stdlib.h>
#include <shlobj.h>
#include <exdisp.h>
#include "winmain.h"
#include "events.h"
#include "ctr.h"


#define APPNAME "MSJ WebBrowser OC container"

LPCSTR szFrameClass  = "MSJ OLE Container Frame Class";

BOOL RegisterClasses(HINSTANCE hInstance);
BOOL InitApplication(HINSTANCE hInstance, LPSTR lpCmdLine);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char szAppName[] = APPNAME; // The name of this application
char szTitle[]   = APPNAME; // The title bar text

HINSTANCE   g_hInst       = 0; // current instance
HWND        g_hWndBrowser = 0;
HWND        g_hWndFrame   = 0;
HWND        g_hWndEdit    = 0;
HWND        g_hWndBtn     = 0;
CMSJOCCtr * g_pCtr        = 0;

//+---------------------------------------------------------------------------
//
//  Function:   WinMain
//
//  Synopsis:   standard entrypoint for GUI Win32 apps
//
//----------------------------------------------------------------------------
int APIENTRY
WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR     lpCmdLine,
        int       nCmdShow)
{
    MSG                      msg;
    LPOLEINPLACEACTIVEOBJECT pIPAO;

#ifdef NEVER
    _CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_ALLOC_MEM_DF);
#endif

#ifdef NEVER
    // uncomment this if you need to track a CRT debug heap reported mem leak
    // put the integer value reported by heap in {n) below
    _CrtSetBreakAlloc(n);
#endif

    if (FAILED(::OleInitialize(NULL)))
        return FALSE;

    if (!::InitApplication(hInstance, lpCmdLine))
        return (FALSE);

    // Perform application initialization:
    if (!::InitInstance(hInstance, nCmdShow))
        return (FALSE);

    // Main message loop:
    while (::GetMessage(&msg, NULL, 0, 0))
    {
        if (g_pCtr)
        {
            pIPAO = g_pCtr->GetIPAObject();
            if (pIPAO && !pIPAO->TranslateAccelerator(&msg))
               continue;  // IPA object handled; we're done.

            // the inplaceactive object didn't consume the message,
            // so continue here.
        }
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    _CrtDumpMemoryLeaks();

    return (msg.wParam);
}

//+---------------------------------------------------------------------------
//
//  Function:   RegisterClasses
//
//  Synopsis:   register all our window classes.
//
//  Arguments:  [hInstance] -- HINSTANCE of this module.
//
//----------------------------------------------------------------------------
BOOL RegisterClasses(HINSTANCE hInstance)
{
    WNDCLASS wc;
    BOOL bRC = FALSE;

    // Fill in window class structure with parameters that describe
    // the main window.
    ::memset(&wc, 0, sizeof wc);

    wc.style         = CS_DBLCLKS;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbWndExtra    = 4;
    wc.hInstance     = hInstance;
    wc.hIcon         = ::LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = szAppName;

    if (FALSE == ::RegisterClass(&wc))
        return FALSE;

    // now register the framewindow class.
    wc.lpfnWndProc   = (WNDPROC) CMSJOCCtr::WndProc;
    wc.lpszClassName = szFrameClass;

    return  ::RegisterClass(&wc) ? TRUE : FALSE;
}

//+---------------------------------------------------------------------------
//
//  Function:   InitApplication
//
//  Synopsis:   detects if this is not first instance + registers classes.
//              BUGBUG - Program Management needs to decide whether we
//              permit multiple instances or not.  Right now it doesn't
//
//----------------------------------------------------------------------------
BOOL InitApplication(HINSTANCE hInstance, LPSTR lpCmdLine)
{
    HWND      hwnd;

    g_hInst = hInstance;

    // Win32 will always set hPrevInstance to NULL, so lets check
    // things a little closer. This is because we only want a single
    // version of this app to run at a time
    hwnd = ::FindWindow(szAppName, NULL);   // search by class name
    if (hwnd)
    {
        // We found another version of ourself. Lets defer to it:
        if (::IsIconic(hwnd))
            ::ShowWindow(hwnd, SW_RESTORE);

        ::SetForegroundWindow(hwnd);

        return FALSE;
    }

    // Register the window class and return success/failure code.
    return ::RegisterClasses(hInstance);
}

//+---------------------------------------------------------------------------
//
//  Function:   InitInstance
//
//  Synopsis:   standard main window creation routine, tweaked for our needs
//
//----------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // create the browser
    g_hWndBrowser = ::CreateWindow(
                szAppName,
                szTitle,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                hInstance,
                0);

    if (!g_hWndBrowser)
        return (FALSE);

    ::ShowWindow(g_hWndBrowser, nCmdShow);
    ::UpdateWindow(g_hWndBrowser);

    return (TRUE);
}


//+---------------------------------------------------------------------------
//
//  Function:   WndProc
//
//  Synopsis:   very unusual type of function - gets called by system to
//              process windows messages.
//
//  Arguments:  same as always.

//----------------------------------------------------------------------------
LRESULT CALLBACK
WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    UINT        wmId;
    INT         wmEvent;
    PAINTSTRUCT ps;
    HDC         hdc;
    LPMSJOCCtr  pCtr;
    RECT        rc;
    INT         x;

    if (message == WM_NCCREATE)
    {
        pCtr = new CMSJOCCtr(hWnd);
        if (!pCtr)
            return -1;

        g_pCtr = pCtr;

        ::SetWindowLong(hWnd, GWL_USERDATA, (LONG)pCtr);
        goto DoDefault;
    }
    else
    {
        pCtr = (LPMSJOCCtr)::GetWindowLong(hWnd, GWL_USERDATA);
    }

    switch (message)
    {
    case WM_CREATE:
        g_hWndFrame = ::CreateWindow(
                    szFrameClass,
                    "",
                    WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
                    0,0,0,0,
                    hWnd,
                    (HMENU) ID_FRAME,
                    g_hInst,
                    (LPCREATESTRUCT)pCtr);

        if (!g_hWndFrame)
            return -1;

        g_hWndEdit = ::CreateWindow(
                           "edit",
                           "",
                           WS_CHILD | WS_VISIBLE,
                           0,0, CXEDIT, CYBUTTON,
                           hWnd,
                           (HMENU)ID_EDIT,
                           g_hInst,
                           0);

        if (!g_hWndEdit)
            return -1;

        x = CXEDIT;

        if (!::CreateWindow(
                       "button",
                       "Navigate!",
                       WS_CHILD | WS_VISIBLE,
                       x, 0, CXBUTTON, CYEDIT,
                       hWnd,
                       (HMENU) ID_NAVIGATE,
                        g_hInst,
                        0))
        {
            return -1;
        }

        x += CXBUTTON + 1;

        if (!::CreateWindow(
                       "button",
                       "Back",
                       WS_CHILD | WS_VISIBLE,
                       x, 0, CXBUTTON, CYEDIT,
                       hWnd,
                       (HMENU) ID_BACK,
                       g_hInst,
                        0))
        {
            return -1;
        }

        x += CXBUTTON + 1;

        if (!::CreateWindow(
                       "button",
                       "Forward",
                       WS_CHILD | WS_VISIBLE,
                       x, 0, CXBUTTON, CYEDIT,
                       hWnd,
                       (HMENU) ID_FORWARD,
                       g_hInst,
                        0))
        {
            return -1;
        }

        x += CXBUTTON + 1;

        if (!::CreateWindow(
                       "button",
                       "Refresh",
                       WS_CHILD | WS_VISIBLE,
                       x, 0, CXBUTTON, CYEDIT,
                       hWnd,
                       (HMENU) ID_REFRESH,
                       g_hInst,
                        0))
        {
            return -1;
        }

        if (pCtr->CreateBrowserOC(g_hWndEdit))
            return -1;

        break;

    case WM_CTLCOLOREDIT:
        return (LRESULT)::GetStockObject(GRAY_BRUSH);
        break;

    case WM_ACTIVATEAPP:
        pCtr->OnActivateApp(wParam, lParam);
        break;

    case WM_ERASEBKGND:
        ::OutputDebugString("Erase background called\n");
        goto DoDefault;
        break;

    case WM_SIZE:
        if (SIZE_MINIMIZED != wParam)
            pCtr->DoLayout(LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_QUERYNEWPALETTE:
    case WM_PALETTECHANGED:
        if (WM_QUERYNEWPALETTE == message)
            return pCtr->QueryNewPalette();
        else
            return pCtr->PaletteChanged(wParam);
        break;

    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        //Parse the menu selections:
        switch (wmId)
        {
        case ID_NAVIGATE:
        {
            CHAR    achURL[MAX_PATH];
            if (::GetWindowText(g_hWndEdit, achURL, NElems(achURL)))
                !pCtr->Navigate(achURL);
            break;
        }

        case ID_BACK:
            pCtr->Back();
            break;

        case ID_FORWARD:
            pCtr->Forward();
            break;

        case ID_REFRESH:
            pCtr->Refresh();
            break;

        default:
            goto DoDefault;
            break;
        }
        break;

    case WM_PAINT:
    {
        if (pCtr->GetState() < OS_INPLACE)
        {
            hdc = ::BeginPaint(hWnd, &ps);
            ::GetWindowRect(g_hWndFrame, &rc);
            ::MapWindowPoints(g_hWndFrame, hWnd, (LPPOINT) &rc, 2);
            pCtr->Paint(hdc, &rc);
            ::EndPaint(hWnd, &ps);
            break;
        }
        else
            goto DoDefault;
    }

    case WM_DESTROY:
        pCtr->ShutDown();
        ::CoFreeUnusedLibraries();
        ::OleUninitialize();
        ::PostQuitMessage(0);
        break;

    case WM_NCDESTROY:
        ::SetWindowLong(hWnd, GWL_USERDATA, 0);
        g_pCtr = 0;
        pCtr->Release();
        break;

    default:

DoDefault:
        return ::DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
