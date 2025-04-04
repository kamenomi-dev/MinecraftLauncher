#include "pch.h"
#include "Button.h"

using namespace Launcher::Components;

Button* Launcher::Components::button(
    wstring ID, SIZE size, POINT position, wstring content
) {
    const auto ptr = new Button;
    ptr->SetID(ID);
    ptr->SetType(L"Comp.BUtton");
    ptr->SetSize(size);
    ptr->SetPosition(position);

    return ptr;
}
