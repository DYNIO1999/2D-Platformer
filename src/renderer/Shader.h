#ifndef _SRC_RENDERER_SHADER_H_
#define _SRC_RENDERER_SHADER_H_
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/Assert.h"

namespace LightInDarkness
{
    enum class ShaderType :GLenum{
        NoneShader  = GL_NONE,
        VertexShader = GL_VERTEX_SHADER,
        FragmentShader = GL_FRAGMENT_SHADER,
        GeometryShader = GL_GEOMETRY_SHADER,
        TessellationControlShader = GL_TESS_CONTROL_SHADER,
        TessellationEvaluationShader= GL_TESS_EVALUATION_SHADER,
        ComputeShader = GL_COMPUTE_SHADER,
    };
    //ONE FILE SHADER ?
    class Shader
    {
    public:
        Shader() =default;
        Shader(const std::string& _path);
        ~Shader();
        static std::shared_ptr<Shader> Create(const std::string &_path);

        void Bind();

        

        //UNIFORMS;
        void SetFloat(const std::string& _name, float _value);
        void SetInt(const std::string& _name, int _value);
        void SetMat4(const std::string& _name, const glm::mat4& _value);
        void SetMat3(const std::string &_name, const glm::mat3 &_value);
        void SetVec4(const std::string &_name, const glm::vec4 &_value);
        void SetVec3(const std::string &_name, const glm::vec3 &_value);
        void SetVec2(const std::string &_name, const glm::vec2 &_value);
        uint GetID(){return m_shaderID;};
    private:
        void ParseShader(const std::string &_source);
        void CompileShaders();
        void GetAllShaderUniforms();
        std::string ReadShader();
        ShaderType CheckShaderType(const std::string& _type);
        int GetUniformLocation(const std::string &_name);

        std::unordered_map<ShaderType, std::string> m_shaders;
        std::unordered_map<std::string,int> m_uniformLocations;
        
        std::string m_shaderPath;
        bool m_isComputeShader;
        unsigned int m_shaderID;
    };    
} 

#endif