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

    virtual void SetID(const wstring)              = 0;
    virtual void SetType(const wstring)            = 0;
    virtual void SetSize(const Gdiplus::Size)      = 0;
    virtual void SetPosition(const Gdiplus::Point) = 0;

    virtual const wstring        GetID()       = 0;
    virtual const wstring        GetType()     = 0;
    virtual const Gdiplus::Size  GetSize()     = 0;
    virtual const Gdiplus::Point GetPosition() = 0;

  private:
    StatusFlags _statusFlags{};
};
} // namespace UI
} // namespace MinecraftLauncher

#endif // !_MinecraftLauncher_UI_Basis_H_
