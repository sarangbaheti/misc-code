// Customer.cpp : implementation file
//

#include "stdafx.h"
#include "ThreadDB.h"
#include "Customer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomer

IMPLEMENT_DYNCREATE(CCustomer, CCmdTarget)

CCustomer::CCustomer()
{
	EnableAutomation();
	m_firstName = "(none)" ;
	m_lastName = "(none)" ;
	m_socialSecurityNumber = 999 ;
}

CCustomer::CCustomer(LPTSTR firstName, LPTSTR lastName, long SocSec)
{
	EnableAutomation();
	m_firstName = firstName ;
	m_lastName = lastName ;
	m_socialSecurityNumber = SocSec ;
}

CCustomer::~CCustomer()
{
}


void CCustomer::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	PostQuitMessage (0) ;
	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCustomer, CCmdTarget)
	//{{AFX_MSG_MAP(CCustomer)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCustomer, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCustomer)
	DISP_PROPERTY_NOTIFY(CCustomer, "LastName", m_lastName, OnLastNameChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CCustomer, "FirstName", m_firstName, OnFirstNameChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CCustomer, "SocialSecurityNumber", m_socialSecurityNumber, OnSocialSecurityNumberChanged, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICustomer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {940B07D1-3664-11D0-9077-00608C86B89C}
static const IID IID_ICustomer =
{ 0x940b07d1, 0x3664, 0x11d0, { 0x90, 0x77, 0x0, 0x60, 0x8c, 0x86, 0xb8, 0x9c } };

BEGIN_INTERFACE_MAP(CCustomer, CCmdTarget)
	INTERFACE_PART(CCustomer, IID_ICustomer, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomer message handlers

void CCustomer::OnLastNameChanged() 
{
	// TODO: Add notification handler code

}

void CCustomer::OnFirstNameChanged() 
{
	// TODO: Add notification handler code

}

void CCustomer::OnSocialSecurityNumberChanged() 
{
	// TODO: Add notification handler code

}
