#include "Shader.h"

namespace LightInDarkness{

    Shader::Shader(const std::string &_path)
    :m_shaderPath(_path)
    {

    }

    Shader::~Shader(){

    }

    void Shader::CreateFromString(const std::string &_source){

    }

    void Shader::Bind(){
        glUseProgram(m_shaderID);
    }

    void Shader::GetAllShaderUniforms()
    {
    }

    // UNIFORMS;
    void Shader::SetFloat(const std::string &_name, float _value){

    }
    void Shader::SetInt(const std::string &_name, int _value){

    }
    void Shader::SetMat4(const std::string &_name, const glm::mat4 &_value){

    }
    void Shader::SetMat3(const std::string &_name, const glm::mat3 &_value){

    }
    void Shader::SetVec4(const std::string &_name, const glm::vec4 &_value){

    }
    void Shader::SetVec3(const std::string &_name, const glm::vec3 &_value){

    }
    void Shader::SetVec2(const std::string &_name, const glm::vec2 &_value){
        
    }
}