#include "pch.h"

#include "./Window.h"
#include "UI.h"

using namespace MinecraftLauncher;

static ULONG_PTR               _gdipToken{NULL};
static UI::WindowControlBlock* _windowControlBlockFirst{nullptr};

extern HINSTANCE UI::processInstance{};

static LRESULT WindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

static void InitializeWindowInstance(
    UI::WindowControlBlock* wcb
) {
    auto window = wcb->currentWindow;

    const auto& classText = window->initialWindowProperties.ClassText;
    WNDCLASSEXW classInfo{};
    classInfo.cbSize        = sizeof WNDCLASSEXW;
    classInfo.style         = CS_HREDRAW | CS_VREDRAW;
    classInfo.hInstance     = UI::processInstance;
    classInfo.lpfnWndProc   = WindowsMessageProcessor;
    classInfo.lpszClassName = classText.c_str();

    RegisterClassExW(&classInfo);

    window->Initialize();
    wcb->isInitialized = true;
}

bool UI::Initialize(
    HINSTANCE hInstance
) {
    Gdiplus::GdiplusStartupInput input{};
    if (Gdiplus::GdiplusStartup(&_gdipToken, &input, nullptr) != Gdiplus::Ok) {
        return false;
    }

    auto wcb = _windowControlBlockFirst;
    do {
        InitializeWindowInstance(wcb);
        wcb = wcb->NextWCB;
    } while (wcb->NextWCB);

    return true;
}

void UI::Uninitialize() {
    if (_gdipToken != NULL) {
        Gdiplus::GdiplusShutdown(_gdipToken);
        _gdipToken = NULL;
    }
}

bool UI::IsInitializedUI() {
    return _gdipToken != NULL;
}

void UI::CreateUIWindow(
    Window* window
) {
    auto* wcb          = new WindowControlBlock;
    wcb->currentWindow = window;

    if (_windowControlBlockFirst == nullptr) {
        _windowControlBlockFirst = wcb;
    } else {
        auto tempWcb = _windowControlBlockFirst;

        while (tempWcb->NextWCB) {
            tempWcb = tempWcb->NextWCB;
        }

        tempWcb->NextWCB = wcb;
        wcb->PrevWCB     = tempWcb;
    }
}
