#ifndef _TOLEINPLACEFRAME_H__
#define _TOLEINPLACEFRAME_H__

#include <windows.h>
#include <mshtmhst.h>

class TOleInPlaceFrame : public IOleInPlaceFrame {
public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
		void **ppv) = 0;
	virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;

	// IOleWindow
	virtual HRESULT STDMETHODCALLTYPE GetWindow(HWND *phwnd);
	virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode);

	// IOleInPlaceUIWindow
	virtual HRESULT STDMETHODCALLTYPE GetBorder(LPRECT lprectBorder);
	virtual HRESULT STDMETHODCALLTYPE RequestBorderSpace(
		LPCBORDERWIDTHS pborderwidths);
	virtual HRESULT STDMETHODCALLTYPE SetBorderSpace(
		LPCBORDERWIDTHS pborderwidths);
	virtual HRESULT STDMETHODCALLTYPE SetActiveObject(
		IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName);

	// IOleInPlaceFrame
	virtual HRESULT STDMETHODCALLTYPE InsertMenus(HMENU hmenuShared,
		LPOLEMENUGROUPWIDTHS lpMenuWidths);
	virtual HRESULT STDMETHODCALLTYPE SetMenu(HMENU hmenuShared,
		HOLEMENU holemenu, HWND hwndActiveObject);
	virtual HRESULT STDMETHODCALLTYPE RemoveMenus(HMENU hmenuShared);
	virtual HRESULT STDMETHODCALLTYPE SetStatusText(LPCOLESTR pszStatusText);
	virtual HRESULT STDMETHODCALLTYPE EnableModeless(BOOL fEnable);
	virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpmsg,
		WORD wID);
};

#endif
