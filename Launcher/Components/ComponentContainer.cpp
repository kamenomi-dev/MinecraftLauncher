#include "pch.h"
#include "ComponentContainer.h"

using namespace Launcher::Components;

ComponentContainer::ComponentContainer() {
    _pRoot->SetType(L"Comp.Root");
    _pRoot->TagComponentFirst();
}

void ComponentContainer::Push(
    initializer_list<Base*> components
) {
    for (auto component : components) {
        component->SetParent(_pRoot.get());
    }
}

unique_ptr<Base>& ComponentContainer::GetContainer() {
    return _pRoot;
}
