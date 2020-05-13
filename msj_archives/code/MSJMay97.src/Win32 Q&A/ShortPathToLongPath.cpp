/******************************************************************************
Module name: ShortPathToLongPath.cpp
Written by:  Jeffrey Richter
Notices:     Written 1997 by Jeffrey Richter
******************************************************************************/


#include <Windows.h>
#include <ShlObj.h>
#include <wchar.h>


///////////////////////////////////////////////////////////////////////////////


int WINAPI WinMain (HINSTANCE hinst, HINSTANCE hintPrev, LPSTR pszCmdLine, int nCmdShow) {
   int nNumArgs = 0;
   LPWSTR pszShortPathNameW = CommandLineToArgvW(GetCommandLineW(), &nNumArgs)[1];

   LPSHELLFOLDER psfDesktop = NULL;
   ULONG chEaten = 0;
   LPITEMIDLIST pidlShellItem = NULL;
   WCHAR szLongPath[_MAX_PATH] = { 0 };

   // Get the Desktop's shell folder interface
   HRESULT hr = SHGetDesktopFolder(&psfDesktop);

   // Request an ID list (relative to the desktop) for the short pathname
   hr = psfDesktop->ParseDisplayName(NULL, NULL, pszShortPathNameW, &chEaten, &pidlShellItem, NULL);
   psfDesktop->Release();  // Release the desktop's IShellFolder
   
   if (FAILED(hr)) {

      // If we couldn't get an ID list for the shoft pathname, it must not exist.      
      lstrcpyW(szLongPath, L"Error: Path not found!");

   } else {

      // We did get an ID list, convert it to a long pathname
      SHGetPathFromIDListW(pidlShellItem, szLongPath);

      // Free the ID list allocated by ParseDisplayName
      LPMALLOC pMalloc = NULL;
      SHGetMalloc(&pMalloc);
      pMalloc->Free(pidlShellItem);
      pMalloc->Release();
   }

   // Display the short pathname in the caption and the long pathname in the box.
   MessageBox(NULL, szLongPath, pszShortPathNameW, MB_OK);

   return(0);
}


///////////////////////////////// End of File /////////////////////////////////
