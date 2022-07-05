#include "Renderer.h"

namespace LightInDarkness
{
    RendererData Renderer::s_rendererData;
    void Renderer::Initialize(){
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(openglErrorCallback, nullptr);

        s_rendererData.vertexArray = VertexArray::Create();
        s_rendererData.vertices.emplace_back(VertexData{glm::vec3{-1.0f, -1.0f, 0.0f}, glm::vec2{0.0f, 0.0f}});
        s_rendererData.vertices.emplace_back(VertexData{glm::vec3{-1.0f, 1.0f, 0.0f}, glm::vec2{0.0f, 1.0f}});
        s_rendererData.vertices.emplace_back(VertexData{glm::vec3{1.0f, 1.0f, 0.0f}, glm::vec2{1.0f, 1.0f}});
        s_rendererData.vertices.emplace_back(VertexData{glm::vec3{1.0f, -1.0f, 0.0f}, glm::vec2{1.0f, 0.0f}});
        
        s_rendererData.indices.emplace_back(0);
        s_rendererData.indices.emplace_back(1);
        s_rendererData.indices.emplace_back(3);
        s_rendererData.indices.emplace_back(1);
        s_rendererData.indices.emplace_back(2);
        s_rendererData.indices.emplace_back(3);

        s_rendererData.vertexBuffer = VertexBuffer::Create(s_rendererData.vertices.data(), s_rendererData.vertices.size()* sizeof(VertexData));
        s_rendererData.indexBuffer = IndexBuffer::Create(s_rendererData.indices.data(), s_rendererData.indices.size() * sizeof(uint));
        s_rendererData.vertexBufferLayout = VertexBufferLayout::Create();

        s_rendererData.vertexBufferLayout->Push<float>(3);
        s_rendererData.vertexBufferLayout->Push<float>(2);

        s_rendererData.vertexArray->AddBuffer<VertexBuffer, VertexBufferLayout>(*s_rendererData.vertexBuffer, *s_rendererData.vertexBufferLayout);
        s_rendererData.vertexArray->AddBuffer<IndexBuffer>(*s_rendererData.indexBuffer);

        s_rendererData.colorShader = Shader::Create("../../resources/shaders/ColorShader.glsl");
        s_rendererData.textureShader = Shader::Create("../../resources/shaders/TextureShader.glsl");
    }
    void Renderer::Clear(const glm::vec4 &color)
    {
        glClearColor(color.r,color.g,color.b,color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void Renderer::BeginScene(const OrtoCamera &_camera)
    {
        s_rendererData.currentViewProjection = _camera.GetViewProjectionMatrix();
    }

    void Renderer::DrawRect(const glm::vec2 _position, const glm::vec2 _size, const glm::vec4 _color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f),glm::vec3{_position,0.0f})*
        glm::scale(glm::mat4(1.0f), glm::vec3{_size.x, _size.y,1.0f});
        
        s_rendererData.vertexArray->Bind();
        s_rendererData.colorShader->Bind();
        s_rendererData.colorShader->SetMat4("u_Model", transform);
        s_rendererData.colorShader->SetMat4("u_ViewProjection", s_rendererData.currentViewProjection);
        s_rendererData.colorShader->SetVec4("u_Color", _color);

        glDrawElements(GL_TRIANGLES, s_rendererData.indices.size(), GL_UNSIGNED_INT, 0);
    }

    void Renderer::DrawRect(const glm::vec2 _position, const glm::vec2 _size, std::shared_ptr<Texture> _texture)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f),glm::vec3{_position,0.0f})*
        glm::scale(glm::mat4(1.0f), glm::vec3{_size.x, _size.y,1.0f});
        s_rendererData.vertexArray->Bind();
        s_rendererData.textureShader->Bind();
       
        _texture->Bind(0);

        s_rendererData.textureShader->SetInt("u_Texture", _texture->GetSlot());
        s_rendererData.textureShader->SetMat4("u_Model", transform);
        s_rendererData.textureShader->SetMat4("u_ViewProjection", s_rendererData.currentViewProjection);
        glDrawElements(GL_TRIANGLES, s_rendererData.indices.size(), GL_UNSIGNED_INT, 0);
    }

    void Renderer::DrawCircle(const glm::vec2 _position, float _radius, const glm::vec4 _color)
    {
    }
    void Renderer::DrawLine()
    {
    }

    void Renderer::DrawRotatedRect(const glm::vec2 _position, const glm::vec2 _size, float _rotation, const glm::vec4 _color)
    {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), glm::vec3{_position.x, _position.y, 0.0f}) *
            glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), {0.0f, 0.0f, 1.0f}) *
            glm::scale(glm::mat4(1.0f), {_size.x, _size.y, 1.0f});
        s_rendererData.vertexArray->Bind();
        s_rendererData.colorShader->Bind();
        s_rendererData.colorShader->SetMat4("u_Model", transform);
        s_rendererData.colorShader->SetMat4("u_ViewProjection", s_rendererData.currentViewProjection);
        s_rendererData.colorShader->SetVec4("u_Color", _color);

        glDrawElements(GL_TRIANGLES, s_rendererData.indices.size(), GL_UNSIGNED_INT, 0);
    }

    void Renderer::DrawRotatedRect(const glm::vec2 _position, const glm::vec2 _size, float _rotation, std::shared_ptr<Texture> _texture)
    {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), glm::vec3{_position.x, _position.y, 0.0f}) *
            glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), {0.0f, 0.0f, 1.0f}) *
            glm::scale(glm::mat4(1.0f), {_size.x, _size.y, 1.0f});
        
        s_rendererData.vertexArray->Bind();
        _texture->Bind(0);
        s_rendererData.textureShader->SetInt("u_Texture", _texture->GetSlot());
        s_rendererData.textureShader->SetMat4("u_Model", transform);
        s_rendererData.textureShader->SetMat4("u_ViewProjection", s_rendererData.currentViewProjection);
        glDrawElements(GL_TRIANGLES, s_rendererData.indices.size(), GL_UNSIGNED_INT, 0);
    }
    void Renderer::EndScene(){

    }
    void Renderer::Shutdown(){

    }
}