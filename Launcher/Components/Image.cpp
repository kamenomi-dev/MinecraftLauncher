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

    const auto scaleFactor = CalculateFitInsideScale();

    // Skip rendering if comopnent size is unset.
    if (scaleFactor == 0.0f) {
        return;
    }

    const auto image{_pLoadedImage.get()};
    struct {
        float offsetX;
        float offsetY;
        float cx;
        float cy;
    } vec4{0.f, 0.f, 0.f, 0.f};

    vec4.cx = std::roundf(image->GetWidth() * scaleFactor);
    vec4.cy = std::roundf(image->GetHeight() * scaleFactor);
    if (vec4.cx < 1) vec4.cx = 1;
    if (vec4.cy < 1) vec4.cy = 1;

    vec4.offsetX = (ComponentSize.Width - vec4.cx) / 2;
    vec4.offsetY = (ComponentSize.Height - vec4.cy) / 2;

    graphics.DrawImage(image, vec4.offsetX, vec4.offsetY, vec4.cx, vec4.cy);
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
}

float Image::CalculateFitInsideScale() {
    if (ComponentSize.Width == 0 || ComponentSize.Height == 0) {
        OutputDebugStringA("Error: Image component cannot work well since ComponentSize is {0, 0}");
        return 0.0f;
    }

    float sizeRatioByWidth  = (ComponentSize.Width * 1.f) / (_pLoadedImage->GetWidth() * 1.f);
    float sizeRatioByHeight = (ComponentSize.Height * 1.f) / (_pLoadedImage->GetHeight() * 1.f);

    return std::min<float>(sizeRatioByWidth, sizeRatioByHeight);
};

Image* Launcher::Components::image(
    wstring ID, Rect rect, const WCHAR* file
) {
    const auto ptr = new Image;
    ptr->SetID(ID);
    ptr->SetRect(rect);

    ptr->SetImage(file);

    return ptr;
}
