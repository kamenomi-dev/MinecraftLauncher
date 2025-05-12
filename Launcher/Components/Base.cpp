#include "pch.h"
#include "Base.h"
#include "Frame.h"
#include "Window.h"
#include "ComponentContainer.h"

using namespace Gdiplus;

using namespace Launcher::Components;

Base::~Base() {
    if (_nodeComp.next) delete _nodeComp.next;
    if (_nodeComp.childFirst) delete _nodeComp.childFirst;
}

void Base::Invalidate() {
    // Todo
    RECT rcWnd{NULL};
    rcWnd.left   = ComponentPosition.X;
    rcWnd.top    = ComponentPosition.Y;
    rcWnd.right  = ComponentPosition.X + ComponentSize.Width;
    rcWnd.bottom = ComponentPosition.Y + ComponentSize.Height;

    if (_nodeComp.root)
        InvalidateRect((HWND)_nodeComp.root->componentContainer->GetWrapper()->GetRenderableHandle(), &rcWnd, 1);
};

bool Base::TryHitTest(
    const Gdiplus::Point rawTarget
) {
    // auto target = ConvertAbsoluteToRelative(rawTarget);
    return _RectComp.Contains(rawTarget);
}

void Base::SetID(
    const wstring id
) {
    if (_bInited) {
        OutputDebugStringA("Component.Base's ID couldn't be set after having inited.");
        abort();
    }

    _idComp = id;
}

wstring Base::GetID() const {
    return _idComp;
}

void Base::SetType(
    const wstring type
) {
    if (_bInited) {
        OutputDebugStringA("Component.Base's Type couldn't be set after having inited.");
        abort();
    }

    _tyComp = type;
}

wstring Base::GetType() const {
    return _tyComp;
}

void Base::SetRect(
    const Rect rect
) {
    _RectComp = rect;
}

Rect& Base::GetRect() {
    return _RectComp;
}

void Base::SetSize(
    const Size size
) {
    _RectComp.Width = size.Width;
    _RectComp.Height = size.Height;
}

Size Base::GetSize() const {
    Size szComp{};
    _RectComp.GetSize(&szComp);

    return szComp;
}

void Base::SetPosition(
    const Point position
) {
    _RectComp.X = position.X;
    _RectComp.Y = position.Y;
}

Point Base::GetPosition() const {
    Point ptPos{};
    _RectComp.GetLocation(&ptPos);

    return ptPos;
}

void Base::SetVisible(
    const bool status
) {
    _bVisible = status;
}

bool Base::GetVisible() const {
    return _bVisible;
}

void Base::SetDisabled(
    const bool status
) {
    _bDisabled = status;
}

bool Base::GetDisabled() const {
    return _bDisabled;
}

void Base::TagComponentFirst() {
    if (_bInited) {
        OutputDebugStringA("Component.Base's \"bFirst\" tag couldn't be set after having inited.");
        abort();
    }

    _bFirst = true;
}

bool Base::IsFristComponent() const {
    return _bFirst;
}

void Base::TagComponentLast() {
    if (_bInited) {
        OutputDebugStringA("Component.Base's \"bLast\" tag couldn't be set after having inited.");
        abort();
    }

    _bLast = true;
}

bool Base::IsLastComponent() const {
    return _bLast;
}

Base* Launcher::Components::base(
    const wstring ID, Rect rect
) {
    const auto ptr = new Base;
    ptr->SetID(ID);
    ptr->SetRect(rect);

    return ptr;
}
