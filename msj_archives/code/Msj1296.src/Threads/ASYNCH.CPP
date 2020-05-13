// Asynch.cpp : implementation file
//

#include "stdafx.h"
#include "multithrd.h"
#include "asynch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

CAsynchGarbageCollector::CAsynchGarbageCollector()
{
	CreateThread();
}

void CAsynchGarbageCollector::CollectGarbage(void* pBuf)
{	
	CGarbageObject* pObj = new CGarbageObject;
	ASSERT(pObj);
	pObj->m_pGarbage = pBuf;			// create fresh garbage object

	CSingleLock csl(&m_CritSect);		// be safe
	csl.Lock();							// when accessing garbage list

	m_BuffList.AddTail(pObj);			// add the garbage to the list
	int count = m_BuffList.GetCount();
	csl.Unlock();							

	// if it's time, release the garbage on the other thread
	if (count >= CleanTime)
		GetEvent()->SetEvent();
}


void CAsynchGarbageCollector::DoWork()
{
	if (!m_BuffList.IsEmpty())
	{
		CSingleLock csl(&m_CritSect);		// be safe
		csl.Lock();							// when accessing garbage list

		while (!m_BuffList.IsEmpty())
		{
			// We could check the buffers before release
			// Now remove the garbage
			delete (static_cast<CGarbageObject*> (m_BuffList.GetHead()))->m_pGarbage;
			delete m_BuffList.RemoveHead();				// and the list entry
		}

		csl.Unlock();							
	}
	// Now we could de-fragment the released buffers
}