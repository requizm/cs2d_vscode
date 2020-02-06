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

	Shader squareShader;
	Outline outline;
	//Outline title_line = Outline();

	void RenderSquare(Square square, glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec3 borderColor, float borderSize, GLfloat rotate = 0.0F);
	void RenderSquare(Square square, glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat rotate = 0.0F);
	void RenderLine(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat rotate = 0.0F);
};

#endif // SQUARE_RENDERER_H