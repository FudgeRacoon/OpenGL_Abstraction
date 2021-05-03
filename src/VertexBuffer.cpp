#include "Core/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* vertices, float* texCoord, uint32_t* indicies, uint32_t verticesSize, uint32_t texCoordSize, uint32_t indiciesSize)
{
    //Create a vertex array object to store VBOs
    glGenVertexArrays(1, &this->VAO_ID);
    glBindVertexArray(this->VAO_ID);

    //Add the vertices position attribute
    this->AddAttribute(0, vertices, verticesSize, 3, 3 * sizeof(float));
    this->AddAttribute(1, texCoord, texCoordSize, 2, 2 * sizeof(float));
    
    //Create an index buffer
    this->CreateIndexBuffer(indiciesSize, indicies);

    glBindVertexArray(0);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteVertexArrays(1, &this->VAO_ID);

    for(auto& attrib : this->attribs)
        glDeleteBuffers(1, attrib);

    this->attribs.clear();
}

void VertexBuffer::AddAttribute(int index, const void* data, uint32_t size, uint32_t format, uint32_t stride)
{   
    uint32_t* vertexBufferObject = new uint32_t;

    //Bind the VAO the attribute will be added to
    glBindVertexArray(this->VAO_ID);

    //Create a vertex buffer object and bind to the GL_ARRAY_BUFFER
    glGenBuffers(1, vertexBufferObject);   
    glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    //Insert into the vertex array object
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, format, GL_FLOAT, GL_FALSE, stride, 0);

    //Unbind the the current VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->attribs.push_back(vertexBufferObject);
}
void VertexBuffer::CreateIndexBuffer(uint32_t indiciesSize, uint32_t* indicies)
{
    //Create an element buffer object and bind to the GL_ELEMENT_ARRAY_BUFFER
    glGenBuffers(1, &this->EBO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesSize, indicies, GL_STATIC_DRAW);

    //Unbind the current EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    this->attribs.push_back(&EBO_ID);
}
void VertexBuffer::Bind()
{
    glBindVertexArray(this->VAO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
}
void VertexBuffer::UnBind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
}