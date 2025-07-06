#pragma once
#include <Utils/Noncopyable.h>
#include <Components/Base.h>

namespace UIFramework {
namespace Components {

class ContainerComponent : public Component {
  public:
    ContainerComponent();
    ~ContainerComponent();

    void Render(Gdiplus::Graphics& graphics) {};
    HDC  RenderContainer();

  protected:
    HDC     containerDC{nullptr};
    HBITMAP containerBitmap{nullptr};
    HBITMAP containerPrevBitmap{nullptr};
};

class Container : public Utils::Noncopyable {
  public:
    void Insert(Component*);

  protected:
    ContainerComponent _ContainerComponent{};
};
} // namespace Components
} // namespace UIFramework