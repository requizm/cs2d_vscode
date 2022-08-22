#ifndef EDITORMAPRENDERER_H
#define EDITORMAPRENDERER_H

#include <memory>

#include "../../Core/Math/Matrix4.hpp"
#include "../../Core/Math/Vector2.hpp"
#include "../../Core/Math/Vector3.hpp"
#include "../../Core/Renderer/Shader.hpp"
#include "EmptyRect.hpp"

class EditorMapRenderer
{
   public:
    EditorMapRenderer() = default;
    EditorMapRenderer(EditorMapRenderer &&) = default;
    EditorMapRenderer(const EditorMapRenderer &) = default;
    EditorMapRenderer &operator=(EditorMapRenderer &&) = default;
    EditorMapRenderer &operator=(const EditorMapRenderer &) = default;
    ~EditorMapRenderer() = default;

    void init(unsigned int tileCount);
    void addRect(const Vector2<int> &position,
                 const Vector2<int> &size,
                 const Vector3<float> &color,
                 float transperancy, int rotate);
    void updateData();
    void render();

    void setProjection(const Matrix4<float> &projection);


   private:
    // EmptyRect properties

    std::unique_ptr<Vertex_EmptyRect[]> er_vertices;
    std::unique_ptr<unsigned int[]> er_indices;
    unsigned int er_index = 0;
    unsigned int er_indicesIndex = 0;
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;
    EmptyRect emptyRects;
    Shader batchShader_world;

    float l1[2] = {0.0F, 1.0F};
    float l2[2] = {1.0F, 1.0F};
    float l3[2] = {1.0F, 0.0F};
    float l4[2] = {0.0F, 0.0F};
};

#endif  // EDITORMAPRENDERER_H