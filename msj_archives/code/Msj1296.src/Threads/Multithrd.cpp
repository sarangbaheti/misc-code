// Multithrd.cpp : implementation file
//

#include "stdafx.h"
#include "Multithrd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMultiThread, CWinThread)

/////////////////////////////////////////////////////////////////////////////
// MultiThread

BOOL CMultiThread::CreateThread(DWORD dwCreateFlags, UINT nStackSize, 
						   LPSECURITY_ATTRIBUTES lpSecurityAttrs, 
						   UINT nMilliSecs)
{
	m_nCycleTime = nMilliSecs;
	m_bEndThread = FALSE;

	// Create a non-signaled, manual-reset event to synchronize destruction
	m_pExitEvent = new CEvent(FALSE, TRUE);
	ASSERT(m_pExitEvent);

	// Create a non-signaled, auto-reset event to wait on for work cycle
	m_pWorkEvent = new CEvent();
	ASSERT(m_pWorkEvent);

	// Start second thread
	return CWinThread::CreateThread(dwCreateFlags, nStackSize, lpSecurityAttrs);
}

CMultiThread::~CMultiThread()
{
	// Start up the other thread so it can complete.
	// When it does, it will set the exit event and the object can be destructed.
	m_bEndThread = TRUE;
	m_pWorkEvent->SetEvent();
	CSingleLock csl(m_pExitEvent);
	csl.Lock();							// wait for 2nd thread to finish
	csl.Unlock();						
	delete m_pWorkEvent;
	delete m_pExitEvent;
}

int CMultiThread::Run()
{
	CSingleLock csl(m_pWorkEvent);		// synch on the work event

	while (!m_bEndThread)				// loop until we're done
	{
		csl.Lock(m_nCycleTime);			// wait for event or timeout
		csl.Unlock();			
		DoWork();						// and then do some work
	}

	m_pExitEvent->SetEvent();			// not waiting signal
	return CWinThread::Run();
}
