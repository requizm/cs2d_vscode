#ifndef SQUARE_RENDERER_H
#define SQUARE_RENDERER_H
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Models/UI/Square.hpp"
#include "../Models/UI/Circle.hpp"
#include "../Models/Shader.hpp"
#include "../Models/UI/Outline.hpp"

class SquareRenderer
{
public:
	SquareRenderer();
	SquareRenderer(bool init);
	~SquareRenderer();

	Shader squareShader_ui;
	Shader squareShader_world;
	Outline outline;
	Square square;
	Circle emptyCircle;
	Circle filledCircle;

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
	void ui_RenderFilledSquare(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, bool outline, const Vector3<float> &borderColor, float borderSize, GLfloat transperancy = 1.0F, int rotate = 0);

	/**
	 * @brief 
	 * 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param transperancy 1.0F
	 * @param rotate 0
	 */
	void ui_RenderFilledSquare(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, GLfloat transperancy = 1.0F, int rotate = 0);

	/**
	 * @brief 
	 * 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param transperancy 1.0F
	 * @param rotate 0
	 */
	void world_RenderFilledSquare(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, GLfloat transperancy = 1.0F, int rotate = 0);

	/**
	 * @brief 
	 * 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param lineSize 
	 * @param transperancy 1.0F
	 * @param rotate 0
	 */
	void world_RenderEmptySquareWithLine(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, float lineSize, GLfloat transperancy = 1.0F, int rotate = 0);

	/**
	 * @brief 
	 * 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param lineSize 
	 * @param transperancy 1.0F
	 * @param rotate 0
	 */
	void ui_RenderEmptySquareWithLine(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, float lineSize, GLfloat transperancy = 1.0F, int rotate = 0);

	/**
	 * @brief 
	 * 
	 * @param startPos 
	 * @param endPos 
	 * @param color 
	 * @param lineSize 1.0F
	 * @param transperancy 0.0F
	 */
	void ui_RenderLine(Vector2<int> startPos, Vector2<int> endPos, const Vector3<float> &color, float lineSize = 1.0F, GLfloat transperancy = 1.0F);

	/**
	 * @brief 
	 * 
	 * @param startPos 
	 * @param endPos 
	 * @param color 
	 * @param lineSize 1.0F
	 * @param transperancy 1.0F
	 */
	void world_RenderLine(Vector2<int> startPos, Vector2<int> endPos, const Vector3<float> &color, float lineSize = 1.0F, GLfloat transperancy = 1.0F);

	/**
	 * @brief 
	 * 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param transperancy 1.0F
	 * @param rotate 0
	 */
	void ui_RenderEmptySquare(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, GLfloat transperancy = 1.0F, int rotate = 0);

	/**
	 * @brief 
	 * 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param transperancy 1.0F
	 * @param rotate 0
	 */
	void world_RenderEmptySquare(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, GLfloat transperancy = 1.0F, int rotate = 0);

	/**
	 * @brief 
	 * 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param transperancy 1.0F
	 * @param rotate 0
	 */
	void ui_RenderEmptyCircle(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, GLfloat transperancy = 1.0F, int rotate = 0);

	/**
	 * @brief 
	 * 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param transperancy 1.0F
	 * @param rotate 0
	 */
	void ui_RenderFilledCircle(Vector2<int> position, Vector2<int> size, const Vector3<float> &color, GLfloat transperancy = 1.0F, int rotate = 0);

	void SetProjection(Matrix4<float> proj);
};

#endif // SQUARE_RENDERER_H