#pragma once

#ifndef _UIFramework_Components_Window_Window_H_
#define _UIFramework_Components_Window_Window_H_

namespace UIFramework {
namespace Components {
class Window : public Utils::Noncopyable {
  public:
    std::unique_ptr<Utils::DoubleBuffer> doubleBuffer = nullptr;
};
} // namespace Components
} // namespace UIFramework

#endif // !_UIFramework_Components_Window_Window_H_
