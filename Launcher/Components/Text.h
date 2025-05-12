#pragma once

#ifndef _Component_Text_Header_
#define _Component_Text_Header_

#include "Base.h"

namespace Launcher {
namespace Components {

enum TextVerticalAlignmentStyles : UCHAR {
    TextVerticalAlignmentLeft = 0,
    TextVerticalAlignmentMiddle,
    TextVerticalAlignmentRight
};

enum TextHorzionalAlignmentStyles : UCHAR {
    TextHorzionalAlignmentTop = 0,
    TextHorzionalAlignmentMiddle,
    TextHorzionalAlignmentBottom
};

// TextStatus, storaging the Text style.
// desc: HorizonalLeft and VerticalTop will be enabled when
//       other Horizional-xxx and Vertical-xxx properties aren't enabled.
struct TextStatus {
    UCHAR HorizonalAligment : 2;
    UCHAR VerticalAligment  : 2;
};

class Text : public Base {
  public:
    Text() : Base() { SetType(L"Comp.Text"); };

    void OnPaint(Gdiplus::Graphics&);

    bool TryHitTest(
        const Gdiplus::Point
    ) {
        // NOTICE: A Text component should not be tried hit test.
        return false;
    };

    wstring GetContent();
    void    SetContent(const wstring&);

    TextHorzionalAlignmentStyles GetHorzionalAligement() const;
    void                         SetHorzionalAligement(const TextHorzionalAlignmentStyles alignment);
    TextVerticalAlignmentStyles  GetVerticalAligement() const;
    void                         SetVerticalAligement(const TextVerticalAlignmentStyles alignment);

    __declspec(property(get = GetContent, put = SetContent)) wstring Content;

  private:
    wstring    _textContent{};
    TextStatus _statusFlags{NULL};
};

Text* text(
    wstring ID, Rect rect, const wstring& content = L"text",
    const TextHorzionalAlignmentStyles = TextHorzionalAlignmentTop,
    const TextVerticalAlignmentStyles  = TextVerticalAlignmentLeft
);

} // namespace Components
} // namespace Launcher

#endif // _Component_Text_Header_