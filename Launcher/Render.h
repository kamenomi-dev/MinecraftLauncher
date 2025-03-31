#pragma once

#ifndef __RENDER_H__
#define __RENDER_H__

class SwapBuffer {
  public:
    SwapBuffer(HWND hWnd, bool bLayered = false);
    ~SwapBuffer();

    void Present();

    void UpdateSize(LPARAM);
    void UpdatePosition(LPARAM);

    HDC GetGraphicsDC() const { return _hVirtualDC; }

  private:
    void _UpdateBitmap();

    bool    _bLayered{false};
    HDC     _hOriginDC{nullptr};
    HWND    _hOriginWnd{nullptr};
    SIZE    _szOriginWnd{};
    POINT   _posOriginWnd{};
    HDC     _hVirtualDC{nullptr};
    HBITMAP _hCurrVirtualBitmap{nullptr};
    HBITMAP _hLastVirtualBitmap{nullptr};
};

#endif // !__RENDER_H__
