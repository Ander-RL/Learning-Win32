#include "BaseWindow.h"



BaseWindow::BaseWindow() : m_hwnd(NULL) { }

BaseWindow::~BaseWindow() { DestroyWindow(m_hwnd); }

HWND BaseWindow::Window() const { return m_hwnd; }

LRESULT CALLBACK BaseWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case (WM_NCCREATE):
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		BaseWindow* pBaseWindow = (BaseWindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pBaseWindow);

		pBaseWindow->m_hwnd = hwnd;
		break;
	}

	case (WM_DESTROY):
	{
		PostQuitMessage(0);
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

BOOL BaseWindow::Create(
	PCWSTR lpWindowName,
	DWORD dwStyle,
	DWORD dwExStyle,
	int x,
	int y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu)
{
	WNDCLASS wc = { 0 };

	wc.lpfnWndProc = BaseWindow::WindowProc;
	wc.hInstance = GetModuleHandle(NULL); // = hInstance de wWinMain
	wc.lpszClassName = ClassName();

	RegisterClass(&wc);

	m_hwnd = CreateWindowEx(
		dwExStyle, 
		ClassName(), 
		lpWindowName, 
		dwStyle, 
		x, y,
		nWidth, nHeight, 
		hWndParent, 
		hMenu,
		GetModuleHandle(NULL), 
		this);

	return (m_hwnd ? TRUE : FALSE);
}
