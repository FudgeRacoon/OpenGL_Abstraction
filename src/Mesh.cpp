#include "Core/Mesh.h"

Mesh::Mesh() 
    : texture(nullptr), position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), 
      scale(glm::vec3(1.0f, 1.0f, 1.0f)), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {} 
Mesh::Mesh(float vertices[], uint32_t verticesSize, uint32_t indicies[], uint32_t indiciesSize) 
    : position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), 
      scale(glm::vec3(1.0f, 1.0f, 1.0f)), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{  
    this->indiciesCount = indiciesSize / sizeof(uint32_t);
    buffer = new VertexBuffer(vertices, indicies, verticesSize, indiciesSize);
}
Mesh::~Mesh()
{
    delete this->buffer;
    delete this->texture;
}

void Mesh::AddTexture(const char* filepath, float* texCoord, uint32_t texCoordSize)
{
    this->texture = new Texture(filepath);
    this->buffer->AddAttribute(1, texCoord, texCoordSize, 2, 2 * sizeof(float));
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