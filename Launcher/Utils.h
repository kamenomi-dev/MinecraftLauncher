#pragma once

#ifndef __RENDER_H__
#include "Render.h"
#endif // !__RENDER_H__


#ifndef __UTILS_H__
#define __UTILS_H__

namespace Launcher {

class LauncherWindow;

namespace Utils {

namespace System {
struct VersionStruct {
    // NT major version.
    ULONG Major;
    // NT minor version.
    ULONG Minor;
    // Shared collection generation numbers that are not decorated with C or F. GetVersionEx hides real numbers.
    ULONG Build;
};

VersionStruct GetCorrectVersion();
} // namespace System

class WindowWrapper {

  public:
    enum BlurTypes : UCHAR {
        Auto = 0,
        Aero,
        Acrylic,
        Mica
    };

    struct WindowInitOptions {
        bool isLayered;

        wstring title;
        SIZE    size;
        POINT   position;
    };

    typedef bool(__stdcall* WndProc)(HWND, UINT, WPARAM, LPARAM, LRESULT&);

    friend class LauncherWindow;

  public:
    WindowWrapper(HINSTANCE hInstance, wstring classText, wstring titleText, WndProc pfnWndProc);
    ~WindowWrapper();

    bool Initialize();
    void Run(int showType);

    void  SetSize(SIZE);
    SIZE  GetSize() const;
    void  SetPosition(POINT);
    POINT GetPosition() const;

    static LRESULT CommonWindowsMessageProcessor(HWND, UINT, WPARAM, LPARAM);
    static int     MessageLoop();

    virtual void OnCreate(bool bNonClient) {};
    virtual bool OnClose() { return true; };
    virtual void OnPaint(Gdiplus::Graphics&, bool bNonClient) {};
    virtual void OnExit() {};

    bool EnableLayeredStyle(bool bToggle);
    // It adapts to the platform without manually setting its blur style.
    bool EnableBackgroundBlur(bool bToggle);
    bool EnableBackgroundBlur(bool bToggle, BlurTypes);

    HWND GetHWND() const { return _hWnd; };

    __declspec(property(get = GetHWND)) HWND hWindow;

  private:
    void _WindowExit();

  private:
    bool              _bInit{false};
    WindowInitOptions _initOptions{};

    ULONG_PTR  _uGdipToken{};
    HWND       _hWnd{NULL};
    WndProc    _wndProc{nullptr};
    WNDCLASSEX _wndClass{sizeof(WNDCLASSEX), NULL};

    SwapBuffer* _pSwapBuffer{nullptr};
};

} // namespace Utils
} // namespace Launcher

#endif // __UTILS_H__