#include "Main.h"

BOOL WINAPI EnumWindowProc(HWND Window, LPARAM Context)
{
    ((WindowList *)Context)->RecordWindow(Window);
    return TRUE;
}

bool IsShellWindow(HWND Window)
{
    if(!IsWindow(Window) || !IsWindowVisible(Window))
    {
        return false;
    }
    if(GetAncestor(Window, GA_PARENT) != GetDesktopWindow())
    {
        return false;
    }

    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    if(ClientRect.right - ClientRect.left <= 1 || ClientRect.bottom - ClientRect.top <= 1)
    {
        return false;
    }
    
    char cDescription[256];
    GetWindowText(Window, cDescription, 256);
    String Description = cDescription;
    if(Description.Length() == 0 || Description == "Start")
    {
        return false;
    }

    // Start at the root owner
    /*HWND hwndWalk = GetAncestor(Window, GA_ROOTOWNER);

    // See if we are the last active visible popup
    HWND hwndTry;
    while ((hwndTry = GetLastActivePopup(hwndWalk)) != hwndTry)
    {
        if (IsWindowVisible(hwndTry)) break;
        hwndWalk = hwndTry;
    }
    return (hwndWalk == Window);*/
    return true;
}

void WindowList::RecordWindow(HWND Window)
{
    if(IsShellWindow(Window))
    {
        _AllWindows.PushEnd();
        WindowInfo &CurWindow = _AllWindows.Last();
        CurWindow.Window = Window;
    
        RECT WindowRect, ClientRect;
        GetWindowRect(Window, &WindowRect);
        GetClientRect(Window, &ClientRect);
        CurWindow.Dimensions = Vec2i(ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top);
    
        char Description[256];
        GetWindowText(Window, Description, 256);
        CurWindow.Description = Description;

        if(CurWindow.Description == "Program Manager")
        {
            CurWindow.Description = "Whole Screen";
        }
    }
}

void WindowList::UpdateList()
{
    _AllWindows.FreeMemory();
    //EnumWindows(EnumWindowProc, (LPARAM)this);
    //EnumDesktopWindows(NULL, EnumWindowProc, (LPARAM)this);
    EnumChildWindows(GetDesktopWindow(), EnumWindowProc, (LPARAM)this);
}

void WindowList::Save(const String &Filename)
{
    ofstream File(Filename.CString());
    File << _AllWindows.Length() << endl;
    for(UINT Index = 0; Index < _AllWindows.Length(); Index++)
    {
        const WindowInfo &CurWindow = _AllWindows[Index];
        File << UINT32(CurWindow.Window) << '\t' << CurWindow.Dimensions.x << '\t' << CurWindow.Dimensions.y << '\t' << CurWindow.Description << endl;
    }
}
