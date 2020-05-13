// ScreenCaptureDLL.cpp : Defines the exported functions for the DLL application.
//

#include "Main.h"
#include "ScreenCaptureDLL.h"

ExternalWindowCapture *g_Capture = NULL;

SCREENCAPTUREDLL_API UINT32 BeginVideoCapture(UINT32 WindowHandle, UINT32 WholeWindow, UINT32 X, UINT32 Y, UINT32 Width, UINT32 Height, UINT32 BitRate, UINT32 FrameRate, UINT32 AudioDeviceIndex, char *Filename)
{
    if(g_Capture != NULL)
    {
        MessageBox(NULL, "Capture must be stopped before BeginCapture is called", "Error", MB_OK);
        return 1;
    }
    
    g_Capture = new ExternalWindowCapture;
    PersistentAssert(g_Capture != NULL, "Failed to allocate ExternalWindowCapture");

    if(FrameRate < 5)
    {
        FrameRate = 5;
    }
    if(BitRate < 1000)
    {
        BitRate = 1000;
    }
    
    UINT Result = g_Capture->Init(String(Filename), (HWND)WindowHandle, BitRate, FrameRate, AudioDeviceIndex);
    if(Result != 0)
    {
        g_Capture->FreeMemory();
        delete g_Capture;
        g_Capture = NULL;
    }
    return Result;
}

SCREENCAPTUREDLL_API UINT32 CaptureVideoFrame()
{
    if(g_Capture == NULL)
    {
        MessageBox(NULL, "CaptureFrame called before BeginCapture", "Error", MB_OK);
        return 1;
    }

    g_Capture->Capture();
    return 0;
}

SCREENCAPTUREDLL_API UINT32 StopVideoCapture()
{
    if(g_Capture == NULL)
    {
        MessageBox(NULL, "StopCapture called before BeginCapture", "Error", MB_OK);
        return 1;
    }

    g_Capture->FreeMemory();
    delete g_Capture;
    g_Capture = NULL;
    return 0;
}

SCREENCAPTUREDLL_API UINT32 EnumerateAndSaveWindows()
{
    WindowList List;
    List.UpdateList();
    List.Save("Windows.txt");
    return 0;
}

SCREENCAPTUREDLL_API UINT32 EnumerateAndSaveAudioCaptureDevices()
{
    AudioCaptureList List;
    List.UpdateList();
    List.Save("AudioCaptureDevices.txt");
    return 0;
}

SCREENCAPTUREDLL_API UINT32 ReSizeWindow(UINT32 WindowHandle, UINT32 NewWidth, UINT32 NewHeight)
{
    RECT ClientRect, ScreenRect;
    HWND Window = (HWND)WindowHandle;
    GetClientRect(Window, &ClientRect);
    GetWindowRect(Window, &ScreenRect);
    int BorderWidth = ScreenRect.right - ScreenRect.left - ClientRect.right;
    int BorderHeight = ScreenRect.bottom - ScreenRect.top - ClientRect.bottom;
    MoveWindow(Window, ScreenRect.left, ScreenRect.top, NewWidth + BorderWidth, NewHeight + BorderHeight, TRUE);
    return 0;
}
