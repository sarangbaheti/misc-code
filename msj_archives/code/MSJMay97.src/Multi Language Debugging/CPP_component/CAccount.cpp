#include "stdafx.h"
#include "CAccount.h"
#include <tchar.h>

CAccount::CAccount()
	{
	m_lAccountID = 0;
	m_dblBalance = 0.0;
	m_cbAccountID = 0;
	m_cbBalance = 0;
	}

CAccount::~CAccount()
	{
	}

BOOL CAccount::Prepare(LPCTSTR lpszQuery /* = NULL */)
	{
	BOOL bRet = CRow::Prepare(lpszQuery);
	bRet &= BindParam(1, &m_lAccountID, &m_cbAccountID);
	bRet &= BindParam(2, &m_dblBalance, &m_cbBalance);
	return bRet;
	}

BOOL CAccount::Execute()
	{
	BOOL bRet = CRow::Execute();
	bRet &= Bind(1, &m_lAccountID, &m_cbAccountID);
	bRet &= Bind(2, &m_dblBalance, &m_cbBalance);
	return bRet;
	}

BOOL CAccount::IsValidAccount(long lAccountID)
	{
	HSTMT hStmtValid = NULL;
	RETCODE rc;
	// This function uses a separate statement that shows off a sp
	// call.  You can use the Visual C++ Enterprise SQL Debugger to
	// debug the sp.
	//
	// Prepare the statement
	::SQLAllocStmt(m_hConnect, &hStmtValid);
	if (hStmtValid == NULL)
		return FALSE;
	::SQLSetStmtOption(m_hStmt, SQL_CURSOR_TYPE,
			SQL_CURSOR_FORWARD_ONLY);
	::SQLSetStmtOption(m_hStmt, SQL_CONCURRENCY,
			SQL_CONCUR_READ_ONLY);
	::SQLPrepare(hStmtValid, (SQLCHAR*) "{call sp_validaccount(?)}",
			SQL_NTS);
	::SQLBindParameter(hStmtValid, 1, SQL_PARAM_INPUT, SQL_C_LONG,
			SQL_INTEGER, 0, 0, &m_lAccountID, 0, &m_cbAccountID);
	// Execute the statement if it fails, we know the account doesn't
	// exist.
	m_lAccountID = lAccountID;
	rc = ::SQLExecute(hStmtValid);
	::SQLFreeStmt(hStmtValid, SQL_DROP);
	return SQLSUCCEEDED(rc);
	}
