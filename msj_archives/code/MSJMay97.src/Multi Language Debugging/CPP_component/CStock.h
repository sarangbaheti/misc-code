#if !defined DEF_CStock_
	#define  DEF_CStock_

#include "CDBStock.h"
#include "CPP_component.h"
#include "resource.h"

class CStock : 
	public CComDualImpl<IStock, &IID_IStock, &LIBID_CPP_COMPONENTLib>,
	public CComObjectRoot,
	public CComCoClass<CStock,&CLSID_CStock>
	{
public:
	CStock();
	virtual ~CStock();
	BEGIN_COM_MAP(CStock)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IStock)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CStock) 
	DECLARE_REGISTRY(CStock, _T("Stock.Stock.1"), _T("Stock.Stock"),
			IDS_PROJNAME, THREADFLAGS_APARTMENT)
// IStock
public:
	STDMETHOD(Buy)(long lAccount, BSTR bstrStock, long lShares, double dblPrice);
	STDMETHOD(Sell)(long lAccount, BSTR bstrStock, long lShares, double dblPrice);
	STDMETHOD(put_Commission)(double dblCommission);
	STDMETHOD(get_Commission)(double* retval);
// Attributes
protected:
	CDBStock m_Stock;
	double	m_dblCommission;
	};

#endif // !defined DEF_CStock_
