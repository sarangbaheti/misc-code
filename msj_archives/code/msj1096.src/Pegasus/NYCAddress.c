/******************************************************************************
Module name: NYCAddress.c
Written by:  Dave Edson
Edited by:   Jeffrey Richter
******************************************************************************/


#ifndef STRICT
#define STRICT
#endif
#include <Windows.h>
#include <WindowsX.h>
#include "Resource.h"


///////////////////////////////////////////////////////////////////////////////


typedef enum {
   AVEOP_ADD,
   AVEOP_SUBTRACT,
   AVEOP_FIFTH_AVE,
   AVEOP_SEVENTH_AVE,
   AVEOP_BWAY,
   AVEOP_CPW,
   AVEOP_RIVERSIDE
} AVEOP;


struct {
   LPTSTR szName;      // Avenue name
   AVEOP  aveop;       // How address on this avenue should be interpreted
   int    nKeyNumber;  // Used for AVEOP_ADD / AVEOP_SUBTRACT
} Avenues[] = {
   {__TEXT("Avenue A"),            AVEOP_ADD,        3 },
   {__TEXT("Avenue B"),            AVEOP_ADD,        3 },
   {__TEXT("Avenue C"),            AVEOP_ADD,        3 },
   {__TEXT("Avenue D"),            AVEOP_ADD,        3 },
   {__TEXT("Broadway"),            AVEOP_BWAY,       0 },
   {__TEXT("1st Ave"),             AVEOP_ADD,        3 },
   {__TEXT("2nd Ave"),             AVEOP_ADD,        3 },
   {__TEXT("3rd Ave"),             AVEOP_ADD,       10 },
   {__TEXT("4th Ave"),             AVEOP_ADD,        8 },
   {__TEXT("5th Ave"),             AVEOP_FIFTH_AVE,  0 },
   {__TEXT("Ave of Americas"),     AVEOP_SUBTRACT,  12 },
   {__TEXT("7th Ave"),             AVEOP_SEVENTH_AVE,0 },
   {__TEXT("8th Ave"),             AVEOP_ADD,        9 },
   {__TEXT("9th Ave"),             AVEOP_ADD,       13 },
   {__TEXT("10th Ave"),            AVEOP_ADD,       14 },
   {__TEXT("11th Ave"),            AVEOP_ADD,       15 },
   {__TEXT("Amsterdam Ave"),       AVEOP_ADD,       59 },
   {__TEXT("Audobon Ave"),         AVEOP_ADD,      165 },
   {__TEXT("Central Park West"),   AVEOP_CPW,        0 },
   {__TEXT("Columbus Ave"),        AVEOP_ADD,       59 },
   {__TEXT("Convent Ave"),         AVEOP_ADD,      127 },
   {__TEXT("Edgecomb Ave"),        AVEOP_ADD,      134 },
   {__TEXT("Ft. Washington Ave"),  AVEOP_ADD,      158 },
   {__TEXT("Lenox Avenue"),        AVEOP_ADD,       10 },
   {__TEXT("Lexington Avenue"),    AVEOP_ADD,       28 },
   {__TEXT("Madison Avenue"),      AVEOP_ADD,       27 },
   {__TEXT("Manhattan Avenue"),    AVEOP_ADD,      100 },
   {__TEXT("Park Avenue"),         AVEOP_ADD,       34 },
   {__TEXT("Park Avenue South"),   AVEOP_ADD,        8 },
   {__TEXT("Pleasant Avenue"),     AVEOP_ADD,      101 },
   {__TEXT("Riverside"),           AVEOP_RIVERSIDE,  0 },
   {__TEXT("St. Nicholas Avenue"), AVEOP_ADD,      110 },
   {__TEXT("Wadsworth Avenue"),    AVEOP_ADD,      173 },
   {__TEXT("West End Avenue"),     AVEOP_ADD,       59 },
   {__TEXT("York Avenue"),         AVEOP_ADD,        4 }
};


///////////////////////////////////////////////////////////////////////////////


BOOL NYCAddr_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
   int i;
   HWND hwndAvenues = GetDlgItem(hwnd, IDC_AVENUE);
   for (i = 0; i < (sizeof(Avenues) / sizeof(Avenues[0])); i++)
      ComboBox_AddString(hwndAvenues, Avenues[i].szName);
   ComboBox_SetCurSel(hwndAvenues, 0);
   return(TRUE);
}


///////////////////////////////////////////////////////////////////////////////


int FigureCrossStreet (int nNumber, int nAvenue) {
   int nXStreet = -1;   // Cross street
   switch (Avenues[nAvenue].aveop) {
      case AVEOP_ADD:
         nXStreet = nNumber / 20 + Avenues[nAvenue].nKeyNumber;
         break;

      case AVEOP_SUBTRACT:
         nXStreet = nNumber / 20 - Avenues[nAvenue].nKeyNumber;
         break;

      case AVEOP_FIFTH_AVE:
         if      (nNumber <=  108) nXStreet = nNumber / 20 + 11;
         else if (nNumber <=  200) nXStreet = nNumber / 20 + 13;
         else if (nNumber <=  400) nXStreet = nNumber / 20 + 16;
         else if (nNumber <=  600) nXStreet = nNumber / 20 + 18;
         else if (nNumber <=  775) nXStreet = nNumber / 20 + 20;
         else if (nNumber <= 1286) nXStreet = nNumber / 10 - 18;
         else if (nNumber <= 1494) 
            nXStreet = nNumber / 10 - 20 - (nNumber - 1310) / 20;
         break;

    case AVEOP_SEVENTH_AVE:
         if (nNumber <=  1800) nXStreet = nNumber / 20 + 12;
         else nXStreet = nNumber / 20 + 20;
         break;

    case AVEOP_BWAY:
        if (nNumber <=  754) ;
        else if (nNumber <=  846) nXStreet = nNumber / 20 - 29;
        else if (nNumber <=  953) nXStreet = nNumber / 20 - 25;
        else nXStreet = nNumber / 20 - 31;
        break;

    case AVEOP_CPW:
        nXStreet = nNumber / 10 + 60;
        break;

    case AVEOP_RIVERSIDE:
        if (nNumber <=  567) nXStreet = nNumber / 10 + 72;
        else nXStreet = nNumber / 10 + 78;
        break;
   }
   return(nXStreet);
}


///////////////////////////////////////////////////////////////////////////////


void NYCAddr_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
   int   nNumber;
   int   nAvenue;
   int   nXStreet;
   BOOL  fTranslated;
   TCHAR szAnswer[128];

   switch (id) {
      case IDOK:
         nNumber = GetDlgItemInt(hwnd, IDC_NUMBER, &fTranslated, FALSE);
         nAvenue = ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_AVENUE));
         nXStreet = FigureCrossStreet(nNumber, nAvenue);
         if (-1 != nXStreet) {
            wsprintf(szAnswer, 
               __TEXT("The nearest cross-street for %d %s is")
               __TEXT("approximately Street #%d"),
               nNumber, Avenues[nAvenue].szName, nXStreet);
         } else
            wsprintf(szAnswer, __TEXT("Can't calculate cross street"));
         SetDlgItemText(hwnd, IDC_CROSSSTREET, szAnswer);
         break;

      case IDCANCEL:  
         EndDialog(hwnd, 0); 
         break;
   }
}


///////////////////////////////////////////////////////////////////////////////


// The normal HANDLE_MSG macro in WINDOWSX.H does not work properly for dialog
// boxes because DlgProc's return a BOOL instead of an LRESULT (like
// WndProcs). This chHANDLE_DLGMSG macro corrects the problem:
#define chHANDLE_DLGMSG(hwnd, message, fn)                           \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,               \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


///////////////////////////////////////////////////////////////////////////////


BOOL WINAPI NYCAddr_DlgProc(HWND hwnd, UINT uMsg, 
   WPARAM wParam, LPARAM lParam) {
 
   switch(uMsg) {
      chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, NYCAddr_OnInitDialog);
      chHANDLE_DLGMSG(hwnd, WM_COMMAND,    NYCAddr_OnCommand);
   }
   return(FALSE);
}


///////////////////////////////////////////////////////////////////////////////


int WINAPI WinMain(HINSTANCE hinstExe, HINSTANCE hinstExePrev,
#ifdef TARGET_NT
    LPSTR pszCmdLine,
#else
    LPWSTR pszCmdLine,
#endif
   int nCmdShow) {
   return(DialogBox(hinstExe, MAKEINTRESOURCE(IDD_NYCADDRESS), 
      NULL, NYCAddr_DlgProc));
}


///////////////////////////////// End of File /////////////////////////////////
