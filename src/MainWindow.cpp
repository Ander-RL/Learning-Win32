#include "MainWindow.h"
#include "resource/resource.h"

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
	case WM_COMMAND: // Menu options
		switch (LOWORD(wParam)) 
		{
		case ID_FILE_NEW:
			MessageBox(m_hwnd, L"New file", L"Menu option New", MB_OK | MB_ICONASTERISK);
			break;

		case ID_FILE_OPEN:
			MessageBox(m_hwnd, L"Menu option Open", L"Open", MB_OK | MB_ICONASTERISK);
			break;

		case ID_FILE_EXIT:
			int msgBoxID = MessageBox(m_hwnd, L"Are you sure you want to exit?", L"Exit", MB_OKCANCEL | MB_ICONHAND);
			if (msgBoxID == IDOK) PostMessage(m_hwnd, WM_CLOSE, 0, 0);
			break;
		}
		break;

	case WM_CLOSE:
		OutputDebugString(L"MAIN WINDOW HANDLEMESSAGE -> WM_CLOSE\n");
		DestroyWindow(m_hwnd);
		return 0;

	case WM_DESTROY:
		OutputDebugString(L"MAIN WINDOW HANDLEMESSAGE -> WM_DESTROY\n");
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
		OutputDebugString(L"MAIN WINDOW HANDLEMESSAGE -> DefWindowProc\n");
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wc.hIcon = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, LR_DEFAULTSIZE);

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

	// Centering the window in the screen
	RECT rc;

	GetWindowRect(m_hwnd, &rc);

	int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
	int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;

	SetWindowPos(m_hwnd, HWND_TOP, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	ShowWindow(m_hwnd, m_nCmdShow);
	UpdateWindow(m_hwnd);

	return (m_hwnd ? TRUE : FALSE);
}