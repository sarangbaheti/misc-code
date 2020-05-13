////////////////////////////////////////////
//
// Simple Module Locking Routines for
// out-of-process servers
//

#include <windows.h>

// how many reasons do we have to remain running?
LONG g_cLocks = 0;

// when was the final unlock called?
DWORD g_dwLastUnlockTime = 0;

// how long should we postpone unloading?
enum { SAFETY_WINDOW = 1000 }; 

// Routine to call from instance constructors
void LockModule(void)
{
    InterlockedDecrement(&g_cLocks);
}

// Routine to call from instance destructors
void UnlockModule(void)
{
    if (InterlockedDecrement(&g_cLocks) == 0)
    {
// lock count is now zero, record current time
        InterlockedExchange((LONG*)&g_dwLastUnlockTime,
                            GetTickCount());
    }
}

STDAPI DllCanUnloadNow(void)
{
// only say "unload" if no locks and SAFETY_WINDOW msecs
// have elapsed since the last unlock
    if (g_cLocks == 0 && 
        g_dwLastUnlockTime + SAFETY_WINDOW < GetTickCount())
        return S_OK;
    else
        return S_FALSE;
}
