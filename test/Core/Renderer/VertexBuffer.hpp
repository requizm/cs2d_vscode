#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>

#include <cstddef>

class VertexBuffer
{
   public:
    VertexBuffer() = default;
    VertexBuffer(VertexBuffer &&) = default;
    VertexBuffer(const VertexBuffer &) = default;
    VertexBuffer &operator=(VertexBuffer &&) = default;
    VertexBuffer &operator=(const VertexBuffer &) = default;
    ~VertexBuffer();

    void Init(std::size_t size);
    void Init(float *data, std::size_t size);

    void Bind() const;
    void Unbind() const;
    void ChangeData(unsigned int offset, float *data, std::size_t size);

   private:
    unsigned int id = 0;
};

#endif  // VERTEXBUFFER_H