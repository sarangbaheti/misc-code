/******************************************************************************
Module name: LISWatch.c
Notices: Written 1997 Jeffrey Richter
Purpose: Local-Input State (LIS) Watcher utility.
******************************************************************************/


#define STRICT
#include <windows.h>
#include <windowsx.h>
#pragma warning(disable: 4001)    /* Single line comment */
#include "resource.h"
#include <tchar.h>
#include <stdio.h>


/////////////////////////// chHANDLE_DLGMSG Macro /////////////////////////////


// The normal HANDLE_MSG macro in WINDOWSX.H does not work properly for dialog
// boxes because DlgProc's return a BOOL instead of an LRESULT (like
// WndProcs). This chHANDLE_DLGMSG macro corrects the problem:
#define chHANDLE_DLGMSG(hwnd, message, fn)                           \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,               \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


//////////////////////////////// chDIMOF Macro ////////////////////////////////


// This macro evaluates to the number of elements in an array. 
#define chDIMOF(Array) (sizeof(Array) / sizeof(Array[0]))


///////////////////////////////////////////////////////////////////////////////


#define TIMER_DELAY (1 * 1000) // 1 second * 1000 milliseconds

UINT  g_uTimerId = 1;
DWORD g_dwThreadIdAttachTo = 0;  // 0=System-wide; Non-zero=specifc thread


///////////////////////////////////////////////////////////////////////////////


BOOL LISWatch_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam) {

   // Update our contents periodically
   g_uTimerId = SetTimer(hwnd, g_uTimerId, TIMER_DELAY, NULL);

   // Make our window on top of all others
   SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

   // Give our window an icon 
   SendMessage(hwnd, WM_SETICON, TRUE, 
      (LPARAM) LoadIcon(GetWindowInstance(hwnd), 
         MAKEINTRESOURCE(IDI_LISWATCH)));
   return(TRUE);                  // Accept default focus window.
}


///////////////////////////////////////////////////////////////////////////////


void LISWatch_OnLButtonDown (HWND hwnd, BOOL fDoubleClick, 
   int x, int y, UINT keyFlags) {

   // If we're attached to a thread, detach from it
   if (g_dwThreadIdAttachTo != 0)
      AttachThreadInput(GetCurrentThreadId(), g_dwThreadIdAttachTo, FALSE);

   // Set capture to ourself and change the mouse cursor
   SetCapture(hwnd);
   SetCursor(LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_EYES)));
}


///////////////////////////////////////////////////////////////////////////////


void LISWatch_OnLButtonUp (HWND hwnd, int x, int y, UINT keyFlags) {

   if (GetCapture() == hwnd) {

      // If we had mouse capture set, get the ID of the thread that
      // created the window that is under the mouse cursor.
      POINT pt;
      pt.x = LOWORD(GetMessagePos());
      pt.y = HIWORD(GetMessagePos());
      ReleaseCapture();
      g_dwThreadIdAttachTo = GetWindowThreadProcessId(
         ChildWindowFromPointEx(GetDesktopWindow(), pt, CWP_SKIPINVISIBLE), 
         NULL);

      if (g_dwThreadIdAttachTo == GetCurrentThreadId()) {
         // The mouse button is released on one of our windows, 
         // monitor local-input state on a system-wide basis
         g_dwThreadIdAttachTo = 0;
      } else {
         // The mouse button is released on a window that our thread didn't
         // create, monitor local input state for that thread only.
         AttachThreadInput(GetCurrentThreadId(), g_dwThreadIdAttachTo, TRUE);	
      }
   }
}


///////////////////////////////////////////////////////////////////////////////


static void CalcWndText (HWND hwnd, LPTSTR szBuf, int nLen) {

   TCHAR szClass[50], szCaption[50], szBufT[150];

   if (hwnd == (HWND) NULL) {
      _tcscpy(szBuf, __TEXT("(no window)")); return;
   }

   if (!IsWindow(hwnd)) {
      _tcscpy(szBuf, __TEXT("(invalid window)")); return;
   }

   GetClassName(hwnd, szClass, chDIMOF(szClass));
   GetWindowText(hwnd, szCaption, chDIMOF(szCaption));
   _stprintf(szBufT, __TEXT("[%s] %s"), (LPTSTR) szClass,
      (*szCaption == 0) ? (LPTSTR) __TEXT("(no caption)")
      : (LPTSTR) szCaption);
   _tcsncpy(szBuf, szBufT, nLen - 1);
   szBuf[nLen - 1] = 0; // Force zero-terminated string
}


//////////////////////////////////////////////////////////////


void LISWatch_OnTimer (HWND hwnd, UINT id) {

   TCHAR szBuf[100] = __T("System-wide");
   HWND hwndForeground = GetForegroundWindow();
   DWORD dwThreadIdAttachTo = g_dwThreadIdAttachTo;

   if (dwThreadIdAttachTo == 0) {
      // If monitoring local input state system-wide, attach our input
      // state to the thread that created the current foreground window.
      dwThreadIdAttachTo = 
         GetWindowThreadProcessId(hwndForeground, NULL);
      AttachThreadInput(GetCurrentThreadId(), dwThreadIdAttachTo, TRUE);	
   } else wsprintf(szBuf, __T("0x%08x"), dwThreadIdAttachTo);
   SetWindowText(GetDlgItem(hwnd, IDC_THREADID), szBuf);

   CalcWndText(GetFocus(), szBuf, chDIMOF(szBuf));
   SetWindowText(GetDlgItem(hwnd, IDC_WNDFOCUS), szBuf);

   CalcWndText(GetActiveWindow(), szBuf, chDIMOF(szBuf));
   SetWindowText(GetDlgItem(hwnd, IDC_WNDACTIVE), szBuf);

   CalcWndText(GetCapture(), szBuf, chDIMOF(szBuf));
   SetWindowText(GetDlgItem(hwnd, IDC_WNDCAPTURE), szBuf);

   CalcWndText(hwndForeground, szBuf, chDIMOF(szBuf));
   SetWindowText(GetDlgItem(hwnd, IDC_WNDFOREGRND), szBuf);

   if (g_dwThreadIdAttachTo == 0) {
      // If monitoring local input state system-wide, detach our input
      // state from the thread that created the current foreground window.
      AttachThreadInput(GetCurrentThreadId(), dwThreadIdAttachTo, FALSE);	
   }
}


///////////////////////////////////////////////////////////////////////////////


void LISWatch_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {

   switch (id) {

      case IDOK:
      case IDCANCEL:              // Allows dialog box to close
         EndDialog(hwnd, id);
         break;
   }
}


///////////////////////////////////////////////////////////////////////////////

        
BOOL WINAPI LISWatch_DlgProc (HWND hwnd, UINT uMsg,
   WPARAM wParam, LPARAM lParam) {

   switch (uMsg) {

      // Standard Window's messages
      chHANDLE_DLGMSG(hwnd, WM_INITDIALOG,  LISWatch_OnInitDialog);
      chHANDLE_DLGMSG(hwnd, WM_COMMAND,     LISWatch_OnCommand);
      chHANDLE_DLGMSG(hwnd, WM_TIMER,       LISWatch_OnTimer);
      chHANDLE_DLGMSG(hwnd, WM_LBUTTONDOWN, LISWatch_OnLButtonDown);
      chHANDLE_DLGMSG(hwnd, WM_LBUTTONUP,   LISWatch_OnLButtonUp);
   }
   return(FALSE);                 // We didn't process the message.
}


///////////////////////////////////////////////////////////////////////////////


int WINAPI WinMain (HINSTANCE hinstExe, HINSTANCE hinstPrev,
   LPSTR lpszCmdLine, int nCmdShow) {

   DialogBox(hinstExe, MAKEINTRESOURCE(IDD_LISWATCH),
      NULL, LISWatch_DlgProc);

   return(0);
}


//////////////////////////////// End of File //////////////////////////////////
