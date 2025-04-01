#pragma once

#ifndef __RENDER_H__
#include "Render.h"
#endif // !__RENDER_H__


#ifndef __UTILS_H__
#define __UTILS_H__

namespace Launcher {

class LauncherWindow;

namespace Utils {

namespace System {
struct VersionStruct {
    // NT major version.
    ULONG Major;
    // NT minor version.
    ULONG Minor;
    // Shared collection generation numbers that are not decorated with C or F. GetVersionEx hides real numbers.
    ULONG Build;
};

VersionStruct GetCorrectVersion();
} // namespace System

namespace Window {

enum BlurTypes {
    None,
    Auto,
    Aero,
    Acrylic,
    Mica
};

bool EnableLayeredStyle(HWND, bool);
// It adapts to the platform without manually setting its blur style.
bool EnableBackgroundBlur(HWND, bool bToggle);
bool EnableBackgroundBlur(HWND, bool, BlurTypes);
} // namespace Window

} // namespace Utils
} // namespace Launcher

#endif // __UTILS_H__