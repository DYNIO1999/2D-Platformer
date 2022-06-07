#include "Renderer.h"

namespace LightInDarkness
{

    void Renderer::Initialize(){
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(openglErrorCallback, nullptr);
    }
    void Renderer::Clear(const glm::vec4 &color)
    {
        glClearColor(color.r,color.g,color.b,color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void Renderer::BeginDraw(const glm::mat4 &viewProj){
        std::cout<<viewProj[0][0]<<'\n';
    }

    static void DrawRect(){
        
    }
    static void DrawCircle(){

    }
    static void DrawLine(){
        
    }
    static void DrawRotatedQuad(){

    }
    void Renderer::EndDraw(){

    }
    void Renderer::Shutdown(){

    }
}