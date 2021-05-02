#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>
#include <GL/glew.h>

class VertexBuffer
{
private:
    unsigned int VAO_ID;
    unsigned int EBO_ID;
    std::vector<uint32_t*> attribs;

public:
    VertexBuffer(float* vertices, float* texCoord, uint32_t* indicies, uint32_t verticesSize, uint32_t texCoordSize, uint32_t indiciesSize);
    ~VertexBuffer();

private:
    void CreateIndexBuffer(uint32_t indiciesSize, uint32_t* indices);

public:
    void AddAttribute(int index, const void* data, uint32_t size, uint32_t format, uint32_t stride);
    void Bind();
    void UnBind();
};

#endif