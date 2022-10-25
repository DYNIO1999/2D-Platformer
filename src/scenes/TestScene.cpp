#include "TestScene.h"
#include "core/App.h"

namespace DEngine
{
    TestScene::TestScene(){

    }
    TestScene::~TestScene()
    {
    }

    void TestScene::OnInit(){


        auto &window = App::Get().GetWindow();
        auto [winWidth, winHeight] = window.GetWindowSize();
        m_camera.SetCamera((static_cast<float>(winWidth) / static_cast<float>(winHeight)), 10.0f);
        m_camera.SetCameraSpeed(20.0f);

       testShader = Shader::Create("../../resources/shaders/ColorShader.glsl");
       testTexture = Texture::Create("../../resources/textures/woodwall.png");
       spriteSheetTexture = Texture::Create("../../resources/textures/sheet.png");

       window.SetVSync(true);
    }
    void TestScene::OnEvent(){
    
    }
    void TestScene::OnUpdate(float dt){

        m_camera.OnUpdate(dt);

        Renderer::Clear(glm::vec4(0.0, 0.0, 0.0, 1.0f));
        
        
        //Renderer::s_rendererData.drawCalls =0;
        Renderer::BeginScene(m_camera);
        for (size_t i = 0; i < 100; i++)
        {
            for (size_t j = 0; j < 100; j++)
            {
                Renderer::DrawRect({0.0f+i, 0.0f+j}, {1.0f, 1.0}, {1.0f, 0.0f+(0.1*i), 0.0f+(0.1*j), 1.0}); 
            }
            
        }
        Renderer::EndScene();
        //APP_ERROR("DrawCalls {}", Renderer::s_rendererData.drawCalls);
    }
    void TestScene::OnShutdown(){
        Renderer::Shutdown();
    }
} 

