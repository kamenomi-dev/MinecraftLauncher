#pragma once
#include <Utils/Noncopyable.h>

namespace UIFramework {
namespace Components {
class Container;

class Component : public Utils::Noncopyable {

    struct CompoentNodeStructure {
        Component* _root       = nullptr;
        Component* _parent     = nullptr;
        Component* _childFirst = nullptr;
        Component* _next       = nullptr;
        Component* _previous   = nullptr;
    };

  public:
    ~Component() { DestroyTree(); };

    void DestroyTree() {
        auto currentComp = GetChildFirst();
        while (currentComp) {
            auto targetComp = currentComp;
            currentComp     = currentComp->GetNext();

            delete targetComp;
        }
    };

    void SeparateAll() {
        // Separate from root
        GetRootRef() = nullptr;

        SeparateNearRelation();
    }

    void SeparateNearRelation() {
        // Separate from parent
        if (auto& parent = GetParentRef()) {
            auto& parentFirstChild = parent->GetChildFirstRef();
            if (parentFirstChild == this) {
                parentFirstChild = GetNext();
            }

            parent = nullptr;
        }

        // Separate from sibling
        if (GetPrevious()) {
            GetPrevious()->GetNextRef() = GetNext();
        }
        if (GetNext()) {
            GetNext()->GetPreviousRef() = GetPrevious();
        }

        GetPreviousRef() = GetNextRef() = nullptr;
    }


    void Parentify(
        Component* parent
    ) {
        SeparateAll();

        auto& childFirst = parent->GetChildFirstRef();
        if (childFirst) {
            auto end = childFirst;

            while (auto next = end->GetNext()) {
                end = next;
            }

            end->GetNextRef() = this;
            GetPreviousRef()  = end;
        } else {
            childFirst = this;
        }

        GetRootRef()   = parent->GetRoot();
        GetParentRef() = parent;
    }

    void Emplace(
        Component* child, UINT index = -1
    ) {
        child->SeparateNearRelation();

        if (index == -1 || GetChildFirst() == nullptr) {
            child->Parentify(this); // Automatically insert into the end.
            return;
        }

        //
        // Case 1: The position of child is inserted at position-0
        //  id : |      0      |    1    |    2    |    3    |
        // name:   Child First   child 1   child 2   child 3
        //       ^
        //       | Insert here.
        //
        // Case 2: The position of child isn't inserted at position-0
        //  id : |    ...    |  .. N-1   |   N ..  |    ...    |
        // name:   child ...   child N-1   child N   child ...
        //                               ^
        //                               | Insert here.
        //

        Component* insertPointer{GetChildFirst()};
        for (UINT idx = 0; idx < index; idx++) {
            insertPointer = insertPointer->GetNext();

            if (!insertPointer->GetNext()) {
                break;
            }
        }

        if (index == 0) {
            GetChildFirstRef() = child;
        }

        child->GetParentRef()                      = this;
        child->GetNextRef()                        = insertPointer;
        child->GetPreviousRef()                    = insertPointer->GetPrevious();
        insertPointer->GetNext()->GetPreviousRef() = child;
    }

    Component* GetRoot() { return _nodeStruct._root; };
    Component* GetParent() { return _nodeStruct._parent; };
    Component* GetChildFirst() { return _nodeStruct._childFirst; };
    Component* GetNext() { return _nodeStruct._next; };
    Component* GetPrevious() { return _nodeStruct._previous; };

    Component*& GetRootRef() { return _nodeStruct._root; };
    Component*& GetParentRef() { return _nodeStruct._parent; };
    Component*& GetChildFirstRef() { return _nodeStruct._childFirst; };
    Component*& GetNextRef() { return _nodeStruct._next; };
    Component*& GetPreviousRef() { return _nodeStruct._previous; };

  public:
    bool IsRoot = {false};

  private:
    CompoentNodeStructure _nodeStruct{nullptr};
};
} // namespace Components
} // namespace UIFramework