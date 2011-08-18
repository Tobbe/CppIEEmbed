#ifndef _TOLECLIENTSITE_H__
#define _TOLECLIENTSITE_H__

#include <windows.h>
#include <mshtmhst.h>

class TOleClientSite : public IOleClientSite {
public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
		void **ppv) = 0;
	virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;

	// IOleClientSite
	virtual HRESULT STDMETHODCALLTYPE SaveObject();
	virtual HRESULT STDMETHODCALLTYPE GetMoniker(DWORD dwAssign,
		DWORD dwWhichMoniker, IMoniker **ppmk);
	virtual HRESULT STDMETHODCALLTYPE GetContainer(IOleContainer **ppContainer);
	virtual HRESULT STDMETHODCALLTYPE ShowObject();
	virtual HRESULT STDMETHODCALLTYPE OnShowWindow(BOOL fShow);
	virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout();
};

#endif
