// Asynch.h : header file
//

/////////////////////////////////////////////////////////////////////////////

class CGarbageObject : public CObject
{
public:
	void* m_pGarbage;
};


/////////////////////////////////////////////////////////////////////////////
const int CleanTime = 5;			// garbage cleanup limit

class CAsynchGarbageCollector : public CMultiThread
{									// making base class private requires new
public:
	CAsynchGarbageCollector();
	virtual ~CAsynchGarbageCollector() {}

	void CollectGarbage(void* pBuf);	// get the garbage

protected:
	CObList m_BuffList;				// garbage list
	CCriticalSection m_CritSect;	// arbitrator for garbage list
									// then release it
	virtual void DoWork();			// here
};
