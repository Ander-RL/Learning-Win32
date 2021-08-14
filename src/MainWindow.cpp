#include "MainWindow.h"

MainWindow::MainWindow(HINSTANCE hInstance, LPCWSTR ClassName, int nCmdShow)
	: m_hInstance(hInstance), m_className(ClassName), m_nCmdShow(nCmdShow) 
{
	OutputDebugString(L"MAIN WINDOW CONSTRUCTOR\n");
}

PCWSTR  MainWindow::GetClassName() const { return m_className; }

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	OutputDebugString(L"MAIN WINDOW HANDLEMESSAGE\n");

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(m_hwnd, L"TEXT", L"CAPTION", MB_OKCANCEL);

	case WM_CLOSE:
		DestroyWindow(m_hwnd);

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(m_hwnd, &ps);
	}
	return 0;

	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}

BOOL MainWindow::Create(
	PCWSTR lpWindowName,
	DWORD dwStyle,
	DWORD dwExStyle,
	int nWidth,
	int nHeight,
	int x,
	int y,
	HWND hWndParent,
	HMENU hMenu)
{
	OutputDebugString(L"MAIN WINDOW CREATE\n");

	WNDCLASS wc = { 0 };

	wc.lpfnWndProc = BaseWindow::WindowProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = GetClassName();

	if (RegisterClass(&wc)) 
	{ 
		OutputDebugString(L"MAIN WINDOW CREATE CLASS REGISTERED\n"); 
	}
	else
	{
		OutputDebugString(L"MAIN WINDOW CREATE CLASS UNABLE TO REGISTER\n");
	}

	m_hwnd = CreateWindowEx(
		dwExStyle,
		GetClassName(),
		lpWindowName,
		dwStyle,
		x, y,
		nWidth, nHeight,
		hWndParent,
		hMenu,
		m_hInstance,
		this);

	if (!m_hwnd)
	{
		OutputDebugString(L"--------- Window Creation Failed ---------\n");
		ExitProcess(0);
	}

	ShowWindow(m_hwnd, m_nCmdShow);
	UpdateWindow(m_hwnd);

	return (m_hwnd ? TRUE : FALSE);
}