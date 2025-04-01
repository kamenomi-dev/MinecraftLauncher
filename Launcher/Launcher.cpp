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
    main.Initialize();
    main.Run(nCmdShow);

    return LauncherWindow::MessageLoop();
}

LauncherWindow::LauncherWindow(
    HINSTANCE hInstance
)
: WindowWrapper(hInstance, LAUNCHER_WINDOW_CLASS, L"MinecraftLauncher", LauncherWindow::WindowsMessageProcessor) {
    this->SetSize({800, 600});
};

bool LauncherWindow::WindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& result
) {
    result = NULL;
    return false;
}

void Launcher::LauncherWindow::OnCreate(
    bool b
) {
    if (b) return;

    Utils::Window::EnableBackgroundBlur(hWindow, true);
}

void LauncherWindow::OnPaint(
    Gdiplus::Graphics& grap, bool isNonClient
) {
    if (isNonClient) {
        return;
    }

    grap.Clear(Gdiplus::Color(100, 123, 23, 20));
}
