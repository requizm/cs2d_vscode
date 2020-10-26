#include "SpriteRenderer.h"
#include "../Models/Texture.h"

#define PI 3.14159265
SpriteRenderer::SpriteRenderer(const Shader shader)
{
	this->shader = shader;
}

SpriteRenderer::SpriteRenderer() = default;

SpriteRenderer::~SpriteRenderer() = default;

void SpriteRenderer::DrawSprite(const Sprite &sprite, Vector2<float> position, Vector2<float> size, GLfloat rotate, bool drawCenter,
								GLfloat shineFactor, bool isSelected, GLfloat time)
{
	// Prepare transformations
	this->shader.Use();
	Matrix4 model = Matrix4(1.0F);
	if (drawCenter)
		model = Projection::translate(model, Vector3(position.x - size.x / 2, position.y - size.y / 2, 0.0F));
	else
		model = Projection::translate(model, Vector3(position.x, position.y, 0.0F));
	// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, glm::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	 // Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0F));					 // Last scale

	glm::mat4 ab = glm::mat4(1.0F);
	if (drawCenter)
		ab = glm::translate(ab, glm::vec3(position.x - size.x / 2, position.y - size.y / 2, 0.0F));
	else
		ab = glm::translate(ab, glm::vec3(position.x, position.y, 0.0F));
	// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//ab = glm::translate(ab, glm::vec3(position.x, position.y, 0.0f));
	ab = glm::translate(ab, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	ab = glm::rotate(ab, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));	 // Then rotate
	ab = glm::translate(ab, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	ab = glm::scale(ab, glm::vec3(size.x, size.y, 1.0F));					 // Last scale

	


	this->shader.SetMatrix4("model", model);
	this->shader.SetInteger("overrideColor", 0);
	this->shader.SetFloat("shineFactor", shineFactor);

	this->shader.SetInteger("selectedTile", isSelected);
	if (isSelected)
	{
		this->shader.SetFloat("time", time);
	}

	glActiveTexture(GL_TEXTURE0);
	sprite.texture.Bind();

	glBindVertexArray(sprite.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->shader.UnUse();
}

void SpriteRenderer::DrawSprite(const Sprite &sprite, Vector2<float> position, Vector2<float> size, Vector3<float> color, bool drawCenter,
								GLfloat rotate, GLfloat shineFactor, bool isSelected)
{
	//rotate = rotate * static_cast<GLfloat>(PI) / static_cast<GLfloat>(180);
	// Prepare transformations
	this->shader.Use();
	Matrix4 model = Matrix4(1.0F);
	if (drawCenter)
		model = Projection::translate(model, Vector3(position.x - size.x / 2, position.y - size.y / 2, 0.0F));
	else
		model = Projection::translate(model, Vector3(position.x, position.y, 0.0F));
	// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	// Move origin of rotation to center of quad
	model = Projection::rotate(model, glm::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	// Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f));								// Last scale

	this->shader.SetMatrix4("model", model);
	this->shader.SetInteger("overrideColor", 1);
	this->shader.SetVector3f("uniformColor", color);
	//this->shader.SetInteger("selectedTile", isSelected); // gerek yok, buraya girmeyecek bile
	//this->shader.SetFloat("shineFactor", shineFactor); // gerek yok, buraya girmeyecek bile
	glActiveTexture(GL_TEXTURE0);
	sprite.texture.Bind();

	glBindVertexArray(sprite.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->shader.UnUse();
}

void SpriteRenderer::DrawSprite(const Sprite &sprite, Matrix4<float> model)
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

void SpriteRenderer::SetProjection(Matrix4<float> projection)
{
	this->shader.Use();
	this->shader.SetMatrix4("projection", projection);
	this->shader.UnUse();
}