#ifndef OUTLINE_H
#define OUTLINE_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Outline
{
public:
	Outline();
	~Outline();
	GLuint VAO = 0;
	void initData();
	
};
#endif // OUTLINE_H
