#include "Core/Mesh.h"

Mesh::Mesh() 
    : texture(nullptr), position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), 
      scale(glm::vec3(1.0f, 1.0f, 1.0f)), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {} 
Mesh::Mesh(float vertices[], uint32_t verticesSize, float texCoord[], uint32_t texCoordSize, uint32_t indicies[], uint32_t indiciesSize) 
    : texture(nullptr), position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), 
      scale(glm::vec3(1.0f, 1.0f, 1.0f)), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{  
    this->indiciesCount = indiciesSize / sizeof(uint32_t);
    buffer = new VertexBuffer(vertices, texCoord, indicies, verticesSize, texCoordSize, indiciesSize);
}
Mesh::~Mesh()
{
    delete this->buffer;
    delete this->texture;
}

void Mesh::AddTexture(const char* filepath)
{
    this->texture = new Texture(filepath);
}

VertexBuffer* Mesh::GetVertexBuffer()
{
    return this->buffer;
}
Texture* Mesh::GetTexture()
{
    return this->texture;
}
uint32_t Mesh::GetIndiciesCount()
{
    return this->indiciesCount;
}