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

  public:
    shared_ptr<Gdiplus::Image> _pLoadedImage{};
};
} // namespace Components
} // namespace Launcher

#endif // !_Component_Image_Header_
