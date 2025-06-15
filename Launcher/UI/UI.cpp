#include "pch.h"

#include "./Window.h"
#include "Utils.h"
#include "UI.h"

using namespace MinecraftLauncher;

static ULONG_PTR                                           _gdipToken{NULL};
static UI::Utils::DoublyLinkedNode<UI::WindowControlBlock> _WCB_First{};

extern HINSTANCE UI::processInstance{};

static LRESULT WindowsMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
    auto currentTargetWindow = ;

    if (uMsg == WM_CREATE) {
        auto wnd = (UI::Window*)(void*)(lParam);
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

inline static void InitializeWindowInstance(
    UI::Utils::DoublyLinkedNode<UI::WindowControlBlock>* wcb, int nCmdShow
) {
    auto window = wcb->Node->currentWindow;

    auto hWnd                = window->Initialize(UI::processInstance, WindowsMessageProcessor, nCmdShow);
    wcb->Node->windowHandle  = hWnd;
    wcb->Node->isInitialized = true;
}

bool UI::Initialize(
    HINSTANCE hInstance, int nCmdShow
) {
    Gdiplus::GdiplusStartupInput input{};
    if (Gdiplus::GdiplusStartup(&_gdipToken, &input, nullptr) != Gdiplus::Ok) {
        return false;
    }

    auto wcb = &_WCB_First;
    while (wcb++) {
        InitializeWindowInstance(wcb, nCmdShow);
        wcb = wcb++;
    };

    return true;
}

void UI::Uninitialize() {

    auto currentWcb = &_WCB_First;
    do {
        const auto next = currentWcb++;

        const wstring classText = currentWcb->Node->currentWindow->initialWindowProperties.ClassText;

        currentWcb->Node->isInitialized = false;
        delete currentWcb->Node->currentWindow;

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

    if (!_WCB_First.Node) {
        _WCB_First.Node.reset(wcb);
    } else {
        auto* tempWcb = &_WCB_First;

        while (tempWcb++) {
            tempWcb = tempWcb++;
        }

        (*tempWcb)                  += wcb;
        tempWcb->NextNode->PrevNode  = tempWcb;
    }
}
