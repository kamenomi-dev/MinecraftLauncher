#pragma once

#ifndef _Component_ComponentContainer_h_
#define _Component_ComponentContainer_h_

#include "Defines.h"
#include "Base.h"
#include "Frame.h"

namespace Launcher {
namespace Components {

typedef void(__stdcall ForEachFeedback)(Base*, void*);
typedef void(__stdcall NotificationReceiver)(NotificationInformation<>&);

class ComponentContainer {

    typedef struct __structStatusEnvironmentInformation {
        Base* pCurrHoveredComp;
        Base* pPrevHoveredComp;

        __structStatusEnvironmentInformation() {
            pCurrHoveredComp = nullptr;
            pPrevHoveredComp = nullptr;
        }
    } StatusEnvironmentInformation, SEI_;

  public:
    ComponentContainer();

    void RegisterNotificationReceiver(NotificationReceiver*);
    template <typename DetailInformation = Base::BaseNotificationInformation>
    void CallAllNotificationReceivers(
        NotificationInformation<DetailInformation>& notify
    ) {
        for (auto pFn : _notificationReceivers) {
            if (!pFn) {
                OutputDebugStringA("Oops, notify receiver should not be nullptr. ");
                abort();
            }

            pFn(notify);
        }
    };

    void Push(initializer_list<Base*>);
    template <typename P>
    void ForEach(
        ForEachFeedback feedback, P& params
    ) {
        stack<Base*> nodeStack{};
        nodeStack.push(_pRoot.get());

        while (!nodeStack.empty()) {
            auto currentNode = nodeStack.top();
            nodeStack.pop();

            feedback(currentNode, &params);

            auto         child = currentNode->GetChildFirst();
            stack<Base*> tempStack{};
            while (child) {
                tempStack.push(child);
                child = (*child).operator++();
            }
            while (!tempStack.empty()) {
                nodeStack.push(tempStack.top());
                tempStack.pop();
            }
        }
    }

    Base* HitTest(LPARAM);

    bool SystemMessageProcessor(HWND, UINT, WPARAM, LPARAM, LRESULT&);
    void CallAllComponentRenderer(Gdiplus::Graphics&, Gdiplus::Rect = {});

    unique_ptr<Frame>& GetContainer();

  private:
    unique_ptr<Frame>             _pRoot = make_unique<Frame>();
    vector<NotificationReceiver*> _notificationReceivers{};
    StatusEnvironmentInformation  _statusInfo{};
};
} // namespace Components
} // namespace Launcher

#endif // _Component_ComponentContainer_h_