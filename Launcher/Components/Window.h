#pragma once

#ifndef _Component_Window_Header_
#define _Component_Window_Header_

namespace Launcher {
namespace Components {

class WindowWrapper {

  public:
    typedef bool(__stdcall* WndProc)(HWND, UINT, WPARAM, LPARAM, LRESULT&);

    struct WindowInitOptions {
        bool isLayered;

        HWND    hParent;
        wstring title;
        SIZE    size;
        POINT   position;
    };


    friend class LauncherWindow;

  public:
    WindowWrapper(HINSTANCE hInstance, wstring classText, wstring titleText, WndProc pfnWndProc);
    ~WindowWrapper();

    bool Initialize();
    void Run(int showType);

    void  SetParent(HWND);
    HWND  GetParent() const;
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

/// <summary>
/// 这里继承了窗口包装器，但是不代表这个视觉包装类是会由此创建窗口的，而是另开一个为
/// VisualWrapper 作为类名的窗口，并将视觉面的渲染给它。
/// 但是这里有个问题，不能明确这个窗口的功能，它是用户窗口的父窗口，但是对其非客户区操作就有问题了。
/// Todo，必须Todo，总该不能俩个窗口处理合并在一起啊？
/// </summary>
/// <seealso cref="WindowWrapper" />
class VisualWrapper : WindowWrapper {};
} // namespace Components
} // namespace Launcher

#endif // _Component_Window_Header_