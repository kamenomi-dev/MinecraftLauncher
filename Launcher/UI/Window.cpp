#include "pch.h"
#include "Window.h"

using namespace MinecraftLauncher::UI;

void Window::Initialize() {
    const auto& props = initialWindowProperties;

}

void Window::SetTitle(
    wstring
) {}

const wstring Window::GetTitle() {
    return wstring();
}

void Window::SetID(
    wstring
) {}

void Window::SetSize(
    Gdiplus::Size
) {}

void Window::SetPosition(
    Gdiplus::Point
) {}

void Window::SetVisible(
    bool
) {}

void Window::SetDisabled(
    bool
) {}

const wstring Window::GetID() {
    return wstring();
}

const wstring Window::GetType() {
    return wstring();
}

const Gdiplus::Size Window::GetSize() {
    return Gdiplus::Size();
}

const Gdiplus::Point Window::GetPosition() {
    return Gdiplus::Point();
}

const bool Window::GetVisible() {
    return false;
}

const bool Window::GetDisabled() {
    return false;
}
