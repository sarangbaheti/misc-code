// TippyDialogaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see TippyDialog.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CTippyDialogAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
};

// This declares the one instance of the CTippyDialogAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global TippyDialogaw.  (Its definition is in TippyDialogaw.cpp.)
extern CTippyDialogAppWiz TippyDialogaw;
