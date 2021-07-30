#include "VertexArray.hpp"

VertexArray::~VertexArray()
{
    if (id != 0)
        glDeleteVertexArrays(1, &id);
}

void VertexArray::Init()
{
    glGenVertexArrays(1, &id);
}

void VertexArray::Bind()
{
    glBindVertexArray(id);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout)
{
    glBindVertexArray(id);
    buffer.Bind();
    const std::size_t stride = layout.GetStride();
    int i = 0;
    for (auto &ly : layout.layouts)
    {
        glEnableVertexAttribArray(i++);
        glVertexAttribPointer(ly.index, ly.size, ly.type, GL_FALSE, stride, (GLvoid *)ly.offset);
    }
    buffer.Unbind();
    glBindVertexArray(0);
}
