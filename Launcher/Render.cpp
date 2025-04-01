#include "pch.h"
#include "Render.h"

SwapBuffer::SwapBuffer(
    HWND hWnd, bool bLayered
) {
    _bLayered   = bLayered;
    _hOriginWnd = hWnd;

    if (!bLayered) {
        _hOriginDC = GetDC(hWnd);
    } else {
        _hOriginDC = GetWindowDC(hWnd);
    }
    _hVirtualDC = CreateCompatibleDC(_hOriginDC);

    /*if (bLayered) {
        RECT rcWnd{};
        GetWindowRect(hWnd, &rcWnd);
        _szOriginWnd.cx = rcWnd.right - rcWnd.left;
        _szOriginWnd.cy = rcWnd.bottom - rcWnd.top;
    }*/

    _UpdateBitmap();
}

SwapBuffer::~SwapBuffer() {
    ReleaseDC(_hOriginWnd, _hOriginDC);

    DeleteBitmap(_hCurrVirtualBitmap);
    SelectBitmap(_hVirtualDC, _hLastVirtualBitmap);
    DeleteDC(_hVirtualDC);

    _hOriginDC   = nullptr;
    _hOriginWnd  = nullptr;
    _szOriginWnd = {};

    _hVirtualDC         = nullptr;
    _hCurrVirtualBitmap = nullptr;
    _hLastVirtualBitmap = nullptr;
}

void SwapBuffer::Present() {
    if (_bLayered) {
        POINT         srcPos{0, 0};
        BLENDFUNCTION blendFunc{};
        blendFunc.AlphaFormat         = AC_SRC_ALPHA;
        blendFunc.BlendFlags          = 0;
        blendFunc.BlendOp             = AC_SRC_OVER;
        blendFunc.SourceConstantAlpha = 255;

        /*AlphaBlend(
            _hOriginDC, 0, 0, _szOriginWnd.cx, _szOriginWnd.cy, _hVirtualDC, 0, 0, _szOriginWnd.cx, _szOriginWnd.cy,
            blendFunc
        );*/
        UpdateLayeredWindow(
            _hOriginWnd, nullptr, &_posOriginWnd, &_szOriginWnd, _hVirtualDC, &srcPos, NULL, &blendFunc, ULW_ALPHA
        );
        return;
    }
    BitBlt(_hOriginDC, 0, 0, _szOriginWnd.cx, _szOriginWnd.cy, _hVirtualDC, 0, 0, SRCCOPY);
}

void SwapBuffer::UpdateSize(
    LPARAM lParam
) {
    _szOriginWnd.cx = GET_X_LPARAM(lParam);
    _szOriginWnd.cy = GET_Y_LPARAM(lParam);
    _UpdateBitmap();
}

void SwapBuffer::UpdatePosition(
    LPARAM lParam
) {
    _posOriginWnd.x = GET_X_LPARAM(lParam);
    _posOriginWnd.y = GET_Y_LPARAM(lParam);
}

inline static HBITMAP CreateVirtualBitmap(HDC hDc, SIZE szGrap);
void                  SwapBuffer::_UpdateBitmap() {
    if (_hLastVirtualBitmap) {
        DeleteBitmap(_hCurrVirtualBitmap);
        _hCurrVirtualBitmap = nullptr;
    }

    _hCurrVirtualBitmap = CreateVirtualBitmap(_hOriginDC, _szOriginWnd);
    if (_hLastVirtualBitmap) SelectBitmap(_hVirtualDC, _hCurrVirtualBitmap);
    else _hLastVirtualBitmap = SelectBitmap(_hVirtualDC, _hCurrVirtualBitmap);
}

inline static HBITMAP CreateVirtualBitmap(
    HDC hDC, SIZE szGrap
) {
    if (szGrap.cx == 0 || szGrap.cy == 0) {
        return nullptr;
    }

    BITMAPINFO bmpInfo{0};
    bmpInfo.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth       = szGrap.cx;
    bmpInfo.bmiHeader.biHeight      = -szGrap.cy;
    bmpInfo.bmiHeader.biPlanes      = 1;
    bmpInfo.bmiHeader.biBitCount    = 32;
    bmpInfo.bmiHeader.biCompression = BI_RGB;

    // It's likely that rgb data could be hooked.
    void*   pBits   = nullptr;
    HBITMAP hBitmap = CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, &pBits, NULL, 0);
    if (hBitmap == nullptr) {
        // Create bitmap failed.
        auto lastError = GetLastError();
        OutputDebugStringA("Failed to create DIB section for swapchain. ");
        abort();
    }

    return hBitmap;
}