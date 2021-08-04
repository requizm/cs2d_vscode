#ifndef OUTLINETEST_H
#define OUTLINETEST_H

#include <GL/glew.h>

#include "VertexArray.hpp"

struct VertexOne
{
    float vertex[2];
    float model_1[4];
    float model_2[4];
    float model_3[4];
    float model_4[4];
    float color[3];
    float trans;
};

class OutlineTest
{
   public:
    OutlineTest() = default;
    ~OutlineTest() = default;

    void initData();

    VertexArray va;
    VertexBuffer vb, ib;
};
#endif  // OUTLINETEST_H
