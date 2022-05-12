#include "App.h"



namespace LightInDarkness{
    App::App(){

    }
    App::~App()
    {

    }
    void App::Initialize(){
        m_isRunning = true;
    }
    void App::Run(){
        Initialize();
        while (m_isRunning)
        {
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
}