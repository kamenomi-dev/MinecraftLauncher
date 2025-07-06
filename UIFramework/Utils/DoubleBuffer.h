#pragma once
#include "pch.h"
#include "logger.cpp"
#include "Noncopyable.h"

namespace UIFramework {
namespace Utils {
class DoubleBuffer : Noncopyable {
  public:
    DoubleBuffer() = default;
    ~DoubleBuffer() {
        if (memoryBitmap) {
            SelectBitmap(memoryDeviceContext, memoryPrevBitmap);
            DeleteBitmap(memoryBitmap);
            DeleteDC(memoryDeviceContext);
        }

        if (windowDeviceContext) {
            ReleaseDC(window, windowDeviceContext);
        }

        memoryDeviceContext = nullptr;
        memoryBitmap = memoryPrevBitmap = nullptr;

        window              = nullptr;
        windowDeviceContext = nullptr;
    };

    void BindWindow(
        HWND hWnd
    ) {
        window              = hWnd;
        windowDeviceContext = GetDC(hWnd);

        _isLayered = (GetWindowLongW(hWnd, GWL_EXSTYLE) & WS_EX_LAYERED);

        memoryDeviceContext = CreateCompatibleDC(windowDeviceContext);
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

        if (memoryBitmap) {
            DeleteBitmap(memoryBitmap);
            memoryBitmap = nullptr;
        }

        memoryBitmap = CreateCompatibleBitmap(memoryDeviceContext, windowSize.cx, windowSize.cy);
        if (!memoryBitmap) {
            NotifyError(L"Failed to create buffered bitmap. ");
            return;
        }

        if (memoryPrevBitmap) {
            SelectBitmap(memoryDeviceContext, memoryBitmap);
            return;
        }

        memoryPrevBitmap = SelectBitmap(memoryDeviceContext, memoryBitmap);
    };

    void RefreshLayout() const {
        if (!_isLayered) {
            BitBlt(windowDeviceContext, 0, 0, windowSize.cx, windowSize.cy, memoryDeviceContext, 0, 0, SRCCOPY);
        }
    };
    void RefreshLayout(
        RECT rcPaint
    ) const {
        if (!_isLayered) {
            BitBlt(
                windowDeviceContext, rcPaint.left, rcPaint.top, rcPaint.bottom - rcPaint.top,
                rcPaint.right - rcPaint.left, memoryDeviceContext, 0, 0, SRCCOPY
            );
        }
    };
    void RefreshLayoutToMemory(
        HDC hDC
    ) {
        BitBlt(memoryDeviceContext, 0, 0, windowSize.cx, windowSize.cy, hDC, 0, 0, SRCCOPY);
    }

    HWND window{nullptr};
    SIZE windowSize{};
    HDC  windowDeviceContext{nullptr};

    HBITMAP memoryBitmap{nullptr};
    HBITMAP memoryPrevBitmap{nullptr};
    HDC     memoryDeviceContext{nullptr};

  private:
    bool _isLayered;
};
} // namespace Utils
} // namespace UIFramework
