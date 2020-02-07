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
	//Outline title_line = Outline();

	void RenderSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec3 borderColor, float borderSize, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void RenderSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderEmptySquareWithLine(glm::vec2 position, glm::vec2 size, glm::vec3 color, float lineSize, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void RenderLine(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void ui_RenderEmptySquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void world_RenderEmptySquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy = 1.0F, GLfloat rotate = 0.0F);
	void SetProjection(glm::mat4 proj);
};

#endif // SQUARE_RENDERER_H