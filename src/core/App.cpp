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
        s_eventDispatcher.Subscribe<WindowResizeEvent>(BIND_EVENT_FUNCTION(App::OnWindowResize));
        s_eventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FUNCTION(App::OnWindowClose));
    }
    void App::Run(){
        Initialize();
        while (m_isRunning)
        {
            OnEvent();
            OnUpdate();
            m_Window->Update();
        }
        Shutdown();
         
    }
    void App::Shutdown(){
    
    }
    void App::OnEvent(){
        
    }
    void App::OnUpdate(){

    }
    void App::OnWindowClose(const Event&){
        m_isRunning =false;
    }
    void App::OnWindowResize(const Event &e){
        auto event = s_eventDispatcher.Cast<WindowResizeEvent>(e);
        glViewport(0.0,0.0,event.m_width, event.m_height);
        std::cout<<"Viewport resized!"<<'\n';
    }
}