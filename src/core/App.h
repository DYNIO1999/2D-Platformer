#ifndef _SRC_CORE_APP_H
#define _SRC_CORE_APP_H

#include <iostream>
#include <memory>

#include "Window.h"
#include "events/EventDispatcher.h"
namespace LightInDarkness{
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)
class App
{
public:
    App();
    ~App();
    void Run();

    static float GetDeltaTime(){return s_deltaTime;}
    static EventDispatcher s_eventDispatcher;
private:
    void OnWindowClose(const Event &);
    void OnWindowResize(const Event &);
    
    void OnEvent();
    void OnUpdate();
    
    void Initialize();
    void Shutdown();
    bool m_isRunning;
    static float s_deltaTime;

    WindowProperties m_windowProps;
    std::shared_ptr<Window> m_Window;
};
}
#endif