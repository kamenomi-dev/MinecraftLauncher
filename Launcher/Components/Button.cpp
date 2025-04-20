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

    graphics.Clear(_btnStatus.isMouseDown ? Color(56, 56, 56) : (_btnStatus.isMouseHovered ? Color(61, 61, 61) : Color(31, 31, 31)));
    graphics.DrawString(
        _textContent.c_str(), _textContent.size(), &contentFont, RectF(0, 0, GetSize().cx, GetSize().cy), &centeredFormat,
        &brush
    );
}

void Button::OnNotify(
    NotificationInformation<>& notify
) {
    if (lstrcmpW(notify.NotifyType, NOTIFY_COMPONENT_MOVEIN) == 0 or lstrcmpW(notify.NotifyType, NOTIFY_COMPONENT_MOVEOUT) == 0) {
        _btnStatus.isMouseHovered = (lstrcmpW(notify.NotifyType, NOTIFY_COMPONENT_MOVEIN) == 0);
        Invalidate();
    }

    if (lstrcmpW(notify.NotifyType, NOTIFY_COMPONENT_MOUSEUP) == 0 or lstrcmpW(notify.NotifyType, NOTIFY_COMPONENT_MOUSEDOWN) == 0) {
        _btnStatus.isMouseDown = (lstrcmpW(notify.NotifyType, NOTIFY_COMPONENT_MOUSEDOWN) == 0);
        Invalidate();
    }
}

wstring Button::GetContent() {
    return _textContent;
}

void Button::SetContent(
    const wstring& content
) {
    _textContent = content;
    Invalidate();
}

Button* Launcher::Components::button(
    wstring ID, POINT position, SIZE size, const wstring& content
) {
    const auto ptr = new Button;
    ptr->SetID(ID);
    ptr->SetSize(size);
    ptr->SetPosition(position);

    ptr->SetContent(content);

    return ptr;
}