#include "App.h"
#include "input/Input.h"
#include "scenes/CheckersScene.h"
namespace DEngine{

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

        //Logger
        Logger::Init();
        //Logger
        
        //Renderer
        Renderer::Initialize();
        //Rednerer
        //Scenes
        SceneManager::Get().PushScene(std::make_shared<CheckersScene>());

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

            std::string dt = std::to_string(s_deltaTime);
            m_Window->SetWindowTitle(dt);
            m_lastFrameTime = currentTime;
            //std::cout<<"DELTA TIME:"<<s_deltaTime<<'\n';
        }
        Shutdown();
         
    }
    void App::Shutdown(){
        Renderer::Shutdown();
    }
    void App::OnWindowClose(const Event&){
        m_isRunning =false;
    }
    void App::OnWindowResize(const Event &e){
        auto event = s_eventDispatcher.Cast<WindowResizeEvent>(e);
        APP_ERROR("APP EVENT RESIZE {} {}", event.m_width, event.m_height);
        glViewport(0.0,0.0,event.m_width, event.m_height);
    }
}