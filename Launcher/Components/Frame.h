#pragma once

#ifndef _Component_Frame_H_
#define _Component_Frame_H_

#include "Base.h"
#include "ComponentContainer.h"

namespace Launcher {
namespace Components {

class Frame : public Base {
  public:
    Frame(
        ComponentContainer* container
    )
    : Base() {
        SetType(L"Comp.Frame");
        componentContainer = container;
    };

    ComponentContainer* componentContainer;
};
} // namespace Components
} // namespace Launcher

#endif // !_Component_Frame_H_
