#include "pch.h"

static void NotifyError(
    const wstring content
) {
    OutputDebugStringW((L"[UI] [Error]" + content).c_str());
    MessageBoxW(NULL, content.c_str(), L"UI Framework error! ", MB_OK);
    abort();
}

static void NotifyWarning(
    const wstring content
) {
    OutputDebugStringW((L"[UI] [Warning]" + content).c_str());
    // MessageBoxW(NULL, content.c_str(), L"UI Framework error! ", MB_OK);
    // abort();
}
