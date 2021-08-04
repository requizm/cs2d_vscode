#include "EmptyRect.hpp"

void EmptyRect::initData(unsigned int vertexCount)
{
    va.Init();
    vb.Init(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex_EmptyRect));
    VertexBufferLayout layout;
    layout.Add(2, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(4, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(4, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(4, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(4, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(3, GL_FLOAT, sizeof(GL_FLOAT));
    layout.Add(1, GL_FLOAT, sizeof(GL_FLOAT));

    vb.Bind();
    ib.Init(GL_ELEMENT_ARRAY_BUFFER, (vertexCount + ((vertexCount / 4) - 1)) * sizeof(unsigned int));
    vb.Unbind();

    va.AddBuffer(vb, layout);
}