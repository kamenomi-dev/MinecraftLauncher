#pragma once

#ifndef _Component_Button_Header_
#define _Component_Button_Header_

#include "Base.h"

namespace Launcher {
namespace Components {
class Button : public Base {
  public:
    void OnPaint(Gdiplus::Graphics&);

    wstring GetContent();
    void    SetContent(const wstring&);

    __declspec(property(get = GetContent, put = SetContent)) wstring Content;

  private:
    wstring _btnContent{};
};

Button* button(wstring ID, SIZE size, POINT position, const wstring& content = L"Button");

} // namespace Components
} // namespace Launcher

#endif // _Component_Button_Header_