// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SCREENCAPTUREDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SCREENCAPTUREDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SCREENCAPTUREDLL_EXPORTS
#define SCREENCAPTUREDLL_API __declspec(dllexport)
#else
#define SCREENCAPTUREDLL_API __declspec(dllimport)
#endif

SCREENCAPTUREDLL_API UINT32 BeginVideoCapture(UINT32 WindowHandle, UINT32 WholeWindow, UINT32 X, UINT32 Y, UINT32 Width, UINT32 Height, UINT32 BitRate, UINT32 FrameRate, UINT32 AudioDeviceIndex, char *Filename);
SCREENCAPTUREDLL_API UINT32 CaptureVideoFrame();
SCREENCAPTUREDLL_API UINT32 StopVideoCapture();

SCREENCAPTUREDLL_API UINT32 EnumerateAndSaveWindows();
SCREENCAPTUREDLL_API UINT32 EnumerateAndSaveAudioCaptureDevices();
SCREENCAPTUREDLL_API UINT32 ReSizeWindow(UINT32 WindowHandle, UINT32 NewWidth, UINT32 NewHeight);
