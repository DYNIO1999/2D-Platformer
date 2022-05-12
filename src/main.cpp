#include <iostream>
#include "core/App.h"
#include "events/WindowEvents.h"
#include "events/EventDispatcher.h"

//#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)
//bool onEvent1(const LightInDarkness::Event<LightInDarkness::WindowEvents> &event)
//{
//    if (event.GetEventType() == LightInDarkness::WindowEvents::WindowClose)
//    {
//        std::cout << "Window close!"<< std::endl;
//
//        int x =10;
//        int y =20;
//        std::cout<<x+y<<'\n';
//    }
//    return true;
//}
//
//bool onEvent2(const LightInDarkness::Event<LightInDarkness::WindowEvents> &event)
//{
//    if (event.GetEventType() == LightInDarkness::WindowEvents::WindowClose)
//    {
//        std::cout << "Window close!" << std::endl;
//    }
//    return true;
//}
//
//class TestClass{
//    public:
//    bool onWindowEvents(const LightInDarkness::Event<LightInDarkness::WindowEvents> &event)
//    {
//        if (event.GetEventType() == LightInDarkness::WindowEvents::WindowClose)
//        {
//            std::cout << "HEHEHHEHEHEH!" << std::endl;
//        }
//        return true;
//    }
//};
int main()
{

    LightInDarkness::App &app = LightInDarkness::App::Get();
    app.Run();
    //    //LightInDarkness::App app;
    //    //app.Run();
    //
    //    LightInDarkness::EventDispatcher<LightInDarkness::WindowEvents> dispatcher1;
    //    dispatcher1.Subscribe(LightInDarkness::WindowEvents::WindowClose, onEvent1);
    //    dispatcher1.Subscribe(LightInDarkness::WindowEvents::WindowClose, onEvent2);
    //    TestClass testClass;
    //
    //    dispatcher1.Subscribe(LightInDarkness::WindowEvents::WindowClose,std::bind(&TestClass::onWindowEvents, testClass, std::placeholders::_1 ));
    //    dispatcher1.Subscribe(LightInDarkness::WindowEvents::WindowClose, [](const LightInDarkness::Event<LightInDarkness::WindowEvents> &event) -> bool
    //                          {
    //
    //    if (event.GetEventType() == LightInDarkness::WindowEvents::WindowClose)
    //    {
    //        std::cout << "Lambda!" << std::endl;
    //    }
    //            return true; });
    //    LightInDarkness::WindowCloseEvent test;
    //    dispatcher1.DispatchAll(test);
    return 0;
}
