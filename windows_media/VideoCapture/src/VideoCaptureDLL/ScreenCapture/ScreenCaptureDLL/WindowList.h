struct WindowInfo
{
    HWND Window;
    Vec2i Dimensions;
    String Description;
};

class WindowList
{
public:
    void UpdateList();
    void Save(const String &Filename);
    
    void RecordWindow(HWND Window);
private:
    Vector<WindowInfo> _AllWindows;
};
