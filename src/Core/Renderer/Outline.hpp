#ifndef OUTLINE_H
#define OUTLINE_H

#include <GL/glew.h>

class Outline
{
public:
	Outline();
	~Outline();
	GLuint VAO;
	void initData();
};
#endif // OUTLINE_H
