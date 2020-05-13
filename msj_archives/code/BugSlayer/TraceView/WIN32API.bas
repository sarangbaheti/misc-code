Attribute VB_Name = "WIN32API"
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' John Robbins
' Microsoft Systems Journal, December 1997 - Bugslayer Column!
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' FILE         :     WIN32API.bas
' DESCRIPTION  :
'  The WIN32 API functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                             General Types
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Type STARTUPINFO
    cb As Long
    lpReserved As String
    lpDesktop As String
    lpTitle As String
    dwX As Long
    dwY As Long
    dwXSize As Long
    dwYSize As Long
    dwXCountChars As Long
    dwYCountChars As Long
    dwFillAttribute As Long
    dwFlags As Long
    wShowWindow As Integer
    cbReserved2 As Integer
    lpReserved2 As Byte
    hStdInput As Long
    hStdOutput As Long
    hStdError As Long
End Type

Type PROCESS_INFORMATION
    hProcess As Long
    hThread As Long
    dwProcessID As Long
    dwThreadID As Long
End Type

Type CRITICAL_SECTION
    LockCount As Long
    RecursionCount As Long
    OwningThread As Long
    LockSemaphore As Long
    Reserved As Long
End Type

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                         Constants and defines
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Public Const INFINITE As Long = &HFFFFFFFF

Public Const WAIT_OBJECT_0 As Long = &H0
Public Const WAIT_ABANDONED_0 As Long = &H80
Public Const WAIT_TIMEOUT As Long = &H102

Public Const STILL_ACTIVE As Long = &H103

Public Const WM_MBUTTONDOWN As Long = &H207

Public Const GENERIC_READ As Long = &H80000000
Public Const GENERIC_WRITE As Long = &H40000000

Public Const CREATE_NEW As Long = 1
Public Const CREATE_ALWAYS As Long = 2
Public Const OPEN_EXISTING As Long = 3
Public Const OPEN_ALWAYS As Long = 4
Public Const TRUNCATE_EXISTING As Long = 5

Public Const FILE_BEGIN As Long = 0
Public Const FILE_CURRENT As Long = 1
Public Const FILE_END As Long = 2

Public Const FILE_SHARE_READ                 As Long = &H1
Public Const FILE_SHARE_WRITE                As Long = &H2
Public Const FILE_ATTRIBUTE_READONLY         As Long = &H1
Public Const FILE_ATTRIBUTE_HIDDEN           As Long = &H2
Public Const FILE_ATTRIBUTE_SYSTEM           As Long = &H4
Public Const FILE_ATTRIBUTE_DIRECTORY        As Long = &H10
Public Const FILE_ATTRIBUTE_ARCHIVE          As Long = &H20
Public Const FILE_ATTRIBUTE_NORMAL           As Long = &H80
Public Const FILE_ATTRIBUTE_TEMPORARY        As Long = &H100
Public Const FILE_ATTRIBUTE_COMPRESSED       As Long = &H800
Public Const FILE_NOTIFY_CHANGE_FILE_NAME    As Long = &H1
Public Const FILE_NOTIFY_CHANGE_DIR_NAME     As Long = &H2
Public Const FILE_NOTIFY_CHANGE_ATTRIBUTES   As Long = &H4
Public Const FILE_NOTIFY_CHANGE_SIZE         As Long = &H8
Public Const FILE_NOTIFY_CHANGE_LAST_WRITE   As Long = &H10
Public Const FILE_NOTIFY_CHANGE_SECURITY     As Long = &H100
Public Const MAILSLOT_NO_MESSAGE             As Long = INFINITE
Public Const MAILSLOT_WAIT_FOREVER           As Long = INFINITE
Public Const FILE_CASE_SENSITIVE_SEARCH      As Long = &H1
Public Const FILE_CASE_PRESERVED_NAMES       As Long = &H2
Public Const FILE_UNICODE_ON_DISK            As Long = &H4
Public Const FILE_PERSISTENT_ACLS            As Long = &H8
Public Const FILE_FILE_COMPRESSION           As Long = &H10
Public Const FILE_VOLUME_IS_COMPRESSED       As Long = &H8000

Public Const INVALID_HANDLE_VALUE As Long = INFINITE

Public Const SWP_NOMOVE     As Long = 2
Public Const SWP_NOSIZE     As Long = 1
Public Const HWND_TOPMOST   As Long = -1
Public Const HWND_NOTOPMOST As Long = -2

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                       Generally Useful Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Declare Function CloseHandle Lib "Kernel32" _
         (ByVal hObject As Long) As Long

Declare Sub OutputDebugString Lib "Kernel32" _
         Alias "OutputDebugStringA" _
         (ByVal lpOutputString As String)

Declare Sub DebugBreak Lib "Kernel32" ()

Declare Sub Sleep Lib "Kernel32" (ByVal dwMilliseconds As Long)

Declare Function GetCurrentProcessId Lib "Kernel32" () As Long

Declare Function GetLastError Lib "Kernel32" () As Long

Declare Function SendMessage Lib "user32" _
         Alias "SendMessageA" _
         (ByVal hwnd As Long, _
          ByVal wMsg As Long, _
          ByVal wParam As Any, _
          lParam As Any) As Long

Declare Function PostMessage Lib "user32" _
         Alias "PostMessageA" _
         (ByVal hwnd As Long, _
         ByVal wMsg As Long, _
         ByVal wParam As Long, _
         ByVal lParam As Long) As Long

Declare Function GetDiskFreeSpace Lib "Kernel32" _
         Alias "GetDiskFreeSpaceA" _
         (ByVal lpRootPathName As String, _
         ByRef lpSectorsPerCluster As Long, _
         ByRef lpBytesPerSector As Long, _
         ByRef lpNumberOfFreeClusters As Long, _
         ByRef lpTotalNumberOfClusters As Long) As Long

Declare Function SetWindowPos Lib "user32" _
        (ByVal hwnd As Long, _
         ByVal hWndInsertAfter As Long, _
         ByVal x As Long, _
         ByVal y As Long, _
         ByVal cx As Long, _
         ByVal cy As Long, _
         ByVal wFlags As Long) As Long


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' INI Reading/Writing Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Declare Function GetPrivateProfileString Lib "Kernel32" _
         Alias "GetPrivateProfileStringA" _
         (ByVal lpAppName As String, _
         ByVal lpKeyName As String, _
         ByVal lpDefault As String, _
         ByVal lpReturnedString As String, _
         ByVal nSize As Long, _
         ByVal lpFileName As String) As Long

Declare Function GetPrivateProfileInt Lib "Kernel32" _
         Alias "GetPrivateProfileIntA" _
         (ByVal lpAppName As String, _
          ByVal lpKeyName As String, _
          ByVal nDefault As Long, _
          ByVal lpFileName As String) As Long

Declare Function GetPrivateProfileSection Lib "Kernel32" _
         Alias "GetPrivateProfileSectionA" _
         (ByVal lpAppName As String, _
         ByVal lpReturnedString As String, _
         ByVal nSize As Long, _
         ByVal lpFileName As String) As Long

Declare Function GetPrivateProfileSectionNames Lib "Kernel32" _
         Alias "GetPrivateProfileSectionNamesA" _
         (ByVal lpszReturnBuffer As String, _
         ByVal nSize As Long, _
         ByVal lpFileName As String) As Long

Declare Function WritePrivateProfileSection Lib "Kernel32" _
         Alias "WritePrivateProfileSectionA" _
         (ByVal lpAppName As String, _
         ByVal lpString As String, _
         ByVal lpFileName As String) As Long

Declare Function WritePrivateProfileString Lib "Kernel32" _
         Alias "WritePrivateProfileStringA" _
         (ByVal lpAppName As String, _
         ByVal lpKeyName As String, _
         ByVal lpString As String, _
         ByVal lpFileName As String) As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                            Thread Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

' Note:  This declaration of CreateThread does not allow you to pass
'  thread attributes.  This is the CreateThread that should be used most
'  often because the parameter for the thread function is passed by
'  reference.
Public Declare Function CreateThread Lib "Kernel32" _
         (ByVal lpThreadAttributes As Long, _
          ByVal dwStackSize As Long, _
          ByVal lpStartAddress As Any, _
          ByRef lpParameter As Any, _
          ByVal dwCreationFlags As Long, _
          ByRef lpThreadId As Long) As Long

' If you only are passing a single variable type like an integer or
'  string as the thread parameter, use this version of CreateThread.
' Note that I set the lpParameter type to long.
Public Declare Function CreateThread_ByValParam Lib "Kernel32" _
         Alias "CreateThread" _
         (ByVal lpThreadAttributes As Long, _
          ByVal dwStackSize As Long, _
          ByVal lpStartAddress As Any, _
          ByVal lpParameter As Long, _
          ByVal dwCreationFlags As Long, _
          ByRef lpThreadId As Long) As Long

Public Declare Function TerminateThread Lib "Kernel32" _
         (ByVal hThread As Long, _
          ByVal dwExitCode As Long) As Long

Declare Function SuspendThread Lib "Kernel32" _
         (ByVal hThread As Long) As Long

Declare Function ResumeThread Lib "Kernel32" _
         (ByVal hThread As Long) As Long

Declare Function GetExitCodeThread Lib "Kernel32" _
         (ByVal hThread As Long, _
          ByRef lpExitCode As Long) As Long

Declare Sub ExitThread Lib "Kernel32" (ByVal dwExitCode As Long)

Declare Function GetCurrentThread Lib "Kernel32" () As Long

Declare Function GetCurrentThreadId Lib "Kernel32" () As Long


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                            Event Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Declare Function CreateEvent Lib "Kernel32" Alias "CreateEventA" _
         (ByVal lpEventAttributes As Long, _
          ByVal bManualReset As Long, _
          ByVal bInitialState As Long, _
          ByVal lpName As String) As Long

Declare Function OpenEvent Lib "Kernel32" Alias "OpenEventA" _
         (ByVal dwDesiredAccess As Long, _
          ByVal bInheritHandle As Long, _
          ByVal lpName As String) As Long

Declare Function SetEvent Lib "Kernel32" _
         (ByVal hEvent As Long) As Long

Declare Function ResetEvent Lib "Kernel32" _
         (ByVal hEvent As Long) As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                       Critical Section Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Declare Sub InitializeCriticalSection Lib "Kernel32" _
         (ByRef lpCriticalSection As CRITICAL_SECTION)

Declare Sub DeleteCriticalSection Lib "Kernel32" _
         (ByRef lpCriticalSection As CRITICAL_SECTION)

Declare Sub EnterCriticalSection Lib "Kernel32" _
         (ByRef lpCriticalSection As CRITICAL_SECTION)

Declare Sub LeaveCriticalSection Lib "Kernel32" _
         (ByRef lpCriticalSection As CRITICAL_SECTION)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                       Synchronization Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Declare Function WaitForMultipleObjects Lib "Kernel32" _
         (ByVal nCount As Long, _
          ByRef lpHandles As Long, _
          ByVal bWaitAll As Long, _
          ByVal dwMilliseconds As Long) As Long

Declare Function WaitForSingleObject Lib "Kernel32" _
         (ByVal hHandle As Long, _
          ByVal dwMilliseconds As Long) As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'              Process Creation and Manipulation Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Declare Function CreateProcess Lib "Kernel32" Alias "CreateProcessA" _
         (ByVal lpApplicationName As String, _
          ByVal lpCommandLine As String, _
          ByVal lpProcessAttributes As Long, _
          ByVal lpThreadAttributes As Long, _
          ByVal bInheritHandles As Long, _
          ByVal dwCreationFlags As Long, _
          ByVal lpEnvironment As String, _
          ByVal lpCurrentDriectory As String, _
          ByRef lpStartupInfo As STARTUPINFO, _
          ByRef lpProcessInformation As PROCESS_INFORMATION) As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                             Misc. Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Declare Function ReadProcessMemory Lib "Kernel32" _
         (ByVal hProcess As Long, _
          ByVal lpBaseAddress As Long, _
          ByVal lpBuffer As String, _
          ByVal nSize As Long, _
          ByVal lpNumberOfBytesWritten As Long) As Long

Declare Function SetWindowText Lib "user32" Alias "SetWindowTextA" _
         (ByVal hwnd As Long, _
          ByVal lpString As String) As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'                        File Handling Functions
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Declare Function CreateFile Lib "Kernel32" Alias "CreateFileA" _
         (ByVal lpFileName As String, _
          ByVal dwDesiredAccess As Long, _
          ByVal dwShareMode As Long, _
          ByVal lpSecurityAttributes As Long, _
          ByVal dwCreationDisposition As Long, _
          ByVal dwFlagsAndAttributes As Long, _
          ByVal hTemplateFile As Long) As Long

Declare Function SetFilePointer Lib "Kernel32" _
         (ByVal hFile As Long, _
          ByVal lDistanceToMove As Long, _
          ByVal lpDistanceToMoveHigh As Long, _
          ByVal dwMoveMethod As Long) As Long

Declare Function SetEndOfFile Lib "Kernel32" _
         (ByVal hFile As Long) As Long

Declare Function GetFileSize Lib "Kernel32" _
         (ByVal hFile, _
          ByVal lpFileSizeHigh) As Long

Declare Function DeleteFile Lib "Kernel32" Alias "DeleteFileA" _
         (ByVal lpFileName) As Long

