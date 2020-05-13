#include "stdafx.h"
#include "CRow.h"
#include <tchar.h>

CRow::CRow()
	{
	m_hEnvironment = NULL;
	m_hConnect = NULL;
	m_hStmt = NULL;
	m_uRowStatus = 0;
	m_lpszQuery = NULL;
	}

CRow::~CRow()
	{
	Close();
	if (m_lpszQuery != NULL)
		{
		delete m_lpszQuery;
		m_lpszQuery = NULL;
		}
	}

BOOL CRow::Open(DWORD dwCursor, DWORD dwConcur)
	{
	RETCODE rc;
	// Go ahead and allocate the environment
	if (m_hEnvironment == NULL)
		::SQLAllocEnv(&m_hEnvironment);
	if (m_hEnvironment == NULL)
		return FALSE;
	rc = ::SQLAllocConnect(m_hEnvironment, &m_hConnect);
	if (SQLSUCCEEDED(rc))
		{
		// Set the connection to not use the ODBC Cursor Library
		::SQLSetConnectOption(m_hConnect, SQL_ODBC_CURSORS,
					SQL_CUR_USE_DRIVER);
		// Connect to the database
		if (!SQLSUCCEEDED(SQLConnect(m_hConnect,
				(SQLCHAR*) "VCEESamples",SQL_NTS,
				(SQLCHAR*) "sa", SQL_NTS,
				(SQLCHAR*) NULL, SQL_NTS)))
			{
			Close();
			return FALSE;
			}
		// Don't reallocate if statement already exists
		if (m_hStmt == NULL)
			{
			if (!REPORTERROR(SQLAllocStmt(m_hConnect, &m_hStmt)) ||
					!REPORTERROR(SQLSetStmtOption(m_hStmt,
					SQL_CURSOR_TYPE, dwCursor)) ||
					!REPORTERROR(SQLSetStmtOption(m_hStmt,
					SQL_CONCURRENCY, dwConcur)))
				{
				// Disconnect
				Close();
				return FALSE;
				}
			}
		}
	return SQLSUCCEEDED(rc);
	}

BOOL CRow::Close()
	{
	if (m_hStmt != NULL)
		{
		REPORTERROR(SQLFreeStmt(m_hStmt, SQL_DROP));
		m_hStmt = NULL;
		}
	if (m_hConnect != NULL)
		{
		::SQLDisconnect(m_hConnect);
		::SQLFreeConnect(m_hConnect);
		m_hConnect = NULL;
		}
	if (m_hEnvironment != NULL)
		{
		::SQLFreeEnv(m_hEnvironment);
		m_hEnvironment = NULL;
		}
	return TRUE;
	}


BOOL CRow::Prepare(LPCTSTR lpszQuery /* = NULL */)
	{
	if (m_hStmt != NULL)
		::SQLCancel(m_hStmt);
	// Get Query all setup
	if (lpszQuery != NULL)
		{
		if (m_lpszQuery != NULL)
			delete m_lpszQuery;
		m_lpszQuery = new TCHAR[_tcslen(lpszQuery)+1];
		if (m_lpszQuery == NULL)
			return FALSE;
		_tcscpy(m_lpszQuery, lpszQuery);
		}
	// Prepare Query
	if (m_lpszQuery == NULL)
		return REPORTERROR(SQLPrepare(m_hStmt,
				(SQLCHAR*) GetDefaultSQL(), SQL_NTS));
	else
		return REPORTERROR(SQLPrepare(m_hStmt,
				(SQLCHAR*) m_lpszQuery, SQL_NTS));
	}

BOOL CRow::Execute()
	{
	return REPORTERROR(SQLExecute(m_hStmt));
	}

BOOL CRow::Bind(short nItem, long* plValue, SDWORD* pcbValue)
	{
	return REPORTERROR(SQLBindCol(m_hStmt, nItem, SQL_C_SLONG,
			plValue, 0, pcbValue));
	}

BOOL CRow::Bind(short nItem, double* pdblValue, SDWORD* pcbValue)
	{
	return REPORTERROR(SQLBindCol(m_hStmt, nItem, SQL_C_DOUBLE,
			pdblValue, 0, pcbValue));
	}

BOOL CRow::Bind(short nItem, BOOL* pbValue, SDWORD* pcbValue)
	{
	return REPORTERROR(SQLBindCol(m_hStmt, nItem, SQL_C_BIT,
			pbValue, 0, pcbValue));
	}

BOOL CRow::Bind(short nItem, LPCTSTR lpszValue, SDWORD* pcbValue,
		long lLength)
	{
	return REPORTERROR(SQLBindCol(m_hStmt, nItem, SQL_C_CHAR,
			(void*) lpszValue, lLength, pcbValue));
	}

BOOL CRow::BindParam(short nItem, long* plValue, SDWORD* pcbValue)
	{
	return REPORTERROR(SQLBindParameter(m_hStmt, nItem,
			SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0,
			plValue, 0, pcbValue));
	}

BOOL CRow::BindParam
		(short nItem, double* pdblValue, SDWORD* pcbValue)
	{
	return REPORTERROR(SQLBindParameter(m_hStmt, nItem,
			SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			pdblValue, 0, pcbValue));
	}

BOOL CRow::BindParam(short nItem, BOOL* pbValue, SDWORD* pcbValue)
	{
	return REPORTERROR(SQLBindParameter(m_hStmt, nItem,
			SQL_PARAM_INPUT, SQL_C_BIT, SQL_BIT, 0, 0,
			pbValue, 0, pcbValue));
	}

BOOL CRow::BindParam(short nItem, LPCTSTR lpszValue, SDWORD* pcbValue, long lLength)
	{
	*pcbValue = SQL_NTS;
	return REPORTERROR(SQLBindParameter(m_hStmt, nItem,
			SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0,
			(void*) lpszValue, lLength, pcbValue));
	}

BOOL CRow::Update(short uRow /* = 1 */)
	{
	return REPORTERROR(SQLSetPos(m_hStmt, uRow, SQL_UPDATE,
			SQL_LOCK_NO_CHANGE));
	}

BOOL CRow::Delete(short uRow /* = 1 */)
	{
	return REPORTERROR(SQLSetPos(m_hStmt, uRow, SQL_DELETE,
			SQL_LOCK_NO_CHANGE));
	}

BOOL CRow::Add(short uRow /* = 1 */)
	{
	return REPORTERROR(SQLSetPos(m_hStmt, uRow, SQL_ADD,
			SQL_LOCK_NO_CHANGE));
	}

BOOL CRow::MoveFirst()
	{
	DWORD dwFetched;
	RETCODE rc = ::SQLExtendedFetch(m_hStmt, SQL_FETCH_FIRST,
			1, &dwFetched, &m_uRowStatus);
	return REPORTERROR(rc);
	}

BOOL CRow::MoveNext()
	{
	DWORD dwFetched;
	return REPORTERROR(SQLExtendedFetch(m_hStmt, SQL_FETCH_RELATIVE,
			1, &dwFetched, &m_uRowStatus));
	}

BOOL CRow::ReportODBCError(SQLRETURN ret)
	{
	if ((ret != SQL_SUCCESS) && (ret != SQL_NO_DATA_FOUND))
		DBReportODBCError();
	return SQLSUCCEEDED(ret);
	}

void CRow::DBReportODBCError()
	{
	TCHAR szErrorBuf[256];
	UCHAR szState[SQL_SQLSTATE_SIZE];
	SDWORD dwNativeErr;
	UCHAR szError[SQL_MAX_MESSAGE_LENGTH];
	SWORD sw;
	LPTSTR pszErrorBuf = szErrorBuf;
	int nLen;
	for (;;)
		{
		int nRetVal = ::SQLError(m_hEnvironment, m_hConnect, m_hStmt,
			szState, &dwNativeErr, szError, SQL_MAX_MESSAGE_LENGTH-1,
			&sw);
		if (nRetVal != SQL_SUCCESS &&
				nRetVal != SQL_SUCCESS_WITH_INFO)
			break;
		nLen = lstrlen((LPCTSTR) szState);
		memcpy(pszErrorBuf, szState, nLen);
		pszErrorBuf += nLen;
		nLen = lstrlen((LPCTSTR) szError);
		memcpy(pszErrorBuf, szError, nLen + 1);
		pszErrorBuf += nLen;
		pszErrorBuf[0] = '\r';
		pszErrorBuf[1] = '\n';
		pszErrorBuf[2] = '\0';
		pszErrorBuf += 2;
		}
	OutputDebugString(szErrorBuf);
	}
