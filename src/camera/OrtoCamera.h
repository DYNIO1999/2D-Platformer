#ifndef _SRC_CAMERA_ORTO_CAMERA_H
#define _SRC_CAMERA_ORTO_CAMERA_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "core/App.h"
#include "events/MouseEvents.h"

namespace DEngine{
class OrtoCamera
{
public:
    OrtoCamera() = default;
    OrtoCamera(float _aspectRatio, float _zoom = 1.0f);
    ~OrtoCamera();

    void SetCamera(float _aspectRatio, float _zoom = 1.0f);
    void SetProjection(float _left, float _right, float _bottom, float _top);
    const glm::mat4& GetViewMatrix() const{return m_viewMatrix;}
    const glm::mat4 &GetProjectionMatrix() const { return m_projectionMatrix;}
    const glm::mat4 &GetViewProjectionMatrix() const { return m_viewProjectionMatrix;}
    void OnUpdate(float dt);
    void SetCameraSpeed(float _speed){
        m_cameraSpeed =_speed;
    }

    void SetZoom(float _zoom);

    void OnEvent();
private:

    void OnWindowResize(const Event &e);
    void OnMouseScrolledEvent(const Event &e);
    void UpdateViewMatrix();
    float m_zoom{1.0f};
    float m_aspectRatio{1.0f};
    float m_cameraSpeed{1.0f};
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_viewProjectionMatrix;
    glm::vec3 m_position{0.0f,0.0f,0.0f};
};
}
#endif