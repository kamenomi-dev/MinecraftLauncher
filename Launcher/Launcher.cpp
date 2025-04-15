#include "pch.h"
#include "Utils.h"
#include "Render.h"

#include "./Components/Window.h"

#include "Launcher.h"

using namespace Launcher;

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow
) {
    LauncherWindow main{hInstance};
    main.Push({Components::button(L"test.button", {200, 100}, {200, 200}, L"Hello")});

    main.Initialize();
    main.Run(nCmdShow);

    return LauncherWindow::MessageLoop();
}

LauncherWindow::LauncherWindow(
    HINSTANCE hInstance
)
: WindowWrapper(hInstance, LAUNCHER_WINDOW_CLASS, L"MinecraftLauncher", LauncherWindow::WindowsMessageProcessor) {
    this->SetSize({800, 600});
    this->SetPosition(true);
};

bool LauncherWindow::WindowsMessageProcessor(
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

void LauncherWindow::OnPaint(
    Gdiplus::Graphics& grap
) {
    grap.Clear(Gdiplus::Color(255, rand() % 255, 23, 20));
}
