#pragma once

#ifndef _Component_ComponentContainer_h_
#define _Component_ComponentContainer_h_

#include "Base.h"

namespace Launcher {
namespace Components {

class ComponentContainer {
  public:
    ComponentContainer() {
        _pRoot->SetType(L"Comp.Root");
        _pRoot->TagComponentFirst();
    }

    void Push(initializer_list<Base*>);

  private:
    unique_ptr<Base> _pRoot = make_unique<Base>();
};
} // namespace Components
} // namespace Launcher

#endif // _Component_ComponentContainer_h_