#pragma once

#ifndef __DEFINES_H__
#define __DEFINES_H__

namespace Launcher {
namespace Components {
constexpr auto NOTIFY_COMPONENT_MOVEIN  = L"Notify.Component.MoveIn";
constexpr auto NOTIFY_COMPONENT_MOVEOUT = L"Notify.Component.MoveOut";

constexpr auto NOTIFY_COMPONENT_MOUSEUP          = L"Notify.Component.MouseUp";
constexpr auto NOTIFY_COMPONENT_MOUSEDOWN        = L"Notify.Component.MouseDown";
constexpr auto NOTIFY_COMPONENT_MOUSEMOVE        = L"Notify.Component.MouseMove";
constexpr auto NOTIFY_COMPONENT_MOUSECLICK       = L"Notify.Component.MouseClick";
constexpr auto NOTIFY_COMPONENT_MOUSEDOUBLECLICK = L"Notify.Component.MouseDoubleClick";

class Base;
struct BaseNotificationInformation;

template <typename DetailInformation = BaseNotificationInformation>
struct NotificationInformation {
    const wchar_t*    NotifyType;
    Base*             Emitter;
    DetailInformation Data;

    struct {
        HWND   hWnd;
        UINT   uMsg;
        WPARAM wParam;
        LPARAM lParam;
    } OriginalData;
};
} // namespace Components
} // namespace Launcher

#endif