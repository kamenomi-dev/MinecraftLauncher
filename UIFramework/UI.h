#pragma once
#include "Logger.cpp"

static bool InitializeGdiplus(
    bool bInit
) {
    static ULONG_PTR gdipToken{NULL};

    if (bInit) {
        if (gdipToken != NULL) {
            return false;
        }

        Gdiplus::GdiplusStartupInput startupInput{nullptr};
        return Gdiplus::GdiplusStartup(&gdipToken, &startupInput, nullptr) == Gdiplus::Ok;
    }

    if (gdipToken) {
        Gdiplus::GdiplusShutdown(gdipToken);
    };

    return gdipToken != NULL;
};

namespace UIFramework {
inline void UiInitialize() {
    if (!InitializeGdiplus(true)) {
        NotifyError(L"Couldn't initialize Gdiplus library. ");
    }
};

inline void _Private_UiUninitialize() {
    if (!InitializeGdiplus(false)) {
        NotifyError(L"Undetected error: Gdiplus hadn't initialized yet. ");
    }
};

inline UINT Startup() {
    MSG systemMessage{};
    while (GetMessageW(&systemMessage, nullptr, NULL, NULL)) {
        TranslateMessage(&systemMessage);
        DispatchMessageW(&systemMessage);
    }

    _Private_UiUninitialize();
    return systemMessage.wParam;
}
} // namespace UIFramework