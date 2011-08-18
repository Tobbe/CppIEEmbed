#include "toleclientsite.h"
#include <crtdbg.h> // For _ASSERT()

#define NOTIMPLEMENTED _ASSERT(0); return E_NOTIMPL

HRESULT STDMETHODCALLTYPE TOleClientSite::SaveObject()
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE TOleClientSite::GetMoniker(DWORD dwAssign,
	DWORD dwWhichMoniker, IMoniker **ppmk)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE TOleClientSite::GetContainer(
	IOleContainer **ppContainer)
{
	// Retrieves a pointer to the object's container.
	// Simple containers that do not support links to their embedded objects
	// probably do not need to implement this method. Instead, they can return
	// E_NOINTERFACE and set ppContainer to NULL.

	*ppContainer = NULL;
	return E_NOINTERFACE;
}

HRESULT STDMETHODCALLTYPE TOleClientSite::ShowObject()
{
	// This method is called when someone wants the web browser container to
	// display its object to the user.
	// A common reason this method is called is that someone called DoVerb with
	// a verb that requires the web browser to be visible. One such verb is
	// OLEIVERB_SHOW

	return S_OK;
}

HRESULT STDMETHODCALLTYPE TOleClientSite::OnShowWindow(BOOL fShow)
{
	NOTIMPLEMENTED;
}

HRESULT STDMETHODCALLTYPE TOleClientSite::RequestNewObjectLayout()
{
	NOTIMPLEMENTED;
}
