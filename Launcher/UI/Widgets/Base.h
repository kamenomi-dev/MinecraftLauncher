#pragma once

#ifndef _MinecraftLauncher_UI_Widgets_Base_H_
#define _MinecraftLauncher_UI_Widgets_Base_H_

#include "../Basis.h"

namespace MinecraftLauncher {
namespace UI {
namespace Widgets {
class Base : public IVisualObject {
    void Initialize();

    void OnPaint(Gdiplus::Graphics&);

    void SetID(wstring);
    void SetType(wstring);
    void SetSize(Gdiplus::Size);
    void SetPosition(Gdiplus::Point);

    const wstring        GetID();
    const wstring        GetType();
    const Gdiplus::Size  GetSize();
    const Gdiplus::Point GetPosition();
};
} // namespace Widgets
} // namespace UI
} // namespace MinecraftLauncher
#endif // !_MinecraftLauncher_UI_Widgets_Base_H_
