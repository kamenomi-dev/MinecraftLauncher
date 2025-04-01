#include "pch.h"
#include "Utils.h"

#include "./Interfaces/User32/WindowCompositionAttribute.h"

using namespace Launcher::Utils;

/// <summary>
/// Gets the correct version on Windows.
/// </summary>
System::VersionStruct System::GetCorrectVersion() {
#ifdef _WINDOWS
    auto sharedUserData = (BYTE*)0x7FFE0000;
    return {*(ULONG*)(sharedUserData + 0x26c), *(ULONG*)(sharedUserData + 0x270), *(ULONG*)(sharedUserData + 0x260)};
#else
    return {
        NULL, NULL, NULL
    }
#endif // _WINDOWS
}

bool Window::EnableLayeredStyle(
   HWND hWnd, bool bToggle
) {
    auto exStyle = GetWindowLongW(hWnd, GWL_EXSTYLE);

    if (bToggle) {
        exStyle |= WS_EX_LAYERED;
    } else {
        exStyle &= ~WS_EX_LAYERED;
    }

    return !!SetWindowLongW(hWnd, GWL_EXSTYLE, exStyle);
}

bool Window::EnableBackgroundBlur(
    HWND hWnd, bool bToggle
) {
    return EnableBackgroundBlur(hWnd, bToggle, BlurTypes::Auto);
}

bool Window::EnableBackgroundBlur(
    HWND hWnd, bool bToggle, BlurTypes type
) {
    const auto version = System::GetCorrectVersion();
    // Lower than or equal Windows7.
    if (version.Major < 10 && version.Minor <= 1) {
        DWM_BLURBEHIND blurBehind{};
        blurBehind.dwFlags  = DWM_BB_ENABLE;
        blurBehind.fEnable  = bToggle;
        blurBehind.hRgnBlur = NULL;

        return SUCCEEDED(DwmEnableBlurBehindWindow(hWnd, &blurBehind));
    }

    // Hight than Windows 7 and lower than Windows 11.
    if ((type != BlurTypes::Mica) || version.Build < 22000) {
        using namespace Launcher::Interfaces::User32;

        // User32 is already loaded; otherwise, the window cannot be created.
        const auto hUser32 = GetModuleHandleW(L"User32.dll");

        auto setWindowCompositionAttribute =
            (pfnSetWindowCompositionAttribute)GetProcAddress(hUser32, "SetWindowCompositionAttribute");

        if (setWindowCompositionAttribute == nullptr) {
            return false;
        }

        ACCENT_POLICY accent{ACCENT_ENABLE_BLURBEHIND, NULL};
        if (type == BlurTypes::Acrylic || (type == BlurTypes::Auto && version.Major == 10)) {
            // accent.AccentState = ACCENT_ENABLE_ACRYLICBLURBEHIND;
            OutputDebugStringA("Acrylic has a lag bug on Windows 10, so using Aero actually. \n");
        }

        if (!bToggle) {
            accent.AccentState = ACCENT_DISABLED;
        }

        WINDOWCOMPOSITIONATTRIBDATA data{};
        data.Attrib = WCA_ACCENT_POLICY;
        data.pvData = &accent;
        data.cbData = sizeof(accent);

        auto ret = setWindowCompositionAttribute(hWnd, &data);
        return ret;
    }

    // DWMWA_MICA_EFFECT 1029
    return SUCCEEDED(DwmSetWindowAttribute(hWnd, 1029, &bToggle, sizeof bToggle));
}
