#pragma once
#include <Utils/Noncopyable.h>

namespace UIFramework {
namespace Components {
class Container : public Utils::Noncopyable {
  public:
    void Insert(Component);
  private:
    Component _ContainerComponent{};
};
} // namespace Components
} // namespace UIFramework