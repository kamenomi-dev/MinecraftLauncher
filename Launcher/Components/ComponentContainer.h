#pragma once

#ifndef _Component_ComponentContainer_h_
#define _Component_ComponentContainer_h_

#include "Defines.h"

namespace Launcher {
namespace Components {

class Base;
class Frame;
class Interface_BaseWrapper;

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

    void ConnectWindow(Interface_BaseWrapper*);

    // ========================================================
    // // Component Operation .
    // ========================================================

    typedef bool(__stdcall TryFindComponent_Filter)(Base* currentComponent, const void* filterData);

    void  Push(initializer_list<Base*>);
    Base* HitTest(LPARAM);
    Base* TryFindComponent(TryFindComponent_Filter filterFn, const void* filterData);
    Base* FindComponentByID(const wstring& id);

    // ========================================================
    // // Notification Operation .
    // ========================================================

    void RegisterNotificationReceiver(NotificationReceiver*);
    template <typename DetailInformation = BaseNotificationInformation>
    void CallAllNotificationReceivers(
        NotificationInformation<DetailInformation>& notify
    ) {
        if (notify.Emitter) {
            notify.Emitter->OnNotify(notify);
        }

        for (auto pFn : _notificationReceivers) {
            if (!pFn) {
                OutputDebugStringA("Oops, notify receiver should not be nullptr. ");
                abort();
            }

            pFn(notify);
        }
    };

    bool SystemMessageProcessor(HWND, UINT, WPARAM, LPARAM, LRESULT&);
    void CallAllComponentRenderer(Gdiplus::Graphics&, Gdiplus::Rect = {});

    unique_ptr<Frame>&     GetContainer();
    Interface_BaseWrapper* GetWrapper() { return _pConnectedWindow; };

  private:
    Interface_BaseWrapper*        _pConnectedWindow{nullptr};
    unique_ptr<Frame>             _pRoot;
    vector<NotificationReceiver*> _notificationReceivers{};
    StatusEnvironmentInformation  _statusInfo{};
};
} // namespace Components
} // namespace Launcher

#endif // _Component_ComponentContainer_h_