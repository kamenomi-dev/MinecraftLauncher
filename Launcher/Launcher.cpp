﻿#include "pch.h"
#include "Defines.h"
#include "Utils.h"
#include "Render.h"

#include "./Components/Window.h"
#include "./Components/Button.h"
#include "./Components/Text.h"

#include "Launcher.h"

using namespace Launcher;
using namespace Launcher::Components;

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow
) {
    LauncherWindow main{hInstance};
    main.Push(
        {Components::button(L"test.button", {200, 200}, {200, 100}, L"I'm a button."),
         Components::text(L"↖", {0, 0}, {200, 200}, L"↖", TextHorzionalAlignmentTop, TextVerticalAlignmentLeft),
         Components::text(L"↑", {0, 0}, {200, 200}, L"↑", TextHorzionalAlignmentTop, TextVerticalAlignmentMiddle),
         Components::text(L"↗", {0, 0}, {200, 200}, L"↗", TextHorzionalAlignmentTop, TextVerticalAlignmentRight),
         Components::text(L"←", {0, 0}, {200, 200}, L"←", TextHorzionalAlignmentMiddle, TextVerticalAlignmentLeft),
         Components::text(L"♥", {0, 0}, {200, 200}, L"♥", TextHorzionalAlignmentMiddle, TextVerticalAlignmentMiddle),
         Components::text(L"→", {0, 0}, {200, 200}, L"→", TextHorzionalAlignmentMiddle, TextVerticalAlignmentRight),
         Components::text(L"↙", {0, 0}, {200, 200}, L"↙", TextHorzionalAlignmentBottom, TextVerticalAlignmentLeft),
         Components::text(L"↓", {0, 0}, {200, 200}, L"↓", TextHorzionalAlignmentBottom, TextVerticalAlignmentMiddle),
         Components::text(L"↘", {0, 0}, {200, 200}, L"↘", TextHorzionalAlignmentBottom, TextVerticalAlignmentRight)}
    );

    main.Initialize();
    main.Run(nCmdShow);

    return LauncherWindow::MessageLoop();
}

LauncherWindow::LauncherWindow(
    HINSTANCE hInstance
)
: WindowWrapper(hInstance, LAUNCHER_WINDOW_CLASS, L"MinecraftLauncher", LauncherWindow::SystemMessageProcessor) {
    this->SetSize({800, 600});
    this->SetPosition(true);
    this->RegisterNotificationReceiver(OnNotify);
};

bool LauncherWindow::SystemMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& result
) {

    if (uMsg == WM_NCCALCSIZE) {
        // return true;
    }

    result = NULL;
    return false;
}

void LauncherWindow::OnCreate(
    bool b
) {
    if (b) return;

    // Utils::Window::EnableBackgroundBlur(hWindow, true);
}

void LauncherWindow::OnNotify(
    Components::NotificationInformation<>& notify
) {
    cos(1);

    if (notify.NotifyType == Components::NOTIFY_COMPONENT_MOUSECLICK) {
        MessageBoxW(notify.OriginalData.hWnd, notify.Emitter->ComponentID.c_str(), L"Clicked", S_OK);
    }
}

void LauncherWindow::OnPaint(
    Gdiplus::Graphics& grap
) {
    grap.Clear(Gdiplus::Color::CornflowerBlue);
}
