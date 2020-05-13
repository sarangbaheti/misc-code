/**************************************************************************

   File:          CoolBar.c
   
**************************************************************************/

#define STRICT
//#define UNICODE

/**************************************************************************
   Include Files
**************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "resource.h"

/**************************************************************************
   Local Function Prototypes
**************************************************************************/

int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT HandleCommand(HWND, WPARAM, LPARAM);
BOOL CALLBACK About(HWND, UINT, WPARAM, LPARAM);
HWND BuildCoolbar(HWND);
LRESULT HandleNotify(HWND, WPARAM, LPARAM);
void MoveCoolbar(HWND);
void UpdateMenu(HWND, HMENU);

/**************************************************************************
   Global Variables
**************************************************************************/

#define ID_COOLBAR   1000
#define ID_COMBOBOX  2000
#define ID_BUTTON    2001

#define TOP    0x00
#define LEFT   0x01
#define BOTTOM 0x02
#define RIGHT  0x03

HINSTANCE   g_hInst;
WORD        g_wSide;
TCHAR       g_szClassName[] = TEXT("CoolBarSampleClass");

/******************************************************************************

   WinMain

******************************************************************************/

int PASCAL WinMain(  HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
{
MSG      msg;
INITCOMMONCONTROLSEX iccex;

iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
iccex.dwICC = ICC_COOL_CLASSES;
InitCommonControlsEx(&iccex);

if(!hPrevInstance)
   if(!InitApplication(hInstance))
      return FALSE;

if (!InitInstance(hInstance, nCmdShow))
   return FALSE;

while(GetMessage( &msg, NULL, 0x00, 0x00))
   {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
   }

return msg.wParam;
}

/*****************************************************************************

   InitApplication

*****************************************************************************/

BOOL InitApplication(HINSTANCE hInstance)
{
WNDCLASS  wc;

wc.style          = 0;
wc.lpfnWndProc    = (WNDPROC)MainWndProc;
wc.cbClsExtra     = 0;
wc.cbWndExtra     = 0;
wc.hInstance      = hInstance;
wc.hIcon          = LoadIcon(NULL, MAKEINTRESOURCE(IDI_MAINICON));
wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
wc.lpszMenuName   = MAKEINTRESOURCE(IDM_MAINMENU);
wc.lpszClassName  = g_szClassName;

return RegisterClass(&wc);
}

/*****************************************************************************

   InitInstance

*****************************************************************************/

BOOL InitInstance(   HINSTANCE hInstance,
                     int nCmdShow)
{
HWND  hWnd;

g_hInst = hInstance;

hWnd = CreateWindowEx(  0,
                        g_szClassName,
                        TEXT("CoolBar Application"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

if (!hWnd)
   return FALSE;

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);

return TRUE;

}

/*****************************************************************************

   MainWndProc

*****************************************************************************/

LRESULT CALLBACK MainWndProc( HWND hWnd,
                              UINT uMessage,
                              WPARAM wParam,
                              LPARAM lParam)
{
switch (uMessage)
   {
   case WM_CREATE:
      g_wSide = TOP;

      BuildCoolbar(hWnd);
      break;

   case WM_NOTIFY:
      return HandleNotify(hWnd, wParam, lParam);
   
   case WM_INITMENUPOPUP:
      UpdateMenu(hWnd, (HMENU)wParam);
      break;
   
   case WM_SIZE:
      MoveCoolbar(hWnd);
      break;

   case WM_DESTROY:
      PostQuitMessage(0);
      break;

   case WM_COMMAND:
      return HandleCommand(hWnd, wParam, lParam);

   default:
      break;
   }
return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

/*****************************************************************************

   HandleCommand

*****************************************************************************/

LRESULT HandleCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
switch (wParam)
   {
   case ID_BUTTON:
      MessageBeep(MB_OK);
      break;

   case ID_COMBOBOX:
      MessageBeep(MB_OK);
      break;

   case IDM_TOP:
      if(g_wSide != TOP)
         {
         //destroy the existing Coolbar
         DestroyWindow(GetDlgItem(hWnd, ID_COOLBAR));
         
         //change to the new side
         g_wSide = TOP;

         //create the new Coolbar
         BuildCoolbar(hWnd);

         /*
         We have to do this because the coolbar will recalculate it's 
         rectangle after the first time it is sized.
         */
         MoveCoolbar(hWnd);
         }
      break;

   case IDM_BOTTOM:
      if(g_wSide != BOTTOM)
         {
         //destroy the existing Coolbar
         DestroyWindow(GetDlgItem(hWnd, ID_COOLBAR));
         
         g_wSide = BOTTOM;

         //create the new Coolbar
         BuildCoolbar(hWnd);

         /*
         We have to do this because the coolbar will recalculate it's 
         rectangle after the first time it is sized.
         */
         MoveCoolbar(hWnd);
         }
      break;

   case IDM_LEFT:
      if(g_wSide != LEFT)
         {
         //destroy the existing Coolbar
         DestroyWindow(GetDlgItem(hWnd, ID_COOLBAR));
         
         g_wSide = LEFT;

         //create the new Coolbar
         BuildCoolbar(hWnd);

         /*
         We have to do this because the coolbar will recalculate it's 
         rectangle after the first time it is sized.
         */
         MoveCoolbar(hWnd);
         }
      break;

   case IDM_RIGHT:
      if(g_wSide != RIGHT)
         {
         //destroy the existing Coolbar
         DestroyWindow(GetDlgItem(hWnd, ID_COOLBAR));
         
         g_wSide = RIGHT;

         //create the new Coolbar
         BuildCoolbar(hWnd);

         /*
         We have to do this because the coolbar will recalculate it's 
         rectangle after the first time it is sized.
         */
         MoveCoolbar(hWnd);
         }
      break;
   
   case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
   
   case IDM_ABOUT:
      DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;   
      
   }
return 0;
}

/*****************************************************************************

   About

*****************************************************************************/

BOOL CALLBACK About( HWND hDlg, 
                     UINT uMessage, 
                     WPARAM wParam, 
                     LPARAM lParam)
{
switch (uMessage)
   {
   case WM_INITDIALOG:
      return TRUE;
      
   case WM_COMMAND:
      switch(wParam)
         {
         case IDOK:
            EndDialog(hDlg, IDOK);
            return TRUE;

         case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
         }
      break;
    } 
    
return FALSE;
}

/*****************************************************************************

   BuildCoolbar

*****************************************************************************/

HWND BuildCoolbar(HWND hwndParent)
{
HWND     hwndCoolbar = NULL;
LRESULT  lResult;

hwndCoolbar = CreateWindowEx( WS_EX_TOOLWINDOW, 
                              REBARCLASSNAME, 
                              NULL,
                              WS_VISIBLE |
                                 WS_BORDER | 
                                 WS_CHILD | 
                                 WS_CLIPCHILDREN | 
                                 WS_CLIPSIBLINGS | 
                                 RBS_TOOLTIPS |
                                 RBS_VARHEIGHT | 
                                 RBS_BANDBORDERS | 
                                 CCS_NODIVIDER | 
                                 CCS_NOPARENTALIGN |
                                 ((g_wSide & 0x01) ? CCS_VERT : 0),  //g_wSide is odd if this is a vertical bar
                              0, 
                              0, 
                              200, 
                              100, 
                              hwndParent, 
                              (HMENU)ID_COOLBAR, 
                              g_hInst, 
                              NULL);

if(hwndCoolbar)
   {
   REBARINFO      rbi;
   HIMAGELIST     himlCoolbar;
   HICON          hIcon;
   REBARBANDINFO  rbbi;
   HWND           hwndChild;
   RECT           rc;
   TCHAR          szString[64];

   //set up the CoolBar
   himlCoolbar = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);
   hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_MAINICON));

   ImageList_AddIcon(himlCoolbar, hIcon);

   rbi.cbSize  = sizeof(rbi);
   rbi.fMask   = RBIM_IMAGELIST;
   rbi.himl    = himlCoolbar;
   lResult = SendMessage(hwndCoolbar, RB_SETBARINFO, 0, (LPARAM)&rbi);
   
   //add a band that contains a combobox
   hwndChild = CreateWindowEx(   0, 
                                 TEXT("combobox"), 
                                 NULL,
                                 WS_VISIBLE |
                                    WS_CHILD | 
                                    WS_TABSTOP |
                                    WS_VSCROLL |
                                    WS_CLIPCHILDREN | 
                                    WS_CLIPSIBLINGS | 
                                    CBS_AUTOHSCROLL | 
                                    CBS_DROPDOWN,
                                 0, 
                                 0, 
                                 100, 
                                 200, 
                                 hwndCoolbar, 
                                 (HMENU)ID_COMBOBOX, 
                                 g_hInst, 
                                 NULL);

   //add some stuff to the combobox
   {
   int   i;

   for(i = 0; i < 25; i++)
      {
      wsprintf(szString, TEXT("Item %d"), i + 1);
      SendMessage(hwndChild, CB_ADDSTRING, 0, (LPARAM)szString);
      }
   }
   
   GetWindowRect(hwndChild, &rc);
   
   ZeroMemory(&rbbi, sizeof(rbbi));
   rbbi.cbSize       = sizeof(REBARBANDINFO);
   rbbi.fMask        = RBBIM_CHILD | 
                        RBBIM_CHILDSIZE | 
                        RBBIM_ID | 
                        RBBIM_STYLE | 
                        RBBIM_COLORS |
                        RBBIM_TEXT |
                        RBBIM_BACKGROUND |
                        RBBIM_IMAGE;
   rbbi.cxMinChild   = rc.right - rc.left;
   rbbi.cyMinChild   = rc.bottom - rc.top;
   rbbi.clrFore      = GetSysColor(COLOR_BTNTEXT);
   rbbi.clrBack      = GetSysColor(COLOR_BTNFACE);
   rbbi.fStyle       = RBBS_CHILDEDGE | 
                        RBBS_FIXEDBMP;
   rbbi.wID          = ID_COMBOBOX;
   rbbi.hwndChild    = hwndChild;
   rbbi.lpText       = TEXT("ComboBox");
   rbbi.hbmBack      = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND));
   rbbi.iImage       = 0;

   lResult = SendMessage(hwndCoolbar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)(LPREBARBANDINFO)&rbbi);

   //add a band that contains a button
   hwndChild = CreateWindowEx(   0, 
                                 TEXT("button"), 
                                 TEXT("Button"),
                                 WS_CHILD | 
                                    BS_PUSHBUTTON,
                                 0, 
                                 0, 
                                 100, 
                                 50, 
                                 hwndCoolbar, 
                                 (HMENU)ID_BUTTON, 
                                 g_hInst, 
                                 NULL);
   
   GetWindowRect(hwndChild, &rc);
   
   ZeroMemory(&rbbi, sizeof(rbbi));
   rbbi.cbSize       = sizeof(REBARBANDINFO);
   rbbi.fMask        =  RBBIM_CHILD | 
                        RBBIM_CHILDSIZE | 
                        RBBIM_ID | 
                        RBBIM_STYLE | 
                        RBBIM_COLORS |
                        RBBIM_TEXT |
                        RBBIM_BACKGROUND;
   rbbi.cxMinChild   = rc.right - rc.left;
   rbbi.cyMinChild   = rc.bottom - rc.top;
   rbbi.clrFore      = GetSysColor(COLOR_BTNTEXT);
   rbbi.clrBack      = GetSysColor(COLOR_BTNFACE);
   rbbi.fStyle       = RBBS_CHILDEDGE | 
                        RBBS_FIXEDBMP;
   rbbi.wID          = ID_BUTTON;
   rbbi.hwndChild    = hwndChild;
   rbbi.lpText       = TEXT("Button");
   rbbi.hbmBack      = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND));


   lResult = SendMessage(hwndCoolbar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)(LPREBARBANDINFO)&rbbi);
   }

MoveCoolbar(hwndParent);

return hwndCoolbar;
}

/*****************************************************************************

   HandleNotify

*****************************************************************************/

LRESULT HandleNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
LPNMHDR  lpNM = (LPNMHDR)lParam;

switch(lpNM->code)
   {
   case RBN_HEIGHTCHANGE:
      break;

   }

return FALSE;
}

/**************************************************************************

   MoveCoolbar()
   
**************************************************************************/

void MoveCoolbar(HWND hWnd)
{
RECT  rc,
      rcCoolbar;
int   x,
      y,
      cx,
      cy;

GetClientRect(hWnd, &rc);
GetWindowRect(GetDlgItem(hWnd, ID_COOLBAR), &rcCoolbar);

switch(g_wSide)
   {
   default:
   case TOP:
      //align the coolbar along the top of the window
      x = 0;
      y = 0;
      cx = rc.right - rc.left;
      cy = rc.bottom - rc.top;
      break;

   case LEFT:
      //align the coolbar along the left side of the window
      x = 0;
      y = 0;
      cx = rcCoolbar.right - rcCoolbar.left;
      cy = rc.bottom - rc.top;
      break;

   case BOTTOM:
      //align the coolbar along the bottom of the window
      x = 0;
      y = rc.bottom - (rcCoolbar.bottom - rcCoolbar.top);
      cx = rc.right - rc.left;
      cy = rcCoolbar.bottom - rcCoolbar.top;
      break;

   case RIGHT:
      //align the coolbar along the right side of the window
      x = rc.right - (rcCoolbar.right - rcCoolbar.left);
      y = 0;
      cx = rcCoolbar.right - rcCoolbar.left;
      cy = rc.bottom - rc.top;
      break;
   }

MoveWindow( GetDlgItem(hWnd, ID_COOLBAR), 
            x, 
            y, 
            cx, 
            cy, 
            TRUE);
}

/**************************************************************************

   UpdateMenu()
   
**************************************************************************/

void UpdateMenu(HWND hWnd, HMENU hMenu)
{
UINT  uCheck;

switch(g_wSide)
   {
   default:
   case TOP:
      uCheck = IDM_TOP;
      break;

   case LEFT:
      uCheck = IDM_LEFT;
      break;

   case RIGHT:
      uCheck = IDM_RIGHT;
      break;

   case BOTTOM:
      uCheck = IDM_BOTTOM;
      break;
   }

CheckMenuRadioItem(hMenu, IDM_TOP, IDM_BOTTOM, uCheck, MF_BYCOMMAND);
}

