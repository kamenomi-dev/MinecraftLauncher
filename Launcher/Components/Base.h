#pragma once

#ifndef _Component_Base_H_
#define _Component_Base_H_

namespace Launcher {

namespace Components {

class Base {

    struct ComponentNodeStruct {
        union Vertical {
            Base* first;
            Base* last;
            Base* next;
            Base* end;
        };

        union Horizontal {
            Base* parent;
            Base* childFirst;
            Base* childEnd;
        };
    };

  public:
    // Invalidating self component is to update itself status.
    void         Invalidate();
    virtual void OnPaint(Gdiplus::Graphics&) {};

    void    SetID(const wstring);
    wstring GetID() const;
    void    SetType(const wstring);
    wstring GetType() const;
    void    SetSize(const SIZE);
    SIZE    GetSize() const;
    void    SetPosition(const POINT);
    POINT   GetPosition() const;

    void TagComponentFirst();
    bool IsFristComponent() const;
    void TagComponentLast();
    bool IsLastComponent() const;

    __declspec(property(get = GetID)) SIZE                           ComponentID;
    __declspec(property(get = GetType)) SIZE                         ComponentType;
    __declspec(property(get = GetSize, put = SetSize)) SIZE          ComponentSize;
    __declspec(property(get = GetPosition, put = SetPosition)) POINT ComponentPosition;

  private:
    bool _bFirst{false};
    bool _bLast{false};
    bool _bInited{false};

    ComponentNodeStruct _nodeComp{};
    wstring             _idComp{};
    wstring             _tyComp{};
    SIZE                _szComp{};
    POINT               _posComp{};
};

Base* base(
    const wstring ID, SIZE size, POINT position
) {
    const auto ptr = new Base;
    ptr->SetID(ID);
    ptr->SetType(L"Comp.Base");
    ptr->SetSize(size);
    ptr->SetPosition(position);

    return ptr;
}

} // namespace Components
} // namespace Launcher

#endif // _Component_Base_H_