#include "App.h"
#include "input/Input.h"
#include "scenes/TestScene.h"

namespace LightInDarkness{

    EventDispatcher App::s_eventDispatcher;
    float App::s_deltaTime =0.0f;

    App::App()
    {

    }
    App::~App()
    {

    }
    void App::Initialize(){

        m_lastFrameTime = 0.0f;

        m_isRunning = true;
        m_Window = std::make_shared<Window>(m_windowProps);
        s_eventDispatcher.Subscribe<WindowCloseEvent>(BIND_EVENT_FUNCTION(App::OnWindowClose));
        s_eventDispatcher.Subscribe<WindowResizeEvent>(BIND_EVENT_FUNCTION(App::OnWindowResize));

        SceneManager::Get().PushScene(std::make_shared<TestScene>());
        //Scenes
    }
    void App::Run(){
        Initialize();
        while (m_isRunning)
        {
            if(!SceneManager::Get().IsEmpty()){
            SceneManager::Get().Current()->OnEvent();
            SceneManager::Get().Current()->OnUpdate(App::GetDeltaTime());
            }
            m_Window->Update();
            float currentTime  = glfwGetTime();
            s_deltaTime = currentTime - m_lastFrameTime;
            //std::cout<<"DELTA TIME:"<<s_deltaTime<<'\n';
            m_lastFrameTime = currentTime;
        }
        Shutdown();
         
    }
    void App::Shutdown(){
    
    }
    void App::OnWindowClose(const Event&){
        m_isRunning =false;
    }
    void App::OnWindowResize(const Event &e){
        auto event = s_eventDispatcher.Cast<WindowResizeEvent>(e);
        glViewport(0.0,0.0,event.m_width, event.m_height);
    }
}