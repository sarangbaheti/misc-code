// bounceth.cpp : implementation file
//

#include "stdafx.h"
#include "bounceth.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define WIDTH 	10
#define HEIGHT 	10


/////////////////////////////////////////////////////////////////////////////
// CBounceThread

IMPLEMENT_DYNCREATE(CBounceThread, CWinThread)

extern BOOL g_Beep ;
extern DWORD NextBeepTime ;

CBounceThread::CBounceThread()
{
}

CBounceThread::~CBounceThread()
{
}

BOOL CBounceThread::InitInstance()
{
/*
Get the current time.  Use MOD to get a random x and y starting position
and direction.
*/
	SYSTEMTIME st ;
	RECT r ;

  	GetSystemTime (&st);          
  	           
  	m_pControl->GetClientRect (&r) ;

  	m_xPos = (st.wMilliseconds % r.right);  
  	m_yPos = (st.wMilliseconds % r.bottom);  

  	m_HorzDir = 1 ;
  
  	if(st.wMilliseconds % 2 == 0)           
  	{                                        
    	m_VertDir = 1 ;
  	}
  	else
  	{
    	m_VertDir = -1 ;
  	}

/*
Initialize the CBrush the we will be using to draw on
*/
	BOOL bInitOK ;
	bInitOK = m_Brush.CreateSolidBrush (RGB(0,255,255)) ;

	return bInitOK ;
}

int CBounceThread::ExitInstance()
{
	m_Brush.DeleteObject( ) ;

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CBounceThread, CWinThread)
	//{{AFX_MSG_MAP(CBounceThread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBounceThread message handlers

BOOL CBounceThread::OnIdle(LONG lCount) 
{

/*
Get the client rectangle, check for contact with edges.  If found, change
directions
*/

	RECT r ;
	m_pControl->GetClientRect (&r);

    
/*
Hit right edge
*/
    if ((m_xPos + WIDTH) > r.right)  
    {
      m_xPos = r.right - WIDTH;
      m_HorzDir = -1;                      
    }

/*
Hit bottom edge
*/
	if ((m_yPos + HEIGHT) > r.bottom)
    {
      m_yPos = r.bottom - HEIGHT;           
      m_VertDir = -1;
    }

/*
Check for left edge
*/
	if (m_xPos == 0)
	{
		m_xPos = 1 ;      
      	m_HorzDir = 1 ;
    }

/*
Check for top edge
*/
	if (m_yPos == 0)
    {                                     
      m_yPos = 1 ;
      m_VertDir = 1 ;
    }

/*
Get a DC for the main window, select this thread's brush into it, draw
and ellipse, release the DC
*/

	CClientDC dc (m_pControl) ;
	dc.SelectObject (&m_Brush) ;             
    dc.Ellipse (m_xPos, m_yPos, m_xPos + WIDTH, m_yPos + HEIGHT);


 /*
 Modify position 
 */
 
    m_xPos += m_HorzDir ;                     
    m_yPos += m_VertDir ;                 
/*
Check to see if we are supposed to beep.
*/
	if (g_Beep)
	{
		DWORD now = GetTickCount ( ) ;

		if (now > NextBeepTime)
		{
			MessageBeep (0) ;
			NextBeepTime = now + 1000 ;
		}
	}
/*
Return TRUE to keep drawing infinitely
*/

 	return TRUE ;
}


BOOL CBounceThread::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->hwnd == NULL)
	{
	}
		
	return CWinThread::PreTranslateMessage(pMsg);
}

