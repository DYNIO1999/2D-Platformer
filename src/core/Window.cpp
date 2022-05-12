#include "Window.h"
#include "App.h"
namespace LightInDarkness{
    void Window::Initialize()
    {
        int check = glfwInit();
        assert(check != 0 && "Could not intialize GLFW!");
        m_window = glfwCreateWindow(m_windowData.width, m_windowData.height, m_windowData.title.c_str(), nullptr,nullptr);
        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1); //VSync
        glfwSetWindowUserPointer(m_window,&m_windowData);
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window)
                                   {
			glfwGetWindowUserPointer(window);
            App::s_eventDispatcher.DispatchAll(WindowCloseEvent());
            });
    }
    void Window::Shutdown()
    {

    }
}