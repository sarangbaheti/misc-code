// Multithrd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
class CMultiThread : public CWinThread
{
DECLARE_DYNCREATE(CMultiThread)
public:
	CMultiThread() {}
	virtual ~CMultiThread();

	BOOL CreateThread(DWORD dwCreateFlags = 0,		// masks CWinThread::CreateThread
					  UINT nStackSize = 0,
					  LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL,
					  UINT nMilliSecs = INFINITE);	// upper time limit to wait

	BOOL InitInstance() {return TRUE;}
	int Run();

protected:
	CEvent*		m_pWorkEvent;			// do work event
	CEvent*		m_pExitEvent;			// used to synchronize destruction
	int			m_nCycleTime;			// do work cycle time
	BOOL		m_bEndThread;			// end the thread ?

	virtual void DoWork() {}			//*** should be pure virtual
	CEvent* GetEvent() const {return m_pWorkEvent;}	// cycle control event
	int GetCycleTime() const {return m_nCycleTime;}
	void SetCycleTime(int nMilliSecs) {m_nCycleTime = nMilliSecs;}
};
