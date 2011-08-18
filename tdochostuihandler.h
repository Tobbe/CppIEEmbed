#ifndef _TDOCHOSTUIHANDLER_H__
#define _TDOCHOSTUIHANDLER_H__

#include <windows.h>
#include <mshtmhst.h>
#include <mshtmdid.h>
#include <exdispid.h>

class TDocHostUIHandler : public IDocHostUIHandler {
public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
		void **ppv) = 0;
	virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;

	// IDocHostUIHandler
	virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID, POINT *ppt,
		IUnknown *pcmdtReserved, IDispatch *pdispReserved);
	virtual HRESULT STDMETHODCALLTYPE GetHostInfo(DOCHOSTUIINFO *pInfo);
	virtual HRESULT STDMETHODCALLTYPE ShowUI(DWORD dwID,
		IOleInPlaceActiveObject *pActiveObject,
		IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame,
		IOleInPlaceUIWindow *pDoc);
	virtual HRESULT STDMETHODCALLTYPE HideUI();
	virtual HRESULT STDMETHODCALLTYPE UpdateUI();
	virtual HRESULT STDMETHODCALLTYPE EnableModeless(BOOL fEnable);
	virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate(BOOL fActivate);
	virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(BOOL fActivate);
	virtual HRESULT STDMETHODCALLTYPE ResizeBorder(LPCRECT prcBorder,
		IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow);
	virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpMsg,
		const GUID *pguidCmdGroup, DWORD nCmdID);
	virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath(LPOLESTR *pchKey,
		DWORD dw);
	virtual HRESULT STDMETHODCALLTYPE GetDropTarget(IDropTarget *pDropTarget,
		IDropTarget **ppDropTarget);
	virtual HRESULT STDMETHODCALLTYPE GetExternal(IDispatch **ppDispatch);
	virtual HRESULT STDMETHODCALLTYPE TranslateUrl(DWORD dwTranslate,
		OLECHAR *pchURLIn, OLECHAR **ppchURLOut);
	virtual HRESULT STDMETHODCALLTYPE FilterDataObject(IDataObject *pDO,
		IDataObject **ppDORet);
};

#endif
