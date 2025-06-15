#pragma once

#ifndef _UIFramework_Utils_DoublyLinkedNode_H_
#define _UIFramework_Utils_DoublyLinkedNode_H_

#include "Logger.cpp"

namespace UIFramework {
namespace Utils {
template <typename DataType>
class DoublyLinkedNode {
  public:
    DoublyLinkedNode();
    ~DoublyLinkedNode() { Detach(*this); };

    static void Detach(
        DoublyLinkedNode& node
    ) {
        const auto prev = node._Prev;
        const auto next = node._Next;

        if (node._Next) node._Next->_Prev = prev;
        if (node._Prev) node._Prev->_Next = next;
    };

    static void DestoryChain(
        DoublyLinkedNode& node
    ) {
        NotifyWarning(L"Destorying chain may influence program working... ");

        auto firstNode = &node;
        while (firstNode->GetPrev()) {
            firstNode = firstNode->GetPrev();
        }

        auto currentNode = firstNode;
        while (currentNode) {
            auto next = currentNode->GetNext();
            delete currentNode;
            currentNode = next;
        }
    }

    DoublyLinkedNode* GetPrev() { return _Prev; }
    DoublyLinkedNode* GetNext() { return _Next; }

    DoublyLinkedNode* operator--() { return _Prev; }
    DoublyLinkedNode* operator++() { return _Next; }

    DoublyLinkedNode*         _Prev{nullptr};
    DoublyLinkedNode*         _Next{nullptr};
    std::shared_ptr<DataType> _Val{};
};
} // namespace Utils
} // namespace UIFramework

#endif // !_UIFramework_Utils_DoublyLinkedNode_H_
