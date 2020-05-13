#if !defined DEF_CRow_
	#define  DEF_CRow_

class CRow
	{
// Constructors and Destructors
public:
	CRow();
	virtual ~CRow();
// Attributes
protected:
	HENV m_hEnvironment;
	HDBC m_hConnect;
	HSTMT m_hStmt;
	UWORD m_uRowStatus;
	LPTSTR m_lpszQuery;
// Operations
public:
	// Open & Close
	virtual BOOL Open(DWORD dwCursor = SQL_CURSOR_FORWARD_ONLY,
			DWORD dwConcur = SQL_CONCUR_READ_ONLY);
	virtual BOOL Close();
	// SQL Statement Helpers
	virtual LPCTSTR GetDefaultSQL()
		{
		return NULL;
		};
	virtual BOOL Prepare(LPCTSTR lpszQuery = NULL);
	virtual BOOL Execute();
	// Column Binding Helpers
	BOOL Bind(short nItem, long* plValue, SDWORD* pcbValue);
	BOOL Bind(short nItem, double* pdblValue, SDWORD* pcbValue);
	BOOL Bind(short nItem, BOOL* pbValue, SDWORD* pcbValue);
	BOOL Bind(short nItem, LPCTSTR lpszValue, SDWORD* pcbValue,
			long lLength);
	// Parameter Binding Helpers
	BOOL BindParam(short nItem, long* plValue, SDWORD* pcbValue);
	BOOL BindParam(short nItem, double* pdblValue, SDWORD* pcbValue);
	BOOL BindParam(short nItem, BOOL* pbValue, SDWORD* pcbValue);
	BOOL BindParam(short nItem, LPCTSTR lpszValue, SDWORD* pcbValue,
			long lLength);
	// Rowset Helpers : Only forward only handled
	BOOL Update(short lRow = 1);
	BOOL Delete(short lRow = 1);
	BOOL Add(short lRow = 1);
	BOOL MoveFirst();
	BOOL MoveNext();
// Implementation
protected:
	BOOL ReportODBCError(SQLRETURN ret);
	void DBReportODBCError();
	};

#endif // !defined DEF_CRow_
