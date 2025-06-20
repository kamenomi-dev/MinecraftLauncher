#include "pch.h"
#include "Window.h"

#include "logger.cpp"

using namespace UIFramework::Components;

static ATOM                    ui_WndClassAtom{NULL};
static std::map<HWND, Window*> ui_WindowMap{};

Window::Window() {
    if (ui_WndClassAtom == NULL) {
        WNDCLASSEXW classInfo{NULL};
        classInfo.cbSize        = sizeof WNDCLASSEXW;
        classInfo.style         = CS_VREDRAW | CS_HREDRAW;
        classInfo.hIcon         = NULL;
        classInfo.hIconSm       = NULL;
        classInfo.hCursor       = LoadCursor(NULL, IDC_ARROW);
        classInfo.hInstance     = GetModuleHandle(NULL);
        classInfo.lpfnWndProc   = &Window::WindowsMessageProcessor;
        classInfo.lpszClassName = L"UIFramework.Gdiplus.Window";

        ui_WndClassAtom = RegisterClassExW(&classInfo);
        if (!ui_WndClassAtom) {
            NotifyError(L"Error! Couldn't register window class! ");
        }
    }
}

Window::~Window() {
    if (windowHandle) {
        CheckAnyResult(DestroyWindow(windowHandle));

        ui_WindowMap.erase(windowHandle);
        windowHandle = nullptr;
    }

    if (ui_WndClassAtom) {
        // Whether calling UnregisterClassW successfully or not.
        if (UnregisterClassW(MAKEINTATOM(ui_WndClassAtom), GetModuleHandle(NULL))) {
            ui_WndClassAtom = NULL;
        }
    }
}

void Window::Initialize(
    const wstring& title, Rect rect, UINT windowStyle, UINT windowExtraStyle
) {
    if (!ui_WndClassAtom) {
        NotifyError(L"Error! Incorrect calling process as initializing window before registering window class. ");
    }

    auto hWnd = CreateWindowExW(
        windowExtraStyle, L"UIFramework.Gdiplus.Window", title.c_str(), windowStyle, rect.X, rect.Y, rect.Width,
        rect.Height, nullptr, nullptr, GetModuleHandleW(NULL), (void*)this
    );

    if (!hWnd) {
        NotifyError(L"Error! Failed to create window! ");
    }

    windowHandle       = hWnd;
    ui_WindowMap[hWnd] = this;
}

void Window::Close() {
    if (IsWindow(windowHandle)) {
        DestroyWindow(windowHandle);
    }

    ui_WindowMap.erase(windowHandle);
    windowHandle = nullptr;
}

void Window::Show() {
    if (windowHandle) {
        CheckAnyResult(ShowWindow(windowHandle, SW_SHOW));
    }
}

void Window::Hide() {
    if (windowHandle) {
        CheckAnyResult(ShowWindow(windowHandle, SW_HIDE));
    }
}

LRESULT Window::WindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
    auto& currentContext = ui_WindowMap[hWnd];

    if (uMsg == WM_CLOSE) {
        if (currentContext) {
            currentContext->Close();
        }

        if (ui_WindowMap.empty()) {
            PostQuitMessage(0);
        }
    }

    if (uMsg == WM_QUIT) {
        if (!ui_WindowMap.empty()) {
            for (auto context = ui_WindowMap.begin(); context != ui_WindowMap.end(); ++context) {
                if (context->second) {
                    context->second->Close();
                }
            }
        }
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
