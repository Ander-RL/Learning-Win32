#pragma once

#include "BaseWindow.h"


class MainWindow : public BaseWindow
{
public:

	PCWSTR  ClassName() const;

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

};