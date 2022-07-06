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

        VertexBuffer testBuffer{vertices, sizeof(vertices)};
        IndexBuffer testIndexBuffer{indices, sizeof(indices)};
        VertexBufferLayout testLayout;
        testLayout.Push<float>(3);
        testLayout.Push<float>(2);

        vertexArrayObj.AddBuffer<VertexBuffer, VertexBufferLayout>(testBuffer, testLayout);
        vertexArrayObj.AddBuffer<IndexBuffer>(testIndexBuffer);

       testShader = Shader::Create("../../resources/shaders/ColorShader.glsl");
       testTexture = Texture::Create("../../resources/textures/woodwall.png");
       spriteSheetTexture = Texture::Create("../../resources/textures/sheet.png");



       window.SetVSync(true);
    }
    void TestScene::OnEvent(){
    }
    void TestScene::OnUpdate(float dt){

        m_camera.OnUpdate(dt);

        Renderer::Clear(glm::vec4(0.1, 0.047, 0.047, 1.0f));

        Renderer::BeginScene(m_camera); 
        //Renderer::DrawRect({0.0f,0.0f},{0.5f, 1.0f},{0.75f, 0.3f, 0.6f, 1.0});
        glm::vec2 startPos{0.0f,0.0f};
        static float rotation =0.0f;
        rotation += dt*10.0f; 
        for (size_t i = 0; i < 100; i++)
        {
            glm::vec4 color(1);
            for (size_t j = 0; j < 100; j++){
            
            if((((i&1)==0)&&((j&1)!=0)) || (((i&1)!=0)&&((j&1)==0))){
                color = glm::vec4{0.15f, 0.3f, 0.6f, 1.0};
            }else{
                color = glm::vec4{0.25f, 0.7f, 0.6f, 1.0};
            }
            Renderer::DrawRect({startPos.x+(2.1*i), startPos.y+(2.1*j)}, {1.0f, 1.0f}, color);
            
            }
        }
        Renderer::DrawRect({0.0f, 0.0f}, {1.0f, 1.0}, {0.5f, 0.5f, 0.6f, 1.0});
        Renderer::DrawRotatedRect({0.0, 0.0}, {1.2f, 1.0f}, rotation*5, {0.1f, 0.3f, 0.6f, 1.0});
        Renderer::DrawRotatedRect({0.0, 0.0}, {1.1f, 1.0f}, rotation, {0.5f, 0.3f, 0.6f, 1.0});
        
        
        Renderer::DrawRect({0.0f, 0.0f}, {1.1f, 1.0f}, testTexture);
        Renderer::DrawRotatedRect({5.0, 0.0}, {2.0f, 2.0f}, rotation*5, spriteSheetTexture);

        Renderer::EndScene();



        Renderer::SetBlending(false);
        Renderer::BeginScene(m_camera);
        Renderer::DrawRotatedRect({10.0, 0.0}, {2.0f, 2.0f}, rotation * 5, spriteSheetTexture);
        Renderer::EndScene();


        //vertexArrayObj.Bind();
        //glm::mat4 modelMatrix(1.0f);
        ////glDrawArrays(GL_TRIANGLES,0,4);
        //testShader->Bind();
        //testTexture->Bind(0);
        //testShader->SetMat4("u_Model", glm::scale(modelMatrix, glm::vec3(0.5f, 1.0f, 1.0f)));
        //testShader->SetMat4("u_View", m_camera.GetViewMatrix());
        //testShader->SetMat4("u_Projection", m_camera.GetProjectionMatrix());
        //testShader->SetInt("u_Texture",0);
        ////testShader->SetVec4("u_Color", glm::vec4(0.75f, 0.3f, 0.6f, 1.0f));
        //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
    }
    void TestScene::OnShutdown(){
        Renderer::Shutdown();
    }
} 

