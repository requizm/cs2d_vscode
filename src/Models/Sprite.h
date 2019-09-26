#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"

class Sprite
{
public:
	Sprite(Texture2D texture, GLuint x = 0, GLuint y = 0, GLuint width = 0, GLuint height = 0);
	Sprite();
	~Sprite();

	GLuint VAO;
	Texture2D texture;
	glm::vec2 size;

private:
	void initData(GLuint x = 0, GLuint y = 0, GLuint width = 0, GLuint height = 0);
};

#endif // !SPRITE_H
