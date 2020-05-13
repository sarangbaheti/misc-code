#if !defined DEF_CTrades_
	#define  DEF_CTrades_

#include "CRow.h"

class CTrades : public CRow
	{
// Constructors & Destructors
public:
	CTrades();
	virtual ~CTrades();
// Attributes
public:
	long m_lAccountID;
	TCHAR m_szStockName[20];
	long m_lAction;
	long m_lShares;
	double m_dblPrice;
	SDWORD m_cbAccountID;
	SDWORD m_cbStockName;
	SDWORD m_cbAction;
	SDWORD m_cbShares;
	SDWORD m_cbPrice;
// Operations
public:
	virtual LPCTSTR GetDefaultSQL()
		{
		return "select * from StocksTrades where Stock = ?"
				" and Price <= ? and Action = ?";
		};
	virtual BOOL Prepare(LPCTSTR lpszQuery = NULL);
	virtual BOOL Execute();
	};

#endif // !defined DEF_CTrades_
