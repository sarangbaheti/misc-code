////////////////////////////////////////////
//
// Simple Module Locking Routines for
// out-of-process servers
//

#include <windows.h>

// how many reasons do we have to remain running?
LONG g_cLocks = 0;

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
// lock count is now zero, so shutdown nicely
        PostQuitMessage(0);
    }
}
