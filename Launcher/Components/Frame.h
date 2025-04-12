#pragma once

#ifndef _Component_Frame_H_
#define _Component_Frame_H_

#include "Base.h"

namespace Launcher {
namespace Components {
class Frame : public Base {
  public:
    Frame() : Base() { SetType(L"Comp.Frame"); };
};
} // namespace Components
} // namespace Launcher

#endif // !_Component_Frame_H_
