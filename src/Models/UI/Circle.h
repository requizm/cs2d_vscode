#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
 
class Circle
{
public:
    Circle();
    Circle(bool empty);
    ~Circle();

    void initEmptyCircle();
    void initFilledCircle();

    GLuint VAO;
};




#endif