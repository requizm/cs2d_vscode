#include "VertexBufferLayout.hpp"

void VertexBufferLayout::Add(int size, unsigned int type, std::size_t typeSize)
{
    Layout layout;
    layout.offset = currentOffset;

    layout.type = type;
    layout.size = size;

    layout.index = currentIndex++;

    currentOffset += size * typeSize;
    stride += size * typeSize;

    layouts.push_back(layout);
}

std::size_t VertexBufferLayout::GetStride() const
{
    return stride;
}
