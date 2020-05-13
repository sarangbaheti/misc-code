// TitleTip.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTitleTip window

class CTitleTip : public CWnd
{
public:
	CTitleTip();

	virtual BOOL Create(CListBox* pParentWnd);

	virtual void Show(CRect DisplayRect, int nItemIndex);
	virtual void Hide();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitleTip)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTitleTip();

protected:
	const int m_nNoIndex;        // Not a valid index
	static LPCSTR m_pszWndClass; // Registered class name
	int m_nItemIndex;            // Index of currently displayed listbox item
	CListBox* m_pListBox;        // Parent listbox

    const int m_nAutoPopDelay; // In milliseconds.
    UINT m_nTimerId;
    CPoint m_LastMousePosition;

	BOOL IsListBoxOwnerDraw();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTitleTip)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
