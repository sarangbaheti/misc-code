// MSJ Visual Developer Column
//
// This source code is a small sub-set of one of 50 classes
// found in Stingray's Objective Toolkit product
// For more information: http://www.stingsoft.com

//  Author:		Scot Wingo and George Shepherd.
//  Description:	Declarations for MSJSuperView
//  Created:		9/1/97
//


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCloudApp:
// See cloud.cpp for the implementation of this class
//

class CCloudApp : public CWinApp
{
public:
	CCloudApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloudApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCloudApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
