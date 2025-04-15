#pragma once

#ifndef _Component_Window_Header_
#define _Component_Window_Header_

#include "Render.h"
#include "Button.h"
#include "ComponentContainer.h"

namespace Launcher {
namespace Components {

class WindowWrapper : public ComponentContainer {

  public:
    typedef bool(__stdcall* WndProc)(HWND, UINT, WPARAM, LPARAM, LRESULT&);

    struct WindowInitOptions {
        bool isLayered;

        HWND    hParent;
        wstring titleText;
        wstring classText;
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
    void  SetPosition(bool centered);
    void  SetPosition(POINT);
    POINT GetPosition() const;

    static LRESULT CommonWindowsMessageProcessor(HWND, UINT, WPARAM, LPARAM);
    static int     MessageLoop();

    virtual void OnCreate(bool bNonClient) {};
    virtual bool OnClose() { return true; };
    virtual void OnPaint(Gdiplus::Graphics&) {};
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
/// ����̳��˴��ڰ�װ�������ǲ���������Ӿ���װ���ǻ��ɴ˴������ڵģ�������һ��Ϊ
/// VisualWrapper ��Ϊ�����Ĵ��ڣ������Ӿ������Ⱦ������
/// ���������и����⣬������ȷ������ڵĹ��ܣ������û����ڵĸ����ڣ����Ƕ���ǿͻ����������������ˡ�
/// Todo������Todo���ܸò����������ڴ���ϲ���һ�𰡣�
/// </summary>
/// <seealso cref="WindowWrapper" />
class VisualWrapper : WindowWrapper {};
} // namespace Components
} // namespace Launcher

#endif // _Component_Window_Header_