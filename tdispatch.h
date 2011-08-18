#ifndef _TDISPATCH_H__
#define _TDISPATCH_H__

#include <windows.h>
#include <mshtmhst.h>

class TDispatch : public IDispatch {
public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
		void **ppv) = 0;
	virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;

	// IDispatch
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo);
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid,
		ITypeInfo **ppTInfo);
	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid,
		LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid,
		LCID lcid, WORD wFlags, DISPPARAMS *Params, VARIANT *pVarResult,
		EXCEPINFO *pExcepInfo, UINT *puArgErr);
};

#endif;
