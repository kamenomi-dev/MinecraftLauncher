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

BOOL APIENTRY DllMain(
    HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved
) {
    switch (ulReasonForCall) {
    case DLL_PROCESS_ATTACH: {
        DisableThreadLibraryCalls(hModule);
        IsGUIThread(TRUE);

        if (!InitializeGdiplus(true)) {
            NotifyError(L"Couldn't initialize Gdiplus library. ");
        }
    }
    case DLL_PROCESS_DETACH:
        if (!InitializeGdiplus(false)) {
            NotifyError(L"Undetected error: Gdiplus hadn't inited yet. ");
        }
        break;
    }
    return TRUE;
}
