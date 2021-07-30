#ifndef BATCHRENDERER_H
#define BATCHRENDERER_H

#include "../../../src/Core/Math/Matrix4.hpp"
#include "../../../src/Core/Renderer/Shader.hpp"
#include "OutlineTest.hpp"

class BatchRenderer
{
   public:
    BatchRenderer() = default;
    BatchRenderer(bool init);
    BatchRenderer(BatchRenderer &&) = default;
    BatchRenderer(const BatchRenderer &) = default;
    BatchRenderer &operator=(BatchRenderer &&) = default;
    BatchRenderer &operator=(const BatchRenderer &) = default;
    ~BatchRenderer() = default;

    VertexOne gaycums[24];

    void AddRectangle(const Vector3<int> &position, const Vector2<int> &size,
                      const Vector3<float> &color,
                      float transperancy = 1.0F, int rotate = 0);
    void Draw();

    OutlineTest outline;
    Shader batchShader_ui;

    int index = 0;
};


#endif  // BATCHRENDERER_H