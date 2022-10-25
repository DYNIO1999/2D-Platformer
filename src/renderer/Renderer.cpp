#include "Renderer.h"

namespace DEngine
{
    RendererData Renderer::s_rendererData;
    void Renderer::Initialize(){
        glEnable(GL_DEBUG_OUTPUT);
        
        glDebugMessageCallback(openglErrorCallback, nullptr);
        (void)openglErrorCallback;

        s_rendererData.vertexArray = VertexArray::Create();
        s_rendererData.vertexBuffer = VertexBuffer::Create((uint)(s_rendererData.maxVertices * sizeof(RectVertexData)));

        s_rendererData.vertexBufferLayout = VertexBufferLayout::Create();
        s_rendererData.vertexBufferLayout->Push<float>(3);
        s_rendererData.vertexBufferLayout->Push<float>(4);

        s_rendererData.rectVertexBufferBase = new RectVertexData[s_rendererData.maxVertices];
        
        
        s_rendererData.vertexArray->AddBuffer<VertexBuffer, VertexBufferLayout>(*s_rendererData.vertexBuffer, *s_rendererData.vertexBufferLayout);
        
        uint* rectIndices = new uint[s_rendererData.maxIndices]; 
        uint offset = 0;
        for (uint i = 0; i < s_rendererData.maxIndices; i += 6)
        {
            rectIndices[i + 0] = offset + 0;
            rectIndices[i + 1] = offset + 1;
            rectIndices[i + 2] = offset + 2;

            rectIndices[i + 3] = offset + 2;
            rectIndices[i + 4] = offset + 3;
            rectIndices[i + 5] = offset + 0;

            offset += 4;
        }

        s_rendererData.indexBuffer = IndexBuffer::Create(rectIndices, (uint)(s_rendererData.maxIndices * sizeof(uint)));
        s_rendererData.vertexArray->AddBuffer<IndexBuffer>(*s_rendererData.indexBuffer);
        delete[] rectIndices;

        s_rendererData.rectVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        s_rendererData.rectVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        s_rendererData.rectVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
        s_rendererData.rectVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

        s_rendererData.colorShader = Shader::Create("../../resources/shaders/ColorShader.glsl");
        s_rendererData.textureShader = Shader::Create("../../resources/shaders/TextureShader.glsl");
        s_rendererData.isBlending = true;
        s_rendererData.drawCalls =0;
   
    }
    void Renderer::Clear(const glm::vec4 &color)
    {
        glClearColor(color.r,color.g,color.b,color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::StartBatch(){
        s_rendererData.indicesCount = 0;
        s_rendererData.rectVertexBufferPtr = s_rendererData.rectVertexBufferBase;

    }
    void Renderer::FlushBatch(){
        if (s_rendererData.indicesCount == 0){
            return; 
        }

    
        uint dataSize = (uint)((uint8_t *)s_rendererData.rectVertexBufferPtr - (uint8_t *)s_rendererData.rectVertexBufferBase);
        s_rendererData.vertexBuffer->SetSubData(s_rendererData.rectVertexBufferBase, dataSize);
        s_rendererData.vertexArray->Bind();
        s_rendererData.colorShader->Bind();

        s_rendererData.colorShader->SetMat4("u_ViewProjection", s_rendererData.currentViewProjection);
        glDrawElements(GL_TRIANGLES, s_rendererData.indicesCount, GL_UNSIGNED_INT, 0);
        s_rendererData.drawCalls++;
    }

    void Renderer::BeginScene(const OrtoCamera &_camera)
    {
        if(s_rendererData.isBlending){
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        s_rendererData.currentViewProjection = _camera.GetViewProjectionMatrix();
        StartBatch();
        
    }
    void Renderer::DrawRect(const glm::vec2 _position, const glm::vec2 _size, const glm::vec4 _color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f),glm::vec3{_position,0.0f})*
        glm::scale(glm::mat4(1.0f), glm::vec3{_size.x, _size.y,1.0f});
    
        const size_t rectVertexCount = 4;
        //constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};


        if(s_rendererData.indicesCount >= s_rendererData.maxIndices){
            FlushBatch();
            StartBatch();
        }

        for (size_t i = 0; i < rectVertexCount; i++)
        {
            s_rendererData.rectVertexBufferPtr->position = transform * s_rendererData.rectVertexPositions[i];
            s_rendererData.rectVertexBufferPtr->color = _color;
            s_rendererData.rectVertexBufferPtr++;
        }
        s_rendererData.indicesCount += 6;
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
        //glDrawElements(GL_TRIANGLES, s_rendererData.indices.size(), GL_UNSIGNED_INT, 0);
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

        //glDrawElements(GL_TRIANGLES, s_rendererData.indices.size(), GL_UNSIGNED_INT, 0);
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
        //glDrawElements(GL_TRIANGLES, s_rendererData.indices.size(), GL_UNSIGNED_INT, 0);
    }
    void Renderer::EndScene(){
        FlushBatch();
    }
    void Renderer::Shutdown(){
        delete[] s_rendererData.rectVertexBufferBase;
    }
    void Renderer::SetBlending(bool _set){
        s_rendererData.isBlending =_set;
    }
}