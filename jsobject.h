#ifndef _JS_LITESTEP_H__
#define _JS_LITESTEP_H__

#include <windows.h>
#include <mshtmhst.h>
#include <string>
#include <map>

class JSObject : public IDispatch {
private:
	static const DISPID DISPID_USER_EXECUTE = DISPID_VALUE + 1;
	static const DISPID DISPID_USER_WRITEFILE = DISPID_VALUE + 2;
	static const DISPID DISPID_USER_READFILE = DISPID_VALUE + 3;
	static const DISPID DISPID_USER_GETVAL = DISPID_VALUE + 4;
	static const DISPID DISPID_USER_SETVAL = DISPID_VALUE + 5;

	std::map<std::wstring, DISPID> idMap;
	long ref;

	std::map<std::string, std::string> values;

	char *BSTRToLPSTR(BSTR bStr, LPSTR lpstr);

public:
	JSObject();

	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();

	// IDispatch
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo);
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid,
		ITypeInfo **ppTInfo);
	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid,
		LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid,
		LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
		EXCEPINFO *pExcepInfo, UINT *puArgErr);
};

#endif