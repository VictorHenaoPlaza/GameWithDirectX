#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Direct3D9.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    WNDCLASSEX windowClass;
    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
    LPCWSTR className = L"Window Class";

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    windowClass.lpszClassName = className;

    RegisterClassEx(&windowClass);
    ULONG error = GetLastError();

    RECT windowRectangle = { 0, 0, 800, 450 };
    AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

    RECT workingAreaRectangle;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workingAreaRectangle, 0);

    int xDifference = windowRectangle.left / 2;
    int yDifference = (int)floor(windowRectangle.top / 2.f);

    int x = xDifference + (workingAreaRectangle.right - windowRectangle.right) / 2;
    int y = yDifference + (workingAreaRectangle.bottom - windowRectangle.bottom) / 2;

    HWND windowHandle = CreateWindowEx(
        0,
        className,
        L"Original Window Title",
        WS_OVERLAPPEDWINDOW,
        x, y,
        windowRectangle.right - windowRectangle.left,
        windowRectangle.bottom - windowRectangle.top,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(windowHandle, nShowCmd);

    InitializeDirect3D9(windowHandle);

    MSG message;
    ZeroMemory(&message, sizeof(MSG));
    while (message.message != WM_QUIT)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        RenderDirect3D9();
    }

    CleanDirect3D9();
    DestroyWindow(windowHandle);
    UnregisterClass(className, hInstance);

    return message.wParam;
}
