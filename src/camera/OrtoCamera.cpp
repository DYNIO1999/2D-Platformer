#include "OrtoCamera.h"
#include "input/Input.h"
#include "core/Logger.h"


namespace LightInDarkness{

    OrtoCamera::OrtoCamera(float _left, float _right, float _bottom, float _top):
    m_projectionMatrix(glm::ortho(_left,_right,_bottom,_top,-1.0f,1.0f)),
    m_viewMatrix(1.0f)
    {
        auto &window = App::Get();
        window.s_eventDispatcher.Subscribe<WindowResizeEvent>(BIND_EVENT_FUNCTION(OrtoCamera::OnWindowResize));

        m_viewProjectionMatrix =  m_projectionMatrix* m_viewMatrix;
    }

    OrtoCamera::OrtoCamera(float _aspectRatio){
        
    }

    OrtoCamera::~OrtoCamera(){

    }
    void OrtoCamera::SetProjection(float _left, float _right, float _bottom, float _top)
    {
        auto &window = App::Get();
        window.s_eventDispatcher.Subscribe<WindowResizeEvent>(BIND_EVENT_FUNCTION(OrtoCamera::OnWindowResize));
        m_viewMatrix =  glm::mat4(1.0f);
        m_projectionMatrix = glm::ortho(_left, _right, _bottom, _top, -1.0f, 1.0f);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
    void OrtoCamera::SetProjection(float _aspectRatio){
        
    }
    
    void OrtoCamera::UpdateViewMatrix()
    {
        glm::mat4 transformMatrix = glm::translate(glm::mat4(1), m_position);
        m_viewMatrix = glm::inverse(transformMatrix);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrtoCamera::OnUpdate(float dt){

        APP_INFO("CAMERA POSITION: {} {} {}", m_position.x, m_position.y, m_position.z);
        
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
        APP_ERROR("CAMERA EVENT RESIZE {} {}", event.m_width, event.m_height);
        glViewport(0.0, 0.0, event.m_width, event.m_height);
    }
}