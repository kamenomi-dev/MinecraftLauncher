#include "pch.h"
#include "Base.h"
#include "Frame.h"
#include "Window.h"
#include "ComponentContainer.h"

using namespace Launcher::Components;

Base::~Base() {
    if (_nodeComp.next) delete _nodeComp.next;
    if (_nodeComp.childFirst) delete _nodeComp.childFirst;
}

void Base::Invalidate() {
    // Todo
    RECT rcWnd{NULL};
    rcWnd.left   = ComponentPosition.x;
    rcWnd.top    = ComponentPosition.y;
    rcWnd.right  = ComponentPosition.x + ComponentSize.cx;
    rcWnd.bottom = ComponentPosition.y + ComponentSize.cy;

    if (_nodeComp.root)
        InvalidateRect((HWND)_nodeComp.root->componentContainer->GetWrapper()->GetRenderableHandle(), &rcWnd, 1);
};

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

void Base::SetSize(
    const SIZE size
) {
    _szComp = size;
}

SIZE Base::GetSize() const {
    return _szComp;
}

void Base::SetPosition(
    const POINT position
) {
    _posComp = position;
}

POINT Base::GetPosition() const {
    return _posComp;
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
    const wstring ID, SIZE size, POINT position
) {
    const auto ptr = new Base;
    ptr->SetID(ID);
    ptr->SetSize(size);
    ptr->SetPosition(position);

    return ptr;
}
