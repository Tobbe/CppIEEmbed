#include "webwindow.h"

WebWindow::WebWindow(WebformDispatchHandler *wdh) : webformDispatchHandler(wdh)
{
}

void WebWindow::Create(HINSTANCE hInstance, UINT x, UINT y, UINT width, UINT height, bool showScrollbars)
{
	WNDCLASSEX wcex;
	static const char *className = "WebWindowClass";

	this->hInstWebWindow = hInstance;
	this->showScrollbars = showScrollbars;

	if (!GetClassInfoEx(hInstance, className, &wcex)) {
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)WebWindowWndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(this);
		wcex.hInstance = hInstance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = className;
		wcex.hIconSm = NULL;

		if (!RegisterClassEx(&wcex)) {
			MessageBox(NULL, "Error registering WebWindow window class", "WebWindow::Create", MB_OK);
			return;
		}
	}

	webForm = new WebForm(webformDispatchHandler);

	/*HWND hWndDesktop = FindWindow("DesktopBackgroundClass", 0);

	if (hWndDesktop == NULL) {
		hWndDesktop = GetDesktopWindow();
	}*/

	hWndWebWindow = CreateWindowEx(0, className, "WebWindowWindow", /*WS_CHILD*//*WS_POPUP | WS_CLIPCHILDREN*/WS_POPUPWINDOW | WS_CAPTION,
		x, y, width, height, NULL/*hWndDesktop*/, NULL, hInstance, (LPVOID)this);

	if (hWndWebWindow == NULL) {
		MessageBox(NULL, "Error creating WebWindow window", "WebWindow::Create", MB_OK);
		UnregisterClass(className, hInstance);
		return;
	}

	ShowWindow(hWndWebWindow, SW_SHOW);
}

LRESULT CALLBACK WebWindow::WebWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE) {
		WebWindow *webw = (WebWindow*)((LPCREATESTRUCT(lParam))->lpCreateParams);
		webw->hWndWebWindow = hWnd;

		#pragma warning(suppress:4244)
		SetWindowLongPtr(hWnd, 0, (LONG_PTR)webw);

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	#pragma warning(suppress:4312)
	WebWindow *webw = (WebWindow*)GetWindowLongPtr(hWnd, 0);

	if (webw == NULL) {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return webw->InstanceWndProc(msg, wParam, lParam);
}

LRESULT WebWindow::InstanceWndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_CREATE: {
			webForm->create(hWndWebWindow, hInstWebWindow, 103, showScrollbars);

			break;
		}
		case WM_SIZE:
			if (webForm->hWnd) {
				MoveWindow(webForm->hWnd, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
			}

			break;
		case WM_COMMAND: {
			int id = LOWORD(wParam);
			int code = HIWORD(wParam);

			if (id == 103 && code == WEBFN_LOADED) {
			}

			break;
		}
		case WM_DESTROY:
			webForm->Close();
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hWndWebWindow, msg, wParam, lParam);
}