#include "stdafx.h"
#include "CShares.h"
#include <tchar.h>

CShares::CShares()
	{
	m_lAccountID = 0;
	m_szStockName[0] = '\0';
	m_lShares = 0;
	m_cbAccountID = 0;
	m_cbStockName = SQL_NTS;
	m_cbShares = 0;
	}

CShares::~CShares()
	{
	}

BOOL CShares::Prepare(LPCTSTR lpszQuery /* = NULL */)
	{
	BOOL bRet = CRow::Prepare(lpszQuery);
	bRet &= BindParam(1, &m_lAccountID, &m_cbAccountID);
	bRet &= BindParam(2, &m_szStockName[0], &m_cbStockName, 20);
	return bRet;
	}

BOOL CShares::Execute()
	{
	BOOL bRet = CRow::Execute();
	bRet &= Bind(1, &m_lAccountID, &m_cbAccountID);
	bRet &= Bind(2, &m_szStockName[0], &m_cbStockName, 20);
	bRet &= Bind(3, &m_lShares, &m_cbShares);
	return bRet;
	}
