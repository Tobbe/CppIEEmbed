#include "tdochostshowui.h"

HRESULT STDMETHODCALLTYPE TDocHostShowUI::ShowMessage(HWND hwnd,
	LPOLESTR lpstrText, LPOLESTR lpstrCaption, DWORD dwType,
	LPOLESTR lpstrHelpFile, DWORD dwHelpContext, LRESULT *plResult)
{
	// Called by MSHTML to display a message box.
	// It is used for Microsoft JScript alerts among other things
	// S_OK: Host displayed its UI. MSHTML does not display its message box.
	// S_FALSE: Host did not display its UI. MSHTML displays its message box.

	*plResult = IDCANCEL;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostShowUI::ShowHelp(HWND hwnd,
	LPOLESTR pszHelpFile, UINT uCommand, DWORD dwData, POINT ptMouse,
	IDispatch *pDispatchObjectHit)
{
	return S_OK;
}
