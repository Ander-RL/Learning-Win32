#pragma once

#include <Windows.h>


class BaseWindow
{

public:

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BaseWindow();

	~BaseWindow();

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

	HWND Window() const;

protected:

	virtual PCWSTR  ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND m_hwnd;
};