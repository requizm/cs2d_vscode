#ifndef SQUARE_RENDERER_H
#define SQUARE_RENDERER_H

#include <GL/glew.h>

#include "Circle.hpp"
#include "Outline.hpp"
#include "Shader.hpp"
#include "Square.hpp"

class SquareRenderer
{
   public:
    SquareRenderer() = default;
    explicit SquareRenderer(bool init);
    ~SquareRenderer() = default;

    Shader squareShader_ui;
    Shader squareShader_world;
    Outline outline;
    Square square;
    Circle emptyCircle;
    Circle filledCircle;

    float oldLineSize = 1.0F;

    /**
     * @brief
     *
     * @param position
     * @param size
     * @param color
     * @param outline
     * @param borderColor
     * @param borderSize
     * @param transperancy 1.0F
     * @param rotate 0
     */
    void ui_RenderFilledSquare(const Vector2<int> &position, const Vector2<int> &size,
                               const Vector3<float> &color, bool outline,
                               const Vector3<float> &borderColor,
                               float borderSize, GLfloat transperancy = 1.0F,
                               int rotate = 0);

    /**
     * @brief
     *
     * @param position
     * @param size
     * @param color
     * @param transperancy 1.0F
     * @param rotate 0
     */
    void ui_RenderFilledSquare(const Vector2<int> &position, const Vector2<int> &size,
                               const Vector3<float> &color,
                               GLfloat transperancy = 1.0F, int rotate = 0);

    /**
     * @brief
     *
     * @param position
     * @param size
     * @param color
     * @param transperancy 1.0F
     * @param rotate 0
     */
    void world_RenderFilledSquare(const Vector2<int> position, const Vector2<int> size,
                                  const Vector3<float> &color,
                                  GLfloat transperancy = 1.0F, int rotate = 0);

    /**
     * @brief
     *
     * @param startPos
     * @param endPos
     * @param color
     * @param lineSize 1.0F
     * @param transperancy 0.0F
     */
    void ui_RenderLine(const Vector2<int> &startPos, const Vector2<int> &endPos,
                       const Vector3<float> &color, float lineSize = 1.0F,
                       GLfloat transperancy = 1.0F);

    /**
     * @brief
     *
     * @param startPos
     * @param endPos
     * @param color
     * @param lineSize 1.0F
     * @param transperancy 1.0F
     */
    void world_RenderLine(const Vector2<int> &startPos, const Vector2<int> &endPos,
                          const Vector3<float> &color, float lineSize = 1.0F,
                          GLfloat transperancy = 1.0F);

    /**
     * @brief
     *
     * @param position
     * @param size
     * @param color
     * @param transperancy 1.0F
     * @param rotate 0
     */
    void ui_RenderEmptySquare(const Vector2<int> &position, const Vector2<int> &size,
                              const Vector3<float> &color,
                              GLfloat transperancy = 1.0F, int rotate = 0,
                              float lineSize = 1.0F);

    /**
     * @brief
     *
     * @param position
     * @param size
     * @param color
     * @param transperancy 1.0F
     * @param rotate 0
     */
    void world_RenderEmptySquare(const Vector2<int> &position, const Vector2<int> &size,
                                 const Vector3<float> &color,
                                 GLfloat transperancy = 1.0F, int rotate = 0,
                                 float lineSize = 1.0F);

    /**
     * @brief
     *
     * @param position
     * @param size
     * @param color
     * @param transperancy 1.0F
     * @param rotate 0
     */
    void ui_RenderEmptyCircle(const Vector2<int> &position, const Vector2<int> &size,
                              const Vector3<float> &color,
                              GLfloat transperancy = 1.0F, int rotate = 0);

    /**
     * @brief
     *
     * @param position
     * @param size
     * @param color
     * @param transperancy 1.0F
     * @param rotate 0
     */
    void ui_RenderFilledCircle(const Vector2<int> &position, const Vector2<int> &size,
                               const Vector3<float> &color,
                               GLfloat transperancy = 1.0F, int rotate = 0);

    /**
     * @brief
     *
     * @param position
     * @param size
     * @param color
     * @param transperancy 1.0F
     * @param rotate 0
     */
    void world_RenderEmptyCircle(const Vector2<int> &position, const Vector2<int> &size,
                                 const Vector3<float> &color,
                                 GLfloat transperancy = 1.0F, int rotate = 0);

    void SetProjection(const Matrix4<float> proj);
};

#endif  // SQUARE_RENDERER_H