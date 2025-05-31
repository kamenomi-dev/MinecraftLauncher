#pragma once
#ifndef _MinecraftLauncher_UI_UI_H_
#define _MinecraftLauncher_UI_UI_H_

namespace MinecraftLauncher {
namespace UI {

class Window;

struct WindowControlBlock {
    WindowControlBlock* PrevWCB{nullptr};
    WindowControlBlock* NextWCB{nullptr};

    bool isInitialized{false};

    HWND    windowHandle{nullptr};
    Window* currentWindow{nullptr};
};

bool Initialize(HINSTANCE hInstance, int nCmdShow = SW_SHOW);
void Uninitialize();
bool IsInitializedUI();

void CreateUIWindow(Window*);

extern HINSTANCE processInstance;
} // namespace UI
} // namespace MinecraftLauncher

#endif // !_MinecraftLauncher_UI_UI_H_
