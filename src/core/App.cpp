#include "App.h"



namespace LightInDarkness{

    EventDispatcher App::s_eventDispatcher;
    App::App()
    {

    }
    App::~App()
    {

    }
    void App::Initialize(){
        m_isRunning = true;
        m_Window = std::make_shared<Window>(m_windowProps);
        s_eventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FUNCTION(App::OnWindowClose));
        s_eventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FUNCTION(App::OnWindowClose));
        s_eventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FUNCTION(App::OnWindowClose));
        s_eventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FUNCTION(App::OnWindowClose));
    }
    void App::Run(){
        Initialize();
        while (m_isRunning)
        {
            glfwPollEvents();
            OnUpdate();
        }
        Shutdown();
         
    }
    void App::Shutdown(){
    
    }
    void App::OnEvent(){
        
    }
    void App::OnUpdate(){

    }
    void App::OnWindowClose(const Event &){
        std::cout<<"HERHHEHEHEH"<<'\n';
        m_isRunning =false;
    }
}