#pragma once
#include "pch.h"

static inline void NotifyError(
    const wstring content
) {
    auto lastError = GetLastError();
    OutputDebugStringW((L"[UI] [Error:" + std::to_wstring(lastError) + L"]" + content).c_str());
    MessageBoxW(NULL, content.c_str(), L"UI Framework error! ", MB_OK);
    abort();
}

static inline void NotifyWarning(
    const wstring content
) {
    OutputDebugStringW((L"[UI] [Warning]" + content).c_str());
    // MessageBoxW(NULL, content.c_str(), L"UI Framework error! ", MB_OK);
    // abort();
}

// Check result if any including Boolean LResult Long, etc.
static inline void CheckAnyResult(
    long result
) {
    if (result == NULL) {
        return;
    }

    NotifyError(L"Unknown Error! More info to see in the debugger. ");
}