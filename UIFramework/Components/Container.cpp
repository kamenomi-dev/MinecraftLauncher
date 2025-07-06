#include "pch.h"
#include "Container.h"

using namespace UIFramework::Components;

void Container::Insert(
    Component* component
) {
    _ContainerComponent.Emplace(component);
}

ContainerComponent::ContainerComponent() {
    _ComponentData.compType = L"Container";
    containerDC             = CreateCompatibleDC(NULL);
}

ContainerComponent::~ContainerComponent() {
    if (containerPrevBitmap) {
        SelectBitmap(containerDC, containerPrevBitmap);
        DeleteBitmap(containerBitmap);
    }

    if (containerDC) {
        DeleteDC(containerDC);
    }

    containerDC         = nullptr;
    containerPrevBitmap = containerBitmap = nullptr;
}

HDC ContainerComponent::RenderContainer() {
    if (containerPrevBitmap) {
        SelectBitmap(containerDC, containerPrevBitmap);
        DeleteBitmap(containerBitmap);
    }

    containerBitmap = CreateCompatibleBitmap(containerDC, ComponentRect.Width, ComponentRect.Height);
    containerPrevBitmap = SelectBitmap(containerDC, containerBitmap);

    Gdiplus::Graphics graphics{containerDC};

    auto child = GetChildFirst();
    while (child) {
        if (child->ComponentType == L"Container") {
            const auto subContainer   = (ContainerComponent*)child;
            const auto subContainerDC = subContainer->RenderContainer();

            BitBlt(containerDC, 0, 0, ComponentRect.Width, ComponentRect.Height, subContainerDC, 0, 0, SRCCOPY);

            child = child->GetNext();
            continue;
        }

        child->Render(graphics);

        child = child->GetNext();
    }

    return containerDC;
}
