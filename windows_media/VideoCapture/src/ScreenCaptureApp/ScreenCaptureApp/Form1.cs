using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;

namespace ScreenCaptureApp
{
    public partial class Form1 : Form
    {
        class WindowInfo
        {
            public override string ToString()
            {
                return Description;
            }

            public UInt32 Window;
            public UInt32 Width, Height;
            public String Description;
        };

        class AudioCaptureDeviceInfo
        {
            public override string ToString()
            {
                return Description;
            }

            public UInt32 Index;
            public String Description;
        };

        Capture _CaptureThreadEntry;
        Thread _CaptureThread;
        List<WindowInfo> _WindowList;
        List<AudioCaptureDeviceInfo> _AudioList;
        MarkerWindow _MarkerWindow;

        public Form1()
        {
            InitializeComponent();
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            if (_CaptureThreadEntry != null || _CaptureThread != null)
            {
                MessageBox.Show("Capture in progress!");
                return;
            }

            WindowInfo curWindow = null;
            try
            {
                curWindow = _WindowList[AppListComboBox.SelectedIndex];
            } catch {}
            if(curWindow == null)
            {
                MessageBox.Show("You need to select a window to capture");
                return;
            }

            _CaptureThreadEntry = new Capture();

            _CaptureThreadEntry.WindowHandle = curWindow.Window;
            _CaptureThreadEntry.WholeWindow = 1;
            _CaptureThreadEntry.X = 0;
            _CaptureThreadEntry.Y = 0;
            _CaptureThreadEntry.Width = curWindow.Width;
            _CaptureThreadEntry.Height = curWindow.Height;
            _CaptureThreadEntry.BitRate = 20000000;
            _CaptureThreadEntry.FrameRate = 30;
            _CaptureThreadEntry.Audio = 0xFFFFFFFF;
            _CaptureThreadEntry.Filename = String.Format("{0:M-d-yyyy HH.mm.ss}", DateTime.Now) + ".mp4";
            if(AudioComboBox.SelectedIndex >= 1)
            {
                _CaptureThreadEntry.Audio = (uint)(AudioComboBox.SelectedIndex - 1);
            }

            try
            {
                _CaptureThreadEntry.FrameRate = Convert.ToUInt32(FrameRateComboBox.Items[FrameRateComboBox.SelectedIndex]);
            }
            catch { }
            if (DataRateComboBox.SelectedIndex == 0) _CaptureThreadEntry.BitRate = 50 * 8192;
            if (DataRateComboBox.SelectedIndex == 1) _CaptureThreadEntry.BitRate = 100 * 8192;
            if (DataRateComboBox.SelectedIndex == 2) _CaptureThreadEntry.BitRate = 250 * 8192;
            if (DataRateComboBox.SelectedIndex == 3) _CaptureThreadEntry.BitRate = 500 * 8192;
            if (DataRateComboBox.SelectedIndex == 4) _CaptureThreadEntry.BitRate = 1024 * 8192;
            if (DataRateComboBox.SelectedIndex == 5) _CaptureThreadEntry.BitRate = 2048 * 8192;
            if (DataRateComboBox.SelectedIndex == 6) _CaptureThreadEntry.BitRate = 4096 * 8192;
            _CaptureThread = new Thread(new ThreadStart(_CaptureThreadEntry.Start));
            _CaptureThread.Start();

            while (!_CaptureThread.IsAlive) Thread.Sleep(100);
            while (!_CaptureThreadEntry.VideoCaptureAttempted) Thread.Sleep(100);

            if (_CaptureThreadEntry.VideoCaptureStarted)
            {
                StartButton.Enabled = false;
                StopButton.Enabled = true;
            }
            else
            {
                while (_CaptureThread.IsAlive) ;
                _CaptureThread = null;
                _CaptureThreadEntry = null;
            }
        }
        
        private void StopButton_Click(object sender, EventArgs e)
        {
            StopButton.Enabled = false;
            StartButton.Enabled = true;

            if (_CaptureThreadEntry == null || _CaptureThread == null)
            {
                MessageBox.Show("No capture in progress");
                return;
            }
            _CaptureThreadEntry.ThreadExitSignaled = true;

            while (_CaptureThread.IsAlive);

            _CaptureThread = null;
            _CaptureThreadEntry = null;
        }

        private void UpdateWindows_Click(object sender, EventArgs e)
        {
            UpdateWindowListBox();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            DataRateComboBox.Items.Add("50KB/sec");
            DataRateComboBox.Items.Add("100KB/sec");
            DataRateComboBox.Items.Add("250KB/sec");
            DataRateComboBox.Items.Add("500KB/sec");
            DataRateComboBox.Items.Add("1MB/sec");
            DataRateComboBox.Items.Add("2MB/sec");
            DataRateComboBox.Items.Add("4MB/sec");
            DataRateComboBox.SelectedIndex = 5;

            FrameRateComboBox.Items.Add("5");
            FrameRateComboBox.Items.Add("10");
            FrameRateComboBox.Items.Add("15");
            FrameRateComboBox.Items.Add("20");
            FrameRateComboBox.Items.Add("25");
            FrameRateComboBox.Items.Add("30");
            FrameRateComboBox.SelectedIndex = 5;

            ResolutionComboBox.Items.Add("Select New Resolution");
            ResolutionComboBox.Items.Add("320x240");
            ResolutionComboBox.Items.Add("640x480");
            ResolutionComboBox.Items.Add("768x576");
            ResolutionComboBox.Items.Add("1024x768");
            ResolutionComboBox.Items.Add("1280x720");
            ResolutionComboBox.Items.Add("1920x1080");
            ResolutionComboBox.SelectedIndex = 0;

            AudioComboBox.Items.Add("None");
            AudioComboBox.SelectedIndex = 0;
        }

        private void UpdateWindowListBox()
        {
            VideoCapture.CallEnumerateAndSaveWindows();

            String[] allLines = null;
            try
            {
                String loadFilename = "Windows.txt";
                allLines = File.ReadAllLines(loadFilename);
                FileInfo loadedFileInfo = new FileInfo(loadFilename);
                loadedFileInfo.Delete();
            }
            catch { }
            if (allLines == null)
            {
                MessageBox.Show("Failed to read list of active windows!");
            }
            else
            {
                int WindowCount = Convert.ToInt32(allLines[0]);
                _WindowList = new List<WindowInfo>();
                for (int lineIndex = 1; lineIndex < allLines.Length; lineIndex++)
                {
                    String curLine = allLines[lineIndex];
                    String[] curWords = curLine.Split('\t');
                    if (curWords.Length == 4)
                    {
                        WindowInfo NewWindow = new WindowInfo();
                        NewWindow.Window = Convert.ToUInt32(curWords[0]);
                        NewWindow.Width = Convert.ToUInt32(curWords[1]);
                        NewWindow.Height = Convert.ToUInt32(curWords[2]);
                        NewWindow.Description = curWords[3];
                        if (NewWindow.Description != this.Text)
                        {
                            _WindowList.Add(NewWindow);
                        }
                    }
                }

                int selectedIndex = AppListComboBox.SelectedIndex;
                if (selectedIndex == -1)
                {
                    selectedIndex = 0;
                }
                AppListComboBox.Items.Clear();
                if (_WindowList != null)
                {
                    foreach (WindowInfo curWindow in _WindowList)
                    {
                        AppListComboBox.Items.Add(curWindow.ToString());
                    }
                }
                try
                {
                    AppListComboBox.SelectedIndex = selectedIndex;
                }
                catch { }
            }
        }

        private void UpdateAudioListBox()
        {
            VideoCapture.CallEnumerateAndSaveAudioCaptureDevices();

            String[] allLines = null;
            try
            {
                String loadFilename = "AudioCaptureDevices.txt";
                allLines = File.ReadAllLines(loadFilename);
                FileInfo loadedFileInfo = new FileInfo(loadFilename);
                loadedFileInfo.Delete();
            }
            catch { }
            if (allLines == null)
            {
                MessageBox.Show("Failed to read list of audio devices!");
            }
            else
            {
                int deviceCount = Convert.ToInt32(allLines[0]);
                _AudioList = new List<AudioCaptureDeviceInfo>();
                for (int lineIndex = 1; lineIndex < allLines.Length; lineIndex++)
                {
                    String curLine = allLines[lineIndex];
                    String[] curWords = curLine.Split('\t');
                    if (curWords.Length == 2)
                    {
                        AudioCaptureDeviceInfo NewAudio = new AudioCaptureDeviceInfo();
                        NewAudio.Index = Convert.ToUInt32(curWords[0]);
                        NewAudio.Description = curWords[1];
                        _AudioList.Add(NewAudio);
                    }
                }
            }

            int selectedIndex = AudioComboBox.SelectedIndex;
            if (selectedIndex == -1)
            {
                selectedIndex = 0;
            }
            AudioComboBox.Items.Clear();
            AudioComboBox.Items.Add("None");
            int index = 0;
            foreach (AudioCaptureDeviceInfo curDevice in _AudioList)
            {
                AudioComboBox.Items.Add(curDevice.ToString());
                index++;
            }
            try
            {
                AudioComboBox.SelectedIndex = selectedIndex;
            }
            catch { }
        }

        private void AppListComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                WindowInfo curWindow = _WindowList[AppListComboBox.SelectedIndex];
                DimensionsLabel.Text = "Current Dimensions: " + curWindow.Width.ToString() + "x" + curWindow.Height.ToString();
                ResolutionComboBox.SelectedIndex = 0;
                NewWidthTextBox.Text = curWindow.Width.ToString();
                NewHeightTextBox.Text = curWindow.Height.ToString();
            } catch {}
        }

        private void AppListComboBox_DropDown(object sender, EventArgs e)
        {
            UpdateWindowListBox();
        }

        private void AudioComboBox_DropDown(object sender, EventArgs e)
        {
            UpdateAudioListBox();
        }

        private void MarkerWindow_Click(object sender, EventArgs e)
        {
            if (_MarkerWindow == null || _MarkerWindow.IsDisposed)
            {
                _MarkerWindow = new MarkerWindow();
            }
            try
            {
                _MarkerWindow.Show();
            }
            catch { _MarkerWindow = new MarkerWindow(); _MarkerWindow.Show(); }
            UpdateWindowListBox();
            for (int index = 0; index < AppListComboBox.Items.Count; index++)
            {
                if (AppListComboBox.Items[index].ToString() == "Marker Window")
                {
                    AppListComboBox.SelectedIndex = index;
                }
            }
        }

        private void Resize_Click(object sender, EventArgs e)
        {
            try
            {
                WindowInfo curWindow = _WindowList[AppListComboBox.SelectedIndex];
                UInt32 NewWidth = Convert.ToUInt32(NewWidthTextBox.Text);
                UInt32 NewHeight = Convert.ToUInt32(NewHeightTextBox.Text);
                if (NewWidth >= 32 && NewWidth <= 4096 && NewHeight >= 32 && NewHeight <= 4096)
                {
                    VideoCapture.CallReSizeWindow(curWindow.Window, NewWidth, NewHeight);
                }
            }
            catch { }

            string currentWindowName = null;
            try
            {
                currentWindowName = AppListComboBox.Items[AppListComboBox.SelectedIndex].ToString();
            }
            catch { }
            UpdateWindowListBox();
            if (currentWindowName != null)
            {
                for (int index = 0; index < AppListComboBox.Items.Count; index++)
                {
                    if (AppListComboBox.Items[index].ToString() == currentWindowName)
                    {
                        AppListComboBox.SelectedIndex = index;
                    }
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (_CaptureThreadEntry != null || _CaptureThread != null)
            {
                _CaptureThreadEntry.ThreadExitSignaled = true;

                while (_CaptureThread.IsAlive) ;

                _CaptureThread = null;
                _CaptureThreadEntry = null;
            }
        }

        private void AudioComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void ResolutionComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                String ResolutionLine = ResolutionComboBox.Items[ResolutionComboBox.SelectedIndex].ToString();
                String[] curWords = ResolutionLine.Split('x');
                if (curWords.Length == 2)
                {
                    NewWidthTextBox.Text = curWords[0];
                    NewHeightTextBox.Text = curWords[1];
                }
            }
            catch { }
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }
    }

    public class Capture
    {
        public bool ThreadExitSignaled = false;
        public bool VideoCaptureAttempted = false;
        public bool VideoCaptureStarted = false;
        public String Filename;
        public UInt32 WindowHandle, WholeWindow, X, Y, Width, Height, BitRate, FrameRate, Audio;
        public void Start()
        {
            ThreadExitSignaled = false;
            UInt32 Result = VideoCapture.CallBeginVideoCapture(WindowHandle, WholeWindow, X, Y, Width, Height, BitRate, FrameRate, Audio, Filename);
            if (Result == 0)
            {
                VideoCaptureStarted = true;
                VideoCaptureAttempted = true;
            }
            else
            {
                VideoCaptureAttempted = true;
                return;
            }
            while (!ThreadExitSignaled)
            {
                VideoCapture.CallCaptureVideoFrame();
            }
            VideoCapture.CallStopVideoCapture();
        }
    }

    class VideoCapture
    {
        public static UInt32 CallBeginVideoCapture(UInt32 WindowHandle, UInt32 WholeWindow, UInt32 X, UInt32 Y, UInt32 Width, UInt32 Height, UInt32 BitRate, UInt32 FrameRate, UInt32 Audio, String Filename)
        {
            StringBuilder sBuffer = new StringBuilder(256);
            sBuffer.Append(Filename);
            UInt32 Result = BeginVideoCapture(WindowHandle, WholeWindow, X, Y, Width, Height, BitRate, FrameRate, Audio, sBuffer);
            Thread.Sleep(100);
            return Result;
        }
        public static void CallCaptureVideoFrame()
        {
            if (CaptureVideoFrame() != 0)
            {
                MessageBox.Show("Failed to capture video frame");
            }
            Thread.Sleep(100);
        }
        public static void CallStopVideoCapture()
        {
            if (StopVideoCapture() != 0)
            {
                MessageBox.Show("Failed to stop video capture");
            }
            Thread.Sleep(100);
        }
        public static void CallEnumerateAndSaveWindows()
        {
            try
            {
                EnumerateAndSaveWindows();
            }
            catch
            {
                MessageBox.Show("A required DLL was not found.  Most likely, this computer has an operating system prior to Windows 7 installed.");
                Application.Exit();
            }
            Thread.Sleep(100);
        }
        public static void CallEnumerateAndSaveAudioCaptureDevices()
        {
            EnumerateAndSaveAudioCaptureDevices();
            Thread.Sleep(100);
        }
        public static void CallReSizeWindow(UInt32 WindowHandle, UInt32 NewWidth, UInt32 NewHeight)
        {
            ReSizeWindow(WindowHandle, NewWidth, NewHeight);
            Thread.Sleep(100);
        }

        //string ScreenCaptureDLL = "C:\\Code\\allProjects\\ScreenCaptureDLL\\Debug\\ScreenCapture.dll";
        const string ScreenCaptureDLL = "VideoCapture.dll";
        [DllImport(ScreenCaptureDLL)]
        public static extern UInt32 BeginVideoCapture(UInt32 WindowHandle, UInt32 WholeWindow, UInt32 X, UInt32 Y, UInt32 Width, UInt32 Height, UInt32 BitRate, UInt32 FrameRate, UInt32 Audio, StringBuilder Filename);

        [DllImport(ScreenCaptureDLL)]
        public static extern UInt32 CaptureVideoFrame();

        [DllImport(ScreenCaptureDLL)]
        public static extern UInt32 StopVideoCapture();

        [DllImport(ScreenCaptureDLL)]
        public static extern UInt32 EnumerateAndSaveWindows();

        [DllImport(ScreenCaptureDLL)]
        public static extern UInt32 EnumerateAndSaveAudioCaptureDevices();

        [DllImport(ScreenCaptureDLL)]
        public static extern UInt32 ReSizeWindow(UInt32 WindowHandle, UInt32 NewWidth, UInt32 NewHeight);
    }
}
