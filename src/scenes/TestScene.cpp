#include "TestScene.h"

namespace LightInDarkness
{
    TestScene::TestScene(){

    }
    TestScene::~TestScene()
    {
    }

    void TestScene::OnInit(){
        Renderer::Initialize();

        VertexBuffer testBuffer{vertices,sizeof(vertices)};
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

        glUseProgram(shaderProgram);
        vertexArrayObj.Bind();
    
        
        //glDrawArrays(GL_TRIANGLES,0,4);
        testShader->Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
    }
    void TestScene::OnShutdown(){
        Renderer::Shutdown();
    }
} 

