#include "SquareRenderer.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"
#include "../Others/Game_Parameters.h"

SquareRenderer::SquareRenderer()
{
}

SquareRenderer::SquareRenderer(bool init)
{
	this->squareShader = ResourceManager::LoadShader("../resources/shaders/squareVertex.txt", "../resources/shaders/squareFragment.txt", nullptr, "squareShader");
	this->squareShader.Use();
	this->squareShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(Game_Parameters::SCREEN_WIDTH), static_cast<GLfloat>(Game_Parameters::SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f));
	this->squareShader.UnUse();
	outline.initData();
}

SquareRenderer::~SquareRenderer() = default;

void SquareRenderer::RenderSquare(Square square, glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec3 borderColor, float borderSize, GLfloat rotate)
{
	// Prepare transformations
	this->squareShader.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader.SetMatrix4("model", model);
	this->squareShader.SetVector3f("colorUniform", color);
	glBindVertexArray(square.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	
	size.x = size.x + borderSize * 2;
	size.y = size.y + borderSize * 2;
	position.x = position.x - borderSize;
	position.y = position.y - borderSize;
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));							// Last scale	
	this->squareShader.SetMatrix4("model", model);
	this->squareShader.SetVector3f("colorUniform", borderColor);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	this->squareShader.UnUse();
}

void SquareRenderer::RenderSquare(Square square, glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat rotate)
{
	// Prepare transformations
	this->squareShader.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader.SetMatrix4("model", model);
	this->squareShader.SetVector3f("colorUniform", color);
	glBindVertexArray(square.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->squareShader.UnUse();
}

void SquareRenderer::RenderLine(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat rotate)
{
	// Prepare transformations
	this->squareShader.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader.SetMatrix4("model", model);
	this->squareShader.SetVector3f("colorUniform", color);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINES, 0, 4);
	glBindVertexArray(0);
	this->squareShader.UnUse();
}