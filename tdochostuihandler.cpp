#include "tdochostuihandler.h"

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::ShowContextMenu(DWORD dwID,
	POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::GetHostInfo(DOCHOSTUIINFO *pInfo)
{
	// Called at initialization of the browser object UI. We can set various
	// features of the browser object here.
	// We can do disable the 3D border (DOCHOSTUIFLAG_NO3DOUTERBORDER) and
	// other things like hide the scroll bar (DOCHOSTUIFLAG_SCROLL_NO), display
	// picture display (DOCHOSTUIFLAG_NOPICS), disable any script running when
	// the page is loaded (DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE), open a site
	// in a new browser window when the user clicks on some link
	// (DOCHOSTUIFLAG_OPENNEWWIN), and lots of other things. See the MSDN docs
	// on the DOCHOSTUIINFO struct passed to us.
	
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::ShowUI(DWORD dwID,
	IOleInPlaceActiveObject *pActiveObject, IOleCommandTarget *pCommandTarget,
	IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::HideUI()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::UpdateUI()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::EnableModeless(BOOL fEnable)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::OnDocWindowActivate(BOOL fActivate)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::OnFrameWindowActivate(
	BOOL fActivate)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::ResizeBorder(LPCRECT prcBorder,
	IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::TranslateAccelerator(LPMSG lpMsg,
	const GUID *pguidCmdGroup, DWORD nCmdID)
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::GetOptionKeyPath(LPOLESTR *pchKey,
	DWORD dw)
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::GetDropTarget(
	IDropTarget *pDropTarget, IDropTarget **ppDropTarget)
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::GetExternal(IDispatch **ppDispatch)
{
	// Gets the host's IDispatch interface.
	// If the host exposes an automation interface, it can provide a reference
	// to MSHTML through ppDispatch.
	// If the method implementation does not supply an IDispatch, set
	// ppDispatch to NULL, even if the method fails or returns S_FALSE.

	*ppDispatch = NULL;
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::TranslateUrl(DWORD dwTranslate,
	OLECHAR *pchURLIn, OLECHAR **ppchURLOut)
{
	*ppchURLOut = 0;

	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUIHandler::FilterDataObject(IDataObject *pDO,
	IDataObject **ppDORet)
{
	*ppDORet = 0;

	return S_FALSE;
}
