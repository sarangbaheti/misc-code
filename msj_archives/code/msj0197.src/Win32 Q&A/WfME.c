/**************************************************************
Module name: W4ME.c
Written by: Jeffrey Richter
Purpose: WaitForMultipleExpressions
**************************************************************/


#define STRICT
#include <windows.h>
#include <malloc.h>


///////////////////////////////////////////////////////////////


// If you're using old header files, uncomment the lines below
typedef VOID (APIENTRY *PAPCFUNC)(DWORD dwParam);
WINBASEAPI DWORD WINAPI QueueUserAPC (PAPCFUNC pfnAPC, 
   HANDLE hThread, DWORD dwData);

// If you're using old library files, uncomment the line below
//#pragma comment(linker, "/import:QueueUserAPC@12,LIB=KERNEL32")


///////////////////////////////////////////////////////////////


// Internal data structure representing a single expression.
// Used to tell OR threads what objects to wait on.
typedef struct {
	PHANDLE phExpObjects;   // Points to set of handles
	DWORD cExpObjects;      // Number of handles
} EXPRESSION, *PEXPRESSION;


///////////////////////////////////////////////////////////////


// The OR thread function
DWORD WINAPI WFME_ThreadExpression(PVOID pvParam) {

   // This thread function just waits for an expression to
   // come true. The thread waits in an alertable state so 
   // that it can be forced to stop waiting by queueing an
   // entry to its APC queue.
	PEXPRESSION pExpression = (PEXPRESSION) pvParam;
   return(WaitForMultipleObjectsEx(
      pExpression->cExpObjects, pExpression->phExpObjects, 
      TRUE, INFINITE, TRUE));
}


///////////////////////////////////////////////////////////////


// This is the APC callback routine function
VOID WINAPI WFME_ExpressionAPC (DWORD dwData) {
	// This function intentionally left blank
}


///////////////////////////////////////////////////////////////


// Function to wait on mutiple Boolean expressions
DWORD WINAPI WaitForMultipleExpressions(DWORD cExpObjects, 
   CONST HANDLE* pchExpObjects, DWORD dwTimeOut) {

   // Allocate memory for a copy of the handle array because
   // we need 1 more entry and because we write to it.  
   // Use _alloc so that memory is freed automatically.
   PHANDLE phExpObjects = (PHANDLE) 
      _alloca(sizeof(HANDLE) * (cExpObjects + 1));

	DWORD dwObjBegin = 0;   // First index of a set
   DWORD dwObjCur = 0;     // Current index of object in a set

   // Array of thread handles for threads: 1 pet expression
	HANDLE ahThreads[MAXIMUM_WAIT_OBJECTS];

   // Expression information: 1 per possible thread
   EXPRESSION Expression[MAXIMUM_WAIT_OBJECTS];

	DWORD dwExpNum = 0;  // Current expression number
   DWORD dwNumExps = 0; // Total number of expressions

   // Semaphore to guarantee that only 
   // one expression gets satisfied.
   HANDLE hsemOnlyOne = CreateSemaphore(NULL, 1, 1, NULL);

   DWORD dwThreadId, dwWaitRet = 0;

   // Make a local copy of the kernel object handles and add
   // an extra handle at the end for the hsemOnlyOne semaphore.
   CopyMemory(phExpObjects, pchExpObjects, 
      sizeof(HANDLE) * cExpObjects);
   phExpObjects[cExpObjects] = NULL;  // Put sentinel at end

   // Parse the callers handle list by initializing a 
   // structure for each expression and adding hsemOnlyOne 
   // to each expression.
	while ((dwWaitRet != WAIT_FAILED) && 
          (dwObjCur <= cExpObjects)) {

      // While there are no errors, and there are 
      // object handles in the caller's list...
	
      // Find the beginning of the next expression.
      // OR Expressions are separated by NULL handles.
		while (phExpObjects[dwObjCur] != NULL) 
         dwObjCur++;
      
      // Initialize an expression structure which we'll
      // pass to a thread later so that it can wait for the
      // expression to come true.
		phExpObjects[dwObjCur] = hsemOnlyOne;
      Expression[dwNumExps].phExpObjects = 
         &phExpObjects[dwObjBegin];
		Expression[dwNumExps].cExpObjects = 
         dwObjCur - dwObjBegin + 1;
	 
		if (Expression[dwNumExps].cExpObjects 
         > MAXIMUM_WAIT_OBJECTS) {
         // Error: Too many handles in a single expression
         dwWaitRet = WAIT_FAILED;
         SetLastError(ERROR_SECRET_TOO_LONG);
      }

		// Advance to the next expression
		dwObjBegin = ++dwObjCur;
		if (++dwNumExps == MAXIMUM_WAIT_OBJECTS) {
         // Error: Too many expressions
         dwWaitRet = WAIT_FAILED;
         SetLastError(ERROR_TOO_MANY_SECRETS);
      }
	}

   if (dwWaitRet != WAIT_FAILED) {
      // No errors occurred while parsing the handle list

      // Spawn a thrad to wait on each expression
      for (dwExpNum = 0; dwExpNum < dwNumExps; dwExpNum++) {
		   ahThreads[dwExpNum] = CreateThread(NULL, 
            1 /* we only need a small stack */, 
            WFME_ThreadExpression, &Expression[dwExpNum], 
            0, &dwThreadId);
      }

      // Wait for an expressions to come TRUE or for a timeout
      dwWaitRet = WaitForMultipleObjects(dwExpNum, 
         ahThreads, FALSE, dwTimeOut);

	   if (WAIT_TIMEOUT == dwWaitRet) {
         // If we timed-out, we need to check to see if any 
         // expressions were satisfied by checking the state 
         // of the hsemOnlyOne semaphore.
		   dwWaitRet = WaitForSingleObject(hsemOnlyOne, 0);

         if (WAIT_TIMEOUT == dwWaitRet) {
            // If the semaphore was not signalled, some thread 
            // expressions was satisfied and we need to 
            // determine which expression was satisfied.
			   dwWaitRet = WaitForMultipleObjects(dwExpNum, 
               ahThreads, FALSE, INFINITE);
         } else {
            // No expression was satisfied and the call to 
            // WaitForSingleObject gave us the semaphore so we
            // know that no expression will ever be satisfied
            // now -- waiting for an expression has timed-out.
			   dwWaitRet = WAIT_TIMEOUT;
		   }
	   }

      // Break all the waiting expression threads out of 
      // their wait state so that they can terminate cleanly.
	   for (dwExpNum = 0; dwExpNum < dwNumExps; dwExpNum++) {
		   if ((WAIT_TIMEOUT == dwWaitRet) || 
			    (dwExpNum != (dwWaitRet - WAIT_OBJECT_0))) {
            QueueUserAPC(WFME_ExpressionAPC, 
               ahThreads[dwExpNum], 0);
         }
	   }

#ifdef _DEBUG
      // In debug builds, wait for all of the expression 
      // threads to terminate to make sure that we are 
      // forcing the threads to wake up. In non-debug builds, 
      // we'll assume that this works and not keep this 
      // thread waiting any longer.
	   WaitForMultipleObjects(dwExpNum, 
         ahThreads, TRUE, INFINITE);
#endif

      // Close our handles to all the expression threads
	   for (dwExpNum = 0; dwExpNum < dwNumExps; dwExpNum++) {
		   CloseHandle(ahThreads[dwExpNum]);
	   }
   }  // error occurred while parsing

	CloseHandle(hsemOnlyOne);
	return(dwWaitRet);
}


///////////////////////// End of File /////////////////////////
