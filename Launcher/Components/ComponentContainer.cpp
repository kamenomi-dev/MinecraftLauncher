#include "pch.h"
#include "ComponentContainer.h"

using namespace Gdiplus;
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

static Base* TryHitTest(
    Base* currVisibleComp, Point targetPoint
) {
    auto currComp = currVisibleComp;
    while (currComp) {
        if (not currComp->Visible || currComp->Disabled) {
            currComp = currComp->GetNext();
            continue;
        }

        auto finalComp = TryHitTest(currComp->GetChildFirst(), targetPoint);
        if (Rect(currComp->GetPosition().x, currComp->GetPosition().y, currComp->GetSize().cx, currComp->GetSize().cy)
                .Contains(targetPoint)) {
            return finalComp == nullptr ? currComp : finalComp;
        }

        return finalComp;

        currComp = currComp->GetNext();
    }

    return nullptr;
}

Base* ComponentContainer::HitTest(
    LPARAM combinedPoint
) {
    return TryHitTest(GetContainer().get(), {GET_X_LPARAM(combinedPoint), GET_Y_LPARAM(combinedPoint)});
}

static void CallRenderer(
    Base* currLayerComp, Graphics& graphics, Rect invalidatedRect
) {
    auto currComp = currLayerComp;
    while (currComp) {
        if (not currComp->Visible) {
            currComp = currComp->GetNext();
            continue;
        }

        auto currRect =
            Rect(currComp->GetPosition().x, currComp->GetPosition().y, currComp->GetSize().cx, currComp->GetSize().cy);

        if (not invalidatedRect.IsEmptyArea()) {
            currRect.Intersect(invalidatedRect);
        }

        const auto status = graphics.Save();
        graphics.TranslateTransform(currRect.X, currRect.Y);
        graphics.SetClip(Rect(0, 0, currRect.Width, currRect.Height));

        currComp->OnPaint(graphics);

        CallRenderer(currComp->GetChildFirst(), graphics, invalidatedRect);

        graphics.Restore(status);

        currComp = currComp->GetNext();
    }
}

void ComponentContainer::CallAllComponentRenderer(
    Graphics& graphics, Rect invalidatedRect
) {
    CallRenderer(GetContainer().get(), graphics, invalidatedRect);
}

unique_ptr<Base>& ComponentContainer::GetContainer() {
    return _pRoot;
}
