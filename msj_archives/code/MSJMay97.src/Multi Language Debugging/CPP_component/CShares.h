#if !defined DEF_CShares_
	#define  DEF_CShares_

#include "CRow.h"

class CShares : public CRow
	{
// Constructors & Destructors
public:
	CShares();
	virtual ~CShares();
// Attributes
public:
	long m_lAccountID;
	TCHAR m_szStockName[20];
	long m_lShares;
	SDWORD m_cbAccountID;
	SDWORD m_cbStockName;
	SDWORD m_cbShares;
// Operations
public:
	virtual LPCTSTR GetDefaultSQL()
		{
		return "select * from StocksShares where AccountID = ?"
				" and Stock = ?";
		};
	virtual BOOL Prepare(LPCTSTR lpszQuery = NULL);
	virtual BOOL Execute();
	};

#endif // !defined DEF_CShares_
