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
        APP_INFO("SIZE--> {}  {}",winWidth, winHeight);
        m_camera.SetProjection((-static_cast<float>((winWidth / winHeight))) * 10.0f, static_cast<float>((winWidth / winHeight)) * 10.0f, (-1.0f) * 10.0f, 1.0f * 10.0f);

        VertexBuffer testBuffer{vertices, sizeof(vertices)};
        IndexBuffer testIndexBuffer{indices, sizeof(indices)};
        VertexBufferLayout testLayout;
        testLayout.Push<float>(3);
        testLayout.Push<float>(2);


        vertexArrayObj.AddBuffer<VertexBuffer, VertexBufferLayout>(testBuffer, testLayout);
        vertexArrayObj.AddBuffer<IndexBuffer>(testIndexBuffer);

       testShader = Shader::Create("../../resources/shaders/BaseShader.glsl");


    }
    void TestScene::OnEvent(){

    }
    void TestScene::OnUpdate(float dt){

        Renderer::Clear(glm::vec4(0.831, 0.047, 0.047, 1.0f));

        vertexArrayObj.Bind();
    
        glm::mat4 modelMatrix(1.0f);
        
        //glDrawArrays(GL_TRIANGLES,0,4);
        testShader->Bind();
        testShader->SetMat4("u_Model", glm::scale(modelMatrix, glm::vec3(0.5f, 1.0f, 1.0f)));
        testShader->SetMat4("u_View", m_camera.GetViewMatrix());
        testShader->SetMat4("u_Projection", m_camera.GetProjectionMatrix());
        testShader->SetVec4("u_Color", glm::vec4(0.75f, 0.3f, 0.6f, 1.0f));
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
    }
    void TestScene::OnShutdown(){
        Renderer::Shutdown();
    }
} 

