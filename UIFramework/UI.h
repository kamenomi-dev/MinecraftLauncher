#pragma once
#include "pch.h"
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
    InitializeLogger();
    spdlog::info("Success to initialize logger. ");

    if (!InitializeGdiplus(true)) {
        NotifyError(L"Couldn't initialize Gdiplus library. ");
    }
    spdlog::info("Success to initialize Gdiplus. ");
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
    
    spdlog::info("Exited. ");
    UninitializeLogger();

    return (UINT)systemMessage.wParam;
}
} // namespace UIFramework