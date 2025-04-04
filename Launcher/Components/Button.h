#pragma once

#ifndef _Component_Button_Header_
#define _Component_Button_Header_

#include "Base.h"

namespace Launcher {
namespace Components {
class Button : public Base {

};

Button* button(wstring ID, SIZE size, POINT position, wstring content);

} // namespace Components
} // namespace Launcher

#endif // _Component_Button_Header_