#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>

#include <cstddef>

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray
{
   public:
    VertexArray() = default;
    VertexArray(VertexArray &&) = default;
    VertexArray(const VertexArray &) = default;
    VertexArray &operator=(VertexArray &&) = default;
    VertexArray &operator=(const VertexArray &) = default;
    ~VertexArray();

    void Init();
    void Bind();
    void Unbind();

    void AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout);

   private:
    unsigned int id = 0;
};

#endif  // VERTEXARRAY_H