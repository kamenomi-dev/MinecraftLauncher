#pragma once
#ifndef _MinecraftLauncher_UI_UI_H_
#define _MinecraftLauncher_UI_UI_H_

namespace MinecraftLauncher {
namespace UI {

class Window;

bool Initialize();
void Uninitialize();
bool IsInitializedUI();

void CreateUIWindow(Window*);
} // namespace UI
} // namespace MinecraftLauncher

#endif // !_MinecraftLauncher_UI_UI_H_
