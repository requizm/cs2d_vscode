#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <vector>

struct Layout
{
    unsigned int index;
    unsigned int type;
    int size;
    unsigned int offset;
};

class VertexBufferLayout
{
   public:
    VertexBufferLayout() = default;
    VertexBufferLayout(VertexBufferLayout &&) = default;
    VertexBufferLayout(const VertexBufferLayout &) = default;
    VertexBufferLayout &operator=(VertexBufferLayout &&) = default;
    VertexBufferLayout &operator=(const VertexBufferLayout &) = default;
    ~VertexBufferLayout() = default;

    void Add(int size, unsigned int type, std::size_t typeSize);

    std::size_t GetStride() const;

    std::vector<Layout> layouts;

   private:
    unsigned int currentIndex = 0;
    unsigned int currentOffset = 0;

    std::size_t stride = 0;
};

#endif  // VERTEXBUFFERLAYOUT_H