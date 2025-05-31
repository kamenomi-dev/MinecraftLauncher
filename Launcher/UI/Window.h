#pragma once
#ifndef _MinecraftLauncher_UI_Window_H_
#define _MinecraftLauncher_UI_Window_H_

#include "Basis.h"

namespace MinecraftLauncher {
namespace UI {

struct WindowProperties {
    wstring ClassText{L"UI_Window"};
    wstring TitleText{L"DefaultWindow"};
    Size    windowSize{800, 600};
    Point   windowPosition{0, 0};

    bool    IsBlur{false};
    bool    IsCenterAlign{true};
};

class Window : public IVisualObject_InterfaceOnly, public INotify {
  public:
    Window() : IVisualObject_InterfaceOnly(L"UI.Widgets.Window") {};
    virtual void OnPaint(Gdiplus::Graphics&) {};

  public:
    void Initialize();

    void BlurWindow();
    void CenterWindowToScreen();

    LRESULT _Native_WindowsMessageProcessor(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);

    void          SetTitle(wstring);
    const wstring GetTitle();

    void SetID(wstring);
    void SetSize(Gdiplus::Size);
    void SetPosition(Gdiplus::Point);
    void SetVisible(bool);
    void SetDisabled(bool);

    const wstring        GetID();
    const Gdiplus::Size  GetSize();
    const Gdiplus::Point GetPosition();
    const bool           GetVisible();
    const bool           GetDisabled();

  public:
    WindowProperties initialWindowProperties{};
};
} // namespace UI
} // namespace MinecraftLauncher

#endif // !_MinecraftLauncher_UI_Window_H_
