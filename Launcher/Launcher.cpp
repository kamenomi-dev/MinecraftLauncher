#include "pch.h"
#include "Defines.h"
#include "Utils.h"
#include "Render.h"

#include "./Components/Frame.h"
#include "./Components/Window.h"
#include "./Components/Button.h"
#include "./Components/Text.h"
#include "./Components/Image.h" // 2025-05-18: Image added.

#include "Launcher.h"

using namespace Launcher;
using namespace Launcher::Components;

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow
) {
    LauncherWindow main{hInstance};
    main.Push(
        {Components::button(L"test.button", {200, 200, 200, 100}, L"I'm a button."),
         Components::text(L"↖", {0, 0, 200, 200}, L"↖", TextHorzionalAlignmentTop, TextVerticalAlignmentLeft),
         Components::text(L"↑", {0, 0, 200, 200}, L"↑", TextHorzionalAlignmentTop, TextVerticalAlignmentMiddle),
         Components::text(L"↗", {0, 0, 200, 200}, L"↗", TextHorzionalAlignmentTop, TextVerticalAlignmentRight),
         Components::text(L"←", {0, 0, 200, 200}, L"←", TextHorzionalAlignmentMiddle, TextVerticalAlignmentLeft),
         Components::text(L"♥", {0, 0, 200, 200}, L"♥", TextHorzionalAlignmentMiddle, TextVerticalAlignmentMiddle),
         Components::text(L"→", {0, 0, 200, 200}, L"→", TextHorzionalAlignmentMiddle, TextVerticalAlignmentRight),
         Components::text(L"↙", {0, 0, 200, 200}, L"↙", TextHorzionalAlignmentBottom, TextVerticalAlignmentLeft),
         Components::text(L"↓", {0, 0, 200, 200}, L"↓", TextHorzionalAlignmentBottom, TextVerticalAlignmentMiddle),
         Components::text(L"↘", {0, 0, 200, 200}, L"↘", TextHorzionalAlignmentBottom, TextVerticalAlignmentRight),
         Components::image(L"comp.image.0", {0, 0, 64, 64}, L"<Input your file path here.>")}
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

    static auto image = static_cast<Components::Image*>(
        static_cast<Frame*>(notify.Emitter)->componentContainer->FindComponentByID(L"comp.image.0")
    );

    if (notify.NotifyType == Components::NOTIFY_COMPONENT_MOUSECLICK) {
        MessageBoxW(notify.OriginalData.hWnd, notify.Emitter->ComponentID.c_str(), L"Clicked", S_OK);
    }

    if (notify.NotifyType == Components::NOTIFY_COMPONENT_MOUSEMOVE) {
        Size mousePt{GET_X_LPARAM(notify.OriginalData.lParam), GET_Y_LPARAM(notify.OriginalData.lParam)};

        image->SetSize(mousePt);
    }
}

void LauncherWindow::OnPaint(
    Gdiplus::Graphics& grap
) {
    grap.Clear(Gdiplus::Color::CornflowerBlue);
}
