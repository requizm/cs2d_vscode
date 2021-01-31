#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/glew.h>



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