#include "pch.h"
#include "Utils.h"

#include "./Interfaces/User32/WindowCompositionAttribute.h"

using namespace Launcher::Utils;

/// <summary>
/// Gets the correct version on Windows.
/// </summary>
System::VersionStruct System::GetCorrectVersion() {
#ifdef _WINDOWS
    auto sharedUserData = (BYTE*)0x7FFE0000;
    return {*(ULONG*)(sharedUserData + 0x26c), *(ULONG*)(sharedUserData + 0x270), *(ULONG*)(sharedUserData + 0x260)};
#else
    return {
        NULL, NULL, NULL
    }
#endif // _WINDOWS
}

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
        WS_EX_APPWINDOW | (_initOptions.isLayered ? WS_EX_LAYERED : NULL), _wndClass.lpszClassName,
        _initOptions.title.c_str(), WS_OVERLAPPEDWINDOW, _initOptions.position.x, _initOptions.position.y,
        _initOptions.size.cx, _initOptions.size.cy, nullptr, nullptr, _wndClass.hInstance, this
    );

    if (!hWnd) {
        UnregisterClass(_wndClass.lpszClassName, _wndClass.hInstance);
        Gdiplus::GdiplusShutdown(_uGdipToken);

        OutputDebugStringA("Cannot create window.");
        abort();
        return false;
    }

    _bInit       = true;
    _hWnd        = hWnd;
    _pSwapBuffer = new SwapBuffer(hWnd, _initOptions.isLayered);
    return !!hWnd;
}

void WindowWrapper::Run(
    int showType
) {
    ShowWindow(_hWnd, showType);
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
            wrapper->OnCreate(true);
        }
    }

    if (uMsg == WM_CREATE) {
        pWrapper->OnCreate(false);

        /*if (pWrapper) {
            pWrapper->OnCreate(false);
        } else {
            const auto createStruct = *(CREATESTRUCTW*)lParam;
            const auto wrapper      = (WindowWrapper*)createStruct.lpCreateParams;

            if (wrapper) {
                windowWrapperMap[hWnd] = wrapper;
            }
        }*/
    }

    if (pWrapper && uMsg == WM_SIZE) {
        pWrapper->_pSwapBuffer->UpdateSize(lParam);
    }

    if (pWrapper && uMsg == WM_MOVE) {
        pWrapper->_pSwapBuffer->UpdatePosition(lParam);
    }

    if (pWrapper && (uMsg == WM_PAINT || uMsg == WM_NCPAINT)) {
        const auto        swapBuffer = pWrapper->_pSwapBuffer;
        Gdiplus::Graphics graphics{swapBuffer->GetGraphicsDC()};

        pWrapper->OnPaint(graphics, uMsg == WM_NCPAINT);

        swapBuffer->Present();
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

int Launcher::Utils::WindowWrapper::MessageLoop() {
    MSG message{};

    while (GetMessageW(&message, nullptr, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    return (int)message.wParam;
}

bool WindowWrapper::EnableLayeredStyle(
    bool bToggle
) {
    if (_bInit) {
        auto exStyle = GetWindowLongW(_hWnd, GWL_EXSTYLE);

        if (bToggle) {
            exStyle |= WS_EX_LAYERED;
        } else {
            exStyle &= ~WS_EX_LAYERED;
        }

        return !!SetWindowLongW(_hWnd, GWL_EXSTYLE, exStyle);
    }

    _initOptions.isLayered = bToggle;
    return true;
}

bool WindowWrapper::EnableBackgroundBlur(
    bool bToggle
) {
    return EnableBackgroundBlur(bToggle, BlurTypes::Auto);
}

bool WindowWrapper::EnableBackgroundBlur(
    bool bToggle, BlurTypes type
) {
    const auto version = System::GetCorrectVersion();
    // Lower than or equal Windows7.
    if (version.Major < 10 && version.Minor <= 1) {
        DWM_BLURBEHIND blurBehind{};
        blurBehind.dwFlags  = DWM_BB_ENABLE;
        blurBehind.fEnable  = bToggle;
        blurBehind.hRgnBlur = NULL;

        return SUCCEEDED(DwmEnableBlurBehindWindow(_hWnd, &blurBehind));
    }

    // Hight than Windows 7 and lower than Windows 11.
    if ((type != BlurTypes::Mica) || version.Build < 22000) {
        using namespace Launcher::Interfaces::User32;

        // User32 is already loaded; otherwise, the window cannot be created.
        const auto hUser32 = GetModuleHandleW(L"User32.dll");

        auto setWindowCompositionAttribute =
            (pfnSetWindowCompositionAttribute)GetProcAddress(hUser32, "SetWindowCompositionAttribute");

        if (setWindowCompositionAttribute == nullptr) {
            return false;
        }

        ACCENT_POLICY accent{ACCENT_ENABLE_BLURBEHIND, NULL};
        if (type == BlurTypes::Acrylic || (type == BlurTypes::Auto && version.Major == 10)) {
            // accent.AccentState = ACCENT_ENABLE_ACRYLICBLURBEHIND;
            OutputDebugStringA("Acrylic has a lag bug on Windows 10, so using Aero actually.");
        }

        if (!bToggle) {
            accent.AccentState = ACCENT_DISABLED;
        }

        WINDOWCOMPOSITIONATTRIBDATA data{};
        data.Attrib = WCA_ACCENT_POLICY;
        data.pvData = &accent;
        data.cbData = sizeof(accent);

        auto ret = setWindowCompositionAttribute(_hWnd, &data);
        return ret;
    }

    // DWMWA_MICA_EFFECT 1029
    return SUCCEEDED(DwmSetWindowAttribute(_hWnd, 1029, &bToggle, sizeof bToggle));
}

void WindowWrapper::_WindowExit() {
    OnExit();
    // delete this;
}
