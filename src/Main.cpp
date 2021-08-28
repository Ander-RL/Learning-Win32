#ifndef UNICODE
#define UNICODE
#endif 

#include "MainWindow.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow win(hInstance, L"MainWindow", nCmdShow);

    if (!win.Create(L"Notepad --", WS_OVERLAPPEDWINDOW, 0, 1024, 720))
    {
        return 0;
    }

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}