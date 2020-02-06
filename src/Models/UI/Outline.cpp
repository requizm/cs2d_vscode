#include "Outline.h"

Outline::Outline()
{
}

Outline::~Outline() = default;

void Outline::initData()
{
	// Configure VAO/VBO
	GLuint VBO;
	/*GLfloat vertices[16];

	vertices[0] = 0.0f; vertices[1] = 0.0f;
	vertices[2] = 1.0f; vertices[3] = 0.0f;

	vertices[4] = 1.0f; vertices[5] = 0.0f;
	vertices[6] = 1.0f; vertices[7] = 1.0f;

	vertices[8] = 0.0f; vertices[9] = 0.0f;
	vertices[10] = 0.0f; vertices[11] = 1.0f;

	vertices[12] = 1.0f; vertices[13] = 1.0f;
	vertices[14] = 0.0f; vertices[15] = 1.0f;*/

	GLfloat vertices[24];

	vertices[0] = 0.0f;
	vertices[1] = 1.0f;
	
	vertices[2] = 1.0f;
	vertices[3] = 1.0f;
	
	vertices[4] = 1.0f;
	vertices[5] = 0.0f;

	vertices[6] = 0.0f;
	vertices[7] = 0.0f;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), static_cast<GLvoid *>(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}