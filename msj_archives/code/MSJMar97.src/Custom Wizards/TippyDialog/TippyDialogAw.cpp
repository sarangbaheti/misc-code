// TippyDialogaw.cpp : implementation file
//

#include "stdafx.h"
#include "TippyDialog.h"
#include "TippyDialogaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CTippyDialogAppWiz::InitCustomAppWiz()
{
	// There are no steps in this custom AppWizard.
	SetNumberOfSteps(0);

	// TODO: Add any other custom AppWizard-wide initialization here.
}

// This is called just before the custom AppWizard is unloaded.
void CTippyDialogAppWiz::ExitCustomAppWiz()
{
	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
CAppWizStepDlg* CTippyDialogAppWiz::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(pDlg == NULL);	// By default, this custom AppWizard has no steps

	// Set template macros based on the project name entered by the user.

	// Get value of $$root$$ (already set by AppWizard)
	CString strRoot;
	m_Dictionary.Lookup(_T("root"), strRoot);
	
	// Set value of $$Doc$$, $$DOC$$
	CString strDoc = strRoot.Left(6);
	m_Dictionary[_T("Doc")] = strDoc;
	strDoc.MakeUpper();
	m_Dictionary[_T("DOC")] = strDoc;

	// Set value of $$MAC_TYPE$$
	strRoot = strRoot.Left(4);
	int nLen = strRoot.GetLength();
	if (strRoot.GetLength() < 4)
	{
		CString strPad(_T(' '), 4 - nLen);
		strRoot += strPad;
	}
	strRoot.MakeUpper();
	m_Dictionary[_T("MAC_TYPE")] = strRoot;

	// Return NULL to indicate there are no more steps.  (In this case, there are
	//  no steps at all.)
	return NULL;
}

// Here we define one instance of the CTippyDialogAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global TippyDialogaw.
CTippyDialogAppWiz TippyDialogaw;

