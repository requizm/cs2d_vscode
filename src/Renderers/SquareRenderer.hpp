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
	//Outline title_line = Outline();

	void ui_RenderFilledSquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, bool outline, Vector3<float> borderColor, float borderSize, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void ui_RenderFilledSquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderFilledSquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderEmptySquareWithLine(Vector2<float> position, Vector2<float> size, Vector3<float> color, float lineSize, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void ui_RenderEmptySquareWithLine(Vector2<float> position, Vector2<float> size, Vector3<float> color, float lineSize, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);

	void ui_RenderLine(Vector2<float> startPos, Vector2<float> endPos, Vector3<float> color, float lineSize = 1.0F, GLfloat transperancy = 1.0F);
	void world_RenderLine(Vector2<float> startPos, Vector2<float> endPos, Vector3<float> color, float lineSize = 1.0F, GLfloat transperancy = 1.0F);
	void ui_RenderEmptySquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderEmptySquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);

	void ui_RenderEmptyCircle(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void ui_RenderFilledCircle(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void SetProjection(Matrix4<float> proj);
};

#endif // SQUARE_RENDERER_H