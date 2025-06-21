#pragma once
#include "pch.h"

static void _Private_ErrorHandler(
    const string& reason
) {
    MessageBoxA(NULL, reason.c_str(), "UI Framework error! ", MB_OK);
    abort();
}

static void InitializeLogger() {
    spdlog::set_error_handler(_Private_ErrorHandler);
};

static inline void NotifyError(
    const wstring content
) {
    auto lastError = GetLastError();
    spdlog::error(L"Caused to A error by {c}, code is {d}!", content.c_str(), lastError);
}

static inline void NotifyWarning(
    const wstring content
) {
    spdlog::warn(content.c_str());
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