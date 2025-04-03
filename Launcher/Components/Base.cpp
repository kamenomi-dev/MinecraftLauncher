#include "pch.h"
#include "Base.h"

using namespace Launcher::Components;

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

