#include "pch.h"
#include "ComponentContainer.h"

using namespace Launcher::Components;

void ComponentContainer::Push(
    initializer_list<Base*> components
) {
    for (auto component : components) {
        component->SetParent(_pRoot.get());
    }
}
