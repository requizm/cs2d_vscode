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

    void Init(unsigned int type, std::size_t size);
    void Init(unsigned int type, float *data, std::size_t size);

    void Bind() const;
    void Unbind() const;
    void ChangeData(unsigned int offset, float *data, std::size_t size);
    void ChangeData(unsigned int offset, unsigned int *data, std::size_t size);
    void Resize(std::size_t size, float *data);
    void Resize(std::size_t size);

   private:
    unsigned int id = 0;

    unsigned int type;
};

#endif  // VERTEXBUFFER_H