
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
    int Input::s_oldMouseStatus = GLFW_RELEASE;

    bool Input::IsMouseButtonPressedOnce(int button)
    {
        bool state = false;
        auto &window = App::Get().GetWindow();
        auto status = glfwGetMouseButton(window.GetGLFWWindow(), button);
        if (status == GLFW_RELEASE && s_oldMouseStatus == GLFW_PRESS){
            state = true;
        }
        s_oldMouseStatus= status;
        return state;
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
    
    int Input::s_oldKeyStatus = GLFW_RELEASE;
    bool Input::IsKeyPressedOnce(int key)
    {
        bool state = false;
        auto &window = App::Get().GetWindow();
        int status = glfwGetKey(window.GetGLFWWindow(), key);
        if (status == GLFW_RELEASE && s_oldKeyStatus == GLFW_PRESS)
        {
            state = true;
        }
        s_oldKeyStatus = status;
        return state;
    }
}