#pragma once

#include <Windows.h>


class BaseWindow
{

public:
	BaseWindow();

	~BaseWindow();

	HWND Window() const;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:

	virtual PCWSTR  GetClassName() const = 0;
	virtual LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND m_hwnd;
};