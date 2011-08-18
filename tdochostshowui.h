#ifndef _TDOCHOSTSHOWUI_H__
#define _TDOCHOSTSHOWUI_H__

#include <windows.h>
#include <mshtmhst.h>

class TDocHostShowUI : public IDocHostShowUI {
public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
		void **ppv) = 0;
	virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;

	// IDocHostShowUI
	virtual HRESULT STDMETHODCALLTYPE ShowMessage(HWND hwnd,
		LPOLESTR lpstrText, LPOLESTR lpstrCaption, DWORD dwType,
		LPOLESTR lpstrHelpFile, DWORD dwHelpContext, LRESULT *plResult);
	virtual HRESULT STDMETHODCALLTYPE ShowHelp(HWND hwnd, LPOLESTR pszHelpFile,
		UINT uCommand, DWORD dwData, POINT ptMouse,
		IDispatch *pDispatchObjectHit);
};

#endif