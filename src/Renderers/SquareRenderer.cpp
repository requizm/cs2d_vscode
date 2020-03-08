#include "SquareRenderer.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"
#include "../Others/Game_Parameters.h"

SquareRenderer::SquareRenderer()
{
}

SquareRenderer::SquareRenderer(bool init)
{
	this->squareShader_world = ResourceManager::LoadShader("../resources/shaders/squareVertex.txt", "../resources/shaders/squareFragment.txt", nullptr, "squareShader");
	this->squareShader_ui = ResourceManager::LoadShader("../resources/shaders/squareVertex.txt", "../resources/shaders/squareFragment.txt", nullptr, "squareShader");
	this->squareShader_ui.Use();
	this->squareShader_ui.SetMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(Game_Parameters::SCREEN_WIDTH), static_cast<GLfloat>(Game_Parameters::SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f));
	this->squareShader_ui.UnUse();
	outline.initData();
	square = Square(true);
	circle = Square(false);
}

SquareRenderer::~SquareRenderer() = default;

void SquareRenderer::ui_RenderFilledSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, bool outline, glm::vec3 borderColor, float borderSize, GLfloat transperancy, GLfloat rotate)
{
	// Prepare transformations
	this->squareShader_ui.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glBindVertexArray(square.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->squareShader_ui.UnUse();

	if(outline)
		ui_RenderEmptySquareWithLine(position, size, borderColor, borderSize  / 2, transperancy, rotate);
}

void SquareRenderer::ui_RenderFilledSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_ui.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glBindVertexArray(square.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderFilledSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_world.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader_world.SetMatrix4("model", model);
	this->squareShader_world.SetVector3f("colorUniform", color);
	this->squareShader_world.SetFloat("trans", transperancy);
	glBindVertexArray(square.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->squareShader_world.UnUse();
}

void SquareRenderer::world_RenderEmptySquareWithLine(glm::vec2 position, glm::vec2 size, glm::vec3 color, float lineSize, GLfloat transperancy, GLfloat rotate)
{
	//glm::vec2 pos, siz;
	glm::vec2 startPos, endPos;
	//sol kenar
	/*pos = glm::vec2(position.x - lineSize, position.y);
	siz = glm::vec2(lineSize * 2, size.y);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = position;
	endPos = glm::vec2(position.x, position.y + size.y);
	this->world_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//ust kenar
	/*pos = glm::vec2(position.x, position.y - lineSize);
	siz = glm::vec2(size.x, lineSize * 2);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = position;
	endPos = glm::vec2(position.x + size.x, position.y);
	this->world_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//sag kenar
	/*pos = glm::vec2(position.x + size.x - lineSize, position.y);
	siz = glm::vec2(lineSize * 2, size.y);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = glm::vec2(position.x + size.x, position.y);
	endPos = glm::vec2(position.x + size.x, position.y + size.y);
	this->world_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//alt kenar
	/*pos = glm::vec2(position.x, position.y + size.y - lineSize);
	siz = glm::vec2(size.x, lineSize * 2);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = glm::vec2(position.x, position.y + size.y);
	endPos = glm::vec2(position.x + size.x, position.y + size.y);
	this->world_RenderLine(startPos, endPos, color, lineSize, transperancy);
}

void SquareRenderer::ui_RenderEmptySquareWithLine(glm::vec2 position, glm::vec2 size, glm::vec3 color, float lineSize, GLfloat transperancy, GLfloat rotate)
{
	//glm::vec2 pos, siz;
	glm::vec2 startPos, endPos;
	//sol kenar
	/*pos = glm::vec2(position.x - lineSize, position.y);
	siz = glm::vec2(lineSize * 2, size.y);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = position;
	endPos = glm::vec2(position.x, position.y + size.y);
	this->ui_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//ust kenar
	/*pos = glm::vec2(position.x, position.y - lineSize);
	siz = glm::vec2(size.x, lineSize * 2);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = position;
	endPos = glm::vec2(position.x + size.x, position.y);
	this->ui_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//sag kenar
	/*pos = glm::vec2(position.x + size.x - lineSize, position.y);
	siz = glm::vec2(lineSize * 2, size.y);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = glm::vec2(position.x + size.x, position.y);
	endPos = glm::vec2(position.x + size.x, position.y + size.y);
	this->ui_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//alt kenar
	/*pos = glm::vec2(position.x, position.y + size.y - lineSize);
	siz = glm::vec2(size.x, lineSize * 2);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = glm::vec2(position.x, position.y + size.y);
	endPos = glm::vec2(position.x + size.x, position.y + size.y);
	this->ui_RenderLine(startPos, endPos, color, lineSize, transperancy);
}

void SquareRenderer::ui_RenderLine(glm::vec2 startPos, glm::vec2 endPos, glm::vec3 color, float lineSize, GLfloat transperancy)
{
	glm::vec2 size;
	int rotate = 0;
	glm::vec2 dif = endPos - startPos;
	if (abs(dif.y) >= abs(dif.x))
	{
		size = glm::vec2(dif.y, lineSize);
		dif = glm::normalize(dif);
		rotate = glm::degrees(atan2(dif.x, dif.y));
		if (dif.y >= 0)
			rotate += 90;
		else
			rotate -= 90;
	}
	else if (abs(dif.x) > abs(dif.y))
	{
		size = glm::vec2(dif.x, lineSize);
		dif = glm::normalize(dif);
		rotate = glm::degrees(atan2(dif.x, dif.y));
		if (dif.x >= 0)
			rotate -= 90;
		else
			rotate += 90;
	}

	// Prepare transformations
	this->squareShader_ui.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(startPos, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));					   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(static_cast<float>(rotate)), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));					   // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glLineWidth(lineSize);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	glLineWidth(1.0F);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderLine(glm::vec2 startPos, glm::vec2 endPos, glm::vec3 color, float lineSize, GLfloat transperancy)
{
	glm::vec2 size;
	int rotate = 0;
	glm::vec2 dif = endPos - startPos;
	if (abs(dif.y) >= abs(dif.x))
	{
		size = glm::vec2(dif.y, lineSize);
		dif = glm::normalize(dif);
		rotate = glm::degrees(atan2(dif.x, dif.y));
		if (dif.y >= 0)
			rotate += 90;
		else
			rotate -= 90;
	}
	else if (abs(dif.x) > abs(dif.y))
	{
		size = glm::vec2(dif.x, lineSize);
		dif = glm::normalize(dif);
		rotate = glm::degrees(atan2(dif.x, dif.y));
		if (dif.x >= 0)
			rotate -= 90;
		else
			rotate += 90;
	}

	// Prepare transformations
	this->squareShader_world.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(startPos, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));					   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(static_cast<float>(rotate)), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));					   // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale
	this->squareShader_world.SetMatrix4("model", model);
	this->squareShader_world.SetVector3f("colorUniform", color);
	this->squareShader_world.SetFloat("trans", transperancy);
	glLineWidth(lineSize);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	glLineWidth(1.0F);
	this->squareShader_world.UnUse();
}

void SquareRenderer::ui_RenderEmptySquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_ui.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderEmptySquare(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_world.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader_world.SetMatrix4("model", model);
	this->squareShader_world.SetVector3f("colorUniform", color);
	this->squareShader_world.SetFloat("trans", transperancy);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	this->squareShader_world.UnUse();
}

void SquareRenderer::ui_RenderEmptyCircle(glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_ui.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f));								// Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glBindVertexArray(circle.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 360);
	glBindVertexArray(0);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::SetProjection(glm::mat4 proj)
{
	this->squareShader_world.Use();
	this->squareShader_world.SetMatrix4("projection", proj);
	this->squareShader_world.UnUse();
}
