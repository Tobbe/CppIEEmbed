#include "toleinplaceframe.h"

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::GetWindow(HWND *phwnd)
{
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::ContextSensitiveHelp(
	BOOL fEnterMode)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::GetBorder(LPRECT lprectBorder)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::RequestBorderSpace(
	LPCBORDERWIDTHS pborderwidths)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::SetBorderSpace(
	LPCBORDERWIDTHS pborderwidths)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::SetActiveObject(
	IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::InsertMenus(HMENU hmenuShared,
	LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::SetMenu(HMENU hmenuShared,
	HOLEMENU holemenu, HWND hwndActiveObject)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::RemoveMenus(HMENU hmenuShared)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::SetStatusText(
	LPCOLESTR pszStatusText)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::EnableModeless(BOOL fEnable)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceFrame::TranslateAccelerator(LPMSG lpmsg,
	WORD wID)
{
	return E_NOTIMPL;
}
