#include "OrtoCamera.h"
#include "input/Input.h"
#include "core/Logger.h"


namespace DEngine{


    OrtoCamera::OrtoCamera(float _aspectRatio, float _zoom):
    m_aspectRatio(_aspectRatio)
    {
        m_aspectRatio = _aspectRatio;
        m_zoom = _zoom;
        auto &window = App::Get();
        window.s_eventDispatcher.Subscribe<WindowResizeEvent>(BIND_EVENT_FUNCTION(OrtoCamera::OnWindowResize));
        window.s_eventDispatcher.Subscribe<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OrtoCamera::OnMouseScrolledEvent));
        SetProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);
    }

    void OrtoCamera::SetCamera(float _aspectRatio, float _zoom)
    {
        m_aspectRatio = _aspectRatio;
        m_zoom = _zoom;
        auto &window = App::Get();
        window.s_eventDispatcher.Subscribe<WindowResizeEvent>(BIND_EVENT_FUNCTION(OrtoCamera::OnWindowResize));
        window.s_eventDispatcher.Subscribe<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OrtoCamera::OnMouseScrolledEvent));
        SetProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);
    }
    OrtoCamera::~OrtoCamera(){

    }
    void OrtoCamera::SetProjection(float _left, float _right, float _bottom, float _top)
    {
        m_viewMatrix =  glm::mat4(1.0f);
        m_projectionMatrix = glm::ortho(_left, _right, _bottom, _top, -1.0f, 1.0f);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    
    void OrtoCamera::UpdateViewMatrix()
    {
        glm::mat4 transformMatrix = glm::translate(glm::mat4(1), m_position);
        m_viewMatrix = glm::inverse(transformMatrix);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrtoCamera::OnUpdate(float dt){

        
        if (Input::IsKeyPressed(GLFW_KEY_W))
        {
        m_position += glm::vec3(0.0f, m_cameraSpeed, 0.0f) * dt;
        }
        if (Input::IsKeyPressed(GLFW_KEY_S))
        {
            m_position += glm::vec3(0.0f, -m_cameraSpeed, 0.0f)*dt;
        }
        if(Input::IsKeyPressed(GLFW_KEY_A)){
            m_position += glm::vec3(-m_cameraSpeed,0.0f,0.0f)*dt;
        }
        if(Input::IsKeyPressed(GLFW_KEY_D)){
            m_position += glm::vec3(m_cameraSpeed,0.0f,0.0f)*dt;
        }
        UpdateViewMatrix();
    }


    void OrtoCamera::OnEvent(){

    }
    void OrtoCamera::OnWindowResize(const Event &e)
    {
        auto &window = App::Get();
        auto event = window.s_eventDispatcher.Cast<WindowResizeEvent>(e);
        SetCamera(event.m_width/event.m_height,m_zoom);
        glViewport(0.0, 0.0, event.m_width, event.m_height);
    }
    void OrtoCamera::OnMouseScrolledEvent(const Event &e)
    {
        auto event = App::s_eventDispatcher.Cast<MouseScrolledEvent>(e);
        SetZoom(event.m_yoffset);

    }
    void OrtoCamera::SetZoom(float _zoom)
    {
        m_zoom -= _zoom;
        m_zoom = std::max(m_zoom, 0.25f);
        SetProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);

    }
}