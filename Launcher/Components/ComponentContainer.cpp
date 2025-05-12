#include "pch.h"
#include "Defines.h"
#include "ComponentContainer.h"

#include "Base.h"
#include "Frame.h"
#include "Window.h"

using namespace Gdiplus;
using namespace Launcher::Components;

ComponentContainer::ComponentContainer() {
    _pRoot = make_unique<Frame>(this);
    _pRoot->SetType(L"Comp.Root");
    _pRoot->TagComponentFirst();
    _pRoot->Initialize();
}

void ComponentContainer::ConnectWindow(
    Interface_BaseWrapper* wrapper
) {
    _pConnectedWindow = wrapper;
}

void ComponentContainer::RegisterNotificationReceiver(
    NotificationReceiver* receiver
) {
    _notificationReceivers.push_back(receiver);
}

void ComponentContainer::Push(
    initializer_list<Base*> components
) {
    for (auto component : components) {
        component->SetRoot(_pRoot.get());
        component->SetParent(_pRoot.get());
        component->Initialize();
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


        if (currComp->TryHitTest(targetPoint)) {
            const auto childComp = TryHitTest(currComp->GetChildFirst(), targetPoint);

            return childComp == nullptr ? currComp : childComp;
        }

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

        const auto& currRect = currComp->GetRect();
        /* if (not invalidatedRect.IsEmptyArea()) {
             graphics.SetClip(invalidatedRect);
         }*/

        const auto status = graphics.Save();
        graphics.TranslateTransform(currRect.X, currRect.Y);
        graphics.SetClip(Rect(0, 0, currRect.Width, currRect.Height));

        currComp->OnPaint(graphics);

        CallRenderer(currComp->GetChildFirst(), graphics, invalidatedRect);

        graphics.ResetClip();
        graphics.ResetTransform();
        graphics.Restore(status);

        currComp = currComp->GetNext();
    }
}

bool ComponentContainer::SystemMessageProcessor(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult
) {
    NotificationInformation<> notifyInfo{NULL};

    notifyInfo.OriginalData = {hWnd, uMsg, wParam, lParam};

    if (uMsg == WM_MOUSEMOVE) {
        auto currComp = HitTest(lParam);
        if (currComp == _statusInfo.pCurrHoveredComp) {
            return NULL;
        }

        _statusInfo.pPrevHoveredComp = _statusInfo.pCurrHoveredComp;
        _statusInfo.pCurrHoveredComp = currComp;

        if (_statusInfo.pPrevHoveredComp) {
            notifyInfo.Emitter    = _statusInfo.pPrevHoveredComp;
            notifyInfo.NotifyType = NOTIFY_COMPONENT_MOVEOUT;
            CallAllNotificationReceivers(notifyInfo);
        }

        if (_statusInfo.pCurrHoveredComp) {
            notifyInfo.Emitter    = _statusInfo.pCurrHoveredComp;
            notifyInfo.NotifyType = NOTIFY_COMPONENT_MOVEIN;
            CallAllNotificationReceivers(notifyInfo);
        }

        return true;
    }


    static Base* draggingComponent{nullptr};
    if (uMsg == WM_LBUTTONDOWN) {
        notifyInfo.Emitter    = HitTest(lParam);
        notifyInfo.NotifyType = NOTIFY_COMPONENT_MOUSEDOWN;
        CallAllNotificationReceivers(notifyInfo);

        draggingComponent = notifyInfo.Emitter;
    }

    if (uMsg == WM_LBUTTONUP) {
        notifyInfo.Emitter = draggingComponent;
        if (draggingComponent == nullptr) {
            notifyInfo.Emitter = HitTest(lParam);
        }

        notifyInfo.NotifyType = NOTIFY_COMPONENT_MOUSEUP;
        CallAllNotificationReceivers(notifyInfo);

        notifyInfo.NotifyType = NOTIFY_COMPONENT_MOUSECLICK;
        CallAllNotificationReceivers(notifyInfo);
    }

    if (uMsg == WM_LBUTTONDBLCLK) {
        notifyInfo.Emitter    = HitTest(lParam);
        notifyInfo.NotifyType = NOTIFY_COMPONENT_MOUSEDOUBLECLICK;
        CallAllNotificationReceivers(notifyInfo);
    }

    return false;
}

void ComponentContainer::CallAllComponentRenderer(
    Graphics& graphics, Rect invalidatedRect
) {
    CallRenderer(GetContainer().get(), graphics, invalidatedRect);
}

unique_ptr<Frame>& ComponentContainer::GetContainer() {
    return _pRoot;
}
