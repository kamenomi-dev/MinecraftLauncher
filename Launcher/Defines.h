#pragma once
#include "./Components/Base.h"

#ifndef __DEFINES_H__
#define __DEFINES_H__

namespace Launcher {
namespace Components {
constexpr auto NOTIFY_COMPONENT_MOVEIN  = L"Notify.Component.MoveIn";
constexpr auto NOTIFY_COMPONENT_MOVEOUT = L"Notify.Component.MoveOut";

template <typename DetailInformation = Base::BaseNotificationInformation>
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