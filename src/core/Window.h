#ifndef _SRC_CORE_WINDOW_H_
#define _SRC_CORE_WINDOW_H_
#include<iostream>
#include<string>
#include <cassert>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "events/EventDispatcher.h"
#include "events/WindowEvents.h"

namespace LightInDarkness{

struct WindowProperties
{
    WindowProperties(const std::string& title = "Light In Darkness",
    int width = 1600,
    int height = 900
    ):
    title(title),
    width(width),
    height(height)
    {
    }

    std::string title;
    int width;
    int height;
};

class Window
{
public:

    Window(const WindowProperties& props):
    m_windowData(props)
    {
        Initialize();
    }
    ~Window(){
        Shutdown();
    }
    GLFWwindow *GetGLFWWindow() const { return m_window;};

    auto GetWindowSize() {
        return std::pair<int, int>(m_windowData.width, m_windowData.height);
    }

    void Update();
    void SetVSync(bool set);
    bool IsVSync()const{return m_vSync;}
private:
    void Initialize();
    void Shutdown();
    bool m_vSync;
    GLFWwindow* m_window;
    WindowProperties m_windowData;
};
}
#endif