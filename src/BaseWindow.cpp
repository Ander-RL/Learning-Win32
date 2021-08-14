#include "BaseWindow.h"



BaseWindow::BaseWindow() : m_hwnd(NULL) { }

BaseWindow::~BaseWindow() { DestroyWindow(m_hwnd); }

HWND BaseWindow::Window() const { return m_hwnd; }

LRESULT CALLBACK BaseWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	OutputDebugString(L"BASE WINDOW WindowProc\n");

	if (uMsg == WM_NCCREATE)
	{
		OutputDebugString(L"BASE WINDOW WindowProc -> WM_NCCREATE\n");

		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		BaseWindow* pBaseWindow = (BaseWindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pBaseWindow);
	}

	BaseWindow* pBaseWindow = reinterpret_cast<BaseWindow*>(GetWindowLongW(hwnd, GWL_USERDATA));

	LRESULT lResult;

	if (pBaseWindow)
	{
		OutputDebugString(L"BASE WINDOW pBASEWINDOW\n");

		pBaseWindow->m_hwnd = hwnd;
		lResult = pBaseWindow->HandleMessage(hwnd, uMsg, wParam, lParam);
	}
	else
	{
		OutputDebugString(L"BASE WINDOW DefWindowProc\n");

		lResult = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return lResult;
}


