#include "SquareRenderer.hpp"

#include "../../CS2D/Other/GameParameters.hpp"
#include "../Manager/InputManager.hpp"
#include "../Manager/ResourceManager.hpp"
#include "../Math/Projection.hpp"


SquareRenderer::SquareRenderer(bool init)
{
    this->squareShader_world = ResourceManager::LoadShader(
        GameParameters::resDirectory + "shaders/squareVertex.txt",
        GameParameters::resDirectory + "shaders/squareFragment.txt", "",
        "squareShader");
    this->squareShader_ui = ResourceManager::LoadShader(
        GameParameters::resDirectory + "shaders/squareVertex.txt",
        GameParameters::resDirectory + "shaders/squareFragment.txt", "",
        "squareShader");
    this->squareShader_ui.Use();
    Matrix4<float> proj = Projection::ortho(0.0f,
                                            static_cast<float>(GameParameters::SCREEN_WIDTH),
                                            static_cast<float>(GameParameters::SCREEN_HEIGHT),
                                            0.0f, -1.0f, 1.0f);
    this->squareShader_ui.SetMatrix4("projection", proj);
    this->squareShader_ui.UnUse();
    outline.initData();
    square.init();
    emptyCircle = Circle(false);
    filledCircle = Circle(true);
}

void SquareRenderer::ui_RenderFilledSquare(
    const Vector2<int> &position, const Vector2<int> &size, const Vector3<float> &color,
    bool outline, const Vector3<float> &borderColor, float borderSize,
    GLfloat transperancy, int rotate)
{
    // Prepare transformations
    this->squareShader_ui.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0f));  // First translate (transformations are: scale happens
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
    this->squareShader_ui.SetMatrix4("model", model);
    this->squareShader_ui.SetVector3f("colorUniform", color);
    this->squareShader_ui.SetFloat("trans", transperancy);
    glBindVertexArray(square.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    this->squareShader_ui.UnUse();

    if (outline)
        ui_RenderEmptySquare(position, size, borderColor, transperancy, rotate,
                             borderSize / 2);
}

void SquareRenderer::ui_RenderFilledSquare(const Vector2<int> &position,
                                           const Vector2<int> &size,
                                           const Vector3<float> &color,
                                           GLfloat transperancy, int rotate)
{
    this->squareShader_ui.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0f));  // First translate (transformations are: scale happens
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
    this->squareShader_ui.SetMatrix4("model", model);
    this->squareShader_ui.SetVector3f("colorUniform", color);
    this->squareShader_ui.SetFloat("trans", transperancy);
    glBindVertexArray(square.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderFilledSquare(const Vector2<int> &position,
                                              const Vector2<int> &size,
                                              const Vector3<float> &color,
                                              GLfloat transperancy, int rotate)
{
    this->squareShader_world.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0f));  // First translate (transformations are: scale happens
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
    this->squareShader_world.SetMatrix4("model", model);
    this->squareShader_world.SetVector3f("colorUniform", color);
    this->squareShader_world.SetFloat("trans", transperancy);
    glBindVertexArray(square.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    this->squareShader_world.UnUse();
}

void SquareRenderer::ui_RenderLine(const Vector2<int> &startPos, const Vector2<int> &endPos,
                                   const Vector3<float> &color, float lineSize,
                                   GLfloat transperancy)
{
    Vector2<int> endPosN = endPos;
    Vector2<int> startPosN = startPos;
    Vector2<int> size;
    int rotate = 0;
    Vector2<int> difInt = endPosN - startPosN;
    Vector2<float> dif = Vector2<float>(static_cast<float>(difInt.x),
                                        static_cast<float>(difInt.y));
    if (abs(dif.y) >= abs(dif.x))
    {
        size = Vector2<int>(dif.y, lineSize);
        dif = dif.Normalize();
        rotate = static_cast<int>(
            Projection::degrees(static_cast<float>(atan2(dif.x, dif.y))));
        if (dif.y >= 0)
            rotate += 90;
        else
            rotate -= 90;
    }
    else if (abs(dif.x) > abs(dif.y))
    {
        size = Vector2<int>(dif.x, lineSize);
        dif = dif.Normalize();
        rotate = static_cast<int>(Projection::degrees(atan2(dif.x, dif.y)));
        if (dif.x >= 0)
            rotate -= 90;
        else
            rotate += 90;
    }

    // Prepare transformations
    this->squareShader_ui.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(startPos.x), static_cast<float>(startPos.y),
                0.0f));  // First translate (transformations are: scale happens
                         // first, then rotation and then finall translation
                         // happens; reversed order)
    // model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f *
    // size.y,
    // 0.0f));					   // Move origin of rotation to
    // center of quad
    model = Projection::rotate(model,
                               Projection::radians(static_cast<float>(rotate)),
                               Vector3(0.0f, 0.0f, 1.0f));  // Then rotate
    // model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f *
    // size.y, 0.0f));					   // Move origin back
    model = Projection::scale(
        model, Vector3(static_cast<float>(size.x), static_cast<float>(size.y),
                       1.0f));  // Last scale
    this->squareShader_ui.SetMatrix4("model", model);
    this->squareShader_ui.SetVector3f("colorUniform", color);
    this->squareShader_ui.SetFloat("trans", transperancy);
    if (oldLineSize != lineSize)
    {
        glLineWidth(lineSize);
        oldLineSize = lineSize;
    }
    glBindVertexArray(outline.VAO);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
    this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderLine(const Vector2<int> &startPos,
                                      const Vector2<int> &endPos,
                                      const Vector3<float> &color,
                                      float lineSize, GLfloat transperancy)
{
    Vector2<int> endPosN = endPos;
    Vector2<int> startPosN = startPos;
    Vector2<int> size;
    int rotate = 0;
    Vector2<int> difInt = endPosN - startPosN;
    Vector2<float> dif = Vector2<float>(static_cast<float>(difInt.x),
                                        static_cast<float>(difInt.y));
    if (abs(dif.y) >= abs(dif.x))
    {
        size = Vector2<int>(dif.y, lineSize);
        dif = dif.Normalize();
        rotate = static_cast<int>(
            Projection::degrees(static_cast<float>(atan2(dif.x, dif.y))));
        if (dif.y >= 0)
            rotate += 90;
        else
            rotate -= 90;
    }
    else if (abs(dif.x) > abs(dif.y))
    {
        size = Vector2<int>(dif.x, lineSize);
        dif = dif.Normalize();
        rotate = static_cast<int>(Projection::degrees(atan2(dif.x, dif.y)));
        if (dif.x >= 0)
            rotate -= 90;
        else
            rotate += 90;
    }

    // Prepare transformations
    this->squareShader_world.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(startPos.x), static_cast<float>(startPos.y),
                0.0f));  // First translate (transformations are: scale happens
                         // first, then rotation and then finall translation
                         // happens; reversed order)
    // model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f *
    // size.y,
    // 0.0f));					   // Move origin of rotation to
    // center of quad
    model = Projection::rotate(model,
                               Projection::radians(static_cast<float>(rotate)),
                               Vector3(0.0f, 0.0f, 1.0f));  // Then rotate
    // model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f *
    // size.y, 0.0f));					   // Move origin back
    model = Projection::scale(
        model, Vector3(static_cast<float>(size.x), static_cast<float>(size.y),
                       1.0f));  // Last scale
    this->squareShader_world.SetMatrix4("model", model);
    this->squareShader_world.SetVector3f("colorUniform", color);
    this->squareShader_world.SetFloat("trans", transperancy);
    if (oldLineSize != lineSize)
    {
        glLineWidth(lineSize);
        oldLineSize = lineSize;
    }
    glBindVertexArray(outline.VAO);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
    this->squareShader_world.UnUse();
}

void SquareRenderer::ui_RenderEmptySquare(const Vector2<int> &position,
                                          const Vector2<int> &size,
                                          const Vector3<float> &color,
                                          GLfloat transperancy, int rotate,
                                          float lineSize)
{
    this->squareShader_ui.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0f));  // First translate (transformations are: scale happens
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
    this->squareShader_ui.SetMatrix4("model", model);
    this->squareShader_ui.SetVector3f("colorUniform", color);
    this->squareShader_ui.SetFloat("trans", transperancy);
    if (oldLineSize != lineSize)
    {
        glLineWidth(lineSize);
        oldLineSize = lineSize;
    }
    glBindVertexArray(outline.VAO);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
    this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderEmptySquare(const Vector2<int> &position,
                                             const Vector2<int> &size,
                                             const Vector3<float> &color,
                                             GLfloat transperancy, int rotate,
                                             float lineSize)
{
    this->squareShader_world.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0f));  // First translate (transformations are: scale happens
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
    this->squareShader_world.SetMatrix4("model", model);
    this->squareShader_world.SetVector3f("colorUniform", color);
    this->squareShader_world.SetFloat("trans", transperancy);
    if (oldLineSize != lineSize)
    {
        glLineWidth(lineSize);
        oldLineSize = lineSize;
    }
    glBindVertexArray(outline.VAO);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
    this->squareShader_world.UnUse();
}

void SquareRenderer::ui_RenderEmptyCircle(const Vector2<int> &position,
                                          const Vector2<int> &size,
                                          const Vector3<float> &color,
                                          GLfloat transperancy, int rotate)
{
    this->squareShader_ui.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0f));  // First translate (transformations are: scale happens
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
    this->squareShader_ui.SetMatrix4("model", model);
    this->squareShader_ui.SetVector3f("colorUniform", color);
    this->squareShader_ui.SetFloat("trans", transperancy);

    glBindVertexArray(emptyCircle.VAO);
    glDrawArrays(GL_LINE_STRIP, 0, 31);
    glBindVertexArray(0);
    this->squareShader_ui.UnUse();
}

void SquareRenderer::ui_RenderFilledCircle(const Vector2<int> &position,
                                           const Vector2<int> &size,
                                           const Vector3<float> &color,
                                           GLfloat transperancy, int rotate)
{
    this->squareShader_ui.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0f));  // First translate (transformations are: scale happens
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
    this->squareShader_ui.SetMatrix4("model", model);
    this->squareShader_ui.SetVector3f("colorUniform", color);
    this->squareShader_ui.SetFloat("trans", transperancy);

    glBindVertexArray(filledCircle.VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 32);
    glBindVertexArray(0);
    this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderEmptyCircle(const Vector2<int> &position,
                                             const Vector2<int> &size,
                                             const Vector3<float> &color,
                                             GLfloat transperancy, int rotate)
{
    this->squareShader_world.Use();
    Matrix4 model = Matrix4(1.0F);
    model = Projection::translate(
        model,
        Vector3(static_cast<float>(position.x), static_cast<float>(position.y),
                0.0f));  // First translate (transformations are: scale happens
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
    this->squareShader_world.SetMatrix4("model", model);
    this->squareShader_world.SetVector3f("colorUniform", color);
    this->squareShader_world.SetFloat("trans", transperancy);

    glBindVertexArray(emptyCircle.VAO);
    glDrawArrays(GL_LINE_STRIP, 0, 31);
    glBindVertexArray(0);
    this->squareShader_world.UnUse();
}

void SquareRenderer::SetProjection(const Matrix4<float> &proj)
{
    this->squareShader_world.Use();
    this->squareShader_world.SetMatrix4("projection", proj);
    this->squareShader_world.UnUse();
}
