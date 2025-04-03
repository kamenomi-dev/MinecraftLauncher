#pragma once

#ifndef _Component_Button_Header_
#define _Component_Button_Header_

namespace Launcher {
namespace Components {
class Button : public Base {

};

Button* button(
    wstring ID, SIZE size, POINT position, wstring content
) {
    const auto ptr = new Button;
    ptr->SetID(ID);
    ptr->SetType(L"Comp.BUtton");
    ptr->SetSize(size);
    ptr->SetPosition(position);

    return ptr;
}

} // namespace Components
} // namespace Launcher

#endif // _Component_Button_Header_