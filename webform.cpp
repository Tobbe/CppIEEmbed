#include <windows.h>
#include <mshtmhst.h>
#include <mshtmdid.h>
#include <exdispid.h>
#include <DispEx.h>
#include <tchar.h>
#include <string>
#include "webform.h"
#include "TOleClientSite.h"
#include "toleinplaceframe.h"

WebForm::WebForm(WebformDispatchHandler *wdh) :
	ref(1), ibrowser(NULL), cookie(0), isnaving(0), url(NULL), kurl(NULL),
	hasScrollbars(false), hhost(NULL), hWnd(NULL), dispatchHandler(wdh)
{
}

void WebForm::setupOle()
{
	RECT rc;
	GetClientRect(hhost, &rc);

	HRESULT hr;
	IOleObject* iole = 0;
	hr = CoCreateInstance(CLSID_WebBrowser, NULL, CLSCTX_INPROC_SERVER, IID_IOleObject, (void**)&iole);
	if (iole == 0) {
		return;
	}

	hr = iole->SetClientSite(this);
	if (hr != S_OK) {
		iole->Release();
		return;
	}

	hr = iole->SetHostNames(L"MyHost", L"MyDoc");
	if (hr != S_OK) {
		iole->Release();
		return;
	}

	hr = OleSetContainedObject(iole, TRUE);
	if (hr != S_OK) {
		iole->Release();
		return;
	}

	hr = iole->DoVerb(OLEIVERB_SHOW, 0, this, 0, hhost, &rc);
	if (hr != S_OK) {
		iole->Release();
		return;
	}

	bool connected = false;
	IConnectionPointContainer *cpc = 0;
	iole->QueryInterface(IID_IConnectionPointContainer, (void**)&cpc);
	if (cpc != 0) {
		IConnectionPoint *cp = 0;
		cpc->FindConnectionPoint(DIID_DWebBrowserEvents2, &cp);

		if (cp != 0) {
			cp->Advise(this, &cookie);
			cp->Release();
			connected = true;
		}

		cpc->Release();
	}

	if (!connected) {
		iole->Release();
		return;
	}

	iole->QueryInterface(IID_IWebBrowser2, (void**)&ibrowser);
	iole->Release();
}

void WebForm::Close()
{
	if (ibrowser != 0) {
		IConnectionPointContainer *cpc = 0;
		ibrowser->QueryInterface(IID_IConnectionPointContainer, (void**)&cpc);

		if (cpc != 0) {
			IConnectionPoint *cp = 0;
			cpc->FindConnectionPoint(DIID_DWebBrowserEvents2, &cp);

			if (cp != 0) {
				cp->Unadvise(cookie);
				cp->Release();
			}

			cpc->Release();
		}

		IOleObject *iole = 0;
		ibrowser->QueryInterface(IID_IOleObject, (void**)&iole);
		UINT refCount = ibrowser->Release();
		ibrowser = 0;

		if (iole != 0) {
			iole->Close(OLECLOSE_NOSAVE);
			iole->Release();
		}
	}
}

WebForm::~WebForm()
{
	if (url != 0) {
		delete[] url;
	}

	if (kurl != 0) {
		delete[] kurl;
	}
}


void TCharToWide(const char *src, wchar_t *dst, int dst_size_in_wchars)
{
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, src, -1, dst, dst_size_in_wchars);
}

void TCharToWide(const wchar_t *src, wchar_t *dst, int dst_size_in_wchars)
{
	#pragma warning(suppress:4996)
	wcscpy(dst, src);
}

char *BSTRToLPSTR(BSTR bStr, LPSTR lpstr)
{
	int lenW = SysStringLen(bStr);
	int lenA = WideCharToMultiByte(CP_ACP, 0, bStr, lenW, 0, 0, NULL, NULL);

	if (lenA > 0) {
		lpstr = new char[lenA + 1]; // allocate a final null terminator as well
		WideCharToMultiByte(CP_ACP, 0, bStr, lenW, lpstr, lenA, NULL, NULL);
		lpstr[lenA] = '\0'; // Set the null terminator yourself
	} else {
		lpstr = NULL;
	}

	return lpstr;
}

void WebForm::Go(const TCHAR *url)
{
	if (url == NULL || ibrowser == NULL) {
		return;
	}

	wchar_t ws[MAX_PATH];
	TCharToWide(url, ws, MAX_PATH);
	isnaving = 7;
	VARIANT v;
	v.vt = VT_I4;
	v.lVal = 0; // v.lVal = navNoHistory;
	ibrowser->Navigate(ws, &v, NULL, NULL, NULL);

	// (Special case: maybe it's already loaded by the time we get here!)
	if ((isnaving & 2) == 0) {
		WPARAM w = (GetWindowLong(hhost, GWL_ID) & 0xFFFF) | ((WEBFN_LOADED & 0xFFFF) << 16);
		PostMessage(GetParent(hhost), WM_COMMAND, w, (LPARAM)hhost);
	}

	isnaving &= ~4;
}

void WebForm::Forward()
{
	ibrowser->GoForward();
}

void WebForm::Back()
{
	ibrowser->GoBack();
}

void WebForm::Refresh(bool clearCache)
{
	if (clearCache) {
		VARIANT v;
		v.vt = VT_I4;
		v.lVal = REFRESH_COMPLETELY;
		ibrowser->Refresh2(&v);
	} else {
		ibrowser->Refresh();
	}
}

IHTMLDocument2 *WebForm::GetDoc()
{
	IDispatch *dispatch = 0;
	ibrowser->get_Document(&dispatch);
	
	if (dispatch == NULL) {
		return NULL;
	}

	IHTMLDocument2 *doc;
	dispatch->QueryInterface(IID_IHTMLDocument2, (void**)&doc);
	dispatch->Release();
	
	return doc;
}

void WebForm::RunJSFunction(std::string cmd)
{
	IHTMLDocument2 *doc = GetDoc();
	IHTMLWindow2 *win = NULL;
	doc->get_parentWindow(&win);

	if (win != NULL) {
		int lenW = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cmd.c_str(), -1, NULL, 0);
		BSTR bstrCmd = SysAllocStringLen(0, lenW);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cmd.c_str(), -1, bstrCmd, lenW);

		VARIANT v;
		VariantInit(&v);
		win->execScript(bstrCmd, NULL, &v);

		VariantClear(&v);
		SysFreeString(bstrCmd);
		win->Release();
	}

	doc->Release();
}

void WebForm::AddCustomObject(IDispatch *custObj, std::string name)
{
	IHTMLDocument2 *doc = GetDoc();
	IHTMLWindow2 *win = NULL;
	doc->get_parentWindow(&win);
	doc->Release();

	if (win == NULL) {
		return;
	}

	IDispatchEx *winEx;
	win->QueryInterface(&winEx);
	win->Release();

	if (winEx == NULL) {
		return;
	}

	int lenW = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, name.c_str(), -1, NULL, 0);
	BSTR objName = SysAllocStringLen(0, lenW);
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, name.c_str(), -1, objName, lenW);

	DISPID dispid; 
	HRESULT hr = winEx->GetDispID(objName, fdexNameEnsure, &dispid);

	SysFreeString(objName);

	if (FAILED(hr)) {
		return;
	}

	DISPID namedArgs[] = {DISPID_PROPERTYPUT};
	DISPPARAMS params;
	params.rgvarg = new VARIANT[1];
	params.rgvarg[0].pdispVal = custObj;
	params.rgvarg[0].vt = VT_DISPATCH;
	params.rgdispidNamedArgs = namedArgs;
	params.cArgs = 1;
	params.cNamedArgs = 1;

	hr = winEx->InvokeEx(dispid, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &params, NULL, NULL, NULL); 
	winEx->Release();

	if (FAILED(hr)) {
		return;
	}
}

void WebForm::DocumentComplete(const wchar_t *)
{
	isnaving &= ~2;

	if (isnaving & 4) {
		return; // "4" means that we're in the middle of Go(), so the notification will be handled there
	}

	WPARAM w = (GetWindowLong(hhost, GWL_ID) & 0xFFFF) | ((WEBFN_LOADED & 0xFFFF) << 16);
	PostMessage(GetParent(hhost), WM_COMMAND, w, (LPARAM)hhost);
}

HRESULT STDMETHODCALLTYPE WebForm::QueryInterface(REFIID riid, void **ppv)
{
	*ppv = NULL;

	if (riid == IID_IUnknown || riid == IID_IOleClientSite) {
		*ppv = static_cast<IOleClientSite*>(this);
	} else if (riid == IID_IOleWindow || riid == IID_IOleInPlaceSite) {
		*ppv = static_cast<IOleInPlaceSite*>(this);
	} else if (riid == IID_IOleInPlaceUIWindow) {
		*ppv = static_cast<IOleInPlaceUIWindow*>(this);
	} else if (riid == IID_IOleInPlaceFrame) {
		*ppv = static_cast<IOleInPlaceFrame*>(this);
	} else if (riid == IID_IDispatch) {
		*ppv = static_cast<IDispatch*>(this);
	} else if (riid == IID_IDocHostUIHandler) {
		*ppv = static_cast<IDocHostUIHandler*>(this);
	} else if (riid == IID_IDocHostShowUI) {
		*ppv = static_cast<IDocHostShowUI*>(this);
	}

	if (*ppv != NULL) {
		AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE WebForm::AddRef()
{
	return InterlockedIncrement(&ref);
}

ULONG STDMETHODCALLTYPE WebForm::Release()
{
	int tmp = InterlockedDecrement(&ref);
	
	if (tmp == 0) {
		OutputDebugString("WebForm::Release(): delete this");
		delete this;
	}
	
	return tmp;
}

LRESULT CALLBACK WebForm::WebformWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE) {
		WebForm *webf = (WebForm*)((LPCREATESTRUCT(lParam))->lpCreateParams);
		webf->hWnd = hwnd;

		#pragma warning(suppress:4244)
		SetWindowLongPtr(hwnd, 0, (LONG_PTR)webf);

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	#pragma warning(suppress:4312)
	WebForm *webf = (WebForm*)GetWindowLongPtr(hwnd, 0);

	if (webf == NULL) {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return webf->InstanceWndProc(msg, wParam, lParam);
}

LRESULT WebForm::InstanceWndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_CREATE: {
			CREATESTRUCT *cs = (CREATESTRUCT*)lParam;

			if (cs->style & (WS_HSCROLL | WS_VSCROLL)) {
				SetWindowLongPtr(hWnd, GWL_STYLE, cs->style & ~(WS_HSCROLL | WS_VSCROLL));
			}

			break;
		}
		case WM_DESTROY:
			Close();
			Release();
			SetWindowLongPtr(hWnd, 0, 0);
			break;
		case WM_SETTEXT:
			Go((TCHAR*)lParam);
			break;
		case WM_SIZE:
			if (ibrowser != NULL) {
				ibrowser->put_Width(LOWORD(lParam));
				ibrowser->put_Height(HIWORD(lParam));
			}
			break;
		case WM_PAINT: {
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

			FillRect(ps.hdc, &ps.rcPaint, brush);

			DeleteObject(brush);
			EndPaint(hWnd, &ps);

			return 0;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void WebForm::create(HWND hWndParent, HINSTANCE hInstance, UINT id, bool showScrollbars)
{
	hasScrollbars = showScrollbars;
	this->id = id;

	WNDCLASSEX wcex = {0};
	if (!GetClassInfoEx(hInstance, WEBFORM_CLASS, &wcex)) {
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)WebForm::WebformWndProc;
		wcex.hInstance = hInstance;
		wcex.lpszClassName = WEBFORM_CLASS;
		wcex.cbWndExtra = sizeof(WebForm*);

		if(!RegisterClassEx(&wcex)) {
			MessageBox(NULL, "Could not auto register the webform", "WebForm::create", MB_OK);

			return;
		}
	}

	hWnd = CreateWindow(
		WEBFORM_CLASS,
		_T("http://tlundberg.com"),
		WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
		0, 0, 100, 100, hWndParent, (HMENU)(LONG_PTR)id, hInstance, (LPVOID)this);

	hhost = hWnd;

	setupOle();
}

HRESULT STDMETHODCALLTYPE WebForm::Invoke(DISPID dispIdMember, REFIID riid,
	LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
	EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	switch (dispIdMember) { // DWebBrowserEvents2
		case DISPID_BEFORENAVIGATE2: {
			BSTR bstrUrl = pDispParams->rgvarg[5].pvarVal->bstrVal;
			char *lpstrUrl = NULL;

			lpstrUrl = BSTRToLPSTR(bstrUrl, lpstrUrl);
			if (lpstrUrl == NULL) {
				break;
			}

			std::string url = lpstrUrl;
			delete [] lpstrUrl;

			bool cancel = false;

			dispatchHandler->BeforeNavigate(url, &cancel);

			// Set Cancel parameter to TRUE to cancel the current event
			*(((*pDispParams).rgvarg)[0].pboolVal) = cancel ? TRUE : FALSE;

			break;
		}
		case DISPID_DOCUMENTCOMPLETE:
			DocumentComplete(pDispParams->rgvarg[0].pvarVal->bstrVal);
			break;
		case DISPID_NAVIGATECOMPLETE2: {
			BSTR bstrUrl = pDispParams->rgvarg[0].pvarVal->bstrVal;
			char *lpstrUrl = NULL;

			lpstrUrl = BSTRToLPSTR(bstrUrl, lpstrUrl);
			if (lpstrUrl == NULL) {
				break;
			}

			std::string url = lpstrUrl;
			delete [] lpstrUrl;

			dispatchHandler->NavigateComplete(url, this);

			break;
		}
		case DISPID_AMBIENT_DLCONTROL:
			pVarResult->vt = VT_I4;
			pVarResult->lVal = DLCTL_DLIMAGES | DLCTL_VIDEOS | DLCTL_BGSOUNDS | DLCTL_SILENT;
			break;
		default:
			return DISP_E_MEMBERNOTFOUND;
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE WebForm::GetHostInfo(DOCHOSTUIINFO *pInfo)
{
	pInfo->dwFlags = (hasScrollbars ? 0 : DOCHOSTUIFLAG_SCROLL_NO) | DOCHOSTUIFLAG_NO3DOUTERBORDER;
	
	return S_OK;
}

HRESULT STDMETHODCALLTYPE WebForm::GetExternal(IDispatch **ppDispatch)
{
	*ppDispatch = static_cast<IDispatch*>(this);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE WebForm::GetWindow(HWND *phwnd)
{
	*phwnd = hhost;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE WebForm::GetWindowContext(IOleInPlaceFrame **ppFrame,
	IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect,
	LPOLEINPLACEFRAMEINFO info)
{
	*ppFrame = static_cast<IOleInPlaceFrame*>(this);
	AddRef();
	*ppDoc = NULL;
	info->fMDIApp = FALSE;
	info->hwndFrame = hhost;
	info->haccel = 0;
	info->cAccelEntries = 0;
	GetClientRect(hhost, lprcPosRect);
	GetClientRect(hhost, lprcClipRect);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE WebForm::OnPosRectChange(LPCRECT lprcPosRect)
{
	IOleInPlaceObject *iole = NULL;
	ibrowser->QueryInterface(IID_IOleInPlaceObject, (void**)&iole);

	if (iole != NULL) {
		iole->SetObjectRects(lprcPosRect, lprcPosRect);
		iole->Release();
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE WebForm::ShowMessage(HWND hwnd, LPOLESTR lpstrText,
	LPOLESTR lpstrCaption, DWORD dwType, LPOLESTR lpstrHelpFile,
	DWORD dwHelpContext, LRESULT *plResult)
{
	return S_FALSE;
}
