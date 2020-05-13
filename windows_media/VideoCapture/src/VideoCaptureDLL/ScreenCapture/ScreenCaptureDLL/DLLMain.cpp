// dllmain.cpp : Defines the entry point for the DLL application.
#include "Main.h"

#ifdef _DLL
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpszCmdLine, int nCmdShow)
{
    Utility::MessageBox("App Start, Starting Capture");
    ExternalWindowCapture *Capture = new ExternalWindowCapture;
    Capture->Init("Capture.mp4", GetDesktopWindow(), 100000, 30, 0);
    Utility::MessageBox("App Start, Capturing Some Frames");
    for(UINT Index = 0; Index < 100; Index++)
    {
        Capture->Capture();
    }
    Utility::MessageBox("App End, Cleaning Up");
    Capture->FreeMemory();
    delete Capture;
    return 0;
}
