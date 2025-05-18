#pragma once

#ifndef _Component_Image_Header_
#define _Component_Image_Header_

#include "Base.h"

namespace Launcher {
namespace Components {
class Image : public Base {

  public:
    Image() : Base() { SetType(L"Comp.Image"); }

    void OnPaint(Gdiplus::Graphics&);

    void SetImage(IStream* stream);
    void SetImage(const WCHAR* file);

    float CalculateFitInsideScale();

  public:
    shared_ptr<Gdiplus::Image> _pLoadedImage{};
};

Image* image(wstring ID, Rect rect, const WCHAR* file);

} // namespace Components
} // namespace Launcher

#endif // !_Component_Image_Header_
