#pragma once
#include "pch.h"
#include "logger.cpp"
#include "Noncopyable.h"

namespace UIFramework {
namespace Utils {
class DoubleBuffer : Noncopyable {
  public:
    DoubleBuffer() = default;
    ~DoubleBuffer() {};

    void BindWindow(
        HWND hWnd
    ) {
        window        = hWnd;
        deviceContext = GetDC(hWnd);

        _isLayered = (GetWindowLongW(hWnd, GWL_EXSTYLE) & WS_EX_LAYERED);

        bufferedDeviceContext = CreateCompatibleDC(deviceContext);
        UpdateSize();
    }

    void UpdateSize() {
        RECT rect{};
        if (!GetWindowRect(window, &rect)) {
            NotifyWarning(
                L"Window size failed to be updated. I don't that how it could be happend but it did it indeed."
            );

            return;
        }

        windowSize.cx = rect.right - rect.left;
        windowSize.cy = rect.bottom - rect.top;

        if (bufferedBitmap) {
            DeleteBitmap(bufferedBitmap);
            bufferedBitmap = nullptr;
        }

        bufferedBitmap = CreateCompatibleBitmap(bufferedDeviceContext, windowSize.cx, windowSize.cy);
        if (!bufferedBitmap) {
            NotifyError(L"Failed to create buffered bitmap. ");
            return;
        }

        if (lastBufferedBitmap) {
            SelectBitmap(bufferedDeviceContext, bufferedBitmap);
            return;
        }

        lastBufferedBitmap = SelectBitmap(bufferedDeviceContext, bufferedBitmap);
    };

    void RefreshLayout() const {
        if (!_isLayered) {
            BitBlt(deviceContext, 0, 0, windowSize.cx, windowSize.cy, bufferedDeviceContext, 0, 0, SRCCOPY);
        }
    };

    HWND window{nullptr};
    SIZE windowSize{};
    HDC  deviceContext{nullptr};

    HBITMAP bufferedBitmap{nullptr};
    HBITMAP lastBufferedBitmap{nullptr};
    HDC     bufferedDeviceContext{nullptr};

  private:
    bool _isLayered;
};
} // namespace Utils
} // namespace UIFramework
