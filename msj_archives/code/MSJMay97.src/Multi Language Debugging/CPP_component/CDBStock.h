#if !defined DEF_CDBStock_
	#define  DEF_CDBStock_

class CDBStock
	{
// Constructors and Destructors
public:
	CDBStock();
	virtual ~CDBStock();
// Operations
public:
	// Database Level Operations
	BOOL Open();     // handles connections
	BOOL Close();
	BOOL IsValidAccount(long lAccount);
	BOOL BuyStock(long lAccount, LPCTSTR lpszStock, long lShares,
			double dblPrice, double dblCommission);
	BOOL SellStock(long lAccount, LPCTSTR lpszStock, long lShares,
			double dblPrice, double dblCommission);
// Implementation
protected:
	BOOL UpdateAccount(long lAccount, double dblAmount);
	BOOL UpdateShares(long lAccount, LPCTSTR lpszStock, long lShares);
	BOOL TradeShares(LPCTSTR lpszStock, double dblPrice, BOOL bAction,
			long lShares, long* plSharesSold, long* plSellerAccount);
	};

#endif // !defined DEF_CDBStock_
