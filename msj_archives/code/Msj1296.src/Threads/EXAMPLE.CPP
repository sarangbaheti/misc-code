// examples

class CNetworkMonitor : public CMultiThread
{
protected:
	char* m_pBuf;
	int m_bufSize;
	HANDLE m_hDisplayEvent;

 	virtual void DoWork();
	void GetStats();
	void FormatStats();

public:
	CNetworkMonitor(char* pBuf, int bufSize, HANDLE hDisplayEvent);
}

CNetworkMonitor::CNetworkMonitor(char* pBuf, int bufSize, HANDLE hDisplayEvent)
: CMultiThread(5000)	// cycle every 5 seconds
, m_pBuf(pBuf), m_bufSize(bufSize), m_hDisplayEvent(hDisplayEvent)
{
}

CNetworkMonitor::DoWork()
{
	GetStats();			// get some network statistics
	FormatStats();		// format them for display in m_pBuf
	SetEvent(m_hDisplayEvent)	// signal the display object
}



class CAsynchGarbageCollector : public CMultiThread
{
protected:
	HANDLE m_hEvent;
	void* m_pBuf;

	virtual void DoWork();
	
public:
	CAsynchGarbageCollector();
	void CollectGarbage(void* pBuf);
}

CAsynchGarbageCollector::CAsynchGarbageCollector()
: CMultiThread(m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL), 60000)	// timeout every 60 seconds
{
}

CAsynchGarbageCollector::DoWork()
{
	// pick up the garbage (in pBuf)
}

CAsynchGarbageCollector::CollectGarbage(void* pBuf)
{
	m_pBuf = pBuf;
	SetEvent(m_hEvent);
}
