#include "OutlineTest.hpp"

void OutlineTest::initData()
{
    va.Init();
    vb.Init(24 * sizeof(VertexOne));
    VertexBufferLayout layout;
    layout.Add(2, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(4, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(4, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(4, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(4, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(3, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(1, GL_FLOAT, sizeof(GL_FLOAT));

    va.AddBuffer(vb, layout);
}