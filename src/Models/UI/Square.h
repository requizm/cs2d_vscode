#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Square
{
public:
	Square();
	~Square();

	GLuint VAO;

private:
	void initData();
};

#endif // SQUARE_H