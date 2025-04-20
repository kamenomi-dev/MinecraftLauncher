#include "pch.h"
// #include "Utils.h"
#include "Text.h"

using namespace Gdiplus;
using namespace Launcher::Components;

void Text::OnPaint(
    Graphics& graphics
) {
    Font         contentFont{L"Segoe UI", 16, FontStyleBold};
    StringFormat centeredFormat{};
    centeredFormat.SetAlignment((StringAlignment)_statusFlags.VerticalAligment);
    centeredFormat.SetLineAlignment((StringAlignment)_statusFlags.HorizonalAligment);

    SolidBrush brush{Color::Beige};

    graphics.DrawString(
        _textContent.c_str(), _textContent.size(), &contentFont, RectF(0, 0, GetSize().cx, GetSize().cy),
        &centeredFormat, &brush
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

TextHorzionalAlignmentStyles Text::GetHorzionalAligement() const {
    return (TextHorzionalAlignmentStyles)(_statusFlags.HorizonalAligment);
}

void Text::SetHorzionalAligement(
    const TextHorzionalAlignmentStyles alignment
) {
    _statusFlags.HorizonalAligment = (UCHAR)alignment;
}

TextVerticalAlignmentStyles Text::GetVerticalAligement() const {
    return (TextVerticalAlignmentStyles)(_statusFlags.VerticalAligment);
}

void Text::SetVerticalAligement(
    const TextVerticalAlignmentStyles alignment
) {
    _statusFlags.VerticalAligment = (UCHAR)alignment;
}

Text* Launcher::Components::text(
    wstring ID, POINT position, SIZE size, const wstring& content, const TextHorzionalAlignmentStyles hor,
    const TextVerticalAlignmentStyles ver
) {
    const auto ptr = new Text;
    ptr->SetID(ID);
    ptr->SetSize(size);
    ptr->SetPosition(position);

    ptr->SetContent(content);
    ptr->SetHorzionalAligement(hor);
    ptr->SetVerticalAligement(ver);

    return ptr;
}