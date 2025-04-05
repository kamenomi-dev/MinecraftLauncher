#pragma once

#ifndef _Component_ComponentContainer_h_
#define _Component_ComponentContainer_h_

#include "Base.h"

namespace Launcher {
namespace Components {

typedef void(__stdcall ForEachFeedback)(Base*, void*);

class ComponentContainer {
  public:
    ComponentContainer();

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
    unique_ptr<Base>& GetContainer();

  private:
    unique_ptr<Base> _pRoot = make_unique<Base>();
};
} // namespace Components
} // namespace Launcher

#endif // _Component_ComponentContainer_h_