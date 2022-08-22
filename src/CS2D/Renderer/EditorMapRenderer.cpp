#include "EditorMapRenderer.hpp"

#include <cstring>

#include "../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../Core/Manager/ResourceManager.hpp"
#include "../../Core/Math/Projection.hpp"
#include "../Other/GameParameters.hpp"

void EditorMapRenderer::init(unsigned int tileCount)
{
    this->batchShader_world = ResourceManager::LoadShader(
        GameParameters::resDirectory + "shaders/batchVertex.txt",
        GameParameters::resDirectory + "shaders/batchFragment.txt", "",
        "batch");
    this->batchShader_world.Use();
    Matrix4<float> proj = Projection::ortho(0.0f,
                                            static_cast<float>(GameParameters::SCREEN_WIDTH),
                                            static_cast<float>(GameParameters::SCREEN_HEIGHT),
                                            0.0f, -1.0f, 1.0f);
    this->batchShader_world.SetMatrix4("projection", proj);

    vertexCount = tileCount * 4;
    indexCount = (tileCount * 4) + ((tileCount)-1);

    emptyRects.initData(vertexCount);
    er_vertices = std::unique_ptr<Vertex_EmptyRect[]>(new Vertex_EmptyRect[vertexCount]);
    er_indices = std::unique_ptr<unsigned int[]>(new unsigned int[indexCount]);
}

void EditorMapRenderer::addRect(const Vector2<int> &position,
                                const Vector2<int> &size,
                                const Vector3<float> &color,
                                float transperancy, int rotate)
{
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0F));  // First translate (transformations are: scale happens
                         // first, then rotation and then finall translation
                         // happens; reversed order)
    // model = Projection::translate(model, Vector3(position.x, position.y,
    // 0.0f));
    model = Projection::translate(
        model, Vector3(0.5f * static_cast<float>(size.x),
                       0.5f * static_cast<float>(size.y),
                       0.0f));  // Move origin of rotation to center of quad
    model = Projection::rotate(model,
                               Projection::radians(static_cast<float>(rotate)),
                               Vector3(0.0f, 0.0f, 1.0f));  // Then rotate
    model =
        Projection::translate(model, Vector3(-0.5f * static_cast<float>(size.x),
                                             -0.5f * static_cast<float>(size.y),
                                             0.0f));  // Move origin back
    model = Projection::scale(
        model, Vector3(static_cast<float>(size.x), static_cast<float>(size.y),
                       1.0f));  // Last scale

    Vertex_EmptyRect ex;
    memcpy(&ex.color, Projection::value_ptr(color), 3 * sizeof(float));
    memcpy(&ex.model_1, &model[0], 4 * sizeof(float));
    memcpy(&ex.model_2, &model[4], 4 * sizeof(float));
    memcpy(&ex.model_3, &model[8], 4 * sizeof(float));
    memcpy(&ex.model_4, &model[12], 4 * sizeof(float));
    ex.trans = transperancy;


    //line loop
    memcpy(&ex.vertex, &l1, 2 * sizeof(float));
    er_indices[er_indicesIndex++] = er_index;
    er_vertices[er_index++] = ex;

    memcpy(&ex.vertex, &l2, 2 * sizeof(float));
    er_indices[er_indicesIndex++] = er_index;
    er_vertices[er_index++] = ex;

    memcpy(&ex.vertex, &l3, 2 * sizeof(float));
    er_indices[er_indicesIndex++] = er_index;
    er_vertices[er_index++] = ex;

    memcpy(&ex.vertex, &l4, 2 * sizeof(float));
    er_indices[er_indicesIndex++] = er_index;
    er_vertices[er_index++] = ex;

    // There was a memory leak here and I don't know how to fix it. But somehow it works.
    if (er_indicesIndex >= indexCount)
    {
        return;
    }

    er_indices[er_indicesIndex++] = 0xFFFF;
}

void EditorMapRenderer::updateData()
{
    std::size_t buffer_size = (sizeof(Vertex_EmptyRect) * vertexCount);
    float *buffer = new float[buffer_size / 4];
    memcpy(buffer, er_vertices.get(), buffer_size);

    emptyRects.va.Bind();
    emptyRects.vb.ChangeData(0, buffer, buffer_size);
    emptyRects.ib.ChangeData(0, er_indices.get(), sizeof(unsigned int) * indexCount);
    emptyRects.va.Unbind();

    delete[] buffer;
}

void EditorMapRenderer::render()
{
    this->batchShader_world.Use();
    emptyRects.va.Bind();
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xFFFF);

    emptyRects.ib.Bind();
    float lineSize;
    glGetFloati_v(GL_LINE_WIDTH, 0, &lineSize);
    glLineWidth(1.0F);
    glDrawElements(GL_LINE_LOOP, indexCount, GL_UNSIGNED_INT, nullptr);
    glLineWidth(lineSize);

    emptyRects.va.Unbind();
    this->batchShader_world.UnUse();
}

void EditorMapRenderer::setProjection(const Matrix4<float> &projection)
{
    batchShader_world.Use();
    batchShader_world.SetMatrix4("projection", projection);
    batchShader_world.UnUse();
}
