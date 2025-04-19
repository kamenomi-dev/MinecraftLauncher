#include "pch.h"
#include "Utils.h"
#include "Text.h"

using namespace Gdiplus;
using namespace Launcher::Components;

void Text::OnPaint(
    Graphics& graphics
) {
    Font         contentFont{L"Segoe UI", 16, FontStyleBold};
    StringFormat centeredFormat{};
    centeredFormat.SetAlignment(StringAlignmentCenter);
    centeredFormat.SetLineAlignment(StringAlignmentCenter);

    SolidBrush brush{Color::Beige};

    graphics.DrawString(
        _textContent.c_str(), _textContent.size(), &contentFont, RectF(0, 0, GetSize().cx, GetSize().cy), &centeredFormat,
        &brush
    );
}

wstring Text::GetContent() {
    return _textContent;
}

void Text::SetContent(
    const wstring& content
) {
    _textContent = content;
    Invalidate();
}

Text* Launcher::Components::text(
    wstring ID, SIZE size, POINT position, const wstring& content
) {
    const auto ptr = new Text;
    ptr->SetID(ID);
    ptr->SetSize(size);
    ptr->SetPosition(position);

    ptr->SetContent(content);

    return ptr;
}