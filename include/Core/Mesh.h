#ifndef MESH_H
#define MESH_H

#include <stdint.h>
#include <vector>
#include "glm/glm.hpp"
#include "Core/VertexBuffer.h"
#include "Core/Texture.h"

class Mesh
{
private:
    VertexBuffer* buffer;
    Texture* texture;
    uint32_t indiciesCount;

public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

public:
    glm::vec4 color;

public:
    Mesh();
    Mesh(float vertices[], uint32_t verticesSize, uint32_t indicies[], uint32_t indiciesSize);
    ~Mesh();

public:
    void AddTexture(const char* filepath, float* texCoord, uint32_t texCoordSize);

public:
    VertexBuffer* GetVertexBuffer();
    Texture* GetTexture();
    uint32_t GetIndiciesCount();
};

#endif