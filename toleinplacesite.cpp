#include "toleinplacesite.h"
#include <crtdbg.h> // For _ASSERT()

#define NOTIMPLEMENTED _ASSERT(0); return E_NOTIMPL

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::GetWindow(HWND *phwnd)
{
	// This has to be implemented
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::ContextSensitiveHelp(BOOL fEnterMode)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::CanInPlaceActivate()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::OnInPlaceActivate()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::OnUIActivate()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::GetWindowContext(
	IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc,
	LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO info)
{
	// This has to be implemented
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::Scroll(SIZE scrollExtant)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::OnUIDeactivate(BOOL fUndoable)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::OnInPlaceDeactivate()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::DiscardUndoState()
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::DeactivateAndUndo()
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TOleInPlaceSite::OnPosRectChange(LPCRECT lprcPosRect)
{
	// This has to be implemented
	NOTIMPLEMENTED;
}
