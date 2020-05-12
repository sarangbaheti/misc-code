//  source:
//  https://msdn.microsoft.com/en-us/library/ms681418(v=vs.85).aspx
//  Copyright (C) Microsoft. All rights reserved.

/*
* Sample code for the Wait Chain Traversal (WCT) API.
*
* This program enumerates all threads in the system and prints the
* wait chain for each of them.  It should be run from an elevated
* command prompt to get results for services.
*
*/

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wct.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Advapi32.lib")

typedef struct _STR_ARRAY
{
    CHAR Desc[32];
} STR_ARRAY;

// Human-readable names for the different synchronization types.
/*
typedef enum _WCT_OBJECT_TYPE
{
WctCriticalSectionType = 1,
WctSendMessageType,
WctMutexType,
WctAlpcType,
WctComType,
WctThreadWaitType,
WctProcessWaitType,
WctThreadType,
WctComActivationType,
WctUnknownType,
WctSocketIoType,
WctSmbIoType,
WctMaxType
} WCT_OBJECT_TYPE;

typedef enum _WCT_OBJECT_STATUS
{
WctStatusNoAccess = 1,            // ACCESS_DENIED for this object
WctStatusRunning,                 // Thread status
WctStatusBlocked,                 // Thread status
WctStatusPidOnly,                 // Thread status
WctStatusPidOnlyRpcss,            // Thread status
WctStatusOwned,                   // Dispatcher object status
WctStatusNotOwned,                // Dispatcher object status
WctStatusAbandoned,               // Dispatcher object status
WctStatusUnknown,                 // All objects
WctStatusError,                   // All objects
WctStatusMax
} WCT_OBJECT_STATUS;

*/
STR_ARRAY STR_OBJECT_TYPE[] =
{
    { "CriticalSection" },
    { "SendMessage" },
    { "Mutex" },
    { "Alpc" },
    { "Com" },
    { "ThreadWait" },
    { "ProcWait" },
    { "Thread" },
    { "ComActivation" },
    { "Unknown" },
    { "Max" }
};

// Global variable to store the WCT session handle
HWCT g_WctHandle = NULL;

// Global variable to store OLE32.DLL module handle.
HMODULE g_Ole32Hnd = NULL;

//
// Function prototypes
//

static void
PrintWaitChain(
    __in DWORD ThreadId
    );


static BOOL
GrantDebugPrivilege()
/*++

Routine Description:

Enables the debug privilege (SE_DEBUG_NAME) for this process.
This is necessary if we want to retrieve wait chains for processes
not owned by the current user.

Arguments:

None.

Return Value:

TRUE if this privilege could be enabled; FALSE otherwise.

--*/
{
    BOOL             fSuccess = FALSE;
    HANDLE           TokenHandle = NULL;
    TOKEN_PRIVILEGES TokenPrivileges;

    if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
        &TokenHandle))
    {
        printf("Could not get the process token");
        goto Cleanup;
    }

    TokenPrivileges.PrivilegeCount = 1;

    if (!LookupPrivilegeValue(NULL,
        SE_DEBUG_NAME,
        &TokenPrivileges.Privileges[0].Luid))
    {
        printf("Couldn't lookup SeDebugPrivilege name");
        goto Cleanup;
    }

    TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(TokenHandle,
        FALSE,
        &TokenPrivileges,
        sizeof(TokenPrivileges),
        NULL,
        NULL))
    {
        printf("Could not revoke the debug privilege");
        goto Cleanup;
    }

    fSuccess = TRUE;

Cleanup:

    if (TokenHandle)
    {
        CloseHandle(TokenHandle);
    }

    return fSuccess;
}

static BOOL
CheckThreads(
    __in DWORD ProcId
    )
    /*++

    Routine Description:

    Enumerates all threads (or optionally only threads for one
    process) in the system.  It the calls the WCT API on each of them.

    Arguments:

    ProcId--Specifies the process ID to analyze.  If '0' all processes
    in the system will be checked.

    Return Value:

    TRUE if processes could be checked; FALSE if a general failure
    occurred.

    --*/
{
    DWORD processes[1024];
    DWORD numProcesses;
    DWORD i;

    // Try to enable the SE_DEBUG_NAME privilege for this process. 
    // Continue even if this fails--we just won't be able to retrieve
    // wait chains for processes not owned by the current user.
    if (!GrantDebugPrivilege())
    {
        printf("Could not enable the debug privilege");
    }

    // Get a list of all processes currently running.
    if (EnumProcesses(processes, sizeof(processes), &numProcesses) == FALSE)
    {
        printf("Could not enumerate processes");
        return FALSE;
    }

    for (i = 0; i < numProcesses / sizeof(DWORD); i++)
    {
        HANDLE process;
        HANDLE snapshot;

        if (processes[i] == GetCurrentProcessId())
        {
            continue;
        }

        // If the caller specified a Process ID, check if we have a match.
        if (ProcId != 0)
        {
            if (processes[i] != ProcId)
            {
                continue;
            }
        }

        // Get a handle to this process.
        process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processes[i]);
        if (process)
        {
            WCHAR file[MAX_PATH];

            printf("Process 0x%x - ", processes[i]);

            // Retrieve the executable name and print it.
            if (GetProcessImageFileName(process, file, ARRAYSIZE(file)) > 0)
            {
                PCWSTR filePart = wcsrchr(file, L'\\');
                if (filePart)
                {
                    filePart++;
                }
                else
                {
                    filePart = file;
                }

                printf("%S", filePart);
            }

            printf("\n----------------------------------\n");

            // Get a snapshot of this process. This enables us to
            // enumerate its threads.
            snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,
                processes[i]);
            if (snapshot)
            {
                THREADENTRY32 thread;
                thread.dwSize = sizeof(thread);

                // Walk the thread list and print each wait chain
                if (Thread32First(snapshot, &thread))
                {
                    do
                    {
                        if (thread.th32OwnerProcessID == processes[i])
                        {
                            // Open a handle to this specific thread
                            HANDLE threadHandle = OpenThread(THREAD_ALL_ACCESS,
                                FALSE,
                                thread.th32ThreadID);
                            if (threadHandle)
                            {
                                // Check whether the thread is still running
                                DWORD exitCode;
                                GetExitCodeThread(threadHandle, &exitCode);

                                if (exitCode == STILL_ACTIVE)
                                {
                                    // Print the wait chain.
                                    PrintWaitChain(thread.th32ThreadID);
                                }

                                CloseHandle(threadHandle);
                            }
                        }
                    } while (Thread32Next(snapshot, &thread));
                }
                CloseHandle(snapshot);
            }

            CloseHandle(process);
            printf("\n");
        }
    }
    return TRUE;
}

static void
PrintWaitChain(
    __in DWORD ThreadId
    )
    /*++

    Routine Description:

    Enumerates all threads (or optionally only threads for one
    process) in the system. It the calls the WCT API on each thread.

    Arguments:

    ThreadId--Specifies the thread ID to analyze.

    Return Value:

    (none)

    --*/
{
    WAITCHAIN_NODE_INFO NodeInfoArray[WCT_MAX_NODE_COUNT];
    DWORD               Count, i;
    BOOL                IsCycle;

    printf("%d: ", ThreadId);

    Count = WCT_MAX_NODE_COUNT;

    // Make a synchronous WCT call to retrieve the wait chain.
    if (!GetThreadWaitChain(g_WctHandle,
        NULL,
        WCTP_GETINFO_ALL_FLAGS,
        ThreadId,
        &Count,
        NodeInfoArray,
        &IsCycle))
    {
        printf("Error (0X%x)\n", GetLastError());
        return;
    }

    // Check if the wait chain is too big for the array we passed in.
    if (Count > WCT_MAX_NODE_COUNT)
    {
        printf("Found additional nodes %d\n", Count);
        Count = WCT_MAX_NODE_COUNT;
    }

    // Loop over all the nodes returned and print useful information.
    for (i = 0; i < Count; i++)
    {
        switch (NodeInfoArray[i].ObjectType)
        {
        case WctThreadType:
            // A thread node contains process and thread ID.
            printf("[%x:%x:%s]->",
                NodeInfoArray[i].ThreadObject.ProcessId,
                NodeInfoArray[i].ThreadObject.ThreadId,
                ((NodeInfoArray[i].ObjectStatus == WctStatusBlocked) ? "blocked" : "running"));
            break;

        default:
            // A synchronization object.

            // Some objects have names...
            if (NodeInfoArray[i].LockObject.ObjectName[0] != L'\0')
            {
                printf("[%s:%S]->",
                    STR_OBJECT_TYPE[NodeInfoArray[i].ObjectType - 1].Desc,
                    NodeInfoArray[i].LockObject.ObjectName);
            }
            else
            {
                printf("[%s]->",
                    STR_OBJECT_TYPE[NodeInfoArray[i].ObjectType - 1].Desc);
            }
            if (NodeInfoArray[i].ObjectStatus == WctStatusAbandoned)
            {
                printf("<abandoned>");
            }
            break;
        }
    }

    printf("[End]");

    // Did we find a deadlock?
    if (IsCycle)
    {
        printf(" !!!Deadlock!!!");
    }

    printf("\n");
}

static void
Usage()
/*++

Routine Description:

Print usage information to stdout.

--*/
{
    printf("\nPrints the thread wait chains for one or all processes in the system.\n\n");
    printf("\nUsage:\tWctEnum [ProcId]\n");
    printf("\t (no params) -- get the wait chains for all processes\n");
    printf("\t ProcId      -- get the wait chains for the specified process\n\n");
}

static BOOL
InitCOMAccess()
/*++

Routine Description:

Register COM interfaces with WCT. This enables WCT to provide wait
information if a thread is blocked on a COM call.

--*/
{
    PCOGETCALLSTATE       CallStateCallback;
    PCOGETACTIVATIONSTATE ActivationStateCallback;

    // Get a handle to OLE32.DLL. You must keep this handle around
    // for the life time for any WCT session.
    g_Ole32Hnd = LoadLibrary(L"ole32.dll");
    if (!g_Ole32Hnd)
    {
        printf("ERROR: GetModuleHandle failed: 0x%X\n", GetLastError());
        return FALSE;
    }

    // Retrieve the function addresses for the COM helper APIs.
    CallStateCallback = (PCOGETCALLSTATE)
        GetProcAddress(g_Ole32Hnd, "CoGetCallState");
    if (!CallStateCallback)
    {
        printf("ERROR: GetProcAddress failed: 0x%X\n", GetLastError());
        return FALSE;
    }

    ActivationStateCallback = (PCOGETACTIVATIONSTATE)
        GetProcAddress(g_Ole32Hnd, "CoGetActivationState");
    if (!ActivationStateCallback)
    {
        printf("ERROR: GetProcAddress failed: 0x%X\n", GetLastError());
        return FALSE;
    }

    // Register these functions with WCT.
    RegisterWaitChainCOMCallback(CallStateCallback,
        ActivationStateCallback);
    return TRUE;
}

int _cdecl
wmain(
    __in int argc,
    __in_ecount(argc) PWSTR* argv
    )
    /*++

    Routine Description:

    Main entry point for this application.

    --*/
{
    int rc = 1;

    // Initialize the WCT interface to COM. Continue if this
    // fails--there just will not be COM information.
    if (!InitCOMAccess())
    {
        printf("Could not enable COM access\n");
    }

    // Open a synchronous WCT session.
    g_WctHandle = OpenThreadWaitChainSession(0, NULL);
    if (NULL == g_WctHandle)
    {
        printf("ERROR: OpenThreadWaitChainSession failed\n");
        goto Cleanup;
    }

    if (argc < 2)
    {
        // Enumerate all threads in the system.
        CheckThreads(0);
    }
    else
    {
        // Only enumerate threads in the specified process.
        //
        // Take the first command line parameter as the process ID.
        DWORD  ProcId = 0;

        ProcId = _wtoi(argv[1]);
        if (ProcId == 0)
        {
            Usage();
            goto Cleanup;
        }

        CheckThreads(ProcId);
    }

    // Close the WCT session.
    CloseThreadWaitChainSession(g_WctHandle);

    rc = 0;

Cleanup:

    if (NULL != g_Ole32Hnd)
    {
        FreeLibrary(g_Ole32Hnd);
    }

    return rc;
}

