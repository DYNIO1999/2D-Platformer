#include "Window.h"
#include "App.h"
namespace DEngine{
    void Window::Initialize()
    {




        int check = glfwInit();
        assert(check != 0 && "Could not intialize GLFW!");

        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_windowData.width, m_windowData.height, m_windowData.title.c_str(), nullptr,nullptr);
        glfwMakeContextCurrent(m_window);
        check = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        assert(check != 0 && "Could not load OpenGL functions!");

        glfwSetWindowUserPointer(m_window,&m_windowData);

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height)
                                  {
			auto& data = *((WindowProperties*)glfwGetWindowUserPointer(window));
			data.width = width;
			data.height = height;
            App::s_eventDispatcher.DispatchAll(WindowResizeEvent(width,height));
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window)
        {
			glfwGetWindowUserPointer(window);
            App::s_eventDispatcher.DispatchAll(WindowCloseEvent());
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xoffset, double yoffset) {

            (void)window;
            App::s_eventDispatcher.DispatchAll(MouseScrolledEvent((float)xoffset,(float)yoffset));
        });
        SetVSync(true);
    }
    void Window::Shutdown()
    {

    }
    void Window::Update(){
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void Window::SetVSync(bool set){
        if(set){
            glfwSwapInterval(1);
        }else{
            glfwSwapInterval(0);
        }
        m_vSync =set;
    }

}