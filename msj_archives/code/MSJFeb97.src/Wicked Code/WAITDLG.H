//***************************************************************************
//
//  WaitDlg.h
//
//***************************************************************************

class CWaitDialog : public CDialog
{
protected:
    BOOL* m_pFlag;

public:
    CWaitDialog (BOOL*, LPCTSTR = NULL, LPCTSTR = NULL);
    virtual ~CWaitDialog ();

    virtual void OnCancel ();

    BOOL Pump ();
    void SetPercentComplete (int);
    void SetMessageText (LPCTSTR);
    void Close ();
};
