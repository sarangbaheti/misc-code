#include "stdafx.h"

#include "CStock.h"

#include "CDBStock.h"
#include <mtx.h>

CStock::CStock()
	{
	m_dblCommission = 0.0;
	}

CStock::~CStock()
	{
	}

STDMETHODIMP CStock::Buy
		(long lAccount, BSTR bstrStock, long lShares, double dblPrice)
	{
	USES_CONVERSION;
	HRESULT	hr;
	IObjectContext* pContext = NULL;
	double dblCommission = 0.0;
	// Get Context Reference
	hr = GetObjectContext(&pContext);
	if (hr != S_OK)
		return hr;
	// Validate Account
	get_Commission(&dblCommission);
	if (!m_Stock.IsValidAccount(lAccount))
		{
		pContext->SetAbort();
		return E_FAIL;
		}
	if (!m_Stock.BuyStock(lAccount, OLE2T(bstrStock), lShares,
			dblPrice, dblCommission))
		{
		pContext->SetAbort();
		return E_FAIL;
		}
	pContext->SetComplete();
	return S_OK;
	}

STDMETHODIMP CStock::Sell
		(long lAccount, BSTR bstrStock, long lShares, double dblPrice)
	{
	USES_CONVERSION;
	HRESULT hr;
	IObjectContext* pContext = NULL;
	double dblCommission = 0.0;
	hr = GetObjectContext(&pContext);
	if (hr != S_OK)
		return hr;
	// Validate Account
	if (!m_Stock.IsValidAccount(lAccount))
		{
		pContext->SetAbort();
		return E_FAIL;
		}
	get_Commission(&dblCommission);
	if (!m_Stock.SellStock(lAccount, OLE2T(bstrStock), lShares,
			dblPrice, dblCommission))
		{
		pContext->SetAbort();
		return E_FAIL;
		}
	pContext->SetComplete();
	return S_OK;
	}

STDMETHODIMP CStock::put_Commission(double dblPrice)
	{
	m_dblCommission = dblPrice;
	return S_OK;
	}

STDMETHODIMP CStock::get_Commission(double* retval)
	{
	if (retval == NULL)
		return E_POINTER;
	*retval = m_dblCommission;
	return S_OK;
	}
