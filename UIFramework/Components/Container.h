#pragma once
#include <Utils/Noncopyable.h>
#include <Components/Base.h>

namespace UIFramework {
namespace Components {

class ContainerComponent : public Component {
  public:
    bool IsRoot = true;
};

class Container : public Utils::Noncopyable {
  public:
    void Insert(Component*);

  private:
    ContainerComponent _ContainerComponent{};
};
} // namespace Components
} // namespace UIFramework