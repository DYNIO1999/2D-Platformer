#ifndef _SRC_SCENES_TEST_SCENE_H_
#define _SRC_SCENES_TEST_SCENE_H_
#include <iostream>

#include "core/SceneManager.h"
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

        float vertices[12] = {
            -1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f};
        uint indices[6] = {
            0, 1, 2,
            2, 3, 0};

        uint VBO;
        uint IBO;
        uint VAO;

        GLuint shaderProgram;

        const char *vertexShaderSource = R"(#version 460 core
layout (location = 0) in vec3 pos;
void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.000);
})";
        const char *fragmentShaderSource = R"(#version 460 core
out vec4 FragColor;
void main()
{
	FragColor = vec4(0.965, 0.318, 0.000, 1.000);
})";

    private:
    };
}
#endif
