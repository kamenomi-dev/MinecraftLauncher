#include "pch.h"
#include "Button.h"

using namespace Gdiplus;
using namespace Launcher::Components;

void Button::OnPaint(
    Graphics& graphics
) {
    Font         contentFont{L"Segoe UI", 16, FontStyleBold};
    StringFormat centeredFormat{};
    centeredFormat.SetAlignment(StringAlignmentCenter);
    centeredFormat.SetLineAlignment(StringAlignmentCenter);

    SolidBrush brush{Color::Beige};

    graphics.Clear(Color::PaleGoldenrod);
    graphics.DrawString(
        _btnContent.c_str(), _btnContent.size(), &contentFont, RectF(0, 0, GetSize().cx, GetSize().cy), &centeredFormat,
        &brush
    );
}

wstring Button::GetContent() {
    return _btnContent;
}

void Button::SetContent(
    const wstring& content
) {
    _btnContent = content;
    Invalidate();
}

Button* Launcher::Components::button(
    wstring ID, SIZE size, POINT position, const wstring& content
) {
    const auto ptr = new Button;
    ptr->SetID(ID);
    ptr->SetSize(size);
    ptr->SetPosition(position);

    ptr->SetContent(content);

    return ptr;
}