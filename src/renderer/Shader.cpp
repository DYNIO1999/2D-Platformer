#include "Shader.h"
#include "core/Logger.h"
namespace LightInDarkness{

    Shader::Shader(const std::string &_path)
    :m_shaderPath(_path), m_isComputeShader{false}
    {
        std::string result = ReadShader();
        ParseShader(result);
        CompileShaders();
        GetAllShaderUniforms();
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
            if (shaderType == ShaderType::ComputeShader){
                m_isComputeShader = true;
                break;   
            }
        }
    }
    void Shader::CompileShaders(){
    

        std::vector<uint> shaderIDs;
        unsigned int program = glCreateProgram();


        for (const auto &item : m_shaders)
        {
            ShaderType type = item.first;
            std::string source = item.second;
            unsigned int shader = glCreateShader(static_cast<GLenum>(type));
            const GLchar* sourceCString = (const GLchar*)source.c_str(); 
            glShaderSource(shader, 1, &sourceCString, 0);
            glCompileShader(shader);
            
            int isCompiled{0};
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE){
                
                int maxLength{0};
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
                
                std::vector<char> log(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &log[0]);
                
                APP_ERROR("Shader compilation failed:\n {}",&log[0]);
                
                glDeleteShader(shader);

                APP_ASSERT_NO_INFO(false);
            }
            shaderIDs.push_back(shader);
            glAttachShader(program, shader);
        }
        glLinkProgram(program);

        int isLinked{0};
        glGetProgramiv(program, GL_LINK_STATUS,&isLinked);
        if(isLinked ==GL_FALSE){
            int maxLength{0};
            glGetProgramiv(program,GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> log(maxLength);
            glGetProgramInfoLog(program,maxLength,&maxLength,&log[0]);

            APP_ERROR("Shader linking failed:\n {}",&log[0]);

            glDeleteProgram(program);
            for (auto &it : shaderIDs)
            {
                glDeleteProgram(it);
            }
        }
        for(auto &it: shaderIDs){
            glDetachShader(program, it);
        }
        m_shaderID = program;
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
    void Shader::GetAllShaderUniforms()
    {   
        int numberUniforms{0};
        glGetProgramInterfaceiv(GetID(), GL_UNIFORM, GL_ACTIVE_RESOURCES, &numberUniforms);
        //APP_INFO("Active Uniforms: {}", numberUniforms);
        
        GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};
        
        for (int i = 0; i < numberUniforms;i++){
            std::vector<int> results(4);
            glGetProgramResourceiv(m_shaderID, GL_UNIFORM, i, 4, properties, 4, NULL, &results[0]);
            GLint nameBufSize = results[0]+1;

            std::vector<char> name(nameBufSize);
            glGetProgramResourceName(m_shaderID, GL_UNIFORM, i, nameBufSize, NULL, &name[0]);
            //APP_INFO("Uniform Name: {}", &name[0]);
            //APP_INFO("Uniform Location: {}", results[2]);
            std::string temp(&name[0]);
            m_uniformLocations[temp] = results[2];
        }
    }

    int Shader::GetUniformLocation(const std::string &_name){        
        if(m_uniformLocations.find(_name)!=m_uniformLocations.end()){
            return m_uniformLocations[_name];
        }
        APP_WARN("Cant find specifed uniform: NAME[{}] PATH [{}]", _name, m_shaderPath);
        return -1;
    }
    void Shader::SetFloat(const std::string &_name, float _value){
        glUniform1f(GetUniformLocation(_name), _value);
    }
    void Shader::SetInt(const std::string &_name, int _value){
        glUniform1i(GetUniformLocation(_name), _value);
    }
    void Shader::SetMat4(const std::string &_name, const glm::mat4 &_value){
        glUniformMatrix4fv(GetUniformLocation(_name), 1, GL_FALSE, glm::value_ptr(_value));
    }
    void Shader::SetMat3(const std::string &_name, const glm::mat3 &_value){
        glUniformMatrix3fv(GetUniformLocation(_name), 1, GL_FALSE, glm::value_ptr(_value));
    }
    void Shader::SetVec4(const std::string &_name, const glm::vec4 &_value){
        glUniform4f(GetUniformLocation(_name), _value.x, _value.y, _value.z, _value.w);
    }
    void Shader::SetVec3(const std::string &_name, const glm::vec3 &_value){
        glUniform3f(GetUniformLocation(_name), _value.x, _value.y, _value.z);
    }
    void Shader::SetVec2(const std::string &_name, const glm::vec2 &_value){
        glUniform2f(GetUniformLocation(_name), _value.x, _value.y);
    }
}