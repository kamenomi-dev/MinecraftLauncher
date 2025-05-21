#pragma once

#ifndef _MinecraftLauncher_UI_Basis_H_
#define _MinecraftLauncher_UI_Basis_H_

namespace MinecraftLauncher {
namespace UI {

struct StatusFlags {
    bool Visible        : 1;
    bool Disabled       : 1;
    bool Independent    : 1;
    bool NonInheritable : 1;
};

class IVisualObject /* abstract */ {
  public:
    virtual void Initialize() = 0;

    virtual void OnPaint(Gdiplus::Graphics&) = 0;

    virtual void SetID(wstring&)             = 0;
    virtual void SetType(wstring&)           = 0;
    virtual void SetSize(Gdiplus::Size)      = 0;
    virtual void SetPosition(Gdiplus::Point) = 0;
    virtual void SetVisible(bool)            = 0;
    virtual void SetDisabled(bool)           = 0;

    virtual const wstring        GetID()       = 0;
    virtual const wstring        GetType()     = 0;
    virtual const Gdiplus::Size  GetSize()     = 0;
    virtual const Gdiplus::Point GetPosition() = 0;
    virtual const bool           GetVisible()  = 0;
    virtual const bool           GetDisabled() = 0;

  private:
    StatusFlags _statusFlags{};
};
} // namespace UI
} // namespace MinecraftLauncher

#endif // !_MinecraftLauncher_UI_Basis_H_
