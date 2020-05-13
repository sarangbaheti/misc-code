#include "stdafx.h"
#include "CTrades.h"
#include <tchar.h>

CTrades::CTrades()
	{
	m_lAccountID = 0;
	m_szStockName[0] = '\0';
	m_lAction = 0;
	m_lShares = 0;
	m_dblPrice = 0.0;
	m_cbAccountID = 0;
	m_cbStockName = SQL_NTS;
	m_cbAction = 0;
	m_cbShares = 0;
	m_cbPrice = 0;
	}

CTrades::~CTrades()
	{
	}

BOOL CTrades::Prepare(LPCTSTR lpszQuery /* = NULL */)
	{
	BOOL bRet = CRow::Prepare(lpszQuery);
	bRet &= BindParam(1, &m_szStockName[0], &m_cbStockName, 20);
	bRet &= BindParam(2, &m_dblPrice, &m_cbPrice);
	bRet &= BindParam(3, &m_lAction, &m_cbAction);
	return bRet;
	}

BOOL CTrades::Execute()
	{
	BOOL bRet = CRow::Execute();
	bRet &= Bind(1, &m_lAccountID, &m_cbAccountID);
	bRet &= Bind(2, &m_szStockName[0], &m_cbStockName, 20);
	bRet &= Bind(3, &m_lAction, &m_cbAction);
	bRet &= Bind(4, &m_lShares, &m_cbShares);
	bRet &= Bind(5, &m_dblPrice, &m_cbPrice);
	return bRet;
	}
