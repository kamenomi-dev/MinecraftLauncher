#pragma once

#ifndef _Component_Base_H_
#define _Component_Base_H_

namespace Launcher {

namespace Components {

class Base {

    struct ComponentNodeStruct {
        Base* prior;
        Base* next;

        Base* root;
        Base* parent;
        Base* childFirst;
    };

    struct LastNodeStatusStruct {
        Base* parent;
        Base* prior;
        Base* next;
    };

  public:
    ~Base();

    // Invalidating self component is to update itself status.
    void         Invalidate();
    virtual void OnPaint(Gdiplus::Graphics&) {};

    virtual void OnDestroy() {};

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

    __declspec(property(get = GetID)) wstring                        ComponentID;
    __declspec(property(get = GetType)) wstring                      ComponentType;
    __declspec(property(get = GetSize, put = SetSize)) SIZE          ComponentSize;
    __declspec(property(get = GetPosition, put = SetPosition)) POINT ComponentPosition;

    // Node Operation
    LastNodeStatusStruct Detach() {
        if (_nodeComp.parent && _nodeComp.parent->_nodeComp.childFirst == this) {
            _nodeComp.parent->_nodeComp.childFirst = _nodeComp.next;
        }

        if (_nodeComp.prior) _nodeComp.prior->_nodeComp.next = _nodeComp.next;
        if (_nodeComp.next) _nodeComp.next->_nodeComp.prior = _nodeComp.prior;

        LastNodeStatusStruct status{};
        status.parent = _nodeComp.parent;
        status.prior  = _nodeComp.prior;
        status.next   = _nodeComp.next;

        _nodeComp.parent = nullptr;
        _nodeComp.prior  = nullptr;
        _nodeComp.next   = nullptr;

        return status;
    }

    // Node Operation Setter Not safe.
    void SetRoot(
        Base* ptr
    ) {
        _nodeComp.root = ptr;
    }
    void SetParent(
        Base* ptr
    ) {
        Detach();
        _nodeComp.parent = ptr;
        if (ptr) {
            auto comp = ptr->_nodeComp.childFirst;

            if (!comp) {
                ptr->_nodeComp.childFirst = this;
                return;
            }

            while (comp) {
                comp = comp++;
            }

            comp->_nodeComp.next = this;
            _nodeComp.prior      = comp;
        }
    }
    void SetPrior(
        Base* ptr
    ) {
        Detach();

        _nodeComp.prior = ptr;
        if (ptr) {
            auto myParent = ptr->_nodeComp.parent;
            if (myParent->_nodeComp.childFirst == ptr) {
                myParent->_nodeComp.childFirst = this;
            }

            ptr->_nodeComp.next = this;
        }
    };
    void SetNext(
        Base* ptr
    ) {
        _nodeComp.next       = ptr;
        ptr->_nodeComp.prior = this;
    };

    void SetChildFirst(
        Base* ptr
    ) {
        _nodeComp.childFirst = ptr;
    }

    Base* operator--() { return GetPrior(); }
    void  operator-=(
        Base* ptr
    ) {
        const auto lastStatus = Detach();

        if (ptr == nullptr) {
            _nodeComp.parent = lastStatus.parent;
            _nodeComp.next   = lastStatus.next;

            // Restore.
            if (_nodeComp.parent && _nodeComp.parent->_nodeComp.childFirst == _nodeComp.next) {
                _nodeComp.parent->_nodeComp.childFirst = this;
            }
            if (_nodeComp.next) _nodeComp.next->_nodeComp.prior = this;

            return;
        }

        _nodeComp.root   = ptr->_nodeComp.root;
        _nodeComp.parent = ptr->_nodeComp.parent;

        if (ptr->_nodeComp.next) {
            auto myNext    = ptr->_nodeComp.next;
            _nodeComp.next = myNext;

            myNext->_nodeComp.prior = this;
        }

        ptr->_nodeComp.next = this;
        _nodeComp.prior     = ptr;
    }

    Base* operator++() { return GetNext(); }
    void  operator+=(
        Base* ptr
    ) {
        const auto lastStatus = Detach();

        if (ptr == nullptr) {
            _nodeComp.parent = lastStatus.parent;
            _nodeComp.prior  = lastStatus.prior;

            if (_nodeComp.prior) _nodeComp.prior->_nodeComp.next = this;
            return;
        }

        _nodeComp.root   = ptr->_nodeComp.root;
        _nodeComp.parent = ptr->_nodeComp.parent;

        if (ptr->_nodeComp.next) {
            auto myNext    = ptr->_nodeComp.next;
            _nodeComp.next = myNext;

            myNext->_nodeComp.prior = this;
        }

        ptr->_nodeComp.next = this;
        _nodeComp.prior     = ptr;
    }

    // Node Operation Getter
    Base* GetRoot() { return _nodeComp.root; }
    Base* GetParent() { return _nodeComp.parent; }
    Base* GetPrior() { return _nodeComp.prior; };
    Base* GetNext() { return _nodeComp.next; };
    Base* GetChildFirst() { return _nodeComp.childFirst; }

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

Base* base(const wstring ID, SIZE size, POINT position);

} // namespace Components
} // namespace Launcher

#endif // _Component_Base_H_