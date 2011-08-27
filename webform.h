#ifndef _WEBFORM_H__
#define _WEBFORM_H__

#include <mshtml.h>
#include <exdisp.h>
#include <windows.h>
#include <mshtmhst.h>
#include "toleclientsite.h"
#include "toleinplacesite.h"
#include "toleinplaceframe.h"
#include "tdochostuihandler.h"
#include "tdochostshowui.h"
#include "tdispatch.h"
#include "webformdispatchhandler.h"

#define WEBFORM_CLASS (_T("WebformClass"))
// Create a Webfrom control with CreateWindow(WEBFORM_CLASS,_T("initial-url"),...)
// If you specify WS_VSCROLL style then the webform will be created with scrollbars.

#define WEBFN_LOADED 3
// This notification is sent via WM_COMMAND when you have called WebformGo(hWebF, url).
// It indicates that the page has finished loading.

#pragma warning(push)
#pragma warning(disable:4584)
class WebForm : public IUnknown, TOleClientSite, TDispatch, TDocHostShowUI, TDocHostUIHandler, TOleInPlaceSite, TOleInPlaceFrame {
#pragma warning(pop)
private:
	long ref;
	unsigned int isnaving;    // bitmask: 4=haven't yet finished Navigate call, 2=haven't yet received DocumentComplete, 1=haven't yet received BeforeNavigate

	UINT id;
	IWebBrowser2 *ibrowser;   // Our pointer to the browser itself. Released in Close().
	DWORD cookie;             // By this cookie shall the watcher be known

	bool hasScrollbars;       // This is read from WS_VSCROLL|WS_HSCROLL at WM_CREATE
	TCHAR *url;               // This was the url that the user just clicked on
	TCHAR *kurl;              // Key\0Value\0Key2\0Value2\0\0 arguments for the url just clicked on

	WebformDispatchHandler *dispatchHandler;

	IHTMLDocument2 *GetDoc();
public:
	HWND hWnd;

	WebForm(WebformDispatchHandler *wdh);
	~WebForm();
	void create(HWND hWndParent, HINSTANCE hInstance, UINT id, bool showScrollbars);
	void CloseThread();
	void Close();
	void Go(const TCHAR *fn);
	void Forward();
	void Back();
	void Refresh(bool clearCache);
	void RunJSFunction(std::string cmd);
	void AddCustomObject(IDispatch *custObj, std::string name);
	static LRESULT CALLBACK WebformWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT InstanceWndProc(UINT msg, WPARAM wParam, LPARAM lParam);
	void setupOle();

	// IUnknown
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

	// IDispatch
	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid,
		LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
		EXCEPINFO *pExcepInfo, UINT *puArgErr);

	// IDocHostUIHandler
	HRESULT STDMETHODCALLTYPE GetHostInfo(DOCHOSTUIINFO *pInfo);
	HRESULT STDMETHODCALLTYPE GetExternal(IDispatch **ppDispatch);

	// IOleWindow (TOleInPlaceSite)
	HRESULT STDMETHODCALLTYPE GetWindow(HWND *phwnd);

	//IOleInPlaceSite
	HRESULT STDMETHODCALLTYPE GetWindowContext(IOleInPlaceFrame **ppFrame,
		IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect,
		LPOLEINPLACEFRAMEINFO info);
	HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect);

	//IDocHostShowUI
	HRESULT STDMETHODCALLTYPE ShowMessage(HWND hwnd, LPOLESTR lpstrText,
		LPOLESTR lpstrCaption, DWORD dwType, LPOLESTR lpstrHelpFile,
		DWORD dwHelpContext, LRESULT *plResult);

	void BeforeNavigate2(const wchar_t *url, short *cancel);
	void DocumentComplete(const wchar_t *url); 
};

#endif
