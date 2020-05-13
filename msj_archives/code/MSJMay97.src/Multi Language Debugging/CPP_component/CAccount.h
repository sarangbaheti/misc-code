#if !defined DEF_CAccount_
	#define  DEF_CAccount_

#include "CRow.h"

class CAccount : public CRow
	{
// Constructors & Destructors
public:
	CAccount();
	virtual ~CAccount();
// Attributes
public:
	long m_lAccountID;
	double m_dblBalance;
	SDWORD m_cbAccountID;
	SDWORD m_cbBalance;
// Operations
public:
	virtual LPCTSTR GetDefaultSQL()
		{
		return "select * from StocksAccount where AccountID = ?";
		};
	virtual BOOL Prepare(LPCTSTR lpszQuery = NULL);
	virtual BOOL Execute();
	BOOL IsValidAccount(long lAccountID);
	};

#endif // !defined DEF_CAccount_
