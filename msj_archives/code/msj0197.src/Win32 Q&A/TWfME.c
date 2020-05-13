/**************************************************************
Module name: TWfME.C
Written by: Jeffrey Richter
Purpose: Tests the WaitForMultipleExpressions function.
**************************************************************/


#define STRICT
#include <windows.h>
#include <windowsx.h>

#include <tchar.h>

#include "resource.h"
#include "WfME.h"                // WaitForMultipleExpressions


///////////////////////////////////////////////////////////////


// g_ahObjs contains the list of event kernel object
// handles referenced in the Boolean expression.
#define MAX_KERNEL_OBJS     1000
HANDLE g_ahObjs[MAX_KERNEL_OBJS];


// ahExpObjs contains all the expressions. A single expression
// consists of a contiguous set of kernel object handles that 
// is TRUE when all the objects are signaled at the same time. 
// A NULL handle is used to separate OR expressions. 

// A handle value may NOT appear multiple times within an AND 
// expression but the same handle value may appear in 
// different OR expressions.

// An expresion can have a maximum of 64 sets with no more 
// than 63 handles/set plus a NULL handle to separate each set
#define MAX_EXPRESSION_SIZE   ((64 * 63) + 63)


// cExpObjects identifies the number of 
// entries used in the ahExpObjects array.
typedef struct {
   HWND     hwnd;          // UI window for displaying results
   DWORD    dwTimeout;     // How long before timeout
   DWORD    cExpObjects;   // # of entries in object list
   HANDLE   ahExpObjs[MAX_EXPRESSION_SIZE];  // List of objs
} AWFME, *PAWFME;
AWFME g_awfme;


// This message is posted to the UI thread when an expression 
// comes true or when we timeout while waiting for an 
// expression to come TRUE.
#define WM_WAITEND      (WM_USER + 101)


////////////////////// HANDLE_DLGMSG Macro ////////////////////


// The normal HANDLE_MSG macro in WINDOWSX.H does not work 
// properly for dialog boxes because DlgProc's return a BOOL 
// instead of an LRESULT (like WndProcs). This HANDLE_DLGMSG 
// macro corrects the problem:
#define HANDLE_DLGMSG(hwnd, message, fn)                    \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,      \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


///////////////////////////////////////////////////////////////


BOOL TWfME_OnInitDialog (HWND hwnd, HWND hwndFocus, 
   LPARAM lParam) {

   // Initialize the controls in the dialog box
	SetDlgItemInt(hwnd,  IDC_NUMOBJS, 4, FALSE);
	SetDlgItemInt(hwnd,  IDC_TIMEOUT, 30000, FALSE);
	SetDlgItemText(hwnd, IDC_EXPRESSION, 
      _T("1 2 | 2 3 4 | 1 4"));

   // Set the multi-column listbox's column size
   ListBox_SetColumnWidth(GetDlgItem(hwnd, IDC_OBJLIST), 
      LOWORD(GetDialogBaseUnits()) * 4);

   return(TRUE);  // Accept default focus window.
}


///////////////////////////////////////////////////////////////


DWORD WINAPI AsyncWaitForMultipleExpressions (PVOID pvParam) {
   PAWFME pawfme = (PAWFME) pvParam;

   DWORD dw = WaitForMultipleExpressions(pawfme->cExpObjects, 
      pawfme->ahExpObjs, pawfme->dwTimeout);
   PostMessage(pawfme->hwnd, WM_WAITEND, dw, 0);
   return(0);
}


///////////////////////////////////////////////////////////////


LRESULT TWfME_OnWaitEnd (HWND hwnd, WPARAM wParam, 
   LPARAM lParam) {

   int n;

   // Close all the event kernel object handles
   for (n = 0; g_ahObjs[n] != NULL; n++)
      CloseHandle(g_ahObjs[n]);

   // Tell the user the result of running the test
   if (wParam == WAIT_TIMEOUT) 
      SetDlgItemText(hwnd, IDC_RESULT, __TEXT("Timeout"));
   else 
      SetDlgItemInt(hwnd, IDC_RESULT, 
         wParam - WAIT_OBJECT_0, FALSE);

   // Allow the user to change values and run the test again
   EnableWindow(GetDlgItem(hwnd, IDC_NUMOBJS), TRUE);
   EnableWindow(GetDlgItem(hwnd, IDC_TIMEOUT), TRUE);
   EnableWindow(GetDlgItem(hwnd, IDC_EXPRESSION), TRUE);
   EnableWindow(GetDlgItem(hwnd, IDOK), TRUE);
   SetFocus(GetDlgItem(hwnd, IDC_EXPRESSION));

   return(0);
}


///////////////////////////////////////////////////////////////


void TWfME_OnCommand (HWND hwnd, int id, 
   HWND hwndCtl, UINT codeNotify) {

   BOOL fTranslated;
   TCHAR szExpression[100];
   int cObjects, n;
   LPTSTR p;
   DWORD dwThreadId;

   // Obtain the user's settings from the dialog box controls.
   ComboBox_GetText(GetDlgItem(hwnd, IDC_EXPRESSION), 
      szExpression, 
      sizeof(szExpression) / sizeof(szExpression[0]));

   cObjects = GetDlgItemInt(hwnd, IDC_NUMOBJS, 
      &fTranslated, FALSE);

   switch (id) {
      case IDC_OBJLIST:
         switch (codeNotify) {
            case LBN_SELCHANGE:
               // LBN_SELCHANGE doesn't tell us which item
               // changed state: we have to enumerate them all
               // First, reset all the events
               for (n = 0; n < cObjects; n++)
                  ResetEvent(g_ahObjs[n]);

               // Second, set the events that are selected
               for (n = 0; n < cObjects; n++) {
                  if (ListBox_GetSel(GetDlgItem(hwnd, IDC_OBJLIST), n)) 
                     SetEvent(g_ahObjs[n]);
               }	
               break;
         }
         break;

      case IDOK:
         // Prevent the user from changing 
         // values while the test is running
         SetFocus(GetDlgItem(hwnd, IDC_OBJLIST));
         EnableWindow(GetDlgItem(hwnd, IDC_NUMOBJS), FALSE);
         EnableWindow(GetDlgItem(hwnd, IDC_TIMEOUT), FALSE);
         EnableWindow(GetDlgItem(hwnd, IDC_EXPRESSION), FALSE);
         EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);

         // Notify the user that the test is running
         SetDlgItemText(hwnd, IDC_RESULT, 
            __TEXT("Waiting..."));

         // Create all of the desired kernel objects
         ZeroMemory(g_ahObjs, sizeof(g_ahObjs));
         g_awfme.cExpObjects = 0;
         ZeroMemory(g_awfme.ahExpObjs, 
            sizeof(g_awfme.ahExpObjs));
         g_awfme.hwnd = hwnd;
         g_awfme.dwTimeout = GetDlgItemInt(hwnd, IDC_TIMEOUT, 
            &fTranslated, FALSE);

         ListBox_ResetContent(GetDlgItem(hwnd, IDC_OBJLIST));
         for (n = 0; n < cObjects; n++) {
            TCHAR szBuf[20];
            g_ahObjs[n] = 
               CreateEvent(NULL, FALSE, FALSE, NULL);

            wsprintf(szBuf, __TEXT("  %d"), n + 1);
            ListBox_AddString(GetDlgItem(hwnd, IDC_OBJLIST), 
               &szBuf[lstrlen(szBuf) - 3]);
         }

         p = strtok(szExpression, __TEXT(" "));
         while (p != NULL) {
            g_awfme.ahExpObjs[g_awfme.cExpObjects++] = 
               (*p == '|') ? NULL : g_ahObjs[atoi(p) - 1];
            p = strtok(NULL, __TEXT(" "));
         }
         CloseHandle(CreateThread(NULL, 0, 
            AsyncWaitForMultipleExpressions, &g_awfme, 
            0, &dwThreadId));
         break;

      case IDCANCEL:              // Allows dialog to close
         EndDialog(hwnd, id);
         break;
   }   
}


///////////////////////////////////////////////////////////////

        
BOOL WINAPI TW4ME_DlgProc (HWND hwnd, UINT uMsg, 
   WPARAM wParam, LPARAM lParam) {

   switch (uMsg) {

      // Standard Window's messages
      HANDLE_DLGMSG(hwnd, WM_INITDIALOG, TWfME_OnInitDialog);
      HANDLE_DLGMSG(hwnd, WM_COMMAND,    TWfME_OnCommand);

      case WM_WAITEND:
         return(TWfME_OnWaitEnd(hwnd, wParam, lParam)); 
   }
   return(FALSE);    // We didn't process the message.
}


///////////////////////////////////////////////////////////////


int WINAPI WinMain (HINSTANCE hinstExe, 
   HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow) {

   DialogBox(hinstExe, MAKEINTRESOURCE(IDD_TW4ME), 
      NULL, TW4ME_DlgProc);
   return(0);
}


//////////////////////// End of File //////////////////////////
