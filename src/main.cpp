#include <iostream>
#include "core/App.h"
#include "events/WindowEvents.h"
#include "events/EventDispatcher.h"

//#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)
//bool onEvent1(const DEngine::Event<DEngine::WindowEvents> &event)
//{
//    if (event.GetEventType() == DEngine::WindowEvents::WindowClose)
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
//bool onEvent2(const DEngine::Event<DEngine::WindowEvents> &event)
//{
//    if (event.GetEventType() == DEngine::WindowEvents::WindowClose)
//    {
//        std::cout << "Window close!" << std::endl;
//    }
//    return true;
//}
//
//class TestClass{
//    public:
//    bool onWindowEvents(const DEngine::Event<DEngine::WindowEvents> &event)
//    {
//        if (event.GetEventType() == DEngine::WindowEvents::WindowClose)
//        {
//            std::cout << "HEHEHHEHEHEH!" << std::endl;
//        }
//        return true;
//    }
//};
int main()
{

    DEngine::App &app = DEngine::App::Get();
    app.Run();
    //    //DEngine::App app;
    //    //app.Run();
    //
    //    DEngine::EventDispatcher<DEngine::WindowEvents> dispatcher1;
    //    dispatcher1.Subscribe(DEngine::WindowEvents::WindowClose, onEvent1);
    //    dispatcher1.Subscribe(DEngine::WindowEvents::WindowClose, onEvent2);
    //    TestClass testClass;
    //
    //    dispatcher1.Subscribe(DEngine::WindowEvents::WindowClose,std::bind(&TestClass::onWindowEvents, testClass, std::placeholders::_1 ));
    //    dispatcher1.Subscribe(DEngine::WindowEvents::WindowClose, [](const DEngine::Event<DEngine::WindowEvents> &event) -> bool
    //                          {
    //
    //    if (event.GetEventType() == DEngine::WindowEvents::WindowClose)
    //    {
    //        std::cout << "Lambda!" << std::endl;
    //    }
    //            return true; });
    //    DEngine::WindowCloseEvent test;
    //    dispatcher1.DispatchAll(test);
    return 0;
}
