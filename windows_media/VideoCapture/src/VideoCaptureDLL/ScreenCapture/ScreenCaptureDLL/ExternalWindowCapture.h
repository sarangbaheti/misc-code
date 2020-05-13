class ExternalWindowCapture
{
public:
    ExternalWindowCapture()
    {
        _Device = NULL;
        _PlainSurface = NULL;
    }
    ~ExternalWindowCapture();

    void FreeMemory();

    UINT Init(const String &Filename, HWND Window, UINT BitRate, UINT FrameRate, UINT AudioDeviceIndex);
    void Capture();

private:
    
    void LoadPresentationParameters(D3DPRESENT_PARAMETERS &PresentationParameters);
    
    Clock*              _Clock;
    IDirect3DDevice9*   _Device;
    IDirect3DSurface9*  _PlainSurface;
    HWND                _Window, _CaptureWindow;
    Bitmap              _FrontBuffer;
    VideoCompressor     _Compressor;
    Vec2i               _Dimensions;
};
