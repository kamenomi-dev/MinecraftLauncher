#include "pch.h"
#include "Container.h"

using namespace UIFramework::Components;

void Container::Insert(
    Component* component
) {
    _ContainerComponent.Emplace(component);
}
