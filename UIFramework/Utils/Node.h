#pragma once
#include "pch.h"
#include "Noncopyable.h"

namespace UIFramework {
namespace Utils {
class Node : Noncopyable {

  public:
    Node* GetRoot() { return _root; };
    Node* GetParent() { return _parent; };
    Node* GetChildFirst() { return _childFirst; };
    Node* GetNext() { return _next; };
    Node* GetPrevious() { return _previous; };

  private:
    Node* _root       = nullptr;
    Node* _parent     = nullptr;
    Node* _childFirst = nullptr;
    Node* _next       = nullptr;
    Node* _previous   = nullptr;
};
} // namespace Utils
} // namespace UIFramework