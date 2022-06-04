#include "Shader.h"
#include "core/Logger.h"
namespace LightInDarkness{

    Shader::Shader(const std::string &_path)
    :m_shaderPath(_path), m_isComputeShader{false}
    {
        std::string result = ReadShader();
        ParseShader(result);
    }

    Shader::~Shader(){

    }
    std::shared_ptr<Shader> Shader::Create(const std::string &_path)
    {
        std::shared_ptr<Shader> shader = nullptr;
        shader = std::make_shared<Shader>(_path);
        return shader;
    }

    void Shader::Bind(){
        glUseProgram(m_shaderID);
    }
    std::string Shader::ReadShader(){
        std::string shaderSource;
        std::ifstream shaderFile(m_shaderPath, std::ios::in | std::ios::binary);
        if(shaderFile){
            shaderFile.seekg(0, std::ios::end);
            shaderSource.resize(shaderFile.tellg());
            shaderFile.seekg(0, std::ios::beg);
            shaderFile.read(&shaderSource[0], shaderSource.size());
            shaderFile.close();
        }else{
            assert(shaderFile && "Couldnt load shader!");
        }
        return shaderSource;
    }
    void Shader::ParseShader(const std::string &_source)
    {
        const char *typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = _source.find(typeToken, 0);

        while(pos!=std::string::npos){
            size_t endOfLine =  _source.find_first_of("\n",pos);
            assert(endOfLine != std::string::npos && "Syntax Error");
            size_t  begin = pos + typeTokenLength +1;
            std::string type = _source.substr(begin, endOfLine-begin);
            assert(type == "vertex" || type == "fragment" || type == "compute" && "Invalid shader type specified");

            size_t nextLinePosition = _source.find_first_not_of("\n",endOfLine);
            pos = _source.find(typeToken, nextLinePosition);
            auto shaderType  =CheckShaderType(type);
            m_shaders[shaderType] = _source.substr(nextLinePosition, pos - (nextLinePosition == std::string::npos ? _source.size() - 1 : nextLinePosition));
        }
    }
    ShaderType Shader::CheckShaderType(const std::string &_type){
        if (_type == "vertex")
            return ShaderType::VertexShader;
        if (_type == "fragment")
            return ShaderType::FragmentShader;
        if(_type == "tessellation_control")
            return ShaderType::TessellationControlShader;
        if (_type == "tessellation_evaluation")
            return ShaderType::TessellationEvaluationShader;
        if (_type == "compute")
            return ShaderType::ComputeShader;
        return ShaderType::NoneShader;
    }

    //GET ALL UNIFORMS

    /*
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
printf("Active Uniforms: %d\n", count);

for (i = 0; i < count; i++)
{
    glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);

    printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
}

    */

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