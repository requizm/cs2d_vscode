#include "VertexBuffer.hpp"

VertexBuffer::~VertexBuffer()
{
    if (id != 0)
        glDeleteBuffers(1, &id);
}

void VertexBuffer::Init(unsigned int type, std::size_t size)
{
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    glBufferData(type, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(type, 0);
    this->type = type;
}

void VertexBuffer::Init(unsigned int type, float *data, std::size_t size)
{
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    glBufferData(type, size, data, GL_DYNAMIC_DRAW);
    glBindBuffer(type, 0);
    this->type = type;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(type, id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(type, 0);
}

void VertexBuffer::ChangeData(unsigned int offset, float *data, std::size_t size)
{
    glBindBuffer(type, id);
    glBufferSubData(type, offset, size, data);
    glBindBuffer(type, 0);
}

void VertexBuffer::ChangeData(unsigned int offset, unsigned int *data, std::size_t size)
{
    glBindBuffer(type, id);
    glBufferSubData(type, offset, size, data);
    glBindBuffer(type, 0);
}

void VertexBuffer::Resize(std::size_t size, float *data)
{
    glBindBuffer(type, id);
    glBufferData(type, size, data, GL_DYNAMIC_DRAW);
    glBindBuffer(type, 0);
}

void VertexBuffer::Resize(std::size_t size)
{
    glBindBuffer(type, id);
    glBufferData(type, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(type, 0);
}