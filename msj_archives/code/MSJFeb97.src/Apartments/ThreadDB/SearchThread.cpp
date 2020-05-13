// SearchThread.cpp : implementation file
//

#include "stdafx.h"
#include "ThreadDB.h"
#include "SearchThread.h"
#include "customer.h"
#include "threaddbctl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchThread

IMPLEMENT_DYNCREATE(CSearchThread, CWinThread)

CSearchThread::CSearchThread()
{
}

CSearchThread::~CSearchThread()
{

}


BOOL CSearchThread::InitInstance()
{
	HRESULT hr ;
	int i ;
/*
Initialize COM in this thread.
*/
	
	hr = CoInitialize (NULL) ;

/*
Unmarshal interface pointers
*/
	IDispatch *pDispatch ; 	IStream *pStream ;

	for (i = 0 ; i < m_StreamArray.GetSize( ) ; i ++)
	{
		
/*
Get stream pointer from array where control has placed it.
*/
		pStream = (IStream *) m_StreamArray [i] ;
		
/*
Use stream pointer to create IDispatch the I can call from
this thread.
*/
		hr = CoGetInterfaceAndReleaseStream(
			pStream ,				// stream containing marshaling info
			IID_IDispatch,			// interface desired
			(void **) &pDispatch) ;	// output variable

		if (hr != S_OK)
		{
			AfxMessageBox ("Couldn't get interface") ;
		}
/*
Put resulting IDispatch in my array of those pointers.
*/
		m_DispatchArray.Add (pDispatch) ;
	}
/*
Create new client object with arbitrary name
*/
	CCustomer *pCustomer = new CCustomer ("John", "Smith", 999) ;
	LPDISPATCH pDispOut = pCustomer->GetIDispatch (FALSE) ;

/*
Fire event to container
*/
	
	COleDispatchDriver driver;

	for (i = 0 ; i < m_DispatchArray.GetSize( ) ; i ++)
	{
		driver.AttachDispatch((IDispatch *)m_DispatchArray[i], FALSE);

		driver.InvokeHelperV(
			m_pCtrl->eventidSearchFinished, 
			DISPATCH_METHOD, VT_EMPTY, NULL,
			EVENT_PARAM(VTS_DISPATCH), 
			(char *)&pDispOut);

		driver.DetachDispatch();
	}
/*
Release customer object. If event handler wanted a pointer to it,
it will have AddRefd it.
*/
	pCustomer->GetIDispatch (FALSE)->Release ( ) ;

	return TRUE;
}

/*
PostQuitMessage( ) is called from CCustomer::OnFinalRelease( ), thereby
ensuting that the thread stays around long enough to service any
customer objects that it created.
*/

int CSearchThread::ExitInstance()
{
	CoUninitialize( ) ;

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSearchThread, CWinThread)
	//{{AFX_MSG_MAP(CSearchThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchThread message handlers
