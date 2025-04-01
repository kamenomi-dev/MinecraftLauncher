#include "../pch.h"
#include "../Render.h"
#include "./Window.h"

using namespace Launcher::Components;

WindowWrapper::WindowWrapper(
    HINSTANCE hInstance, wstring classText, wstring titleText, WndProc pfnWndProc
) {
    _wndClass.hInstance     = hInstance;
    _wndClass.lpfnWndProc   = &WindowWrapper::CommonWindowsMessageProcessor;
    _wndClass.lpszClassName = classText.c_str();

    _wndProc           = pfnWndProc;
    _initOptions.title = titleText;
}

WindowWrapper::~WindowWrapper() {
    if (!_bInit) {
        return;
    }

    if (_pSwapBuffer) {
        delete _pSwapBuffer;
        _pSwapBuffer = nullptr;
    }

    DestroyWindow(_hWnd);
    UnregisterClass(_wndClass.lpszClassName, _wndClass.hInstance);
    Gdiplus::GdiplusShutdown(_uGdipToken);

    _bInit = false;
}

bool WindowWrapper::Initialize() {
    Gdiplus::GdiplusStartupInput input{};
    if (Gdiplus::GdiplusStartup(&_uGdipToken, &input, nullptr) != Gdiplus::Ok) {
        OutputDebugStringA("Cannot initialize gdiplus.");
        abort();
        return false;
    }

    if (!RegisterClassEx(&_wndClass)) {
        /*  Gdiplus::GdiplusShutdown(_uGdipToken);

          OutputDebugStringA("Cannot register window class information.");
          abort();
          return false;*/
    };

    auto hWnd = CreateWindowExW(
        WS_EX_APPWINDOW, _wndClass.lpszClassName, _initOptions.title.c_str(), WS_OVERLAPPEDWINDOW,
        _initOptions.position.x, _initOptions.position.y, _initOptions.size.cx, _initOptions.size.cy,
        _initOptions.hParent, nullptr, _wndClass.hInstance, this
    );

    if (!hWnd) {
        UnregisterClass(_wndClass.lpszClassName, _wndClass.hInstance);
        Gdiplus::GdiplusShutdown(_uGdipToken);

        OutputDebugStringA("Cannot create window.");
        abort();
        return false;
    }

    if (_initOptions.hParent) {
        ::SetParent(hWnd, _initOptions.hParent);
    }

    _bInit       = true;
    _hWnd        = hWnd;
    _pSwapBuffer = new SwapBuffer(hWnd, false);
    return !!hWnd;
}

void WindowWrapper::Run(
    int showType
) {
    ShowWindow(_hWnd, showType);
}

void WindowWrapper::SetParent(
    HWND hParent
) {
    if (_bInit) {
        ::SetParent(_hWnd, hParent);
    }

    _initOptions.hParent = hParent;
}

HWND WindowWrapper::GetParent() const {
    if (_bInit) {
        return ::GetParent(_hWnd);
    }

    return _initOptions.hParent;
}

void WindowWrapper::SetSize(
    SIZE size
) {
    if (_bInit) {
        SetWindowPos(_hWnd, NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
    }

    _initOptions.size = size;
}

SIZE WindowWrapper::GetSize() const {
    if (_bInit) {
        RECT rect{};
        GetWindowRect(_hWnd, &rect);

        return {rect.right - rect.left, rect.bottom - rect.top};
    }

    return _initOptions.size;
}

void WindowWrapper::SetPosition(
    POINT position
) {
    if (_bInit) {
        SetWindowPos(_hWnd, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    _initOptions.position = position;
}

POINT WindowWrapper::GetPosition() const {
    if (_bInit) {
        RECT rect{};
        GetWindowRect(_hWnd, &rect);

        return {rect.left, rect.top};
    }

    return _initOptions.position;
}

LRESULT WindowWrapper::CommonWindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
    static unordered_map<HWND, WindowWrapper*> windowWrapperMap{};
    auto&                                      pWrapper = windowWrapperMap[hWnd];

    if (uMsg == WM_NCCREATE) {
        const auto createStruct = *(CREATESTRUCTW*)lParam;
        const auto wrapper      = (WindowWrapper*)createStruct.lpCreateParams;

        if (wrapper) {
            windowWrapperMap[hWnd] = wrapper;
            // Handle has already existed, but CreateWindowEx hasn't returned it.
            wrapper->_hWnd = hWnd;
            wrapper->OnCreate(true);
        }
    }

    if (uMsg == WM_CREATE) {
        pWrapper->OnCreate(false);
    }

    if (pWrapper && uMsg == WM_SIZE) {
        pWrapper->_pSwapBuffer->UpdateSize(lParam);

        #if _DEBUG
        OutputDebugStringA(
            (std::to_string(GetTickCount64()) + (" - [MainWindow] WM_SIZE was toggled. \r\n"s)).c_str()
        );
#endif;
    }

    if (pWrapper && uMsg == WM_MOVE) {
        pWrapper->_pSwapBuffer->UpdatePosition(lParam);
    }

    if (pWrapper && (uMsg == WM_PAINT || uMsg == WM_NCPAINT)) {
        const auto        swapBuffer = pWrapper->_pSwapBuffer;
        Gdiplus::Graphics graphics{swapBuffer->GetGraphicsDC()};

        pWrapper->OnPaint(graphics, uMsg == WM_NCPAINT);

        swapBuffer->Present();

        #if _DEBUG
        OutputDebugStringA((std::to_string(GetTickCount64()) + (" - [MainWindow] WM_(NC)PAINT was toggled. \r\n"s)).c_str());
        #endif;
    }

    if (uMsg == WM_CLOSE) {
        if (pWrapper) {
            if (pWrapper->OnClose()) {
                pWrapper->_WindowExit();
                windowWrapperMap.erase(hWnd);
            } else {
                return 0;
            }
        }

        if (windowWrapperMap.empty()) {
            PostQuitMessage(NULL);
        }
    }

    if (uMsg != WM_CLOSE) {
        LRESULT hResult{};
        if (pWrapper && pWrapper->_wndProc(hWnd, uMsg, wParam, lParam, hResult)) {
            return hResult;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WindowWrapper::MessageLoop() {
    MSG message{};

    while (GetMessageW(&message, nullptr, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    return (int)message.wParam;
}

void WindowWrapper::_WindowExit() {
    OnExit();
    // delete this;
}
