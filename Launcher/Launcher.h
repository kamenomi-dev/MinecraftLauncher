#pragma once

#define LAUNCHER_WINDOW_CLASS L"Kamenomi.MinecraftLauncher"

#ifndef __LAUNCHER_H__
#define __LAUNCHER_H__

namespace Launcher {
class LauncherWindow : public Utils::WindowWrapper {
  public:
    LauncherWindow(HINSTANCE);

    static bool WindowsMessageProcessor(HWND, UINT, WPARAM, LPARAM, LRESULT&);
    void        OnPaint(Gdiplus::Graphics&, bool);
};
} // namespace Launcher

#endif // !__LAUNCHER_H__
