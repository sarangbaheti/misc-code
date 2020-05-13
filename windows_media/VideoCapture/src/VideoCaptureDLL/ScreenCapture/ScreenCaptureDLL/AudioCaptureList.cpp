#include "Main.h"

#ifdef INITGUID
#undef INITGUID
#endif

#include <MMDeviceAPI.h>

String GetDeviceName(IMMDeviceCollection *DeviceCollection, UINT DeviceIndex);

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

void AudioCaptureList::UpdateList()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    _AllDevices.FreeMemory();
    
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    IMMDeviceCollection *deviceCollection = NULL;

    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&deviceEnumerator));
    PersistentAssert(SUCCEEDED(hr), "CoCreateInstance failed");
    
    IMMDevice *device = NULL;

    hr = deviceEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &deviceCollection);
    PersistentAssert(SUCCEEDED(hr), "deviceEnumerator->EnumAudioEndpoints failed");
    
    UINT deviceCount;
    hr = deviceCollection->GetCount(&deviceCount);
    PersistentAssert(SUCCEEDED(hr), "deviceCollection->GetCount failed");

    for (UINT DeviceIndex = 0 ; DeviceIndex < deviceCount; DeviceIndex++)
    {
        String deviceName = GetDeviceName(deviceCollection, DeviceIndex);
        Console::WriteLine(String(DeviceIndex) + String(": ") + deviceName);

        _AllDevices.PushEnd();
        AudioCaptureInfo &CurDevice = _AllDevices.Last();
        CurDevice.Index = DeviceIndex;
        CurDevice.Description = deviceName;
    }
    
    SafeRelease(&deviceCollection);
    SafeRelease(&deviceEnumerator);
}

void AudioCaptureList::Save(const String &Filename)
{
    ofstream File(Filename.CString());
    File << _AllDevices.Length() << endl;
    for(UINT Index = 0; Index < _AllDevices.Length(); Index++)
    {
        AudioCaptureInfo &CurDevice = _AllDevices[Index];
        File << UINT32(CurDevice.Index) << '\t' << CurDevice.Description << endl;
    }
}
