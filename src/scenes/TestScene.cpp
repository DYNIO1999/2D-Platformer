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
        m_camera.SetCamera(winWidth/winHeight, 10.0f);
        m_camera.SetCameraSpeed(10.0f);

        VertexBuffer testBuffer{vertices, sizeof(vertices)};
        IndexBuffer testIndexBuffer{indices, sizeof(indices)};
        VertexBufferLayout testLayout;
        testLayout.Push<float>(3);
        testLayout.Push<float>(2);

        vertexArrayObj.AddBuffer<VertexBuffer, VertexBufferLayout>(testBuffer, testLayout);
        vertexArrayObj.AddBuffer<IndexBuffer>(testIndexBuffer);

       testShader = Shader::Create("../../resources/shaders/BaseShader.glsl");
       testTexture = Texture::Create("../../resources/textures/woodwall.png");
    }
    void TestScene::OnEvent(){
            m_camera.OnEvent();
    }
    void TestScene::OnUpdate(float dt){

        m_camera.OnUpdate(dt);

        Renderer::Clear(glm::vec4(0.831, 0.047, 0.047, 1.0f));

        vertexArrayObj.Bind();

        glm::mat4 modelMatrix(1.0f);
        
        //glDrawArrays(GL_TRIANGLES,0,4);
        testShader->Bind();
        testTexture->Bind(0);
        testShader->SetMat4("u_Model", glm::scale(modelMatrix, glm::vec3(0.5f, 1.0f, 1.0f)));
        testShader->SetMat4("u_View", m_camera.GetViewMatrix());
        testShader->SetMat4("u_Projection", m_camera.GetProjectionMatrix());
        testShader->SetInt("u_Texture",0);
        //testShader->SetVec4("u_Color", glm::vec4(0.75f, 0.3f, 0.6f, 1.0f));
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
    }
    void TestScene::OnShutdown(){
        Renderer::Shutdown();
    }
} 

