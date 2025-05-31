#include "pch.h"

#include "./Window.h"
#include "UI.h"

using namespace MinecraftLauncher;

static ULONG_PTR               _gdipToken{NULL};
static UI::WindowControlBlock* _WCB_First{nullptr};

extern HINSTANCE UI::processInstance{};

static LRESULT WindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
    auto currentTargetWindow =;

    if (uMsg == WM_CREATE) {
        auto wnd = (UI::Window*)(void*)(lParam);
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

inline static void InitializeWindowInstance(
    UI::WindowControlBlock* wcb, int nCmdShow
) {
    auto window = wcb->currentWindow;

    auto hWnd          = window->Initialize(UI::processInstance, WindowsMessageProcessor, nCmdShow);
    wcb->windowHandle  = hWnd;
    wcb->isInitialized = true;
}

bool UI::Initialize(
    HINSTANCE hInstance, int nCmdShow
) {
    Gdiplus::GdiplusStartupInput input{};
    if (Gdiplus::GdiplusStartup(&_gdipToken, &input, nullptr) != Gdiplus::Ok) {
        return false;
    }

    auto wcb = _WCB_First;
    do {
        InitializeWindowInstance(wcb, nCmdShow);
        wcb = wcb->NextWCB;
    } while (wcb->NextWCB);

    return true;
}

void UI::Uninitialize() {

    auto currentWcb = _WCB_First;
    do {
        const auto next = currentWcb->NextWCB;

        const wstring classText = currentWcb->currentWindow->initialWindowProperties.ClassText;

        currentWcb->isInitialized = false;
        delete currentWcb->currentWindow;

        UnregisterClassW(classText.c_str(), processInstance);

        delete currentWcb;
        currentWcb = next;
    } while (currentWcb);

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

    if (_WCB_First == nullptr) {
        _WCB_First = wcb;
    } else {
        auto tempWcb = _WCB_First;

        while (tempWcb->NextWCB) {
            tempWcb = tempWcb->NextWCB;
        }

        tempWcb->NextWCB = wcb;
        wcb->PrevWCB     = tempWcb;
    }
}
