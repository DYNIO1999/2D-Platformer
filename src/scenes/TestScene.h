#ifndef _SRC_SCENES_TEST_SCENE_H_
#define _SRC_SCENES_TEST_SCENE_H_
#include <iostream>

#include "core/SceneManager.h"
#include "camera/OrtoCamera.h"
#include "renderer/Renderer.h"


namespace LightInDarkness
{
    class TestScene : public Scene
    {
    public:
        TestScene();
        ~TestScene();

        void OnInit()override;
        void OnEvent() override;
        void OnUpdate(float dt) override;
        void OnShutdown() override;

        float vertices[20] = {
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 
            };
        uint indices[6] = {
            0, 1, 3, 
            1, 2, 3  
        };

        uint VBO;
        uint IBO;
        uint VAO;

        GLuint shaderProgram;
        VertexArray vertexArrayObj;        
        std::shared_ptr<Shader> testShader;
        std::shared_ptr<Texture> testTexture;
        
        OrtoCamera m_camera;

    private:
    };
}
#endif
