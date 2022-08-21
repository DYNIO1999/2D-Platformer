#ifndef _SRC_RENDERER_RENDERER_H_
#define _SRC_RENDERER_RENDERER_H_
#include <glm/glm.hpp>
#include <iostream>

#include "camera/OrtoCamera.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace LightInDarkness{

    static void openglErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const *message, void const *user_param)
    {

        auto const src_str = [source]()
        {
            switch (source)
            {
            case GL_DEBUG_SOURCE_API:
                return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                return "WINDOW SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                return "SHADER COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                return "THIRD PARTY";
            case GL_DEBUG_SOURCE_APPLICATION:
                return "APPLICATION";
            case GL_DEBUG_SOURCE_OTHER:
                return "OTHER";
            }
        }();

        auto const type_str = [type]()
        {
            switch (type)
            {
            case GL_DEBUG_TYPE_ERROR:
                return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY:
                return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE:
                return "PERFORMANCE";
            case GL_DEBUG_TYPE_MARKER:
                return "MARKER";
            case GL_DEBUG_TYPE_OTHER:
                return "OTHER";
            }
        }();

        auto const severity_str = [severity]()
        {
            switch (severity)
            {
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                return "NOTIFICATION";
            case GL_DEBUG_SEVERITY_LOW:
                return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM:
                return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH:
                return "HIGH";
            }
        }();

        if(severity!=GL_DEBUG_SEVERITY_NOTIFICATION){
        std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
        }
    }


struct VertexData{
    glm::vec3 position;
    glm::vec2 textureCords;
};

struct RendererData
{
    glm::mat4 currentViewProjection;
    std::shared_ptr<Shader> textureShader;
    std::shared_ptr<Shader> colorShader;
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<VertexBufferLayout> vertexBufferLayout;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::vector<VertexData> vertices;
    std::vector<uint> indices; 
    uint indexCount;
    bool isBlending;
};
class Renderer
{
public:
    static void Initialize();
    static void Clear(const glm::vec4& color);
    static void BeginScene(const OrtoCamera& _camera);

    static void DrawRect(const glm::vec2 _position, const glm::vec2 _size, const glm::vec4 _color);
    static void DrawRect(const glm::vec2 _position, const glm::vec2 _size, std::shared_ptr<Texture> _texture);

    static void DrawCircle(const glm::vec2 _position, float _radius, const glm::vec4 _color);

    static void DrawRotatedRect(const glm::vec2 _position, const glm::vec2 _size, float _rotation, const glm::vec4 _color);
    static void DrawRotatedRect(const glm::vec2 _position, const glm::vec2 _size, float _rotation, std::shared_ptr<Texture> _texture);


    static void FlushBatch();
    static void DrawLine();


    static void EndScene();
    static void Shutdown();
    static RendererData s_rendererData;
    static void SetBlending(bool _set);

private:
};
}
#endif