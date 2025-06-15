#pragma once

#ifndef _UIFramework_WindowManager_H_
#define _UIFramework_WindowManager_H_

namespace UIFramework {
class WindowManager : public Utils::Singleton<WindowManager> {
    friend class Utils::Singleton<WindowManager>;

  public:
    Components::Window& CreateNewWindow() {}

    std::list<Components::Window> windowList{};
};
} // namespace UIFramework

#endif // !_UIFramework_WindowManager_H_
