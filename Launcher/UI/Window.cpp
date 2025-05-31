#include "pch.h"
#include "Window.h"

using namespace MinecraftLauncher::UI;

HWND Window::Initialize(
    HINSTANCE processInstance, WNDPROC winMsgProc, int nCmdShow
) {
    hProcessInstance                 = processInstance;
    initialWindowProperties.nCmdShow = nCmdShow;
    auto& props                      = initialWindowProperties;

    WNDCLASSEXW classInfo{};
    classInfo.cbSize        = sizeof WNDCLASSEXW;
    classInfo.style         = CS_HREDRAW | CS_VREDRAW;
    classInfo.hInstance     = processInstance;
    classInfo.lpfnWndProc   = winMsgProc;
    classInfo.lpszClassName = props.ClassText.c_str();
    RegisterClassExW(&classInfo);

    hOwnedWindow = CreateWindowExW(
        WS_EX_APPWINDOW, props.ClassText.c_str(), props.TitleText.c_str(), WS_OVERLAPPEDWINDOW, props.windowPosition.X,
        props.windowPosition.Y, props.windowSize.Width, props.windowSize.Height, nullptr, nullptr, processInstance,
        (void*)this
    );

    if (hOwnedWindow == nullptr) {
        OutputDebugStringW(
            L"Oops, A window couldn't be created. Please check your window doesn't conflict with others. "
        );
        abort();
    }

    return hOwnedWindow;
}

void Window::Uninitialize() {
    if (hOwnedWindow == nullptr) {
        OutputDebugStringW(L"Oops, A Window class couldn't be uninited itself because was not inited before. ");
        return;
    }

    const auto& props = initialWindowProperties;
    UnregisterClassW(props.ClassText.c_str(), hProcessInstance);

    DestroyWindow(hOwnedWindow);
    hOwnedWindow = nullptr;
}

LRESULT Window::_Native_WindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp
) {

    if (uMsg == WM_CREATE) {
        if (initialWindowProperties.IsCenterAlign) {
            CenterWindowToScreen();
        }

        if (initialWindowProperties.IsBlur) {
            BlurWindow();
        }

        ShowWindow(hOwnedWindow, initialWindowProperties.nCmdShow);
    }

    return DefWindowProcW(hWnd, uMsg, wp, lp);
}

void Window::SetTitle(
    wstring
) {}

const wstring Window::GetTitle() {
    return wstring();
}

void Window::SetID(
    wstring
) {}

void Window::SetSize(
    Gdiplus::Size
) {}

void Window::SetPosition(
    Gdiplus::Point
) {}

void Window::SetVisible(
    bool
) {}

void Window::SetDisabled(
    bool
) {}

const wstring Window::GetID() {
    return wstring();
}

const Gdiplus::Size Window::GetSize() {
    return Gdiplus::Size();
}

const Gdiplus::Point Window::GetPosition() {
    return Gdiplus::Point();
}

const bool Window::GetVisible() {
    return false;
}

const bool Window::GetDisabled() {
    return false;
}
