#include "BatchRenderer.hpp"

#include "../../../src/CS2D/Other/GameParameters.hpp"
#include "../../../src/Core/Manager/ResourceManager.hpp"
#include "../../../src/Core/Math/Projection.hpp"


BatchRenderer::BatchRenderer(bool init)
{
    this->batchShader_ui = ResourceManager::LoadShader(
        GameParameters::resDirectory + "shaders/batchVertex.txt",
        GameParameters::resDirectory + "shaders/batchFragment.txt", "",
        "batch");
    this->batchShader_ui.Use();
    Matrix4<float> proj = Projection::ortho(0.0f,
                                            static_cast<float>(GameParameters::SCREEN_WIDTH),
                                            static_cast<float>(GameParameters::SCREEN_HEIGHT),
                                            0.0f, -1.0f, 1.0f);
    this->batchShader_ui.SetMatrix4("projection", proj);
    outline.initData();
}
void BatchRenderer::AddRectangle(const Vector3<int> &position,
                                 const Vector2<int> &size,
                                 const Vector3<float> &color,
                                 float transperancy, int rotate)
{
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                static_cast<float>(position.z)));  // First translate (transformations are: scale happens
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

    VertexOne ex;
    memcpy(&ex.color, Projection::value_ptr(color), 3 * sizeof(float));
    memcpy(&ex.model_1, &model[0], 4 * sizeof(float));
    memcpy(&ex.model_2, &model[4], 4 * sizeof(float));
    memcpy(&ex.model_3, &model[8], 4 * sizeof(float));
    memcpy(&ex.model_4, &model[12], 4 * sizeof(float));
    ex.trans = transperancy;

    //triangle
    /*memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(0.0F, 1.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;

    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(1.0F, 0.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;

    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(0.0F, 0.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;

    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(0.0F, 1.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;

    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(1.0F, 1.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;

    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(1.0F, 0.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;*/


    //line loop
    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(0.0F, 1.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;

    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(1.0F, 1.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;

    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(1.0F, 0.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;

    memcpy(&ex.vertex, Projection::value_ptr(Vector2<float>(0.0F, 0.0F)), 2 * sizeof(float));
    gaycums[index++] = ex;
}

void BatchRenderer::Draw()
{
    this->batchShader_ui.Use();
    glBindVertexArray(outline.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, outline.VBO);


    size_t size = sizeof(gaycums);
    glBufferSubData(
        GL_ARRAY_BUFFER, 0, size,
        gaycums);  // Be sure to use glBufferSubData and not glBufferData

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_LINE_LOOP, 0, 16);


    glBindVertexArray(0);

    this->batchShader_ui.UnUse();
}

// OpenGL batching
