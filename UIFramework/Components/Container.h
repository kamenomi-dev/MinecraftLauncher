#pragma once
#include <Utils/Noncopyable.h>
#include <Include/st_tree/st_tree.h>

namespace UIFramework {
namespace Components {
class Container : public Utils::Noncopyable {
  private:
    typedef st_tree::tree<Component, st_tree::ordered<>> _TyComponentTree;
    typedef _TyComponentTree::iterator                   iterator;
    typedef _TyComponentTree::node_type::iterator        node_iterator;

    _TyComponentTree _componentTree{};
};
} // namespace Components
} // namespace UIFramework