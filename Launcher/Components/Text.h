#pragma once

#ifndef _Component_Button_Header_
#define _Component_Button_Header_

#include "Base.h"

namespace Launcher {
namespace Components {
class Text : public Base {
  public:
    Text() : Base() { SetType(L"Comp.Text"); };

    void OnPaint(Gdiplus::Graphics&);

    wstring GetContent();
    void    SetContent(const wstring&);

    __declspec(property(get = GetContent, put = SetContent)) wstring Content;

  private:
    wstring           _textContent{};
    Utils::FlagBits_i _statusFlagBits{};
};

Text* text(wstring ID, SIZE size, POINT position, const wstring& content = L"text");

} // namespace Components
} // namespace Launcher

#endif // _Component_Button_Header_