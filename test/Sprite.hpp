#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>

#include "Texture.hpp"
#include "../src/Core/Math/Vector2.hpp"
#include "../src/Core/Manager/Logger.hpp"

class Sprite
{
public:
	explicit Sprite(Texture2D texture, GLuint x = 0, GLuint y = 0, GLuint width = 0, GLuint height = 0);
	Sprite();
	~Sprite();

	GLuint VAO;
	Texture2D texture;
	Vector2<int> size;

private:
	void initData(GLuint x = 0, GLuint y = 0, GLuint width = 0, GLuint height = 0);
};

#endif // !SPRITE_H
