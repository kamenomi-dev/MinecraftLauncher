#pragma once
#ifndef _MinecraftLauncher_UI_Window_H_
#define _MinecraftLauncher_UI_Window_H_

#include "Basis.h"

namespace MinecraftLauncher {
namespace UI {
class Window : public IVisualObject_InterfaceOnly {
  public:
    virtual void OnPaint(Gdiplus::Graphics&) {};

  protected:
    Window() : IVisualObject_InterfaceOnly(L"UI.Widgets.Window") {};

    void Initialize();

    void          SetTitle(wstring);
    const wstring GetTitle();

    void SetID(wstring);
    void SetSize(Gdiplus::Size);
    void SetPosition(Gdiplus::Point);
    void SetVisible(bool);
    void SetDisabled(bool);

    const wstring        GetID();
    const wstring        GetType();
    const Gdiplus::Size  GetSize();
    const Gdiplus::Point GetPosition();
    const bool           GetVisible();
    const bool           GetDisabled();
};
} // namespace UI
} // namespace MinecraftLauncher

#endif // !_MinecraftLauncher_UI_Window_H_
