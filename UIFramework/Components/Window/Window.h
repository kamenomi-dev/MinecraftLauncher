#pragma once
#include <Utils/Noncopyable.h>
#include <Utils/DoubleBuffer.h>

namespace UIFramework {
namespace Components {
class Window : public Utils::Noncopyable {
  public:
    Window();
    ~Window();

    void Initialize(
        const wstring& = L"I am a Window.", Rect = {0, 0, 800, 600}, UINT = WS_OVERLAPPEDWINDOW, UINT = WS_EX_APPWINDOW
    );
    void Close();
    void Show() const;
    void Hide() const;

    bool _Native_WindowsMessageProcessor(HWND, UINT, WPARAM, LPARAM, LRESULT&);

    static LRESULT WindowsMessageProcessor(HWND, UINT, WPARAM, LPARAM);

  private:
    HWND                                 windowHandle{nullptr};
    std::unique_ptr<Utils::DoubleBuffer> doubleBuffer{nullptr};
};
} // namespace Components
} // namespace UIFramework
