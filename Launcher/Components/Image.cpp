#include "pch.h"
#include "Image.h"

namespace Gdip = Gdiplus;

using namespace Launcher::Components;

void Image::OnPaint(
    Gdiplus::Graphics& graphics
) {

    // If not loaded.
    if (!_pLoadedImage) {
        return;
    }

    // graphics.DrawImage(_pLoadedImage.get());
}

void Image::SetImage(
    IStream* stream
) {
    _pLoadedImage.reset(Gdip::Image::FromStream(stream));
};

void Image::SetImage(
    const WCHAR* file
) {
    _pLoadedImage.reset(Gdip::Image::FromFile(file));
};