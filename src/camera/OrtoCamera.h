#ifndef _SRC_CAMERA_ORTO_CAMERA_H
#define _SRC_CAMERA_ORTO_CAMERA_H
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace LightInDarkness{
class OrtoCamera
{
public:
    OrtoCamera() = default;
    OrtoCamera(float _left, float _right, float _bottom, float _top);
    ~OrtoCamera();

    void SetProjection(float _left, float _right, float _bottom, float _top);
    const glm::mat4& GetViewMatrix() const{return m_viewMatrix;}
    const glm::mat4 &GetProjectionMatrix() const { return m_projectionMatrix;}
    const glm::mat4 &GetViewProjectionMatrix() const { return m_viewProjectionMatrix;}
    void OnUpdate(float dt);

private:
    void UpdateViewMatrix();
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_viewProjectionMatrix;
    glm::vec3 m_position{0.0f,0.0f,0.0f};
};
}
#endif