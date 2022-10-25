
#include "Input.h"
#include "core/App.h"
namespace DEngine
{
    bool Input::IsKeyPressed(int keycode)
    {
        auto &window = App::Get().GetWindow();
        auto state = glfwGetKey(window.GetGLFWWindow(), keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
       auto &window = App::Get().GetWindow();
       auto state = glfwGetMouseButton(window.GetGLFWWindow(), button);
       return state == GLFW_PRESS;
    }

    float Input::GetMouseX()
    {
        auto [x, y] = GetMousePosition();
        return (float)x;
    }

    float Input::GetMouseY()
    {
        auto [x, y] = GetMousePosition();
        return (float)y;
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        auto &window = App::Get().GetWindow();
        double x, y;
        glfwGetCursorPos(window.GetGLFWWindow(), &x, &y);
        return {(float)x, (float)y};
    }
}