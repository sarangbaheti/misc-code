struct AudioCaptureInfo
{
    UINT Index;
    String Description;
};

class AudioCaptureList
{
public:
    void UpdateList();
    void Save(const String &Filename);
    
private:
    Vector<AudioCaptureInfo> _AllDevices;
};
