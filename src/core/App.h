#ifndef _SRC_CORE_APP_H
#define _SRC_CORE_APP_H

#include <iostream>
#include <memory>

#include "Window.h"
#include "events/EventDispatcher.h"
#include "SceneManager.h"
#include "Logger.h"

namespace LightInDarkness{
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)
class App
{
public:
    void Run();

    App(App const &) = delete;
    void operator=(App const &) = delete;

    static App &Get()
    {
        static App instance;
                           
        return instance;
    }
    

    static EventDispatcher& GetDispatcher(){return s_eventDispatcher;}
    static EventDispatcher s_eventDispatcher;
    static float GetDeltaTime(){return s_deltaTime;}
    Window& GetWindow() const {return *m_Window;};
    
private:
    App();
    ~App();

    void OnWindowClose(const Event &);
    void OnWindowResize(const Event &);
    
    void Initialize();
    void Shutdown();
    bool m_isRunning;
    static float s_deltaTime;
    float m_lastFrameTime;

    WindowProperties m_windowProps;
    std::shared_ptr<Window> m_Window;

};
}
#endif