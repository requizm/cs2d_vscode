#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Square
{
public:
	Square();
	Square(bool init);
	~Square();

	GLuint VAO;

private:
	void initData();
	void initCircle();
};

#endif // SQUARE_H