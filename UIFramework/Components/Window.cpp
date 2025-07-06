#include "pch.h"
#include "Window.h"

#include "Logger.cpp"

using namespace UIFramework::Components;

static ATOM                    ui_WndClassAtom{NULL};
static std::map<HWND, Window*> ui_WindowMap{};

Window::Window() : instanceLogger(nullptr), windowHandle(nullptr), doubleBuffer(new Utils::DoubleBuffer) {

    instanceLogger = spdlog::stdout_color_mt("Window:" + std::to_string(ui_WindowMap.size()));
#ifdef _DEBUG
    instanceLogger->set_level(spdlog::level::trace);
#endif

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

    windowHandle = hWnd;
    doubleBuffer->BindWindow(hWnd);
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
    if (instanceLogger) {
        instanceLogger->debug(
            L"Received message: {0}, with data: h {1}, w {2}, l {3}", uMsg, (int)hWnd, (int)wParam, (int)lParam
        );
    }

    switch (uMsg) {
    [[unlikely]] case WM_PAINT: {
        PAINTSTRUCT paintStruct{};
        const auto  hTargetDC = BeginPaint(hWnd, &paintStruct);
        const auto  srcDC     = _ContainerComponent.RenderContainer();

        doubleBuffer->RefreshLayoutToMemory(srcDC);
        doubleBuffer->RefreshLayout(paintStruct.rcPaint);

        EndPaint(hWnd, &paintStruct);
        break;
    }
    }

    return false;
}

LRESULT Window::WindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
    Window* currentContext = nullptr;

    auto iter = ui_WindowMap.find(hWnd);
    if (iter != ui_WindowMap.end()) {
        currentContext = iter->second;
    }

    switch (uMsg) {
    [[unlikely]] case WM_CREATE: {
        if (!currentContext) {
            currentContext = (Window*)((CREATESTRUCT*)lParam)->lpCreateParams;
            ui_WindowMap.emplace(hWnd, currentContext);
        }
        break;
    }
    [[unlikely]] case WM_CLOSE: {
        if (currentContext) {
            currentContext->Close();
        }

        if (ui_WindowMap.empty()) {
            PostQuitMessage(0);
            spdlog::info("All windows closed, shutdown...");
        }
        break;
    }
    [[unlikely]] case WM_QUIT: {
        for (auto& context : ui_WindowMap) {
            context.second->Close();
        }
        break;
    }
    case WM_ERASEBKGND: {
        break;
    }
    default:
        LRESULT result{};
        if (currentContext && currentContext->_Native_WindowsMessageProcessor(hWnd, uMsg, wParam, lParam, result)) {
            return result;
        }

        return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }

    return NULL;
}
