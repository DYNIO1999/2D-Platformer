#include "OrtoCamera.h"

namespace LightInDarkness{

    OrtoCamera::OrtoCamera(float _left, float _right, float _bottom, float _top):
    m_projectionMatrix(glm::ortho(_left,_right,_bottom,_top,-1.0f,1.0f)),
    m_viewMatrix(1.0f)
    {
        m_viewProjectionMatrix =  m_projectionMatrix* m_viewMatrix;
    }
    OrtoCamera::~OrtoCamera(){

    }
    void OrtoCamera::UpdateViewMatrix(){
        glm::mat4 transformMatrix = glm::translate(glm::mat4(1), m_position);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
    void OrtoCamera::SetProjection(float _left, float _right, float _bottom, float _top)
    {
        m_viewMatrix =  glm::mat4(1.0f);
        m_projectionMatrix = glm::ortho(_left, _right, _bottom, _top, -1.0f, 1.0f);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
    void OrtoCamera::OnUpdate(float dt){

    }
}