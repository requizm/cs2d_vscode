#include "SpriteRenderer.h"
#include "../Models/Texture.h"

#define PI 3.14159265
SpriteRenderer::SpriteRenderer(const Shader shader)
{
	this->shader = shader;
}

SpriteRenderer::SpriteRenderer()
= default;

SpriteRenderer::~SpriteRenderer()
= default;

void SpriteRenderer::DrawSprite(const Sprite &sprite, glm::vec2 position, glm::vec2 size, bool drawCenter, GLfloat rotate)
{
	//rotate = rotate * static_cast<GLfloat>(PI) / static_cast<GLfloat>(180);
	// Prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0);
	if (drawCenter)
		model = glm::translate(model, glm::vec3(position.x - size.x / 2, position.y - size.y / 2, 0.0F));
	else
		model = glm::translate(model, glm::vec3(position.x, position.y, 0.0F));
	// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
  //model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);
	this->shader.SetInteger("overrideColor", 0);
	glActiveTexture(GL_TEXTURE0);
	sprite.texture.Bind();

	glBindVertexArray(sprite.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->shader.UnUse();
}

void SpriteRenderer::DrawSprite(const Sprite &sprite, glm::vec2 position, glm::vec2 size, glm::vec3 color, bool drawCenter,
	GLfloat rotate)
{
	//rotate = rotate * static_cast<GLfloat>(PI) / static_cast<GLfloat>(180);
	// Prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0);
	if (drawCenter)
		model = glm::translate(model, glm::vec3(position.x - size.x / 2, position.y - size.y / 2, 0.0F));
	else
		model = glm::translate(model, glm::vec3(position.x, position.y, 0.0F));
	// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
  //model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);
	this->shader.SetInteger("overrideColor", 1);
	this->shader.SetVector3f("uniformColor", color);
	glActiveTexture(GL_TEXTURE0);
	sprite.texture.Bind();

	glBindVertexArray(sprite.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->shader.UnUse();
}

void SpriteRenderer::DrawSprite(const Sprite &sprite, glm::mat4 model)
{
	this->shader.Use();
	this->shader.SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0);
	sprite.texture.Bind();

	glBindVertexArray(sprite.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->shader.UnUse();
}