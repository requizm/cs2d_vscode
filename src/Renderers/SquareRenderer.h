#ifndef SQUARE_RENDERER_H
#define SQUARE_RENDERER_H
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Models/UI/Square.h"
#include "../Models/Shader.h"
#include "../Models/UI/Outline.h"

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
	Square circle;
	//Outline title_line = Outline();

	void ui_RenderFilledSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool outline, glm::vec3 borderColor, float borderSize, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void ui_RenderFilledSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderFilledSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderEmptySquareWithLine(glm::vec2 position, glm::vec2 size, glm::vec3 color, float lineSize, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void ui_RenderEmptySquareWithLine(glm::vec2 position, glm::vec2 size, glm::vec3 color, float lineSize, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);

	void ui_RenderLine(glm::vec2 startPos, glm::vec2 endPos, glm::vec3 color, float lineSize = 1.0F, GLfloat transperancy = 1.0F);
	void world_RenderLine(glm::vec2 startPos, glm::vec2 endPos, glm::vec3 color, float lineSize = 1.0F, GLfloat transperancy = 1.0F);
	void ui_RenderEmptySquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderEmptySquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);

	void ui_RenderEmptyCircle(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void SetProjection(glm::mat4 proj);
};

#endif // SQUARE_RENDERER_H