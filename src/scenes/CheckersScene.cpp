#include "CheckersScene.h"
#include "../input/Input.h"

namespace DEngine{
    CheckersScene::CheckersScene()
    {
    }
    CheckersScene::~CheckersScene()
    {
    }

    void CheckersScene::OnInit()
    {

        auto &window = App::Get().GetWindow();
        auto [winWidth, winHeight] = window.GetWindowSize();
        m_camera.SetCamera((static_cast<float>(winWidth) / static_cast<float>(winHeight)), 10.0f);
        m_camera.SetCameraSpeed(20.0f);

        testShader = Shader::Create("../../resources/shaders/ColorShader.glsl");
        testTexture = Texture::Create("../../resources/textures/woodwall.png");
        spriteSheetTexture = Texture::Create("../../resources/textures/sheet.png");

        window.SetVSync(true);
    }
    void CheckersScene::OnEvent()
    {
    }
    void CheckersScene::OnUpdate(float dt)
    {
        auto &window = App::Get().GetWindow();
        auto [width, height] = window.GetWindowSize();

        auto [mouse_x, mouse_y] = Input::GetMousePosition();
        std::cout<<"X :"<<mouse_x<< " "<< "Y :"<<mouse_y<<'\n';

        float x = (2.0f * mouse_x) / width - 1.0f;
        float y = 1.0f - (2.0f * mouse_y) / height;
        float z = 1.0f;
        glm::vec3 ray_nds = glm::vec3(x, y, z);
        std::cout<<"Vector3D: "<<ray_nds.x<< " "<< ray_nds.y<< ray_nds.z<<" "<<std::endl;

        m_camera.OnUpdate(dt);
        

        Renderer::Clear(glm::vec4(0.7, 0.5, 0.3, 1.0f));
        Renderer::BeginScene(m_camera);
        
        
        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                if((i+j)%2){
                Renderer::DrawRect({0.0f + i, 0.0f + j}, {1.0f, 1.0}, {1.0f,1.0f,1.0f, 1.0f});
                }
                else{
                Renderer::DrawRect({0.0f + i, 0.0f + j}, {1.0f, 1.0}, {0.0f,0.0f,0.0f, 1.0f});
                }
                if ((ray_nds.x >= i && ray_nds.y < i+1) && (ray_nds.y >= j && ray_nds.y < j+1))
                {
                    Renderer::DrawRect({0.0f + i, 0.0f + j}, {1.0f, 1.0}, {1.0f, 0.0f, 0.0f, 1.0f});
                }
            }
        }
        
        Renderer::EndScene();
    }
    void CheckersScene::OnShutdown()
    {
        Renderer::Shutdown();
    }
}