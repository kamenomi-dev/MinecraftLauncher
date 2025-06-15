#pragma once

#ifndef _MinecraftLauncher_UI_Utils_H_
#define _MinecraftLauncher_UI_Utils_H_

namespace MinecraftLauncher {
namespace UI {
namespace Utils {
template <typename Type>
class DoublyLinkedNode {
  public:
    DoublyLinkedNode() : {};
    DoublyLinkedNode(Type* val) : Node(val) {};
    DoublyLinkedNode(Type* val, DoublyLinkedNode<Type>& prev) : Node(val), PrevNode(&prev) {};
    DoublyLinkedNode(Type* val, DoublyLinkedNode<Type>& prev, DoublyLinkedNode<Type>& next)
    : Node(val),
      PrevNode(&prev),
      NextNode(&next) {};

    ~DoublyLinkedNode() {
        if (PrevNode) {
            PrevNode->NextNode = NextNode;
        }

        if (NextNode) {
            NextNode->PrevNode = PrevNode;
        }

        Node = {};
    }

    auto* operator--() { return PrevNode; }
    auto* operator++() { return NextNode; }

    void operator-=(
        Type* val
    ) {
        PrevNode = new DoublyLinkedNode{val};
    }
    void operator+=(
        Type* val
    ) {
        NextNode = new DoublyLinkedNode{val};
    }

    DoublyLinkedNode*     PrevNode{nullptr};
    DoublyLinkedNode*     NextNode{nullptr};
    std::unique_ptr<Type> Node{};

    DoublyLinkedNode(const DoublyLinkedNode&)            = delete;
    DoublyLinkedNode& operator=(const DoublyLinkedNode&) = delete;
};
} // namespace Utils
} // namespace UI
} // namespace MinecraftLauncher

#endif // !_MinecraftLauncher_UI_Utils_H_
