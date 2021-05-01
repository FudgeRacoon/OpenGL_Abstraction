#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>

class Shader
{
private:
    uint32_t programID;

public:
    Shader(const char* vertexShader, const char* fragmentShader);
    ~Shader();

private:
    void CreateShader(const char* filepath, int shaderType);
    std::string ParseShader(const char* filepath);
    
public:
    void SetBool(std::string varName, bool value) const;
    void SetInt(std::string varName, int value) const;
    void SetFloat(std::string varName, float value) const;
    void SetVec3f(std::string varName, float x, float y, float z) const;
    void SetVec3i(std::string varName, int x, int y, int z) const;
    void SetVec4f(std::string varName, float x, float y, float z, float w) const;
    void SetMat4f(std::string varName, float* value) const;

public:
    void Bind() const;
    void UnBind() const;
};

#endif