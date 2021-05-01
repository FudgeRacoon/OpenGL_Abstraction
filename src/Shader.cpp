#include "Core/Shader.h"

Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
    this->programID = glCreateProgram();

    if(this->programID == 0)
        std::cerr << "Failed to create program" << '\n';

    CreateShader(vertexShader, GL_VERTEX_SHADER);
    CreateShader(fragmentShader, GL_FRAGMENT_SHADER);

    glLinkProgram(this->programID);
    glValidateProgram(this->programID);

    int result;
    char log[512];
    glGetProgramiv(this->programID, GL_LINK_STATUS, &result);

    if(result == 0)
    {
        glGetProgramInfoLog(this->programID, 512, nullptr, log);
        std::cerr << "LINKING FAILED\n" << log << '\n';
        return;
    }
}
Shader::~Shader()
{
    glDeleteProgram(this->programID);
}

void Shader::CreateShader(const char* filepath, int shaderType)
{
    std::string source = ParseShader(filepath);
    if(source.empty())
        return;
        
    const char* c_source = source.c_str();

    int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &c_source, nullptr);
    glCompileShader(shader);

    int result = 0;
    char log[512] = {0};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if(result == 0)
    {
        std::string s_shaderType;
        if(shaderType == GL_VERTEX_SHADER)
            s_shaderType = "Vertex Shader";
        else if(shaderType == GL_FRAGMENT_SHADER)
            s_shaderType = "Fragment Shader";
            
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "COMPILATION_FAILED: " << s_shaderType << '\n' << log << '\n';
        return;
    }

    glAttachShader(this->programID, shader);
    glDeleteShader(shader);
}
std::string Shader::ParseShader(const char* filepath)
{
    std::fstream file(filepath, std::ios::in);

    if(!file)
    {
        std::cerr << "Failed to open shader file" << '\n';
        return "";
    }

    std::string line;
    std::stringstream ss;

    while(getline(file, line))
        ss << line << '\n';

    return ss.str();
}

void Shader::SetBool(std::string varName, bool value) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1i(uniformID, value);
}
void Shader::SetInt(std::string varName, int value) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1i(uniformID, value);
}
void Shader::SetFloat(std::string varName, float value) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1f(uniformID, value);
}
void Shader::SetVec3f(std::string varName, float x, float y, float z) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform3f(uniformID, x, y, z);
}
void Shader::SetVec3i(std::string varName, int x, int y, int z) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform3i(uniformID, x, y, z);
}
void Shader::SetVec4f(std::string varName, float x, float y, float z, float w) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform4f(uniformID, x, y, z, w);
}
void Shader::SetMat4f(std::string varName, float* value) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniformMatrix4fv(uniformID, 1, false, value);
}

void Shader::Bind() const
{
    glUseProgram(this->programID);
}
void Shader::UnBind() const
{
    glUseProgram(0);
}