//#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "vfw32.lib")

#include "Main.h"

//#include "Vfw.h"

const bool UseVideoForWindowsCapture = false;
ExternalWindowCapture::~ExternalWindowCapture()
{
    
}

void ExternalWindowCapture::FreeMemory()
{
    if(_PlainSurface)
    {
        _PlainSurface->Release();
        _PlainSurface = NULL;
    }
    if(_Device)
    {
        _Device->Release();
        _Device = NULL;
    }
    if(_Compressor.Capturing())
    {
        _Compressor.FreeMemory();
    }
}

void ExternalWindowCapture::LoadPresentationParameters(D3DPRESENT_PARAMETERS &PresentationParameters)
{
    PresentationParameters.Windowed = TRUE;
    PresentationParameters.BackBufferWidth = 0;
    PresentationParameters.BackBufferHeight = 0;
    PresentationParameters.BackBufferFormat = D3DFMT_UNKNOWN;
    PresentationParameters.BackBufferCount = 0;
    PresentationParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
    PresentationParameters.MultiSampleQuality = 0;
    PresentationParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    //PresentationParameters.hDeviceWindow = _Window;
    PresentationParameters.hDeviceWindow = NULL;
    PresentationParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    PresentationParameters.EnableAutoDepthStencil = FALSE;
    PresentationParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    PresentationParameters.Flags = 0;
}

/*LRESULT PASCAL GrabberCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	lpVHdr->lpData;
	return 0;
}*/


UINT ExternalWindowCapture::Init(const String &Filename, HWND Window, UINT BitRate, UINT FrameRate, UINT AudioDeviceIndex)
{
    _Window = Window;

    if(!IsWindow(Window))
    {
        MessageBox(NULL, "The selected window is not valid.", "Invalid Window", MB_OK | MB_ICONERROR);
        return 1;
    }

    

    if(UseVideoForWindowsCapture)
    {
        /*_CaptureWindow = capCreateCaptureWindow(_T("DirectScreenCaptureWindow"),
            WS_CHILD|WS_CLIPSIBLINGS, 50, 50, 160, 120, 
		    NULL, 0xFFFF);
        PersistentAssert(_CaptureWindow != NULL, "Failed to create capture window");

        if(!capDriverConnect(_CaptureWindow, 0)|| //check other driver indices?
		   !capSetCallbackOnFrame(_CaptureWindow, GrabberCallbackProc)||
		   !capPreview(_CaptureWindow, FALSE))
	    {
            DestroyWindow(_CaptureWindow);
		    PersistentSignalError("Failed to initialize capture window");
        }*/
    }
    else
    {
        IDirect3D9* D3D = Direct3DCreate9(D3D_SDK_VERSION);
        PersistentAssert(D3D != NULL, "Direct3DCreate9 failed");
    
        D3DPRESENT_PARAMETERS PresentationParameters;
        LoadPresentationParameters(PresentationParameters);

        //HRESULT hr = D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &PresentationParameters, &_Device);
        HRESULT hr = D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &PresentationParameters, &_Device);
        if(FAILED(hr))
        {
            MessageBox(NULL, "The selected window is not valid.", "Invalid Window", MB_OK | MB_ICONERROR);
            return 1;
        }
    
        D3D->Release();
    }
    
    RECT ClientRect;
    GetClientRect(_Window, &ClientRect);
    MapWindowPoints(_Window, HWND_DESKTOP, (LPPOINT)&ClientRect, 2);
    _Dimensions = Rectangle2i(ClientRect).Dimensions();

    while(_Dimensions.x % 4 != 0)
    {
        _Dimensions.x++;
    }
    while(_Dimensions.y % 4 != 0)
    {
        _Dimensions.y++;
    }

    _Clock = new Clock;
    _Clock->Start();
    return _Compressor.OpenFile(Filename, _Dimensions.x, _Dimensions.y, BitRate, FrameRate, AudioDeviceIndex, _Clock);
}

void ExternalWindowCapture::Capture()
{
    HRESULT hr = _Device->TestCooperativeLevel();
    if(FAILED(hr))
    {
        if(_PlainSurface)
        {
            _PlainSurface->Release();
            _PlainSurface = NULL;
        }
        if(hr == D3DERR_DEVICENOTRESET)
        {
            D3DPRESENT_PARAMETERS PresentationParameters;
            LoadPresentationParameters(PresentationParameters);
            _Device->Reset(&PresentationParameters);
        }
        return;
    }

    /*IDirect3DSurface9* BackBuffer;
    _Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
    D3DSURFACE_DESC Desc;
    BackBuffer->GetDesc(&Desc);
    BakBuffer->Release();*/

    if(_PlainSurface == NULL)
    {
        D3DDISPLAYMODE DisplayMode;

        IDirect3DSwapChain9* SwapChain;
        _Device->GetSwapChain(0, &SwapChain);
        SwapChain->GetDisplayMode(&DisplayMode);
        SwapChain->Release();
        
        HRESULT hr = _Device->CreateOffscreenPlainSurface(DisplayMode.Width, DisplayMode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &_PlainSurface, NULL);
        PersistentAssert(SUCCEEDED(hr), "CreateOffscreenPlainSurface failed");
    }

    RECT ClientRect;
    GetClientRect(_Window, &ClientRect);
    MapWindowPoints(_Window, HWND_DESKTOP, (LPPOINT)&ClientRect, 2);

    hr = _Device->GetFrontBufferData(0, _PlainSurface);
    PersistentAssert(SUCCEEDED(hr), "GetFrontBufferData failed");
    
    _Compressor.AddFrame(_PlainSurface, Rectangle2i(ClientRect).Min, 0.0);

    //_FrontBuffer.LoadFromSurface(_PlainSurface);
}
