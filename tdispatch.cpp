#include "tdispatch.h"

HRESULT STDMETHODCALLTYPE TDispatch::GetTypeInfoCount(UINT *pctinfo)
{
	*pctinfo = 0;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDispatch::GetTypeInfo(UINT iTInfo, LCID lcid,
	ITypeInfo **ppTInfo)
{
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE TDispatch::GetIDsOfNames(REFIID riid,
	LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE TDispatch::Invoke(DISPID dispIdMember, REFIID riid,
	LCID lcid, WORD wFlags, DISPPARAMS *Params, VARIANT *pVarResult,
	EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	return DISP_E_MEMBERNOTFOUND;
}
