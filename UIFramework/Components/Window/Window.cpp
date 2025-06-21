#include "pch.h"
#include "Window.h"

#include "Logger.cpp"

using namespace UIFramework::Components;

static ATOM                    ui_WndClassAtom{NULL};
static std::map<HWND, Window*> ui_WindowMap{};

Window::Window() : instanceLogger(nullptr), windowHandle(nullptr), doubleBuffer(nullptr) {

    instanceLogger = spdlog::stdout_logger_st("Window:" + std::to_string(ui_WindowMap.size()));

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
        DestroyWindow(windowHandle);

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

    instanceLogger->info("Window closed. ");
}

void Window::Show() const {
    if (windowHandle) {
        CheckAnyResult(ShowWindow(windowHandle, SW_SHOW));
    }
}

void Window::Hide() const {
    if (windowHandle) {
        CheckAnyResult(ShowWindow(windowHandle, SW_HIDE));
    }
}

bool Window::_Native_WindowsMessageProcessor(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT &)
{
    if (this && instanceLogger) {
        instanceLogger->debug(
            L"Received message: {0}, with data: h {1}, w {2}, l {3}", uMsg, (int)hWnd, (int)wParam, (int)lParam
        );
    }

    return false;
}

LRESULT Window::WindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
    Window* currentContext = nullptr;
    for (auto ctx = ui_WindowMap.begin(); ctx != ui_WindowMap.end(); ++ctx) {
        if (ctx->first == hWnd) {
            currentContext = ctx->second;
            break;
        }
    }

    if (uMsg == WM_CREATE) {
        /*LRESULT noop{};
        auto    context = (Window*)(void*)lParam;
        context->_Native_WindowsMessageProcessor(hWnd, uMsg, wParam, lParam, noop);

        return NULL;*/
    }

    if (uMsg == WM_CLOSE) {
        if (currentContext) {
            currentContext->Close();
        }

        if (ui_WindowMap.empty()) {
            PostQuitMessage(0);

            spdlog::info("All windows closed, shutdown...");
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

    LRESULT result{};
    if (currentContext->_Native_WindowsMessageProcessor(hWnd, uMsg, wParam, lParam, result)) {
        return result;
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
