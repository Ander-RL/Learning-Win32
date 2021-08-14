#pragma once

#include "BaseWindow.h"


class MainWindow : public BaseWindow
{
private:
	HINSTANCE m_hInstance;
	LPCWSTR m_className;
	int m_nCmdShow;

public:
	MainWindow(HINSTANCE hInstance, LPCWSTR ClassName, int nCmdShow);

	//~MainWindow();

	BOOL Create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0);

	virtual PCWSTR  GetClassName() const;

	virtual LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};