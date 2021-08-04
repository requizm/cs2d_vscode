#ifndef EmptyRect_H
#define EmptyRect_H

#include <GL/glew.h>

#include "../../Core/Renderer/VertexArray.hpp"

struct Vertex_EmptyRect
{
    float vertex[2];
    float model_1[4];
    float model_2[4];
    float model_3[4];
    float model_4[4];
    float color[3];
    float trans;
};

class EmptyRect
{
   public:
    EmptyRect() = default;
    ~EmptyRect() = default;

    void initData(unsigned int vertexCount);

    VertexArray va;
    VertexBuffer vb, ib;
};
#endif  // EmptyRect_H
