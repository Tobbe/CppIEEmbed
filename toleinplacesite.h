#ifndef _TOLEINPLACESITE_H__
#define _TOLEINPLACESITE_H__

#include <windows.h>
#include <mshtmhst.h>
//#include <mshtmdid.h>

class TOleInPlaceSite : public IOleInPlaceSite {
public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
		void **ppv) = 0;
	virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;

	// IOleWindow
	virtual HRESULT STDMETHODCALLTYPE GetWindow(HWND *phwnd);
	virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode);

	// IOleInPlaceSite
	virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate();
	virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate();
	virtual HRESULT STDMETHODCALLTYPE OnUIActivate();
	virtual HRESULT STDMETHODCALLTYPE GetWindowContext(
		IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc,
		LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO info);
	virtual HRESULT STDMETHODCALLTYPE Scroll(SIZE scrollExtant);
	virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL fUndoable);
	virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate();
	virtual HRESULT STDMETHODCALLTYPE DiscardUndoState();
	virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo();
	virtual HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect);
};

#endif