#pragma once

#define LAUNCHER_WINDOW_CLASS L"Kamenomi.MinecraftLauncher"

#ifndef __LAUNCHER_H__
#define __LAUNCHER_H__

namespace Launcher {
class LauncherWindow : public Components::WindowWrapper {
  public:
    LauncherWindow(HINSTANCE);

    static bool WindowsMessageProcessor(HWND, UINT, WPARAM, LPARAM, LRESULT&);
    void        OnCreate(bool);
    void        OnPaint(Gdiplus::Graphics&);
};
} // namespace Launcher

#endif // !__LAUNCHER_H__
