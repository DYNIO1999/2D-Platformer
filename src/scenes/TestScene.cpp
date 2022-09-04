#include "TestScene.h"
#include "core/App.h"
namespace LightInDarkness
{
    TestScene::TestScene(){

    }
    TestScene::~TestScene()
    {
    }

    void TestScene::OnInit(){
        Renderer::Initialize();
        auto &window = App::Get().GetWindow();
        auto [winWidth, winHeight] = window.GetWindowSize();
        m_camera.SetCamera((static_cast<float>(winWidth) / static_cast<float>(winHeight)), 10.0f);
        m_camera.SetCameraSpeed(10.0f);

       testShader = Shader::Create("../../resources/shaders/ColorShader.glsl");
       testTexture = Texture::Create("../../resources/textures/woodwall.png");
       spriteSheetTexture = Texture::Create("../../resources/textures/sheet.png");

       window.SetVSync(true);
    }
    void TestScene::OnEvent(){
    }
    void TestScene::OnUpdate(float dt){

        m_camera.OnUpdate(dt);

        Renderer::Clear(glm::vec4(0.7, 0.047, 0.047, 1.0f));

        Renderer::BeginScene(m_camera);
        //Rendering
        Renderer::EndScene();
    }
    void TestScene::OnShutdown(){
        Renderer::Shutdown();
    }
} 

