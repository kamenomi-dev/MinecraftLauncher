#include "pch.h"
#include "UI.h"

using namespace MinecraftLauncher;

static ULONG_PTR _pGdiToken{NULL};

bool UI::Initialize() {
    Gdiplus::GdiplusStartupInput input{};
    if (Gdiplus::GdiplusStartup(&_pGdiToken, &input, nullptr) != Gdiplus::Ok) {
        return false;
    }

    return true;
}

void UI::Uninitialize() {
    if (_pGdiToken != NULL) {
        Gdiplus::GdiplusShutdown(_pGdiToken);
        _pGdiToken = NULL;
    }
}

bool UI::IsInitializedUI() {
    return _pGdiToken != NULL;
}
