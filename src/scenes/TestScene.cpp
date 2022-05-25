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
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


        VertexBuffer testBuffer{vertices,sizeof(vertices)};
        IndexBuffer testIndexBuffer{indices, sizeof(indices)};
        VertexBufferLayout testLayout;
        testLayout.Push<float>(3);
        testLayout.Push<float>(2);


        vertexArrayObj.AddBuffer<VertexBuffer, VertexBufferLayout>(testBuffer, testLayout);
        vertexArrayObj.AddBuffer<IndexBuffer>(testIndexBuffer);
    }
    void TestScene::OnEvent(){

    }
    void TestScene::OnUpdate(float dt){



        Renderer::Clear(glm::vec4(0.831, 0.047, 0.047, 1.0f));

        glUseProgram(shaderProgram);
        vertexArrayObj.Bind();
        
        //glDrawArrays(GL_TRIANGLES,0,4);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
    }
    void TestScene::OnShutdown(){
        Renderer::Shutdown();
    }
} 

