// UIFramework Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "../UIFramework/UI.h"
#include "../UIFramework/Components/Window.h"
#include "../UIFramework/Components/Base.h"

int main() {
    std::cout << "Hello World!\n";

    UIFramework::UiInitialize();

    auto a = new UIFramework::Components::Component;
    auto b = new UIFramework::Components::Component;
    auto c = new UIFramework::Components::Component;
    a->Emplace(new UIFramework::Components::Component);
    a->Emplace(new UIFramework::Components::Component);
    a->Emplace(new UIFramework::Components::Component);
    a->Emplace(new UIFramework::Components::Component);
    a->Emplace(b, 0);
    a->Emplace(c, 0);
    c->Parentify(b);

    UIFramework::Components::Window app{};
    app.Insert(a);
    app.Initialize();
    app.Show();

    return UIFramework::Startup();
}
