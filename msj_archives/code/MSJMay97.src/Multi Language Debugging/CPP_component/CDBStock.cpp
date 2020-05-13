#include "stdafx.h"

#include "CDBStock.h"

#include "CAccount.h"
#include "CShares.h"
#include "CTrades.h"

CDBStock::CDBStock()
	{
	}

CDBStock::~CDBStock()
	{
	}

BOOL CDBStock::IsValidAccount(long lAccount)
	{
	CAccount acct;
	acct.Open();
	BOOL bRet = acct.IsValidAccount(lAccount);
	acct.Close();
	return bRet;
	}

BOOL CDBStock::BuyStock(long lBuyerAccount, LPCTSTR lpszStock,
		long lShares, double dblPrice, double dblCommission)
	{
	long lSellerAccount = -1;
	long lSharesSold = 0;
	long lRow = 0;
	if (lpszStock == NULL)
		return FALSE;
	while (lShares > 0)
		{
		if (!TradeShares(lpszStock, dblPrice, FALSE, lShares,
				&lSharesSold, &lSellerAccount))
			break;  // No shares were available.
		lShares -= lSharesSold;
		// Update the account balance
		if (!UpdateAccount(lSellerAccount,
				(lSharesSold*dblPrice)-dblCommission) ||
				!UpdateAccount(lBuyerAccount,
				(lSharesSold*dblPrice*-1)-dblCommission))
			{
			lShares += lSharesSold;
			break;
			}
		// Update the shares in the accounts.
		if (!UpdateShares(lSellerAccount, lpszStock,
				(-1*lSharesSold)) ||
				!UpdateShares(lBuyerAccount, lpszStock, lSharesSold))
			{
			lShares += lSharesSold;
			break;
			}
		}
	// If there are any unbought shares, enter it in the trades
	// Also enter unbought shares if there is an error doing any other
	// work.  We only fail the buy process if this portion fails.
	if (lShares > 0)
		{
		CTrades trades;
		trades.Open(SQL_CURSOR_DYNAMIC, SQL_CONCUR_VALUES);
		trades.Prepare("select * from StocksTrades");
		if (!trades.Execute())
			return FALSE;
		if (!trades.MoveFirst())
			return FALSE;
		// Input information for a new record.
		trades.m_lAccountID = lBuyerAccount;
		_tcscpy(trades.m_szStockName, lpszStock);
		trades.m_lAction = 1;       // Buy Shares
		trades.m_lShares = lShares;
		trades.m_dblPrice = dblPrice;
		trades.m_cbAccountID = 0;
		trades.m_cbAction = 0;
		trades.m_cbShares = 0;
		trades.m_cbPrice = 0;
		trades.m_cbStockName = SQL_NTS;
		// Add the record
		if (!trades.Add(0))
			return FALSE;
		trades.Close();
		}
	return TRUE;
	}

BOOL CDBStock::SellStock(long lSellerAccount, LPCTSTR lpszStock,
		long lShares, double dblPrice, double dblCommission)
	{
	long lBuyerAccount = -1;
	long lSharesBought = 0;
	long lRow = 0;
	if (lpszStock == NULL)
		return FALSE;
	while (lShares > 0)
		{
		if (!TradeShares(lpszStock, dblPrice, TRUE, lShares,
				&lSharesBought, &lBuyerAccount))
			break;  // No shares were available.
		lShares -= lSharesBought;
		// Update the account balance
		if (!UpdateAccount(lBuyerAccount,
				(lSharesBought*dblPrice*-1)-dblCommission) ||
				!UpdateAccount(lSellerAccount,
				(lSharesBought*dblPrice)-dblCommission))
			{
			// Need to reset shares.
			lShares += lSharesBought;
			break;
			}
		// Update the shares in the accounts.
		if (!UpdateShares(lBuyerAccount, lpszStock, lSharesBought) ||
				!UpdateShares(lSellerAccount, lpszStock,
				(-1*lSharesBought)))
			{
			// Need to reset shares.
			lShares += lSharesBought;
			break;
			}
		}
	// If there are any unsold shares, enter it in the trades
	if (lShares > 0)
		{
		CTrades trades;
		trades.Open(SQL_CURSOR_DYNAMIC, SQL_CONCUR_VALUES);
		trades.Prepare("select * from StocksTrades");
		if (!trades.Execute())
			return FALSE;
		if (!trades.MoveFirst())
			return FALSE;
		// Input information for a new record.
		trades.m_lAccountID = lSellerAccount;
		_tcscpy(trades.m_szStockName, lpszStock);
		trades.m_lAction = 0;       // Sell Shares
		trades.m_lShares = lShares;
		trades.m_dblPrice = dblPrice;
		trades.m_cbAccountID = 0;
		trades.m_cbAction = 0;
		trades.m_cbShares = 0;
		trades.m_cbPrice = 0;
		trades.m_cbStockName = SQL_NTS;
		// Add the record
		if (!trades.Add(0))
			return FALSE;
		trades.Close();
		}
	return TRUE;
	}

BOOL CDBStock::UpdateAccount(long lAccount, double dblAmount)
	{
	// Update the seller's account with the shares sold
	CAccount acct;
	acct.Open(SQL_CURSOR_KEYSET_DRIVEN, SQL_CONCUR_LOCK);
	acct.Prepare();
	acct.m_lAccountID = lAccount;
	acct.Execute();
	if (!acct.MoveFirst())
		return FALSE;
	acct.m_dblBalance += dblAmount;
	if (!acct.Update(1))
		return FALSE;
	acct.Close();
	return TRUE;
	}

BOOL CDBStock::TradeShares(LPCTSTR lpszStock, double dblPrice,
		BOOL bAction, long lShares, long* plSharesSold,
		long* plSellerAccount)
	{
	CTrades trades;
	trades.Open(SQL_CURSOR_DYNAMIC, SQL_CONCUR_VALUES);
	BOOL bRet;
	*plSharesSold = 0;
	// Get the correct set of shares depending upon whether we're
	// buying or selling.
	if (bAction == FALSE)
		bRet = trades.Prepare(trades.GetDefaultSQL());
	else
		bRet = trades.Prepare(_T("select * from StocksTrades where"
				" Stock = ? and Price >= ? and Action = ?"));
	if (bRet == FALSE)
		return FALSE;       // Critical error
	_tcscpy(trades.m_szStockName, lpszStock);
	trades.m_dblPrice = dblPrice;
	trades.m_lAction = bAction;
	trades.Execute();
	// Check for any outstanding trades
	if (!trades.MoveFirst())
		return FALSE;           // no trades available
	*plSellerAccount = trades.m_lAccountID;
	if (trades.m_lShares > lShares)
		{
		// If order has more shares to sell than we need
		trades.m_lShares -= lShares;
		*plSharesSold = lShares;
		// Update the current record with (m_lShares-lShares)
		if (!trades.Update(1))
			return FALSE;
		}
	else
		{
		// Order has less shares than we need
		// Decrement shares
		*plSharesSold = trades.m_lShares;
		// Delete the current record
		if (!trades.Delete(1))
			return FALSE;
		}
	trades.Close();
	return TRUE;
	}

BOOL CDBStock::UpdateShares(long lAccount, LPCTSTR lpszStock,
		long lShares)
	{
	CShares shares;
	shares.Open(SQL_CURSOR_DYNAMIC, SQL_CONCUR_VALUES);
	shares.Prepare();
	shares.m_lAccountID = lAccount;
	_tcscpy(shares.m_szStockName, lpszStock);
	shares.Execute();
	// Update the account with the new information
	if (shares.MoveFirst())
		{
		shares.m_lShares += lShares;
		if (!shares.Update(1))
			return FALSE;
		}
	else
		{
		// First batch of shares purchased. Add a new record
		shares.m_lAccountID = lAccount;
		_tcscpy(shares.m_szStockName, lpszStock);
		shares.m_lShares = lShares;
		if (!shares.Add(1))
			return FALSE;
		}
	shares.Close();
	return TRUE;
	}
