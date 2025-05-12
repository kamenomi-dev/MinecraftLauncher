#pragma once

#ifndef _Component_Button_Header_
#define _Component_Button_Header_

#include "Base.h"

namespace Launcher {
namespace Components {
class Button : public Base {

  private:
    struct ButtonStatus {
        bool isMouseHovered;
        bool isMouseDown;
    };

  public:
    Button() : Base() { SetType(L"Comp.Button"); };

    void OnPaint(Gdiplus::Graphics&);
    void OnNotify(NotificationInformation<>&);

    wstring GetContent();
    void    SetContent(const wstring&);

    __declspec(property(get = GetContent, put = SetContent)) wstring Content;

  private:
    wstring      _textContent{};
    ButtonStatus _btnStatus{};
};

Button* button(wstring ID, Rect rect, const wstring& content = L"Button");

} // namespace Components
} // namespace Launcher

#endif // _Component_Button_Header_