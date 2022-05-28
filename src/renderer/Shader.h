#ifndef _SRC_RENDERER_SHADER_H_
#define _SRC_RENDERER_SHADER_H
#include <unordered_map>
#include <string>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace LightInDarkness
{
    //ONE FILE SHADER ?
    class Shader
    {
    public:
        Shader() =default;
        
        Shader(const std::string& _path);
        
        ~Shader();
        
        void CreateFromString(const std::string& _source);
        
        void Bind();
        

        //UNIFORMS;
        void SetFloat(const std::string& _name, float _value);
        void SetInt(const std::string& _name, int _value);
        void SetMat4(const std::string& _name, const glm::mat4& _value);
        void SetMat3(const std::string &_name, const glm::mat3 &_value);
        void SetVec4(const std::string &_name, const glm::vec4 &_value);
        void SetVec3(const std::string &_name, const glm::vec3 &_value);
        void SetVec2(const std::string &_name, const glm::vec2 &_value);

    private:
        std::string m_shaderPath;
        unsigned int m_shaderID;
        void GetAllShaderUniforms();
        std::unordered_map<std::string,int> m_uniformLocations; //? Not sure if that will work need to figure it out!
    };    
} 

#endif