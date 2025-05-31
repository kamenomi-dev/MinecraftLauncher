#pragma once

#ifndef _MinecraftLauncher_UI_Utils_H_
#define _MinecraftLauncher_UI_Utils_H_

namespace MinecraftLauncher {
namespace UI {
namespace Utils {
template <typename Type>
class DoublyLinkedNode {
  public:
    DoublyLinkedNode(Type val) : Node(val) {};
    DoublyLinkedNode(Type val, DoublyLinkedNode<Type>& prev, DoublyLinkedNode<Type>& next)
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

    DoublyLinkedNode* PrevNode{nullptr};
    DoublyLinkedNode* NextNode{nullptr};
    std::shared_ptr<Type>  Node{};
};
} // namespace Utils
} // namespace UI
} // namespace MinecraftLauncher

#endif // !_MinecraftLauncher_UI_Utils_H_
